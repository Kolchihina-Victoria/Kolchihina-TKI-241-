#include <iostream>
#include <vector>

using namespace std;

// Прототипы функций
void inputVector(vector<int>& vec);
void processVector(vector<int>& vec);
void displayVector(const vector<int>& vec);
void printSeparator();

/**
 * @brief Главная функция программы
 * @return  (0 - успешное выполнение)
 * @details Работа программы:
 *          1. Запрашивает у пользователя ввод элементов вектора
 *          2. Выводит исходный вектор
 *          3. Выполняет вставку -1 после каждого элемента
 *          4. Выводит результат
 */
int main() {
    vector<int> numbers;  // Используем стандартный класс vector
    
    printSeparator();
    cout << "    Работа с вектором целых чисел" << endl;
    printSeparator();
    
    // Ввод вектора с клавиатуры
    inputVector(numbers);
    
    // Вывод исходного вектора
    cout << "\nИсходный вектор: ";
    displayVector(numbers);
    
    // Операция вставки
    cout << "\nВставка -1 после каждого элемента..." << endl;
    processVector(numbers);
    
    // Вывод результата
    cout << "Результат: ";
    displayVector(numbers);
    
    // Дополнительная информация
    cout << "\nИнформация об операции:" << endl;
    cout << "Исходное количество элементов: " << numbers.size() / 2 << endl;
    cout << "Результирующий размер: " << numbers.size() << endl;
    cout << "Количество вставок: " << numbers.size() / 2 << endl;
    
    printSeparator();
    cout << "Программа успешно завершена" << endl;
    
    return 0;
}

/**
 * @brief Вводит элементы вектора с клавиатуры
 * @param vec Ссылка на вектор для заполнения
 */
void inputVector(vector<int>& vec) {
    int n, value;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    cout << "Введите " << n << " целых чисел через пробел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        vec.push_back(value);
    }
}

/**
 * @brief Вставляет число -1 после каждого элемента вектора
 * @param vec Ссылка на вектор для обработки
 * @details Использует итератор для перебора элементов вектора.
 *          После каждой вставки итератор корректируется для продолжения обхода.
 */
void processVector(vector<int>& vec) {
    // Получаем итератор на первый элемент вектора
    auto i = vec.begin();
    
    // Цикл продолжается, пока не дойдем до конца вектора
    while (i != vec.end()) {
        // Вставляем -1 после текущего элемента
        // insert возвращает итератор на вставленный элемент
        i = vec.insert(i + 1, -1);
        
        // Переходим к следующему исходному элементу
        // (пропускаем вставленный -1)
        ++i;
    }
}

/**
 * @brief Выводит содержимое вектора на экран
 * @param vec Константная ссылка на вектор
 */
void displayVector(const vector<int>& vec) {
    for (int value : vec) {
        cout << value << " ";
    }
    cout << endl;
}

/**
 * @brief Выводит разделительную линию
 */
void printSeparator() {
    cout << "========================================" << endl;
}
