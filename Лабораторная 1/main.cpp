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
    CaesarCipher cipher(2); // ключ по умолчанию
    string input;
    int choice;

    do 
    {
        cout << "\n=== Шифр Цезаря ===" << endl;
        cout << "1. Задать сдвиг" << endl;
        cout << "2. Получить сдвиг" << endl;
        cout << "3. Зашифровать текст" << endl;
        cout << "4. Расшифровать текст" << endl;
        cout << "5. Зашифровать файл" << endl;
        cout << "6. Расшифровать файл" << endl;
        cout << "7. Назад" << endl;
        cout << "Выберите опцию: ";
        
        getline(cin, input);

        if (input.length() == 1) {
            choice = input[0] - '0';
        }
        else {
            choice = 0;
        }

        switch (choice) 
        {
            case 1: 
            {
                cout << "Введите сдвиг: ";
                getline(cin, input);
                try
                {
                    int key = stoi(input);
                    cipher.setKey(key);
                }
                catch (...)
                {
                    cout << "Ошибка! Введите число." << endl;
                }
                break;
            }
            case 2:
                cout << endl << "Текущий сдвиг: " << cipher.getKey() << endl;
                break;
            case 3: 
            {
                string text;
                cout << "Введите текст для шифрования: ";
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
                getline(cin, text);
                string decrypted = cipher.decrypt(text);
                cout << endl << "Расшифрованный текст: " << decrypted << endl;
                string encrypted = cipher.encrypt(decrypted);
                cout << "Зашифрованный текст: " << encrypted << endl;
                break;
            }
            case 5:
            {
                string inputFile, outputFile;
                cout << "Введите путь к исходному файлу: ";
                getline(cin, inputFile);
                cout << "Введите путь для зашифрованного файла: ";
                getline(cin, outputFile);

                // Добавляем расширение .txt если не указано
                if (outputFile.find('.') == string::npos) {
                    outputFile += ".txt";
                }

                cipher.encryptFile(inputFile, outputFile);
                break;
            }
            case 6:
            {
                string inputFile, outputFile;
                cout << "Введите путь к зашифрованному файлу: ";
                getline(cin, inputFile);
                cout << "Введите путь для расшифрованного файла: ";
                getline(cin, outputFile);

                // Добавляем расширение .txt если не указано
                if (outputFile.find('.') == string::npos) {
                    outputFile += ".txt";
                }

                cipher.decryptFile(inputFile, outputFile);
                break;
            }
            case 7:
            {
                cout << endl << "Выход из шифра Цезаря..." << endl;
                break;
            }
            default:
                cout << endl << "Неверный выбор!" << endl;
        }
    } while (choice != 7);
}

void vigenereMenu()
{
    VigenereCipher cipher("RAF"); // ключ по умолчанию
    string input;
    int choice;

    do
    {
        cout << "\n=== Шифр Виженера ===" << endl;
        cout << "1. Задать ключ" << endl;
        cout << "2. Получить ключ" << endl;
        cout << "3. Зашифровать текст" << endl;
        cout << "4. Расшифровать текст" << endl;
        cout << "5. Зашифровать файл" << endl;
        cout << "6. Расшифровать файл" << endl;
        cout << "7. Назад" << endl;
        cout << "Выберите опцию: ";

        getline(cin, input);

        if (input.length() == 1) {
            choice = input[0] - '0';
        }
        else {
            choice = 0;
        }

        switch (choice)
        {
        case 1:
        {
            string key;
            cout << "Введите ключ: ";
            getline(cin, key);
            try
            {
                cipher.setKey(key);
                cout << "Ключ установлен!" << endl;
            }
            catch (...)
            {
                cout << "Ошибка! Ключ не может быть пустым." << endl;
            }
            break;
        }
        case 2:
            cout << endl << "Текущий ключ: " << cipher.getKey() << endl;
            break;
        case 3:
        {
            string text;
            cout << "Введите текст для шифрования: ";
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
            getline(cin, text);
            string decrypted = cipher.decrypt(text);
            cout << endl << "Расшифрованный текст: " << decrypted << endl;
            string encrypted = cipher.encrypt(decrypted);
            cout << "Зашифрованный текст: " << encrypted << endl;
            break;
        }
        case 5:
        {
            string inputFile, outputFile;
            cout << "Введите путь к исходному файлу: ";
            getline(cin, inputFile);
            cout << "Введите путь для зашифрованного файла: ";
            getline(cin, outputFile);

            if (outputFile.find('.') == string::npos) {
                outputFile += ".txt";
            }

            cipher.encryptFile(inputFile, outputFile);
            break;
        }
        case 6:
        {
            string inputFile, outputFile;
            cout << "Введите путь к зашифрованному файлу: ";
            getline(cin, inputFile);
            cout << "Введите путь для расшифрованного файла: ";
            getline(cin, outputFile);

            if (outputFile.find('.') == string::npos) {
                outputFile += ".txt";
            }

            cipher.decryptFile(inputFile, outputFile);
            break;
        }
        case 7:
        {
            cout << endl << "Выход из шифра Виженера..." << endl;
            break;
        }
        default:
            cout << endl << "Неверный выбор!" << endl;
        }
    } while (choice != 7);
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string input;
    int choice;

    do 
    {
        showMenu();
        getline(cin, input);

        if (input.length() == 1) {
            choice = input[0] - '0';
        }
        else {
            choice = 0;
        }

        switch (choice) 
        {
        case 1:
            caesarMenu();
            break;
        case 2:
            vigenereMenu();
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