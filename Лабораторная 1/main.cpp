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
    CaesarCipher cipher(3); // ���� �� ���������
    int choice;

    do 
    {
        cout << "\n=== ���� ������ ===" << endl;
        cout << "1. ������ �����" << endl;
        cout << "2. �������� �����" << endl;
        cout << "3. ����������� �����" << endl;
        cout << "4. ������������ �����" << endl;
        cout << "5. �����" << endl;
        cout << "�������� �����: ";
        
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                int key;
                cout << "������� �����: ";
                cin >> key;
                cipher.setKey(key);
                break;
            }
            case 2:
                cout << endl << "������� �����: " << cipher.getKey() << endl;
                break;
            case 3: 
            {
                string text;
                cout << "������� ����� ��� ����������: ";
                cin.ignore();
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
                cin.ignore();
                getline(cin, text);
                string decrypted = cipher.decrypt(text);
                cout << endl << "�������������� �����: " << decrypted << endl;
                string encrypted = cipher.encrypt(decrypted);
                cout << "������������� �����: " << encrypted << endl;
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
            choice = stoi(input); // ������� ������������� � �����
        }
        catch (...) {
            choice = 0; // ���� �� ����� - ������ ���������� ��������
        }
       
        switch (choice) {
        case 1:
            caesarMenu();
            break;
        case 2:
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