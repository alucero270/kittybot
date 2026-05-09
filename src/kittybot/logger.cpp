#include "kittybot/logger.hpp"

#include <stdexcept>

namespace kittybot {

Logger::Logger(std::string path) : file_(path) {
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + path);
    }
}

Logger::~Logger() {
    file_.flush();
}

Logger::Logger(Logger&& other) noexcept : file_(std::move(other.file_)) {}

Logger& Logger::operator=(Logger&& other) noexcept {
    if (this != &other) {
        file_ = std::move(other.file_);
    }
    return *this;
}

void Logger::log(std::string_view message) {
    file_ << message << std::endl;
}

LogScope::LogScope(Logger& logger, std::string_view name)
    : logger_(logger),
      name_(name) {
    logger_.log("entering " + name_);
}

LogScope::~LogScope() {
    logger_.log("exiting " + name_);
}

}