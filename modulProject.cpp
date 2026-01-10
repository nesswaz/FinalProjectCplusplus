#include "project.h"
#include <iostream> 
#include <fstream>
#include <limits>

void AddInformation(std::vector<InfoContact>& contacts) {
    // // Используем локальную переменную InfoContact, 
    //чтобы избежать прямого изменения вектора до завершения ввода
    InfoContact add;
    std::cout << "Введите имя контакта: "; 
    std::cin >> add.name;
    // Очищаем буфер ввода, так как после std::cin
    // остаётся символ новой строки, который мешает getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Бесконечный цикл для телефона нужен, чтобы 
    //гарантировать получение корректных данных
    while (true) {
        std::cout << "Введите номер телефона контакта: ";
        std::getline(std::cin, add.phone_number);
        if (IsValidPhoneNumber(add.phone_number))
            break;
        std::cout << "Ошибка. Вы можете ввести только цифры, +, -, () и пробелы.\n";
    }
    while (true) {
        std::cout << "Введите email контакта: "; 
        std::getline(std::cin, add.email);
        if (IsValidEmail(add.email)) {
            break;
        }
        std::cout << "Ошибка. Некорректный ввод email.\n";
    }
    contacts.push_back(add);
    PrintContacts(contacts);
}

void DeleteContacts(std::vector<InfoContact>& contacts) {
    // Проверяем пустоту списка в начале функции для предотвращения ошибок доступа
    if (contacts.empty()) {
        std::cout << "Список контактов пуст. Удаление невозможно.\n\n";
        return;
    }
    PrintContacts(contacts);
    int index = GetIndex(contacts);
    // pop_back() уменьшает размер вектора и уничтожает последний элемент
    contacts.pop_back();
    std::cout << "Удаление прошло успешно! " << std::endl;
    PrintContacts(contacts);
}

void EditContact(std::vector<InfoContact>& contacts) {
    if (contacts.empty()) {
        std::cout << "Список контактов пуст. Редактирование невозможно.\n" << std::endl;
        return;
    }
    PrintContacts(contacts);

    int index = GetIndex(contacts);
    int choice = GetEditChoice(); 
    switch (choice) {
        case 1: {
            // getline() используется вместо cin>>, чтобы разрешить пробелы в именах
            std::cout << "Новое имя: ";
            std::getline(std::cin, contacts[index - 1].name);
            break;
        }
        case 2: {
            while (true) {
                
                std::cout << "Новый телефон: ";
                std::getline(std::cin, contacts[index - 1].phone_number);
                if (IsValidPhoneNumber(contacts[index - 1].phone_number))
                    break;
                std::cout << "Ошибка. Некорректный номер телефона.\n";
            }
            break;
        }
        case 3: {
            
            while (true) {
                std::cout << "Новый email: ";
                std::getline(std::cin, contacts[index - 1].email);
                if (IsValidEmail(contacts[index - 1].email))
                    break;
                std::cout << "Ошибка. Некорректный email.\n";
            }
            break;
        }
        case 4: {
            //Для того чтобы пользователю было удобно изменить всю информацию
            std::cout << "Новое имя: ";
            std::getline(std::cin, contacts[index - 1].name);

            while (true) {
                std::cout << "Новый телефон: ";
                std::getline(std::cin, contacts[index - 1].phone_number);
                if (IsValidPhoneNumber(contacts[index - 1].phone_number))
                    break;
                std::cout << "Ошибка. Некорректный номер телефона.\n";
            }

            while (true) {
                std::cout << "Новый email: ";
                std::getline(std::cin, contacts[index - 1].email);
                if (IsValidEmail(contacts[index - 1].email))
                    break;
                std::cout << "Ошибка. Некорректный email.\n";
            }

            break;
        }
        default: {
            std::cout << "Неверный выбор\n";
            return;
        }
    }
    std::cout << "Изменение прошло успешно\n";
    PrintContacts(contacts);
}

void ManageContactsMenu(std::vector<InfoContact>& contacts) {
    int choice;
    do {
        std::cout << "Выберите один из следующих пунктов: " << std::endl;
        std::cout << "1. Добавление контактов" << std::endl;
        std::cout << "2. Удаление контактов" << std::endl;
        std::cout << "3. Редактирование контактов" << std::endl;
        std::cout << "4. Вернуться в основное меню" << std::endl;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "\nОшибка. Нужно ввести цифру от 1 до 4.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: {
                AddInformation(contacts);
                break;
            }
            case 2: {
                DeleteContacts(contacts);
                break;
            }
            case 3: {
                EditContact(contacts);
                break;
            }
            case 4: {
                std::cout << "Возврат в основное меню" << std::endl;
                break;
            }
            default: {
                std::cout << "Неверный ввод данных" << std::endl;
                break;
            }
        }
    }
    while (choice != 4);
    return;
}

