#include <iostream>      // Для ввода и вывода данных
#include <fstream>       // Для работы с файлами
#include <vector>        // Для использования контейнера vector
#include <algorithm>     // Для алгоритмов transform и copy
#include <functional>    // Для bind и placeholders
#include <string>        // Для работы со строками
#include <iterator>      // Для итераторов потоков istream_iterator

using namespace std;     // Использование стандартного пространства имен
using namespace std::placeholders;  // Для плейсхолдеров _1, _2, _3...

// Структуры
struct point {
    int x;          // Координата X 
    int y;          // Координата Y 
    std::string s;  // Строковая метка (без пробелов)
    
    point mult(const int k) const; // Метод умножения координат точки на число
};

// Функциональные объекты
struct point_plus {
    point operator()(const point& a, const point& b) const; // Перегрузка оператора () для сложения точек
};

// Прототипы функций
std::istream& operator>>(std::istream& is, point& p); // Перегрузка оператора ввода
std::ostream& operator<<(std::ostream& os, const point& p); // Перегрузка оператора вывода
vector<point> readPointsFromFile(const string& filename); // Функция чтения точек из файла
void processPoints(vector<point>& V1, const vector<point>& V2, const int K); // Функция обработки точек
void displayResults(const vector<point>& V1); // Функция вывода результатов

/**
 * @brief Главная функция программы
 * @return завершение программы (0 - успех, 1 - ошибка)
 */
int main() {
    int K = 0;           // Множитель для преобразования точек
    string name1;        // Имя первого файла
    string name2;        // Имя второго файла

    cout << "Введите число K: "; // Вывод приглашения для ввода K
    cin >> K;                    // Ввод значения K

    cout << "Введите имя первого файла: "; // Запрос имени первого файла
    cin >> name1;                          // Ввод имени первого файла

    cout << "Введите имя второго файла: "; // Запрос имени второго файла
    cin >> name2;                          // Ввод имени второго файла
    
    // Чтение точек из файлов
    vector<point> V1 = readPointsFromFile(name1); // Чтение первого вектора точек

    if (V1.empty() && !ifstream(name1).is_open()) { // Проверка успешности открытия файла
        return 1;                                   // Завершение программы с ошибкой
    }
    
    vector<point> V2 = readPointsFromFile(name2); // Чтение второго вектора точек

    if (V2.empty() && !ifstream(name2).is_open()) { // Проверка успешности открытия файла
        return 1;                                   // Завершение программы с ошибкой
    }
    
    // Проверка размеров векторов
    if (V1.size() != V2.size()) { // Проверка одинакового количества элементов
        cerr << "Ошибка: файлы содержат разное количество элементов!" << endl; // Сообщение об ошибке
        cerr << "В первом файле: " << V1.size() << " элементов" << endl; // Размер первого файла
        cerr << "Во втором файле: " << V2.size() << " элементов" << endl; // Размер второго файла
        return 1; // Завершение программы с ошибкой
    }
    
    // Обработка точек
    processPoints(V1, V2, K); // Вызов функции обработки
    
    // Вывод результатов
    displayResults(V1); // Вывод результата на экран
    
    return 0;  // Успешное завершение программы
}


/**
 * @brief Умножение точки на целое число
 * @param k Множитель (целое число)
 * @return Новая точка, полученная умножением координат на k
 */
point point::mult(int k) const {
    point result;              // Создание результирующей точки
    result.x = k * this->x;    // Умножение координаты X
    result.y = k * this->y;    // Умножение координаты Y
    result.s = this->s;        // Копирование строковой метки
    return result;             // Возврат результата
}

/**
 * @brief Оператор вызова функтора point_plus
 * @param a Первая точка
 * @param b Вторая точка
 * @return Результат сложения a и b
 */
point point_plus::operator()(const point& a, const point& b) const {
    point result;              // Создание результирующей точки
    result.x = a.x + b.x;      // Сложение координат X
    result.y = a.y + b.y;      // Сложение координат Y
    result.s = a.s + b.s;      // Конкатенация строк
    return result;             // Возврат результата
}

/**
 * @brief Оператор ввода для структуры point
 * @param is Входной поток
 * @param p Ссылка на объект point для заполнения
 * @return Ссылка на входной поток
 */
std::istream& operator>>(std::istream& is, point& p) {
    is >> p.x >> p.y >> p.s; // Считывание координат и строки
    return is;               // Возврат входного потока
}

/**
 * @brief Оператор вывода для структуры point
 * @param os Выходной поток
 * @param p Константная ссылка на объект point
 * @return Ссылка на выходной поток
 */
std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x << " " << p.y << " " << p.s; // Вывод координат и строки
    return os;                             // Возврат выходного потока
}

/**
 * @brief Чтение точек из файла
 * @param filename Имя файла для чтения
 * @return Вектор точек, прочитанных из файла
 */
vector<point> readPointsFromFile(const string& filename) {
    vector<point> points; // Вектор для хранения считанных точек

    ifstream file(filename); // Открытие файла
    
    if (!file.is_open()) { // Проверка успешности открытия файла
        cerr << "Ошибка: не удалось открыть файл " << filename << endl; // Сообщение об ошибке
        return points;  // Возвращаем пустой вектор
    }
    
    // чтение через итераторы (без явного цикла)
    copy(istream_iterator<point>(file),        // Итератор начала чтения
         istream_iterator<point>(),            // Итератор конца файла
         back_inserter(points));               // Вставка элементов в вектор
    
    file.close(); // Закрытие файла
    return points; // Возврат заполненного вектора
}

/**
 * @brief Обработка векторов точек
 * @param V1 Первый вектор (будет изменен)
 * @param V2 Второй вектор (константный)
 * @param K Множитель для преобразования
 * 
 * Выполняет преобразование: V1[i] = point_plus()(V1[i].mult(K), V2[i])
 */
void processPoints(vector<point>& V1, const vector<point>& V2, const int K) {

    transform(V1.begin(),              // Начало первого диапазона
              V1.end(),                // Конец первого диапазона
              V2.begin(),              // Начало второго диапазона
              V1.begin(),              // Место записи результата
        bind(point_plus(),             // Связывание функтора сложения
            bind(&point::mult, _1, K), // Первый аргумент: V1[i].mult(K)
            _2)                        // Второй аргумент: V2[i]
    );
}

/**
 * @brief Вывод результатов на экран
 * @param V1 Вектор обработанных точек
 */
void displayResults(const vector<point>& V1) {

    cout << "\n========================================" << endl; // Верхняя граница таблицы
    cout << "Результат преобразования вектора V1:" << endl; // Заголовок результата
    cout << "========================================\n" << endl; // Разделительная линия
    
    for (size_t i = 0; i < V1.size(); ++i) { // Цикл по всем элементам вектора
        cout << "Точка " << i + 1 << ": " << V1[i] << endl; // Вывод очередной точки
    }
    
    cout << "\n========================================" << endl; // Нижняя граница таблицы
    cout << "Всего обработано точек: " << V1.size() << endl; // Вывод количества точек
    cout << "========================================" << endl; // Завершающая линия
}
