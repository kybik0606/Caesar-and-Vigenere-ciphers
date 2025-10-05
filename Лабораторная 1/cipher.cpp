#include "cipher.hpp"
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <fstream>
#include <sstream>

// ��������� ��� �������� ���������
constexpr int ENG = 26;
constexpr int RUS = 32;

// ���������� ������� CaesarCipher

CaesarCipher::CaesarCipher(int key) : key_(key) {}

std::string CaesarCipher::encrypt(const std::string& plaintext) const
{
	std::string result;
	for (char c : plaintext)
	{
		result += shiftChar(c, key_);
	}
	return result;
}

std::string CaesarCipher::decrypt(const std::string& ciphertext) const
{
	std::string result;
	for (char c : ciphertext)
	{
		result += shiftChar(c, -key_);
	}
	return result;
}

int CaesarCipher::getKey() const
{
	return key_;
}

void CaesarCipher::setKey(int key)
{
	key_ = key;
}

char::CaesarCipher::shiftChar(char c, int shift) const
{
	char result = c;

	if (c >= 'A' && c <= 'Z')
	{
		c = c + (shift % ENG);
		if (c > 'Z') c = 'A' + (c - 'Z' - 1);
		else if (c < 'A') c = 'Z' - ('A' - c - 1);
		return c;
	}
	if (c >= 'a' && c <= 'z')
	{
		c = c + (shift % ENG);
		if (c > 'z') c = 'a' + (c - 'z' - 1);
		else if (c < 'a') c = 'z' - ('a' - c - 1);
		return c;
	}
	if (c >= '�' && c <= '�')
	{
		c = c + (shift % RUS);
		if (c > '�') c = '�' + (c - '�' - 1);
		else if (c < '�') c = '�' - ('�' - c - 1);
		return c;
	}
	if (c >= '�' && c <= '�')
	{
		c = c + (shift % RUS);
		if (c > '�') c = '�' + (c - '�' - 1);
		else if (c < '�') c = '�' - ('�' - c - 1);
		return c;
	}

	return result;
}

bool CaesarCipher::encryptFile(const std::string& inputFile, const std::string& outputFile) const
{
	try {
		// ��������� ���� ��� ������
		std::ifstream inFile(inputFile);
		if (!inFile.is_open()) {
			std::cout << "������: �� ������� ������� ���� " << inputFile << std::endl;
			return false;
		}

		// ������ ��� ���������� �����
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		std::string content = buffer.str();
		inFile.close();

		// ������� ����������
		std::string encrypted = encrypt(content);

		// ���������� � �������� ����
		std::ofstream outFile(outputFile);
		if (!outFile.is_open()) {
			std::cout << "������: �� ������� ������� ���� " << outputFile << std::endl;
			return false;
		}

		outFile << encrypted;
		outFile.close();

		std::cout << "���� ������� ����������: " << outputFile << std::endl;
		return true;
	}
	catch (const std::exception& e) {
		std::cout << "������ ��� ���������� �����: " << e.what() << std::endl;
		return false;
	}
}

bool CaesarCipher::decryptFile(const std::string& inputFile, const std::string& outputFile) const
{
	try {
		// ��������� ���� ��� ������
		std::ifstream inFile(inputFile);
		if (!inFile.is_open()) {
			std::cout << "������: �� ������� ������� ���� " << inputFile << std::endl;
			return false;
		}

		// ������ ��� ���������� �����
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		std::string content = buffer.str();
		inFile.close();

		// ��������� ����������
		std::string decrypted = decrypt(content);

		// ���������� � �������� ����
		std::ofstream outFile(outputFile);
		if (!outFile.is_open()) {
			std::cout << "������: �� ������� ������� ���� " << outputFile << std::endl;
			return false;
		}

		outFile << decrypted;
		outFile.close();

		std::cout << "���� ������� �����������: " << outputFile << std::endl;
		return true;
	}
	catch (const std::exception& e) {
		std::cout << "������ ��� ������������ �����: " << e.what() << std::endl;
		return false;
	}
}

// ���������� ������� VigenereCipher

VigenereCipher::VigenereCipher(const std::string& key) : key_(key) {}

