#include <iostream>   // Для ввода-вывода
#include <vector>     // Для использования контейнера vector
#include <string>     // Для работы со строками

// Пример функции
int sum(int a, int b) {
    return a + b;
}

int main() {
    // Вывод в консоль
    std::cout << "Привет, мир! Это программа на C++.\n\n";
    
    // Переменные и ввод
    int number;
    std::cout << "Введите целое число: ";
    std::cin >> number;
    
    // Условный оператор
    if (number > 0) {
        std::cout << "Вы ввели положительное число.\n";
    } else if (number < 0) {
        std::cout << "Вы ввели отрицательное число.\n";
    } else {
        std::cout << "Вы ввели ноль.\n";
    }
    
    // Цикл for
    std::cout << "\nСчёт от 1 до 5: ";
    for (int i = 1; i <= 5; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    
    // Работа с вектором (динамический массив)
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "\nЭлементы вектора: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    // Вызов функции
    int result = sum(10, 20);
    std::cout << "\nСумма 10 и 20: " << result << "\n";
    
    // Строки
    std::string name;
    std::cout << "\nВведите ваше имя: ";
    std::cin.ignore(); // Игнорируем предыдущий символ новой строки
    std::getline(std::cin, name);
    std::cout << "Привет, " << name << "!\n";
    
    return 0;
}