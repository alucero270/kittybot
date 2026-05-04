#pragma once

#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
#include <string_view>

namespace kittybot {

enum class LogLevel { Debug = 0, Info = 1, Warn = 2, Error = 3 };

/// Thread-safe logger with RAII file management.
///
/// Writes structured lines to stdout and/or a log file:
///   [YYYY-MM-DD HH:MM:SS.mmm] [LEVEL] message
///
/// The log file is opened in the constructor and flushed+closed in the
/// destructor — no explicit teardown required.
///
/// Non-copyable, non-movable (holds a std::mutex).
class Logger {
   public:
    struct Config {
        LogLevel min_level = LogLevel::Info;
        bool stdout_enabled = true;
        std::filesystem::path log_file{};  ///< Empty = no file output.
    };

    explicit Logger(Config cfg);
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    void log(LogLevel level, std::string_view message);

    void debug(std::string_view msg) { log(LogLevel::Debug, msg); }
    void info(std::string_view msg) { log(LogLevel::Info, msg); }
    void warn(std::string_view msg) { log(LogLevel::Warn, msg); }
    void error(std::string_view msg) { log(LogLevel::Error, msg); }

   private:
    Config cfg_;
    std::ofstream file_;
    std::mutex mu_;

    static std::string_view level_str(LogLevel l) noexcept;
    static std::string timestamp_now();
};

}  // namespace kittybot
