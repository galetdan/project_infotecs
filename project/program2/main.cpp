#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "lib.h"

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Ошибка создания сокета");
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Ошибка привязки сокета");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Ошибка прослушивания сокета");
        close(server_fd);
        return 1;
    }

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("Ошибка принятия соединения");
            continue;
        }

        while (true) {
            int sum;
            ssize_t bytes_received = recv(client_fd, &sum, sizeof(sum), 0);
            if (bytes_received <= 0) {
                perror("Ошибка получения данных");
                close(client_fd);
                break;
            }

            
           if (analyze_string_length(sum)) {
                std::cout << "Полученные данные: " << sum << std::endl;
            } else {
                std::cerr << "Ошибка: Число не удовлетворяет условиям." << std::endl;
            }
        }
    }

    close(server_fd);
    return 0;
}