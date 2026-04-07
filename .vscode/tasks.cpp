#include <iostream>
#include <iterator>
#include <algorithm>

/**
 * @class ProgressionGenerator
 * @brief Класс-генератор членов арифметической прогрессии
 * Реализует функтор, который при каждом вызове возвращает следующий
 * член арифметической прогрессии
 */
class ProgressionGenerator {
private:
    double first;   //Первый член прогрессии
    double diff;    //Разность прогрессии
    int counter;    //Счетчик вызовов (0, 1, 2...)
    
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

// Прототипы функций (объявления)
void printArithmeticProgression(double first_param, double diff_param, int count, std::ostream& os = std::cout);

/**
 * @brief Главная функция программы
 * 
 * Запрашивает у пользователя параметры прогрессии и выводит
 * первые N членов в консоль
 * 
 * @return int 0 при успешном выполнении
 */
int main() {
    double first_param = 0.0;  //Первый член прогрессии (инициализирован)
    double diff_param = 0.0;   //Разность прогрессии (инициализирована)
    int count = 0;             //Количество членов (инициализировано)
    
    // Ввод данных
    std::cout << "Введите первый член прогрессии: ";
    std::cin >> first_param;
    
    std::cout << "Введите разность прогрессии: ";
    std::cin >> diff_param;
    
    std::cout << "Введите количество членов: ";
    std::cin >> count;
    
    // Вывод прогрессии
    printArithmeticProgression(first_param, diff_param, count);
    
    return 0;
}

/**
 * @brief Выводит N членов арифметической прогрессии
 * @param first_param Первый член прогрессии
 * @param diff_param Разность прогрессии
 * @param count Количество членов для вывода
 * @param os Поток вывода (по умолчанию std::cout)
 */
void printArithmeticProgression(double first_param, double diff_param, int count, std::ostream& os) {
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
    ProgressionGenerator generator(first_param, diff_param);
    
    /**
     * @brief Генерация и вывод N членов
     * 
     * Алгоритм generate_n вызывает генератор N раз и выводит
     * результаты через итератор out_it
     */
    std::generate_n(out_it, count, generator);
    
    os << std::endl;
}