std::string VigenereCipher::encrypt(const std::string& plaintext) const
{
	std::string result;

	// �������� ���� �� ����� ������
	std::string longKey = extendKey(key_, plaintext.length());
	size_t key_index = 0;

	for (char c : plaintext) {
		// �������� ������� ������ ����������� �����
		char key_char = longKey[key_index];

		// ��������� ����� �� ������ ��������� �������
		int shift = 0;
		if (key_char >= 'A' && key_char <= 'Z')
		{
			shift = key_char - 'A';
		}
		else if (key_char >= 'a' && key_char <= 'z')
		{
			shift = key_char - 'a';
		}
		else if (key_char >= '�' && key_char <= '�')
		{
			shift = key_char - '�';
		}
		else if (key_char >= '�' && key_char <= '�')
		{
			shift = key_char - '�';
		}

		// ��������� �����
		result += shiftChar(c, shift);
		key_index++;
	}
	return result;
}

std::string VigenereCipher::decrypt(const std::string& ciphertext) const
{
    std::string result;
    size_t key_index = 0;

    for (char c : ciphertext) {
        // �������� ������� ������ �����
        char key_char = key_[key_index % key_.length()];

        // ��������� �������� ����� ��� ������������
        int shift = 0;
        if (key_char >= 'A' && key_char <= 'Z') {
            shift = 26 - (key_char - 'A');
        }
        else if (key_char >= 'a' && key_char <= 'z') {
            shift = 26 - (key_char - 'a');
        }
		else if (key_char >= '�' && key_char <= '�') {
            // ��� ��������� ������������� ���� � Windows-1251
            shift = 32 - (key_char - '�');
        }
		else if (key_char >= '�' && key_char <= '�') {
			// ��� ��������� ������������� ���� � Windows-1251
			shift = 32 - (key_char - '�');
        }

        // ��������� �������� �����
        result += shiftChar(c, shift);
        key_index++;
    }

    return result;
}

bool VigenereCipher::encryptFile(const std::string& inputFile, const std::string& outputFile) const
{
    try {
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile.is_open()) {
            std::cout << "������: �� ������� ������� ���� " << inputFile << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string content = buffer.str();
        inFile.close();

        std::string encrypted = encrypt(content);

        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "������: �� ������� ������� ���� " << outputFile << std::endl;
            return false;
        }

        outFile << encrypted;
        outFile.close();

        std::cout << "���� ������� ����������: " << outputFile << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "������ ��� ���������� �����: " << e.what() << std::endl;
        return false;
    }
}

bool VigenereCipher::decryptFile(const std::string& inputFile, const std::string& outputFile) const
{
    try {
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile.is_open()) {
            std::cout << "������: �� ������� ������� ���� " << inputFile << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string content = buffer.str();
        inFile.close();

        std::string decrypted = decrypt(content);

        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "������: �� ������� ������� ���� " << outputFile << std::endl;
            return false;
        }

        outFile << decrypted;
        outFile.close();

        std::cout << "���� ������� �����������: " << outputFile << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "������ ��� ������������ �����: " << e.what() << std::endl;
        return false;
    }
}

std::string VigenereCipher::getKey() const
{
    return key_;
}

void VigenereCipher::setKey(const std::string& key)
{
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    key_ = key;
}

char VigenereCipher::shiftChar(char c, int shift) const
{
    // ���������� �� �� ������, ��� � � CaesarCipher
    char result = c;

	if (c >= 'A' && c <= 'Z')
	{
		c = c + (shift % ENG);
		if (c > 'Z') c = 'A' + (c - 'Z' - 1);
		else if (c < 'A') c = 'Z' - ('A' - c - 1);
		return c;
	}
	if (c >= 'a' && c <= 'z')
	{
		c = c + (shift % ENG);
		if (c > 'z') c = 'a' + (c - 'z' - 1);
		else if (c < 'a') c = 'z' - ('a' - c - 1);
		return c;
	}
	if (c >= '�' && c <= '�')
	{
		c = c + (shift % RUS);
		if (c > '�') c = '�' + (c - '�' - 1);
		else if (c < '�') c = '�' - ('�' - c - 1);
		return c;
	}
	if (c >= '�' && c <= '�')
	{
		c = c + (shift % RUS);
		if (c > '�') c = '�' + (c - '�' - 1);
		else if (c < '�') c = '�' - ('�' - c - 1);
		return c;
	}

    return result;
}

std::string VigenereCipher::extendKey(const std::string& key, size_t length) const
{
	if (key.empty()) return "A";

	std::string extended;
	extended.reserve(length); // ����������� ������ ��� �������������

	for (size_t i = 0; i < length; i++) {
		extended += key[i % key.length()];
	}

	return extended;
}