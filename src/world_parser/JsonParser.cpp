//
// Created by tobi on 10.10.26.
//

#include "JsonParser.h"


void JsonParser::parse() {
    parseRoot();
}

void JsonParser::parseRoot() {
    Token currentToken = _tokenizer.nextToken();

    switch (currentToken.type) {
        case TokenType::BraceL:
            parseObject();
            break;
        case TokenType::BracketL:
            parseArray();
            break;
        case TokenType::String:
        case TokenType::Number:
        case TokenType::Boolean:
        case TokenType::Null:
            // create value directly, will be implemented later on
            break;
        default:
            throw std::runtime_error("Failed while parsing JSON");
    }
}

void JsonParser::parseObject() {

    Token token = _tokenizer.nextToken();

    while (token.type != TokenType::BraceR) {

        if (token.type == TokenType::String) {
            token = _tokenizer.nextToken();
            if (token.type != TokenType::Colon) {
                throw std::runtime_error("Failed while parsing JSON");
            }
            token = _tokenizer.nextToken();
            parseValue(token);
        }
        else {
            throw std::runtime_error("Failed while parsing JSON");
        }
        token = _tokenizer.nextToken();
        if (token.type == TokenType::Comma) token = _tokenizer.nextToken();
    }
}

void JsonParser::parseValue(Token token) {

    switch (token.type) {
        case TokenType::BraceL:
            parseObject();
            break;
        case TokenType::BracketL:
            parseArray();
        case TokenType::String:
            break;
        case TokenType::Number:
            break;
        case TokenType::Boolean:
            break;
        case TokenType::Null:
            break;
        default:
            throw std::runtime_error("Failed while parsing JSON");
    }
}

void JsonParser::parseArray() {

    Token token = _tokenizer.nextToken();

    while (token.type != TokenType::BracketR) {
        parseValue(token);
        token = _tokenizer.nextToken();
        if (token.type == TokenType::Comma) token = _tokenizer.nextToken();
    }

}
