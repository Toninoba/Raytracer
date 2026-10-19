//
// Created by tobi on 10.10.26.
//

#ifndef RAYTRACER_JSONPARSER_H
#define RAYTRACER_JSONPARSER_H

#include <string>

#include "Tokenizer.h"

class JsonParser {

public:

    explicit JsonParser(const std::string& filepath) : _tokenizer(filepath){}

    void parse();


private:

    void parseRoot();
    void parseObject();
    void parseValue(Token token);
    void parseArray();

    Tokenizer _tokenizer;




};


#endif //RAYTRACER_JSONPARSER_H
