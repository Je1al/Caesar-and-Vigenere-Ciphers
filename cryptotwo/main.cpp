#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <memory> // Для std::unique_ptr (лучшая практика)

// Включаем исправленные заголовки
#include "caesar.h"
#include "vigenere.h"
#include "cipher.h" // Для использования базового класса

using namespace std;

// Функция очистки буфера
void clear_cin() {
    // Используем numeric_limits<streamsize>::max() из <limits>
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Чтение текста из файла
string read_from_file() {
    // ... (функция read_from_file без изменений)
    string filename, text, line;
    cout << "Введите имя файла для чтения: ";
    cin >> filename;
    ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            text += line + "\n";
        }
        file.close();
        // Удаляем последний лишний перенос строки, если он есть
        if (!text.empty() && text.back() == '\n') {
            text.pop_back();
        }
        cout << "Текст успешно прочитан из файла.\n";
    } else {
        cout << "Ошибка: не удалось открыть файл.\n";
    }
    return text;
}

// Запись текста в файл
void write_to_file(const string& text) {
    // ... (функция write_to_file без изменений)
    string filename;
    cout << "Введите имя файла для записи: ";
    cin >> filename;
    ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
        cout << "Результат успешно записан в файл " << filename << "\n";
    } else {
        cout << "Ошибка: не удалось записать в файл.\n";
    }
}

void printMenu() {
    cout << "\n*** Меню шифрования ***\n";
    cout << "1. Задать ключ\n";
    cout << "2. Показать текущий ключ\n";
    cout << "3. Зашифровать текст\n";
    cout << "4. Расшифровать текст\n";
    cout << "5. Выход\n";
    cout << "Выберите пункт: ";
}

// Обработчик шифрования, использующий полиморфизм (Cipher&)
void handle_encryption(Cipher& cipher) {
    int source_choice;
    cout << "Откуда взять текст?\n1. Ввести с консоли\n2. Прочитать из файла\nВаш выбор: ";
    if (!(cin >> source_choice)) { cin.clear(); clear_cin(); return; }
    clear_cin();

    string text;
    if (source_choice == 1) {
        cout << "Введите текст для шифрования: ";
        getline(cin, text);
    } else if (source_choice == 2) {
        text = read_from_file();
    } else {
        cout << "Неверный выбор источника.\n";
        return;
    }

    if (text.empty()) return;

    // Вызов виртуальной функции
    string result = cipher.encrypt(text);

    int dest_choice;
    cout << "Куда записать результат?\n1. Вывести в консоль\n2. Записать в файл\nВаш выбор: ";
    if (!(cin >> dest_choice)) { cin.clear(); clear_cin(); return; }
    clear_cin();

    if (dest_choice == 1) {
        cout << "Зашифрованный текст:\n" << result << endl;
    } else if (dest_choice == 2) {
        write_to_file(result);
    } else {
        cout << "Неверный выбор назначения.\n";
    }
}

// Обработчик дешифрования, использующий полиморфизм (Cipher&)
void handle_decryption(Cipher& cipher) {
    // ... (похожая логика, вызывающая cipher.decrypt(text))
    int source_choice;
    cout << "Откуда взять текст?\n1. Ввести с консоли\n2. Прочитать из файла\nВаш выбор: ";
    if (!(cin >> source_choice)) { cin.clear(); clear_cin(); return; }
    clear_cin();

    string text;
    if (source_choice == 1) {
        cout << "Введите текст для дешифрования: ";
        getline(cin, text);
    } else if (source_choice == 2) {
        text = read_from_file();
    } else {
        cout << "Неверный выбор источника.\n";
        return;
    }

    if (text.empty()) return;

    // Вызов виртуальной функции
    string result = cipher.decrypt(text);

    int dest_choice;
    cout << "Куда записать результат?\n1. Вывести в консоль\n2. Записать в файл\nВаш выбор: ";
    if (!(cin >> dest_choice)) { cin.clear(); clear_cin(); return; }
    clear_cin();

    if (dest_choice == 1) {
        cout << "Расшифрованный текст:\n" << result << endl;
    } else if (dest_choice == 2) {
        write_to_file(result);
    } else {
        cout << "Неверный выбор назначения.\n";
    }
}


int main() {
    // Инициализация шифров
    CaesarCipher caesar(3);
    VigenereCipher vigenere("секрет");

    int choice = 0;
    while (choice != 5) {
        printMenu();
        if (!(cin >> choice)) { // Читаем выбор и проверяем на ошибку
            cout << "Ошибка: введите число.\n";
            cin.clear();
            clear_cin();
            continue;
        }
        clear_cin();

        int cipher_choice = 0;
        
        switch (choice) {
            case 1: { // Задать ключ
                cout << "Выберите шифр:\n1. Цезарь\n2. Виженер\nВаш выбор: ";
                if (!(cin >> cipher_choice)) break;
                clear_cin();

                if (cipher_choice == 1) {
                    int k;
                    cout << "Введите новый сдвиг (число): ";
                    if (!(cin >> k)) { break; }
                    clear_cin();
                    caesar.setKey(k);
                } else if (cipher_choice == 2) {
                    string k;
                    cout << "Введите новый ключ (слово): ";
                    getline(cin, k);
                    vigenere.setKey(k);
                }
                break;
            }
            case 2: { // Показать ключ
                cout << "Ключ для шифра Цезаря: " << caesar.getKey() << endl;
                cout << "Ключ для шифра Виженера: " << vigenere.getKey() << endl;
                break;
            }
            case 3:
            case 4: { // Шифрование / Дешифрование
                cout << "Выберите шифр:\n1. Цезарь\n2. Виженер\nВаш выбор: ";
                if (!(cin >> cipher_choice)) break;
                clear_cin();

                if (cipher_choice == 1) {
                    if (choice == 3) handle_encryption(caesar);
                    else handle_decryption(caesar);
                } else if (cipher_choice == 2) {
                    if (choice == 3) handle_encryption(vigenere);
                    else handle_decryption(vigenere);
                }
                break;
            }
            case 5:
                cout << "Выход.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    }

    return 0;
}
