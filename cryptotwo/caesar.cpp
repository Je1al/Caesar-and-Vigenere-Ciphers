#include "caesar.h"
#include "utils.h"

using namespace std;

CaesarCipher::CaesarCipher(int key) { setKey(key); }
void CaesarCipher::setKey(int key) { this->key = key; }
int CaesarCipher::getKey() const { return key; }

wchar_t CaesarCipher::shiftChar(wchar_t ch, int shift) {
    size_t pos;
    // Логика Цезаря, использующая модульную арифметику
    // (работает для положительного и отрицательного сдвига)
    #define SHIFT_LOGIC(ALPHABET) \
        int n = ALPHABET.size(); \
        return ALPHABET[(pos + (shift % n) + n) % n];

    if ((pos = LATIN_LOWER.find(ch)) != wstring::npos) { SHIFT_LOGIC(LATIN_LOWER); }
    if ((pos = LATIN_UPPER.find(ch)) != wstring::npos) { SHIFT_LOGIC(LATIN_UPPER); }
    if ((pos = CYRILLIC_LOWER.find(ch)) != wstring::npos) { SHIFT_LOGIC(CYRILLIC_LOWER); }
    if ((pos = CYRILLIC_UPPER.find(ch)) != wstring::npos) { SHIFT_LOGIC(CYRILLIC_UPPER); }

    #undef SHIFT_LOGIC
    return ch;
}

wstring CaesarCipher::process_text(const wstring& text, bool encrypt) {
    wstring result;
    int shift = encrypt ? key : -key;
    for (wchar_t wc : text) {
        result += shiftChar(wc, shift);
    }
    return result;
}

// Публичный интерфейс: конвертация string(UTF-8) -> wstring, обработка, wstring -> string(UTF-8)
string CaesarCipher::encrypt(const string& text) {
    return wstring_to_utf8(process_text(utf8_to_wstring(text), true));
}
string CaesarCipher::decrypt(const string& text) {
    return wstring_to_utf8(process_text(utf8_to_wstring(text), false));
}
