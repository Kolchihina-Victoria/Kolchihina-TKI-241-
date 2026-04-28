#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Прототипы функций
void inputVector(vector<int>& vec);
void printVector(const vector<int>& vec);
void printElementCounts(const vector<int>& V);
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

    // Ввод вектора с клавиатуры (исправление ошибки 1)
    inputVector(V);

    // Вывод исходного вектора с помощью отдельной функции (исправление ошибки 2)
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
 */
//исправленная часть кода (нет привязки к числу n и читается из потока ввода от начала до конца)
void inputVector(vector<int>& vec) {
    int value;
//вывод
    cout << "Введите целые числа (Ctrl+D / Ctrl+Z для завершения): ";

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
 * 
 * Исправление ошибки 4: лишний класс, используется простая функция
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
    for (int i = 0; i < length; i++) {
        cout << symbol;
    }
    cout << endl;
}
