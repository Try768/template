#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filename = "data.txt";

    // 1. Baca isi file
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Gagal membuka file untuk dibaca.\n";
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(inFile)),
                         std::istreambuf_iterator<char>());
    inFile.close();

    std::cout << "Isi file sebelum edit:\n" << content << "\n\n";

    // 2. Edit isi (contoh: ganti kata "Hello" menjadi "Hi")
    std::string find = "Hello";
    std::string replace = "Hi";
    size_t pos = 0;
    while ((pos = content.find(find, pos)) != std::string::npos) {
        content.replace(pos, find.length(), replace);
        pos += replace.length();
    }

    // 3. Tulis kembali ke file
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Gagal membuka file untuk ditulis.\n";
        return 1;
    }
    outFile << content;
    outFile.close();

    std::cout << "File berhasil diedit!\n";
    return 0;
}
