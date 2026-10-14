//
// Created by tobi on 10.10.26.
//

#ifndef RAYTRACER_TOKENIZER_H
#define RAYTRACER_TOKENIZER_H

#include <iostream>
#include <fstream>

enum class TokenType {
    BraceL,
    BraceR,
    BracketL,
    BracketR,
    Comma,
    Colon,
    Whitespace,
    String,
    Boolean,
    Number,
    Null,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
public:


    explicit Tokenizer(const std::string& filepath) {
        _jsonFile = std::ifstream(filepath);
    }

    int getChar() {
        const int c = _jsonFile.get();
        return c;
    }

    int peekChar() {
        const int c = _jsonFile.peek();
        return c;
    }

    bool isEOF() const {
        return _jsonFile.eof();
    }

    void skipWhiteSpace();

    Token nextToken();

    std::string readString();

    std::string readNumber();

    std::string readLiteral();


private:

    std::ifstream _jsonFile;


};


#endif //RAYTRACER_TOKENIZER_H
