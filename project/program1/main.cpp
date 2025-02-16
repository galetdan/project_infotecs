#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <algorithm>
#include "lib.h"

std::mutex mtx;
std::condition_variable cv;
std::string shared_buffer;
bool data_available = false;

void thread1() {
    while (true) {
        std::string input;
        std::cout << "Введите строку (только цифры, максимум 64 символа): ";
        std::getline(std::cin, input);

        // Проверка ввода
        if (input.length() > 64 || !std::all_of(input.begin(), input.end(), [](char ch) {
                return std::isdigit(ch) || std::isspace(ch);
            })) {
            std::cerr << "Ошибка: Введите только цифры и пробелы, не более 64 символов.\n";
            continue;
        }

        // Обработка функцией 1
        sort_and_replace(input);

        // Помещение данных в общий буфер
        {
            std::lock_guard<std::mutex> lock(mtx);
            shared_buffer = input;
            data_available = true;
        }
        cv.notify_one();
    }
}

void thread2(int socket_fd) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return data_available; });

        std::string data = shared_buffer;
        shared_buffer.clear();
        data_available = false;
        lock.unlock();

        // Вывод данных на экран
        std::cout << "Обработанная строка: " << data << std::endl;

        // Передача суммы в программу №2
        int sum = calculate_sum(data);
        if (send(socket_fd, &sum, sizeof(sum), 0) < 0) {
            perror("Ошибка отправки данных");
            close(socket_fd);

            // Попытка переподключения
            socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in server_addr{};
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(8080);
            server_addr.sin_addr.s_addr = INADDR_ANY;

            if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                perror("Ошибка подключения к серверу");
                continue;
            }
        }
    }
}

int main() {
    // Создание сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Ошибка создания сокета");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка подключения к серверу");
        close(sock);
        return 1;
    }

    // Запуск потоков
    std::thread t1(thread1);
    std::thread t2(thread2, sock);

    t1.join();
    t2.join();

    close(sock);
    return 0;
}