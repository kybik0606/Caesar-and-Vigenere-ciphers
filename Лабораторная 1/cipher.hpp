#ifndef CIPHERS_HPP
#define CIPHERS_HPP

#include <string>

class CaesarCipher
{
public:
    /**
     * ����������� � ��������� �����
     * @param key - �������� �����
     */
    explicit CaesarCipher(int key);

    /**
     * ���������� ������
     * @param plaintext - �������� �����
     * @return ������������� �����
     */
    std::string encrypt(const std::string& plaintext) const;

    /**
     * ������������ ������
     * @param ciphertext - ������������� �����
     * @return �������������� �����
     */
    std::string decrypt(const std::string& ciphertext) const;

    /**
     * �������� ������� ����
     */
    int getKey() const;

    /**
     * ���������� ����
     */
    void setKey(int key);

private:
    int key_;
    char shiftChar(char c, int shift) const;
};

/**
 * ����� ��� ������ � ������ ��������
 */
class VigenereCipher
{
public:
    /**
     * ����������� � ��������� ����� (������)
     * @param key - ��������� ����
     */
    explicit VigenereCipher(const std::string& key);

    /**
     * ���������� ������
     * @param plaintext - �������� �����
     * @return ������������� �����
     */
    std::string encrypt(const std::string& plaintext) const;

    /**
     * ������������ ������
     * @param ciphertext - ������������� �����
     * @return �������������� �����
     */
    std::string decrypt(const std::string& ciphertext) const;

    /**
     * �������� ������� ����
     */
    std::string getKey() const;

    /**
     * ���������� ����
     */
    void setKey(const std::string& key);

private:
    std::string key_;
    char shiftChar(char c, int shift) const;
};

#endif // CIPHERS_HPP

