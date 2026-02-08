#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001); // Для русских букв
    
    std::cout << "🎉 MinGW 64-bit успешно установлен!\n";
    std::cout << "Архитектура: 64-bit\n";
    std::cout << "Размер указателя: " << sizeof(void*) * 8 << " бит\n";
    
    #ifdef _WIN64
        std::cout << "Собрано для Windows 64-bit\n";
    #endif
    
    return 0;
}