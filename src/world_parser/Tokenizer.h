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
    TokenType type = TokenType::EndOfFile;
    std::string value;

    void print() const {
        std::cout << "Token { type: ";

        switch (type) {
            case TokenType::BraceL:    std::cout << "BraceL"; break;
            case TokenType::BraceR:    std::cout << "BraceR"; break;
            case TokenType::BracketL:  std::cout << "BracketL"; break;
            case TokenType::BracketR:  std::cout << "BracketR"; break;
            case TokenType::Comma:     std::cout << "Comma"; break;
            case TokenType::Colon:     std::cout << "Colon"; break;
            case TokenType::Whitespace:std::cout << "Whitespace"; break;
            case TokenType::String:    std::cout << "String"; break;
            case TokenType::Boolean:   std::cout << "Boolean"; break;
            case TokenType::Number:    std::cout << "Number"; break;
            case TokenType::Null:      std::cout << "Null"; break;
            case TokenType::EndOfFile: std::cout << "EndOfFile"; break;
        }

        std::cout << ", value: \"" << value << "\" }\n";
    }

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

    Token nextToken();

    bool matchLiteral(const std::string& literal);

    std::string readString();
    std::string readNumber();




private:

    std::ifstream _jsonFile;


};


#endif //RAYTRACER_TOKENIZER_H
