#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

/**
 * @brief Функциональный объект для вывода количества повторений элементов
 * 
 * Этот функтор используется с алгоритмом for_each для множества уникальных элементов.
 * Для каждого элемента из множества S он подсчитывает количество его вхождений
 * в мультимножество M и выводит результат.
 */
class PrintElementCount {
private:
    const std::multiset<int>& m_multiset; ///< Ссылка на мультимножество с повторениями
    
public:
    /**
     * @brief Конструктор функционального объекта
     * @param ms Ссылка на мультимножество, содержащее все элементы с повторениями
     */
    PrintElementCount(const std::multiset<int>& ms) : m_multiset(ms) {}
    
    /**
     * @brief Оператор вызова для обработки одного элемента
     * @param element Уникальный элемент для обработки
     * 
     * Подсчитывает количество вхождений элемента в мультимножестве
     * и выводит элемент вместе с его количеством повторений.
     */
    void operator()(int element) const {
        // Функция count возвращает количество элементов, равных заданному
        int count = m_multiset.count(element);
        std::cout << element << " : " << count << std::endl;
    }
};

/**
 * @brief Выводит все различные элементы вектора с количеством их повторений
 * @param V Исходный вектор целых чисел
 * 
 * Функция создает мультимножество M (хранит все элементы с повторениями)
 * и множество S (хранит только уникальные элементы) на основе вектора V.
 * Затем с помощью for_each и функционального объекта выводит каждый
 * уникальный элемент вместе с количеством его вхождений.
 * Результат выводится в порядке возрастания значений элементов.
 */
void printElementCounts(const std::vector<int>& V) {
    if (V.empty()) {
        std::cout << "Вектор пуст" << std::endl;
        return;
    }
    
   
    std::multiset<int> M(V.begin(), V.end());
    
    
    std::set<int> S(V.begin(), V.end());
    
    // Применяем for_each к каждому уникальному элементу из S
    // Функциональный объект PrintElementCount будет выводить результат
    std::for_each(S.begin(), S.end(), PrintElementCount(M));
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном выполнении
 * 
 * Демонстрирует работу функции printElementCounts на примерах
 */
int main() {
    // Пример 1: Вектор с повторяющимися элементами
    std::vector<int> V1 = {5, 2, 8, 2, 5, 5, 3, 8, 1, 2};
    
    std::cout << "Исходный вектор V1: ";
    for (int num : V1) {
        std::cout << num << " ";
    }
    std::cout << "\n\nРезультат (элемент : количество повторений):\n";
    printElementCounts(V1);
    
    std::cout << "\n" << std::string(30, '-') << "\n\n";
    
    // Пример 2: Вектор с одним элементом
    std::vector<int> V2 = {42, 42, 42};
    
    std::cout << "Исходный вектор V2: ";
    for (int num : V2) {
        std::cout << num << " ";
    }
    std::cout << "\n\nРезультат (элемент : количество повторений):\n";
    printElementCounts(V2);
    
    std::cout << "\n" << std::string(30, '-') << "\n\n";
    
    // Пример 3: Пустой вектор
    std::vector<int> V3;
    
    std::cout << "Исходный вектор V3: пуст\n\n";
    printElementCounts(V3);
    
    return 0;
}