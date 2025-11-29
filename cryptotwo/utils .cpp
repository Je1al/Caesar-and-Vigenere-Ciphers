#include "utils.h"
#include <codecvt> // Для std::wstring_convert (хотя и deprecated, но функционально)
#include <locale>  // Для locale

using namespace std;

// Определения алфавитов как широких строк (L"...")
const wstring LATIN_LOWER = L"abcdefghijklmnopqrstuvwxyz";
const wstring LATIN_UPPER = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const wstring CYRILLIC_LOWER = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const wstring CYRILLIC_UPPER = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

// Функции конвертации UTF-8 <-> wstring
wstring utf8_to_wstring(const string& str) {
    if (str.empty()) return L"";
    // Используем static для оптимизации (инициализация один раз)
    static wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(str);
}

string wstring_to_utf8(const wstring& str) {
    if (str.empty()) return "";
    static wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(str);
}
