// include/kittybot/logger.hpp

#pragma once

#include <fstream>
#include <string>
#include <string_view>

namespace kittybot {

class Logger {
public:
    // Constructs a logger that writes to the given file path
    explicit Logger(std::string path);
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&& other) noexcept;
    Logger& operator=(Logger&& other) noexcept;

    void log(std::string_view message);

private:
    std::ofstream file_;
};

class LogScope {
public:
    LogScope(Logger& logger, std::string_view name);
    ~LogScope();

    LogScope(const LogScope&) = delete;
    LogScope& operator=(const LogScope&) = delete;

    LogScope(LogScope&&) = delete;
    LogScope& operator=(LogScope&&) = delete;

private:
    Logger& logger_;
    std::string name_;
};

} // namespace kittybot