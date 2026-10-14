//
// Created by tobi on 10.10.26.
//

#include "Tokenizer.h"
#include <filesystem>
#include "ProjectPaths.h"


int main() {

    namespace fs = std::filesystem;

    auto test_world = fs::path(ProjectPaths::WorldDir / "test_json.json");

    Tokenizer tokenizer(test_world);

    std::cout << tokenizer.isEOF() << std::endl;

    int c;
    while ((c = tokenizer.getChar()) != std::char_traits<char>::eof()) {
        std::cout << static_cast<char>(c);
    }

    std::cout << tokenizer.isEOF() << std::endl;

}
