#include <iostream>      
#include <fstream>       // Для работы с файлами
#include <vector>        
#include <algorithm>     
#include <functional>    // Для bind и placeholders
#include <string>        
#include <iterator>      // добавлено для итераторов(исправленная ошибка)

using namespace std;
using namespace std::placeholders;  // Для плейсхолдеров _1, _2, _3...

// Структуры
struct point {
    int x;          // Координата X 
    int y;          // Координата Y 
    std::string s;  // Строковая метка (без пробелов)
    
    point mult(const int k) const;
};

// Функциональные объекты
struct point_plus {
    point operator()(const point& a, const point& b) const;
};

// Прототипы функций
std::istream& operator>>(std::istream& is, point& p);
std::ostream& operator<<(std::ostream& os, const point& p);
vector<point> readPointsFromFile(const string& filename);
void processPoints(vector<point>& V1, const vector<point>& V2, const int K); //исправленная ошибка(добавила const)
void displayResults(const vector<point>& V1);

/**
 * @brief Главная функция программы
 * @return завершение программы (0 - успех, 1 - ошибка)
 */
int main() {
    int K = 0;           // Множитель для преобразования точек(также исправленная ошибка,иницилизировала переменную)
    string name1;    // Имя первого файла
    string name2;    // Имя второго файла

    cout << "Введите число K: ";
    cin >> K;
    cout << "Введите имя первого файла: ";
    cin >> name1;
    cout << "Введите имя второго файла: ";
    cin >> name2;
    
    // Чтение точек из файлов
    vector<point> V1 = readPointsFromFile(name1);
    if (V1.empty() && !ifstream(name1).is_open()) {
        return 1;
    }
    
    vector<point> V2 = readPointsFromFile(name2);
    if (V2.empty() && !ifstream(name2).is_open()) {
        return 1;
    }
    
    // Проверка размеров векторов
    if (V1.size() != V2.size()) {
        cerr << "Ошибка: файлы содержат разное количество элементов!" << endl;
        cerr << "В первом файле: " << V1.size() << " элементов" << endl;
        cerr << "Во втором файле: " << V2.size() << " элементов" << endl;
        return 1; 
    }
    
    // Обработка точек
    processPoints(V1, V2, K);
    
    // Вывод результатов
    displayResults(V1);
    
    return 0;  
}


/**
 * @brief Умножение точки на целое число
 * @param k Множитель (целое число)
 * @return Новая точка, полученная умножением координат на k
 */
point point::mult(int k) const {
    point result;
    result.x = k * this->x;
    result.y = k * this->y;
    result.s = this->s;
    return result;
}

/**
 * @brief Оператор вызова функтора point_plus
 * @param a Первая точка
 * @param b Вторая точка
 * @return Результат сложения a и b
 */
point point_plus::operator()(const point& a, const point& b) const {
    point result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.s = a.s + b.s;  // Конкатенация строк
    return result;
}

/**
 * @brief Оператор ввода для структуры point
 * @param is Входной поток
 * @param p Ссылка на объект point для заполнения
 * @return Ссылка на входной поток
 */
std::istream& operator>>(std::istream& is, point& p) {
    is >> p.x >> p.y >> p.s;
    return is;
}

/**
 * @brief Оператор вывода для структуры point
 * @param os Выходной поток
 * @param p Константная ссылка на объект point
 * @return Ссылка на выходной поток
 */
std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x << " " << p.y << " " << p.s;
    return os;
}

/**
 * @brief Чтение точек из файла
 * @param filename Имя файла для чтения
 * @return Вектор точек, прочитанных из файла
 */
vector<point> readPointsFromFile(const string& filename) {
    vector<point> points;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return points;  // Возвращаем пустой вектор
    }
    
    // чтение через итераторы (без явного цикла ,исправила-без цикла ,с итератором)
    copy(istream_iterator<point>(file), istream_iterator<point>(), back_inserter(points));
    
    file.close();
    return points;
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
    transform(V1.begin(), V1.end(), V2.begin(), V1.begin(),
        bind(point_plus(),                   
            bind(&point::mult, _1, K),        // Первый аргумент: V1[i].mult(K)
            _2)                               // Второй аргумент: V2[i]
    );
}

/**
 * @brief Вывод результатов на экран
 * @param V1 Вектор обработанных точек
 */
void displayResults(const vector<point>& V1) {
    cout << "\n========================================" << endl;
    cout << "Результат преобразования вектора V1:" << endl;
    cout << "========================================\n" << endl;
    
    for (size_t i = 0; i < V1.size(); ++i) {
        cout << "Точка " << i + 1 << ": " << V1[i] << endl;
    }
    
    cout << "\n========================================" << endl;
    cout << "Всего обработано точек: " << V1.size() << endl;
    cout << "========================================" << endl;
}
