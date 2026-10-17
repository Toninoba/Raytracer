//
// Created by tobi on 10.10.26.
//

#include "Tokenizer.h"
#include <filesystem>
#include "ProjectPaths.h"
#include <stdexcept>



Token Tokenizer::nextToken() {

    Token token;


    int nextChar = peekChar();

    while (nextChar != EOF &&
           std::isspace(static_cast<unsigned char>(nextChar))) {
        getChar();
        nextChar = peekChar();
           }

    if (nextChar == std::char_traits<char>::eof()) {
        token.type = TokenType::EndOfFile;
        return token;
    }

    auto c = static_cast<unsigned char>(nextChar);

    switch (c) {
        case '{':
            token.type = TokenType::BraceL;
            token.value = static_cast<char>(getChar());
            break;
        case '}':
            token.type = TokenType::BraceR;
            token.value = static_cast<char>(getChar());
            break;
        case '[':
            token.type = TokenType::BracketL;
            token.value = static_cast<char>(getChar());
            break;
        case ']':
            token.type = TokenType::BracketR;
            token.value = static_cast<char>(getChar());
            break;
        case ',':
            token.type = TokenType::Comma;
            token.value = static_cast<char>(getChar());
            break;
        case ':':
            token.type = TokenType::Colon;
            token.value = static_cast<char>(getChar());
            break;

        default:
            if (c == 'f') {
                if (matchLiteral("false")) {
                    token.type = TokenType::Boolean;
                    token.value = "false";
                }
                else {
                    throw std::runtime_error("Invalid JSON literal");
                }

            }
            else if (c == 't') {
                if (matchLiteral("true")) {
                    token.type = TokenType::Boolean;
                    token.value = "true";
                }
                else {
                    throw std::runtime_error("Invalid JSON literal");
                }
            }
            else if (c == 'n') {
                if (matchLiteral("null")) {
                    token.type = TokenType::Null;
                    token.value = "null";
                }
                else {
                    throw std::runtime_error("Invalid JSON literal");
                }
            }
            else if (c == '"') {
                // check for string
                token.type = TokenType::String;
                token.value = readString();
            }
            else {
                token.type = TokenType::Number;
                token.value = readNumber();
            }

    }



    return token;
}

bool Tokenizer::matchLiteral(const std::string &literal) {
    for (const char expected : literal) {
        if (getChar() != expected) {
            return false;
        }
    }
    return true;
}

std::string Tokenizer::readString() {
    std::string output;

    // consume opening "
    getChar();

    while (true) {
        int nextChar = getChar();

        if (nextChar == EOF) {
            throw std::runtime_error("Unterminated JSON string");
        }

        if (nextChar == '"') {
            return output;
        }

        if (nextChar == '\\') {
            throw std::runtime_error("Escape sequences not implemented");
        }

        output += static_cast<char>(nextChar);
    }
}

std::string Tokenizer::readNumber() {
    std::string output;

    if (peekChar() == '-') {
        output += static_cast<char>(getChar());
    }

    if (peekChar() == '0') {
        output += static_cast<char>(getChar());

        if (std::isdigit(peekChar())) {
            throw std::runtime_error("Leading zeros are not allowed");
        }
    }
    else if (peekChar() >= '1' && peekChar() <= '9') {
        while (std::isdigit(peekChar())) {
            output += static_cast<char>(getChar());
        }
    }
    else {
        throw std::runtime_error("Invalid JSON number");
    }

    if (peekChar() == '.') {
        output += static_cast<char>(getChar());

        if (!std::isdigit(peekChar())) {
            throw std::runtime_error("Missing digits after decimal point");
        }

        while (std::isdigit(peekChar())) {
            output += static_cast<char>(getChar());
        }
    }

    if (peekChar() == 'e' || peekChar() == 'E') {
        output += static_cast<char>(getChar());

        if (peekChar() == '+' || peekChar() == '-') {
            output += static_cast<char>(getChar());
        }

        if (!std::isdigit(peekChar())) {
            throw std::runtime_error("Missing exponent digits");
        }

        while (std::isdigit(peekChar())) {
            output += static_cast<char>(getChar());
        }
    }

    return output;
}

int main() {

    namespace fs = std::filesystem;

    auto test_world = fs::path(ProjectPaths::WorldDir / "test_json.json");

    Tokenizer tokenizer(test_world);

    std::cout << tokenizer.isEOF() << std::endl;

    Token t = tokenizer.nextToken();

    while (t.type != TokenType::EndOfFile) {
        t.print();
        t = tokenizer.nextToken();


    }



}
