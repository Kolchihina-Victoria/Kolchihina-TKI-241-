#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Прототипы функций

/**
 * @brief Вводит элементы вектора из потока ввода
 * @param vec Ссылка на вектор для заполнения
 */
void inputVector(vector<int>& vec);

/**
 * @brief Выводит содержимое вектора
 * @param vec Константная ссылка на вектор
 */
void printVector(const vector<int>& vec);

/**
 * @brief Выводит количество повторений элементов вектора
 * @param V Исходный вектор
 */
void printElementCounts(const vector<int>& V);

/**
 * @brief Выводит разделительную линию
 * @param symbol Символ разделителя
 * @param length Длина линии
 */
void printSeparator(char symbol = '-', int length = 30);

/**
 * @brief Главная функция программы
 * @return 0 при успешном выполнении
 * 
 * Запрашивает у пользователя ввод вектора и выводит количество повторений элементов
 */
int main() {
    vector<int> V;

    printSeparator('=', 40);
    cout << "   Подсчет повторений элементов вектора" << endl;
    printSeparator('=', 40);

    // Ввод вектора с клавиатуры
    inputVector(V);

    // Вывод исходного вектора с помощью отдельной функции
    cout << "\nИсходный вектор: ";
    printVector(V);

    // Вывод результата
    cout << "\nРезультат (элемент : количество повторений):\n";
    printElementCounts(V);

    printSeparator();
    cout << "Программа успешно завершена" << endl;

    return 0;
}

/**
 * @brief Вводит элементы вектора с клавиатуры
 * @param vec Ссылка на вектор для заполнения
 * 
 * Чтение выполняется из потока ввода от начала до конца (до EOF).
 */
void inputVector(vector<int>& vec) {
    int value = 0;

    // вывод
    cout << "Введите целые числа (Ctrl+D / Ctrl+Z для завершения): ";

    // читаем из потока от начала до конца
    while (cin >> value) {
        vec.push_back(value);
    }
}

/**
 * @brief Выводит содержимое вектора на экран
 * @param vec Константная ссылка на вектор
 */
void printVector(const vector<int>& vec) {
    if (vec.empty()) {
        cout << "пуст";
        return;
    }

    for (int value : vec) {
        cout << value << " ";
    }
}

/**
 * @brief Выводит все различные элементы вектора с количеством их повторений
 * @param V Исходный вектор целых чисел
 * 
 * Функция создает множество S (хранит только уникальные элементы) на основе вектора V.
 * Затем для каждого уникального элемента подсчитывает количество его вхождений.
 * Результат выводится в порядке возрастания значений элементов.

 */
void printElementCounts(const vector<int>& V) {
    if (V.empty()) {
        cout << "Вектор пуст" << endl;
        return;
    }

    // Создаем множество уникальных элементов
    set<int> S(V.begin(), V.end());

    // Для каждого уникального элемента считаем количество повторений
    for (int element : S) {
        // Подсчитываем количество вхождений элемента в вектор
        int count = 0;

        for (int value : V) {
            if (value == element) {
                count++;
            }
        }

        cout << element << " : " << count << endl;
    }
}

/**
 * @brief Выводит разделительную линию
 * @param symbol Символ для разделителя
 * @param length Длина разделителя
 */
void printSeparator(char symbol, int length) {
    for (size_t i = 0; i < static_cast<size_t>(length); i++) {
        cout << symbol;
    }

    cout << endl;
}
