#include "kittybot/logger.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

int main() {
    const std::string path = "test_logger_output.log";
    {
        kittybot::Logger logger(path);
        logger.log("Hello, KittyBot!");
    }

    std::ifstream input(path);
    std::string line;
    std::getline(input, line);

    if (line != "Hello, KittyBot!") {
        std::cerr << "Expected 'Hello, KittyBot!' but got '" << line << "'" << std::endl;
        return 1;
    }

    const std::string scope_path = "test_log_scope_output.log";

    try {
        kittybot::Logger logger(scope_path);
        kittybot::LogScope scope(logger, "danger-zone");

        throw std::runtime_error("simulated failure");
    } catch (const std::runtime_error&) {
        // Expected for this test.
    }

    std::ifstream scope_input(scope_path);

    std::string first_line;
    std::string second_line;

    std::getline(scope_input, first_line);
    std::getline(scope_input, second_line);

    if (first_line != "entering danger-zone") {
        std::cerr << "Expected 'entering danger-zone' but got '" << first_line << "'\n";
        return 1;
    }

    if (second_line != "exiting danger-zone") {
        std::cerr << "Expected 'exiting danger-zone' but got '" << second_line << "'\n";
        return 1;
    }

    return 0;
}