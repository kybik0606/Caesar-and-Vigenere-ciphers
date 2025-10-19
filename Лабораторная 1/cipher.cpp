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
	std::string longKey = extendKey(key_, plaintext.size());

	for (size_t i = 0; i < plaintext.size(); ++i) {
		unsigned char k = static_cast<unsigned char>(longKey[i]);
		int shift = 0;

		if (k >= 'A' && k <= 'Z') shift = k - 'A';
		else if (k >= 'a' && k <= 'z') shift = k - 'a';
		else if (k >= '�' && k <= '�') shift = k - '�';
		else if (k >= '�' && k <= '�') shift = k - '�';

		result += shiftChar(plaintext[i], shift);
	}
	return result;
}

std::string VigenereCipher::decrypt(const std::string& ciphertext) const
{
	std::string result;
	std::string longKey = extendKey(key_, ciphertext.size());

	for (size_t i = 0; i < ciphertext.size(); ++i) {
		unsigned char k = static_cast<unsigned char>(longKey[i]);
		int shift = 0;

		if (k >= 'A' && k <= 'Z') shift = k - 'A';
		else if (k >= 'a' && k <= 'z') shift = k - 'a';
		else if (k >= '�' && k <= '�') shift = k - '�';
		else if (k >= '�' && k <= '�') shift = k - '�';

		result += shiftChar(ciphertext[i], -shift);
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
	unsigned char uc = static_cast<unsigned char>(c);

	if (uc >= 'A' && uc <= 'Z') return 'A' + (uc - 'A' + shift + ENG) % ENG;
	if (uc >= 'a' && uc <= 'z') return 'a' + (uc - 'a' + shift + ENG) % ENG;

	if (uc >= CYR_A && uc <= CYR_YA) return CYR_A + (uc - CYR_A + shift + RUS) % RUS;
	if (uc >= CYR_a && uc <= CYR_ya) return CYR_a + (uc - CYR_a + shift + RUS) % RUS;

	return c;
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