#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "cipher.hpp"

using namespace std;

void showMenu() 
{
    cout << "\n=== Меню шифров ===" << endl;
    cout << "1. Шифр Цезаря" << endl;
    cout << "2. Шифр Виженера" << endl;
    cout << "3. Выход" << endl;
    cout << "Выберите опцию: ";
}

void caesarMenu()
{
    CaesarCipher cipher(3); // ключ по умолчанию
    int choice;

    do 
    {
        cout << "\n=== Шифр Цезаря ===" << endl;
        cout << "1. Задать сдвиг" << endl;
        cout << "2. Получить сдвиг" << endl;
        cout << "3. Зашифровать текст" << endl;
        cout << "4. Расшифровать текст" << endl;
        cout << "5. Назад" << endl;
        cout << "Выберите опцию: ";
        
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                int key;
                cout << "Введите сдвиг: ";
                cin >> key;
                cipher.setKey(key);
                break;
            }
            case 2:
                cout << endl << "Текущий сдвиг: " << cipher.getKey() << endl;
                break;
            case 3: 
            {
                string text;
                cout << "Введите текст для шифрования: ";
                cin.ignore();
                getline(cin, text);
                string encrypted = cipher.encrypt(text);
                cout << endl << "Зашифрованный текст: " << encrypted << endl;
                string decrypted = cipher.decrypt(encrypted);
                cout << "Расшифрованный текст: " << decrypted << endl;

                break;
            }
            case 4: 
            {
                string text;
                cout << "Введите текст для дешифрования: ";
                cin.ignore();
                getline(cin, text);
                string decrypted = cipher.decrypt(text);
                cout << endl << "Расшифрованный текст: " << decrypted << endl;
                string encrypted = cipher.encrypt(decrypted);
                cout << "Зашифрованный текст: " << encrypted << endl;
                break;
            }
            
        }
    } while (choice != 5);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string input;
    int choice;

    do {
        showMenu();
        getline(cin, input);

        try {
            choice = stoi(input); // пробуем преобразовать в число
        }
        catch (...) {
            choice = 0; // если не число - ставим невалидное значение
        }
       
        switch (choice) {
        case 1:
            caesarMenu();
            break;
        case 2:
            break;
        case 3:
            cout << endl << "Выход из программы..." << endl;
            break;
        default:
            cout << endl << "Неверный выбор!" << endl;
        }
    } while (choice != 3);

    return 0;
}