//
// Created by tobi on 10.10.26.
//

#include "JsonParser.h"

#include "JsonValue.h"


JsonValue JsonParser::parse() {
    return parseRoot();
}

JsonValue JsonParser::parseRoot() {
    Token currentToken = _tokenizer.nextToken();

    switch (currentToken.type) {
        case TokenType::BraceL:
            return parseObject();

        case TokenType::BracketL:
            return parseArray();

        case TokenType::String:
            return JsonValue(currentToken.value);

        case TokenType::Number:
            return JsonValue(std::stof(currentToken.value));

        case TokenType::Boolean:
            return JsonValue(currentToken.value == "true");

        case TokenType::Null:
            return JsonValue(nullptr);

        default:
            throw std::runtime_error("Failed while parsing JSON root element");
    }
}

JsonValue JsonParser::parseObject() {

    JsonValue obj = JsonValue::createObject();

    Token token = _tokenizer.nextToken();

    while (token.type != TokenType::BraceR) {

        if (token.type == TokenType::String) {
            std::string key = token.value;

            token = _tokenizer.nextToken();
            if (token.type != TokenType::Colon) {
                throw std::runtime_error("Failed while parsing JSON");
            }
            token = _tokenizer.nextToken();
            JsonValue childValue = parseValue(token);

            obj.set(key, childValue);
        }
        else {
            throw std::runtime_error("Failed while parsing JSON");
        }
        token = _tokenizer.nextToken();
        if (token.type == TokenType::Comma) token = _tokenizer.nextToken();
    }

    return obj;
}

JsonValue JsonParser::parseValue(Token token) {

    switch (token.type) {
        case TokenType::BraceL:
            return parseObject();

        case TokenType::BracketL:
            return parseArray();
        case TokenType::String:
            return JsonValue(token.value);

        case TokenType::Number:
            return JsonValue(std::stof(token.value));

        case TokenType::Boolean:
            return JsonValue(token.value == "true");

        case TokenType::Null:
            return JsonValue(nullptr);
        default:
            throw std::runtime_error("Failed while parsing JSON");
    }
}

JsonValue JsonParser::parseArray() {

    JsonValue arr = JsonValue::createArray();

    Token token = _tokenizer.nextToken();

    while (token.type != TokenType::BracketR) {
        JsonValue element = parseValue(token);
        arr.push_back(element);

        token = _tokenizer.nextToken();
        if (token.type == TokenType::Comma) token = _tokenizer.nextToken();
    }

    return arr;
}
