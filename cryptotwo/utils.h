#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cwctype> // Для towlower

/** @brief Глобальные константы для алфавитов (широкие строки, wchar_t). */
extern const std::wstring LATIN_LOWER;
extern const std::wstring LATIN_UPPER;
extern const std::wstring CYRILLIC_LOWER;
extern const std::wstring CYRILLIC_UPPER;

/**
 * @brief Преобразует строку UTF-8 (std::string) в строку широких символов (std::wstring).
 */
std::wstring utf8_to_wstring(const std::string& str);

/**
 * @brief Преобразует строку широких символов (std::wstring) в строку UTF-8 (std::string).
 */
std::string wstring_to_utf8(const std::wstring& str);

#endif // UTILS_H
