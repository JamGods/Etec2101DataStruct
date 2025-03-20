#include <WordReader.h>
#include <iostream>

WordReader::WordReader(const std::string& filePath)
    : filename(filePath), gen(rd()) {
    file.open(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

WordReader::~WordReader() {
    if (file.is_open()) {
        file.close();
    }
}

bool WordReader::isOpen() const {
    return file.is_open();
}

std::string WordReader::getRandomWord() {
    if (!file.is_open()) return "";

    file.seekg(0, std::ios::end);
    std::streamoff fileSize = file.tellg(); 
    if (fileSize <= 0) return "";

    std::uniform_int_distribution<std::streamoff> dist(0, fileSize - 1);
    std::streamoff randPos = dist(gen);

    file.seekg(randPos);

    // Move backwards until we reach a newline
    while (file.tellg() > 0) {
        file.seekg(-1, std::ios::cur);
        char ch;
        file.get(ch);
        if (ch == '\n') break;
        file.seekg(-1, std::ios::cur);
    }

    // Read the next word
    std::string word;
    std::getline(file, word);
    return word;
}

