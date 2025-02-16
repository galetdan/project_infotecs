#include "lib.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

void sort_and_replace(std::string& input) {
    std::vector<int> numbers;
    std::string num_str;

    // Разбор строки на числа
    for (char ch : input) {
        if (std::isdigit(ch)) {
            num_str += ch;
        } else if (!num_str.empty()) {
            numbers.push_back(std::stoi(num_str));
            num_str.clear();
        }
    }
    if (!num_str.empty()) {
        numbers.push_back(std::stoi(num_str));
    }

    // Сортировка по убыванию
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());

    // Замена четных чисел на "KB"
    std::ostringstream result;
    for (int num : numbers) {
        if (num % 2 == 0) {
            result << "KB ";
        } else {
            result << num << " ";
        }
    }

    input = result.str();
}

int calculate_sum(const std::string& input) {
    int sum = 0;
    std::string num_str;

    for (char ch : input) {
        if (std::isdigit(ch)) {
            num_str += ch;
        } else if (!num_str.empty()) {
            sum += std::stoi(num_str);
            num_str.clear();
        }
    }
    if (!num_str.empty()) {
        sum += std::stoi(num_str);
    }

    return sum;
}

bool analyze_string_length(int number) {
    // Преобразуем число в строку для проверки длины
    std::string input = std::to_string(number);

    // Проверка длины строки
    if (input.length() <= 2) {
        return false;
    }

    // Проверка, делится ли число на 32
    return (number % 32 == 0);
}