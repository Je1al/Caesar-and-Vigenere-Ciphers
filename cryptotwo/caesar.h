#ifndef CAESAR_H
#define CAESAR_H

#include "cipher.h"
#include <string>

class CaesarCipher : public Cipher {
public:
    explicit CaesarCipher(int key = 3);
    void setKey(int key);
    int getKey() const;

    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;

private:
    int key;
    // Приватные методы для работы с Юникодом
    std::wstring process_text(const std::wstring& text, bool encrypt);
    wchar_t shiftChar(wchar_t ch, int shift);
};

#endif // CAESAR_H