int GetEditChoice() {
    int choice;
    while (true) {
        std::cout << "\nЧто вы хотите изменить?\n";
        std::cout << "1. Имя контакта\n";
        std::cout << "2. Телефон контакта\n";
        std::cout << "3. Email контакта\n";
        std::cout << "4. Изменить всю информацию\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (!std::cin.fail() && choice >= 1 && choice <= 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cout << "Некорректный ввод.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int GetIndex(const std::vector<InfoContact>& contacts) {
    // Функция вынесена для повторного использования в разных операциях
    int index;
    while(true) {
        std::cout << "Введите номер (№) контакта, который хотите редактировать: ";
        std::cin >> index;
        // Проверяем fail() для защиты от ввода символов вместо чисел
        if (!std::cin.fail() && index >= 1 && index <= contacts.size()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return index;
        }
        std::cout << "Неверный номер контакта. Попробуйте снова.\n";
        // Очищаем флаги ошибок и буфер ввода, чтобы цикл не завис
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Search(std::vector <InfoContact>& contacts) {
    if (contacts.empty()) {
        std::cout << "\nСписок контактов пуст.\n\n";
        return;
    }
    bool found = false;
    std::string name;
    std::cout << "Введите часть имени для поиска контакта: ";
    std::cin >> name;
    std::cout << "Результат поиска: " << std::endl;
    for (int i = 0; i < contacts.size(); i++) { 
        if (contacts[i].name.find(name) != std::string::npos) {
            // Используем find(), а не ==, потому что нужен поиск по части имен
            std::cout << i + 1 << ". " << contacts[i].name 
                << ", " << contacts[i].phone_number 
                << ", " << contacts[i].email << std::endl;
        found = true;
        }
    }
    if (!found) {
        std::cout << "Контакты не найдены\n";
    }
}

void SortByName(std::vector <InfoContact>& contacts) { 
    PrintContacts(contacts);
    if (contacts.empty()) {
        std::cout << "\nСписок контактов пуст. Сортировка невозможна.\n" << std::endl;
        return;
    }
    if (contacts.size() == 1) {
        std::cout << "\nНе хватает контактов для сортировки.\n";
        PrintContacts(contacts);
        std::cout << std::endl;
        return;
    }
    // Используем пузырьковую сортировку (метод простого обмена)
    // потому что она простая для понимания
    for (int i = 0; i < contacts.size() - 1; i++) {
        for (int j = 0; j < contacts.size() - i - 1; j++) {
            if (contacts[j].name > contacts[j + 1].name) {
                std::swap(contacts[j], contacts[j + 1]);
            }
        }
    }
    std::cout << "Контакты отсортированы по имени.\n";
    PrintContacts(contacts);
}

void WritingToFile(const std::vector<InfoContact>& contacts, const std::string& filename) {
    if (contacts.empty()) {
        std::cout << "Список контактов пуст. Сохранение в файл невозможно.\n" << std::endl;
        return;
    }
    // Проверяем открытие файла, потому что файл может не открыться
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Ошибка при открытии файла!\n";
        return;
    }
    //Выводит в файл пронумерованные контакты
    for (int i = 0; i < contacts.size(); i++) {
        file << i + 1 << ". " << contacts[i].name << ", " 
            << contacts[i].phone_number << ", " 
            << contacts[i].email << "\n";
    }
    file.close();
    std::cout << "Контакты сохранены в файл " << filename << "\n\n";
}

void OutputFromFile(std::vector<InfoContact>& contacts, std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не получилось открыть файл" << std::endl;
        return;
    }
    // Очищаем вектор, потому что новые данные могут добавиться к старым
    contacts.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
             // Ищем позиции двух запятых, тк формат "имя, телефон, email"
            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                InfoContact contact;
                // Используем substr, потому что нужно взять части строки
                contact.name = line.substr(0, pos1);

                contact.phone_number = line.substr(pos1 + 1, pos2 - pos1 - 1);

                contact.email = line.substr(pos2 + 1);
               
                contacts.push_back(contact);
            }
            else {
                std::cout << "Строка не соответствует формату: " << line << std::endl;
            }
        }
    }
    file.close();
    std::cout << "Контакты загружены из файла " << filename << "\n";
    PrintContacts(contacts);
}

void FileOperationsMenu(std::vector <InfoContact>& contacts) {
    int choice;
    do {
        std::cout << "Выберите один из следующих пунктов: " << std::endl;
        std::cout << "1. Сохранение контактов в файл" << std::endl;
        std::cout << "2. Загрузка контактов из файла" << std::endl;
        std::cout << "3. Выход в основное меню" << std::endl;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Введены неверные данные. Введите число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: {
                WritingToFile(contacts, "SaveContacts.txt");
                break;
            }
            case 2: {
                OutputFromFile(contacts, "WriteContacts.txt");
                break;
            }
            case 3: {
                std::cout << "Выход в основное меню" << std::endl;
                break;
            }
            default: {
                std::cout << "Введены неверные данные" << std::endl;
                break;
            }
        }
    }
    while (choice != 3);
}


bool IsValidPhoneNumber(const std::string& phone) { 
    if (phone.empty()) return false;
    for (char c : phone) {
        // Проверяем каждый символ, потому что нужно убедиться 
        // в допустимости всех символов
        if (!isdigit(c) && c != '+' && c != '-' && c != '(' && c != ')' && c != ' ')
            return false;
    }
    return true;
}

bool IsValidEmail(const std::string& email) { 
    if (email.empty())
        return false;
    // Запрещаем пробелы, потому что в email их не бывает
    if (email.find(' ') != std::string::npos)
        return false;
    // Проверяем наличие @, потому что это обязательный символ в email
    int atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0 || atPos == email.size() - 1)
        return false;

    int dotPos = email.find('.', atPos);
    // Проверяем точку после @, потому что домен должен содержать точку
    if (dotPos == std::string::npos || dotPos == email.size() - 1)
        return false;
    return true;
}

void PrintContacts(const std::vector<InfoContact>& contacts) {
    // Выводит список контактов на экран, потому что пользователю будет удобнее
    if (contacts.empty()) {
        std::cout << "Список контактов пуст.\n";
        return;
    }
    std::cout << std::endl;
    std::cout << "Список контактов: \n";
    std::cout << "Имя, телефон, email.\n";
    for (int i = 0; i < contacts.size(); i++) {
        // Нумеруем с 1, потому что пользователи привыкли к нумерации с 1
        std::cout << i + 1 << ". " << contacts[i].name 
            << ", " << contacts[i].phone_number << ", " 
            << contacts[i].email << std::endl;
    }
    std::cout << std::endl;
}
