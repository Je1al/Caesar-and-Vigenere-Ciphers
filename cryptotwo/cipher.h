#ifndef CIPHER_H
#define CIPHER_H

#include <string>

/**
 * @brief Абстрактный базовый класс для всех шифров.
 * Определяет общий интерфейс.
 */
class Cipher {
public:
    /** @brief Виртуальный деструктор. */
    virtual ~Cipher() = default;

    /** @brief Чистая виртуальная функция для шифрования. */
    virtual std::string encrypt(const std::string& text) = 0;

    /** @brief Чистая виртуальная функция для дешифрования. */
    virtual std::string decrypt(const std::string& text) = 0;
};

#endif // CIPHER_H
