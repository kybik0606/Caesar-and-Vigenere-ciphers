#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "cipher.hpp"

using namespace std;

void showMenu() 
{
    cout << "\n=== ���� ������ ===" << endl;
    cout << "1. ���� ������" << endl;
    cout << "2. ���� ��������" << endl;
    cout << "3. �����" << endl;
    cout << "�������� �����: ";
}

void caesarMenu()
{
    CaesarCipher cipher(2); // ���� �� ���������
    string input;
    int choice;

    do 
    {
        cout << "\n=== ���� ������ ===" << endl;
        cout << "1. ������ �����" << endl;
        cout << "2. �������� �����" << endl;
        cout << "3. ����������� �����" << endl;
        cout << "4. ������������ �����" << endl;
        cout << "5. ����������� ����" << endl;
        cout << "6. ������������ ����" << endl;
        cout << "7. �����" << endl;
        cout << "�������� �����: ";
        
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
                cout << "������� �����: ";
                getline(cin, input);
                try
                {
                    int key = stoi(input);
                    cipher.setKey(key);
                }
                catch (...)
                {
                    cout << "������! ������� �����." << endl;
                }
                break;
            }
            case 2:
                cout << endl << "������� �����: " << cipher.getKey() << endl;
                break;
            case 3: 
            {
                string text;
                cout << "������� ����� ��� ����������: ";
                getline(cin, text);
                string encrypted = cipher.encrypt(text);
                cout << endl << "������������� �����: " << encrypted << endl;
                string decrypted = cipher.decrypt(encrypted);
                cout << "�������������� �����: " << decrypted << endl;
                break;
            }
            case 4: 
            {
                string text;
                cout << "������� ����� ��� ������������: ";
                getline(cin, text);
                string decrypted = cipher.decrypt(text);
                cout << endl << "�������������� �����: " << decrypted << endl;
                string encrypted = cipher.encrypt(decrypted);
                cout << "������������� �����: " << encrypted << endl;
                break;
            }
            case 5:
            {
                string inputFile, outputFile;
                cout << "������� ���� � ��������� �����: ";
                getline(cin, inputFile);
                cout << "������� ���� ��� �������������� �����: ";
                getline(cin, outputFile);

                // ��������� ���������� .txt ���� �� �������
                if (outputFile.find('.') == string::npos) {
                    outputFile += ".txt";
                }

                cipher.encryptFile(inputFile, outputFile);
                break;
            }
            case 6:
            {
                string inputFile, outputFile;
                cout << "������� ���� � �������������� �����: ";
                getline(cin, inputFile);
                cout << "������� ���� ��� ��������������� �����: ";
                getline(cin, outputFile);

                // ��������� ���������� .txt ���� �� �������
                if (outputFile.find('.') == string::npos) {
                    outputFile += ".txt";
                }

                cipher.decryptFile(inputFile, outputFile);
                break;
            }
            case 7:
            {
                cout << endl << "����� �� ����� ������..." << endl;
                break;
            }
            default:
                cout << endl << "�������� �����!" << endl;
        }
    } while (choice != 7);
}

void vigenereMenu()
{
    VigenereCipher cipher("RAF"); // ���� �� ���������
    string input;
    int choice;

    do
    {
        cout << "\n=== ���� �������� ===" << endl;
        cout << "1. ������ ����" << endl;
        cout << "2. �������� ����" << endl;
        cout << "3. ����������� �����" << endl;
        cout << "4. ������������ �����" << endl;
        cout << "5. ����������� ����" << endl;
        cout << "6. ������������ ����" << endl;
        cout << "7. �����" << endl;
        cout << "�������� �����: ";

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
            cout << "������� ����: ";
            getline(cin, key);
            try
            {
                cipher.setKey(key);
                cout << "���� ����������!" << endl;
            }
            catch (...)
            {
                cout << "������! ���� �� ����� ���� ������." << endl;
            }
            break;
        }
        case 2:
            cout << endl << "������� ����: " << cipher.getKey() << endl;
            break;
        case 3:
        {
            string text;
            cout << "������� ����� ��� ����������: ";
            getline(cin, text);
            string encrypted = cipher.encrypt(text);
            cout << endl << "������������� �����: " << encrypted << endl;
            string decrypted = cipher.decrypt(encrypted);
            cout << "�������������� �����: " << decrypted << endl;
            break;
        }
        case 4:
        {
            string text;
            cout << "������� ����� ��� ������������: ";
            getline(cin, text);
            string decrypted = cipher.decrypt(text);
            cout << endl << "�������������� �����: " << decrypted << endl;
            string encrypted = cipher.encrypt(decrypted);
            cout << "������������� �����: " << encrypted << endl;
            break;
        }
        case 5:
        {
            string inputFile, outputFile;
            cout << "������� ���� � ��������� �����: ";
            getline(cin, inputFile);
            cout << "������� ���� ��� �������������� �����: ";
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
            cout << "������� ���� � �������������� �����: ";
            getline(cin, inputFile);
            cout << "������� ���� ��� ��������������� �����: ";
            getline(cin, outputFile);

            if (outputFile.find('.') == string::npos) {
                outputFile += ".txt";
            }

            cipher.decryptFile(inputFile, outputFile);
            break;
        }
        case 7:
        {
            cout << endl << "����� �� ����� ��������..." << endl;
            break;
        }
        default:
            cout << endl << "�������� �����!" << endl;
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
            cout << endl << "����� �� ���������..." << endl;
            break;
        default:
            cout << endl << "�������� �����!" << endl;
        }
    } while (choice != 3);
    return 0;
}