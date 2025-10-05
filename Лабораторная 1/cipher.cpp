#include "cipher.hpp"
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <fstream>
#include <sstream>

// Константы для размеров алфавитов
constexpr int ENG = 26;
constexpr int RUS = 32;

// Реализация методов CaesarCipher

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
	if (c >= 'А' && c <= 'Я')
	{
		c = c + (shift % RUS);
		if (c > 'Я') c = 'А' + (c - 'Я' - 1);
		else if (c < 'А') c = 'Я' - ('А' - c - 1);
		return c;
	}
	if (c >= 'а' && c <= 'я')
	{
		c = c + (shift % RUS);
		if (c > 'я') c = 'а' + (c - 'я' - 1);
		else if (c < 'а') c = 'я' - ('а' - c - 1);
		return c;
	}

	return result;
}

bool CaesarCipher::encryptFile(const std::string& inputFile, const std::string& outputFile) const
{
	try {
		// Открываем файл для чтения
		std::ifstream inFile(inputFile);
		if (!inFile.is_open()) {
			std::cout << "Ошибка: не удалось открыть файл " << inputFile << std::endl;
			return false;
		}

		// Читаем все содержимое файла
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		std::string content = buffer.str();
		inFile.close();

		// Шифруем содержимое
		std::string encrypted = encrypt(content);

		// Записываем в выходной файл
		std::ofstream outFile(outputFile);
		if (!outFile.is_open()) {
			std::cout << "Ошибка: не удалось создать файл " << outputFile << std::endl;
			return false;
		}

		outFile << encrypted;
		outFile.close();

		std::cout << "Файл успешно зашифрован: " << outputFile << std::endl;
		return true;
	}
	catch (const std::exception& e) {
		std::cout << "Ошибка при шифровании файла: " << e.what() << std::endl;
		return false;
	}
}

bool CaesarCipher::decryptFile(const std::string& inputFile, const std::string& outputFile) const
{
	try {
		// Открываем файл для чтения
		std::ifstream inFile(inputFile);
		if (!inFile.is_open()) {
			std::cout << "Ошибка: не удалось открыть файл " << inputFile << std::endl;
			return false;
		}

		// Читаем все содержимое файла
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		std::string content = buffer.str();
		inFile.close();

		// Дешифруем содержимое
		std::string decrypted = decrypt(content);

		// Записываем в выходной файл
		std::ofstream outFile(outputFile);
		if (!outFile.is_open()) {
			std::cout << "Ошибка: не удалось создать файл " << outputFile << std::endl;
			return false;
		}

		outFile << decrypted;
		outFile.close();

		std::cout << "Файл успешно расшифрован: " << outputFile << std::endl;
		return true;
	}
	catch (const std::exception& e) {
		std::cout << "Ошибка при дешифровании файла: " << e.what() << std::endl;
		return false;
	}
}

// Реализация методов VigenereCipher

VigenereCipher::VigenereCipher(const std::string& key) : key_(key) {}

std::string VigenereCipher::encrypt(const std::string& plaintext) const
{
	std::string result;

	// Удлиняем ключ до длины текста
	std::string longKey = extendKey(key_, plaintext.length());
	size_t key_index = 0;

	for (char c : plaintext) {
		// Получаем текущий символ удлиненного ключа
		char key_char = longKey[key_index];

		// Вычисляем сдвиг на основе ключевого символа
		int shift = 0;
		if (key_char >= 'A' && key_char <= 'Z')
		{
			shift = key_char - 'A';
		}
		else if (key_char >= 'a' && key_char <= 'z')
		{
			shift = key_char - 'a';
		}
		else if (key_char >= 'А' && key_char <= 'Я')
		{
			shift = key_char - 'А';
		}
		else if (key_char >= 'а' && key_char <= 'я')
		{
			shift = key_char - 'а';
		}

		// Применяем сдвиг
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
        // Получаем текущий символ ключа
        char key_char = key_[key_index % key_.length()];

        // Вычисляем обратный сдвиг для дешифрования
        int shift = 0;
        if (key_char >= 'A' && key_char <= 'Z') {
            shift = 26 - (key_char - 'A');
        }
        else if (key_char >= 'a' && key_char <= 'z') {
            shift = 26 - (key_char - 'a');
        }
		else if (key_char >= 'А' && key_char <= 'Я') {
            // Для заглавных кириллических букв в Windows-1251
            shift = 32 - (key_char - 'А');
        }
		else if (key_char >= 'а' && key_char <= 'я') {
			// Для заглавных кириллических букв в Windows-1251
			shift = 32 - (key_char - 'а');
        }

        // Применяем обратный сдвиг
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
            std::cout << "Ошибка: не удалось открыть файл " << inputFile << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string content = buffer.str();
        inFile.close();

        std::string encrypted = encrypt(content);

        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "Ошибка: не удалось создать файл " << outputFile << std::endl;
            return false;
        }

        outFile << encrypted;
        outFile.close();

        std::cout << "Файл успешно зашифрован: " << outputFile << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка при шифровании файла: " << e.what() << std::endl;
        return false;
    }
}

bool VigenereCipher::decryptFile(const std::string& inputFile, const std::string& outputFile) const
{
    try {
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile.is_open()) {
            std::cout << "Ошибка: не удалось открыть файл " << inputFile << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string content = buffer.str();
        inFile.close();

        std::string decrypted = decrypt(content);

        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "Ошибка: не удалось создать файл " << outputFile << std::endl;
            return false;
        }

        outFile << decrypted;
        outFile.close();

        std::cout << "Файл успешно расшифрован: " << outputFile << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка при дешифровании файла: " << e.what() << std::endl;
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
    // Используем ту же логику, что и в CaesarCipher
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
	if (c >= 'А' && c <= 'Я')
	{
		c = c + (shift % RUS);
		if (c > 'Я') c = 'А' + (c - 'Я' - 1);
		else if (c < 'А') c = 'Я' - ('А' - c - 1);
		return c;
	}
	if (c >= 'а' && c <= 'я')
	{
		c = c + (shift % RUS);
		if (c > 'я') c = 'а' + (c - 'я' - 1);
		else if (c < 'а') c = 'я' - ('а' - c - 1);
		return c;
	}

    return result;
}

std::string VigenereCipher::extendKey(const std::string& key, size_t length) const
{
	if (key.empty()) return "A";

	std::string extended;
	extended.reserve(length); // Резервируем память для эффективности

	for (size_t i = 0; i < length; i++) {
		extended += key[i % key.length()];
	}

	return extended;
}