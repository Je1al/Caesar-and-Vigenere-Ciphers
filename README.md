# Caesar & Vigenère Ciphers (C++)

Classical **Caesar** and **Vigenère** ciphers implemented in C++ with a small
object-oriented design and Unicode (wide-character) support, driven by an
interactive console menu.

## Design

- **`Cipher`** (`cipher.h`) — an abstract base class declaring
  `encrypt()` / `decrypt()`.
- **`CaesarCipher`** (`caesar.{h,cpp}`) — shift cipher with a configurable integer key.
- **`VigenereCipher`** (`vigenere.{h,cpp}`) — keyword-based polyalphabetic cipher.
- Both work over `std::wstring` / `wchar_t`, so text outside plain ASCII is handled.
- `main.cpp` provides the menu: enter text directly or read it from a file, then
  encrypt / decrypt and optionally write the result back to a file.

## Build & run

The repository includes an Xcode project (`cryptotwo.xcodeproj`), but the sources
compile with any C++ toolchain:

```bash
cd cryptotwo
c++ -std=c++17 main.cpp caesar.cpp vigenere.cpp "utils .cpp" -o ciphers
./ciphers
```

## Scope & limitations

These are **classical ciphers built for learning** how substitution and
polyalphabetic schemes work — they are trivially broken (frequency analysis,
Kasiski examination) and **must not be used to protect real data**.
