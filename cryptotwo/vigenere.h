#ifndef VIGENERE_H
#define VIGENERE_H

#include "cipher.h"
#include <string>

class VigenereCipher : public Cipher {
public:
    explicit VigenereCipher(const std::string& key);
    void setKey(const std::string& key);
    std::string getKey() const;

    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;

private:
    std::wstring wide_key;
    // Приватные методы для работы с Юникодом
    std::wstring process_text(const std::wstring& text, bool encrypt);
    wchar_t shiftChar(wchar_t ch, wchar_t key_ch, bool encrypt);
};

#endif // VIGENERE_H
