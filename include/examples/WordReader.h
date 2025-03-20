#ifndef WORD_READER_H
#define WORD_READER_H

#include <fstream>
#include <string>
#include <random>

class WordReader {
private:
    std::ifstream file;
    std::string filename;
    std::random_device rd;
    std::mt19937 gen;

public:
    WordReader(const std::string& filePath);
    ~WordReader();

    std::string getRandomWord();
    bool isOpen() const;
};

#endif // WORD_READER_H
