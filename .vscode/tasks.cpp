#include <iostream>
#include <iterator>
#include <algorithm>

/**
 * @class ProgressionGenerator
 * @brief Класс-генератор членов арифметической прогрессии
 * 
 * Реализует функтор, который при каждом вызове возвращает следующий
 * член арифметической прогрессии
 */
class ProgressionGenerator {
private:
    double first;   ///< Первый член прогрессии (A)
    double diff;    ///< Разность прогрессии (D)
    int counter;    ///< Счетчик вызовов (0, 1, 2...)
    
public:
    /**
     * @brief Конструктор генератора
     * @param a Первый член прогрессии
     * @param d Разность прогрессии
     */
    ProgressionGenerator(double a, double d) 
        : first(a), diff(d), counter(0) {}
    
    /**
     * @brief Оператор вызова - генерирует следующий член
     * @return double Очередной член прогрессии: first + counter * diff
     */
    double operator()() {
        return first + counter++ * diff;
    }
};

/**
 * @brief Выводит N членов арифметической прогрессии
 * @param A Первый член прогрессии
 * @param D Разность прогрессии
 * @param N Количество членов для вывода
 * @param os Поток вывода (по умолчанию std::cout)
 */
void printArithmeticProgression(double A, double D, int N, std::ostream& os = std::cout) {
    /**
     * @brief Итератор вывода для потока os
     * 
     * Создает итератор, который выводит значения типа double
     * в указанный поток с разделителем-пробелом
     */
    std::ostream_iterator<double> out_it(os, " ");
    
    /**
     * @brief Генератор членов прогрессии
     */
    ProgressionGenerator generator(A, D);
    
    /**
     * @brief Генерация и вывод N членов
     * 
     * Алгоритм generate_n вызывает генератор N раз и выводит
     * результаты через итератор out_it
     */
    std::generate_n(out_it, N, generator);
    
    os << std::endl;
}

/**
 * @brief Главная функция программы
 * 
 * Запрашивает у пользователя параметры прогрессии и выводит
 * первые N членов в консоль
 * 
 * @return int 0 при успешном выполнении
 */
int main() {
    double A, D;  ///< Параметры прогрессии
    int N;        ///< Количество членов
    
    // Ввод данных
    std::cout << "Введите первый член прогрессии A: ";
    std::cin >> A;
    
    std::cout << "Введите разность прогрессии D: ";
    std::cin >> D;
    
    std::cout << "Введите количество членов N: ";
    std::cin >> N;
    
    // Вывод прогрессии
    printArithmeticProgression(A, D, N);
    
    return 0;
}