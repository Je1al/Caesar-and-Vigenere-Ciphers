#include "vigenere.h"
#include "utils.h"

using namespace std;

VigenereCipher::VigenereCipher(const string& key) { setKey(key); }

void VigenereCipher::setKey(const string& new_key) {
    wstring temp_key = utf8_to_wstring(new_key);
    wide_key.clear();
    // Фильтрация: берем только буквы и приводим ключ к нижнему регистру
    for (wchar_t wc : temp_key) {
        if (LATIN_LOWER.find(wc) != wstring::npos) wide_key += wc;
        else if (LATIN_UPPER.find(wc) != wstring::npos) wide_key += towlower(wc);
        else if (CYRILLIC_LOWER.find(wc) != wstring::npos) wide_key += wc;
        else if (CYRILLIC_UPPER.find(wc) != wstring::npos) wide_key += towlower(wc);
    }
    // Защита от пустого ключа
    if (wide_key.empty()) wide_key = L"а"; // Используем кириллический символ по умолчанию
}

string VigenereCipher::getKey() const { return wstring_to_utf8(wide_key); }

wchar_t VigenereCipher::shiftChar(wchar_t ch, wchar_t key_ch, bool encrypt) {
    int shift = 0;
    size_t pos;

    // 1. Определяем сдвиг на основе символа ключа
    if ((pos = LATIN_LOWER.find(key_ch)) != wstring::npos) shift = pos;
    else if ((pos = CYRILLIC_LOWER.find(key_ch)) != wstring::npos) shift = pos;
    if (!encrypt) shift = -shift;

    // 2. Применяем сдвиг к символу текста
    #define VIGENERE_SHIFT(ALPHABET) \
        int n = ALPHABET.size(); \
        return ALPHABET[(pos + shift + n) % n];

    if ((pos = LATIN_LOWER.find(ch)) != wstring::npos) { VIGENERE_SHIFT(LATIN_LOWER); }
    if ((pos = LATIN_UPPER.find(ch)) != wstring::npos) { VIGENERE_SHIFT(LATIN_UPPER); }
    if ((pos = CYRILLIC_LOWER.find(ch)) != wstring::npos) { VIGENERE_SHIFT(CYRILLIC_LOWER); }
    if ((pos = CYRILLIC_UPPER.find(ch)) != wstring::npos) { VIGENERE_SHIFT(CYRILLIC_UPPER); }

    #undef VIGENERE_SHIFT
    return ch;
}

wstring VigenereCipher::process_text(const wstring& text, bool encrypt) {
    wstring result;
    size_t key_index = 0;
    if (wide_key.empty()) return text;

    for (wchar_t wc : text) {
        // Циклический выбор символа ключа
        wchar_t shifted = shiftChar(wc, wide_key[key_index % wide_key.size()], encrypt);
        
        // Ключ продвигается только если символ был зашифрован (не пробел, не знак)
        if (shifted != wc) key_index++;
        result += shifted;
    }
    return result;
}

// Публичный интерфейс
string VigenereCipher::encrypt(const string& text) {
    return wstring_to_utf8(process_text(utf8_to_wstring(text), true));
}
string VigenereCipher::decrypt(const string& text) {
    return wstring_to_utf8(process_text(utf8_to_wstring(text), false));
}
