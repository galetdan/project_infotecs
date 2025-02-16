#ifndef LIB_H
#define LIB_H

#include <string>

// Функция 1: Сортирует элементы строки по убыванию и заменяет четные числа на "KB"
void sort_and_replace(std::string& input);

// Функция 2: Возвращает сумму всех числовых значений в строке
int calculate_sum(const std::string& input);

// Функция 3: Проверяет длину строки и кратность суммы (кратна ли сумма 32 и больше ли 2 символов строкаы)
bool analyze_string_length(int number);

#endif // LIB_H