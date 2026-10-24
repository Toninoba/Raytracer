//
// Created by tobi on 10.10.26.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Tokenizer.h"
#include <filesystem>

#include "ProjectPaths.h"

namespace fs = std::filesystem;

static auto test_world = fs::path(ProjectPaths::WorldDir / "test_json.json");

TEST_CASE("Creating a Tokenizer") {
    Tokenizer tokenizer(test_world);
}

TEST_CASE("Getting single characters") {

}