#ifdef _WIN64
#include <windows.h>
#endif
#include "project.h"
#include <iostream>
#include <vector>
#include <limits>

int main() {
    #ifdef _WIN64
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    #endif
    std::vector<InfoContact> contacts;
    int choice;
    do {
        std::cout << "\n<<Умный>> телефонный справочник\n" << std::endl;
        std::cout << "Выберите один из следующих пунктов: " << std::endl;
        std::cout << "1. Показать список контактов" << std::endl;
        std::cout << "2. Добавление, удаление, редактирование информации" << std::endl;
        std::cout << "3. Поиск по части имени" << std::endl;
        std::cout << "4. Сортировка по имени" << std::endl;
        std::cout << "5. Сохранение в файл, загрузка из файла" << std::endl;
        std::cout << "6. Выход из телефонного справочника" << std::endl;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cout <<  "Ошибка. Нужно ввести число от 1 до 6.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: {
                PrintContacts(contacts);
                break;
            }
            case 2: {
                ManageContactsMenu(contacts);
                break;
            }
            case 3: {
                Search(contacts);
                break;
            }
            case 4: {
                SortByName(contacts);
                break;
            }
            case 5: {
                FileOperationsMenu(contacts);
                break;
            }
            case 6: {
                std::cout << "Выход из телефонного справочника" << std::endl;
                break;
            }
            default: {
                std::cout <<  "Неверный ввод данных" << std::endl;
                break;
            }
        }
    }
    while (choice != 6);
    return 0;
}