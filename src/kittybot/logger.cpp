#include "kittybot/logger.hpp"

#include <chrono>
#include <format>
#include <iostream>
#include <stdexcept>

namespace kittybot {

Logger::Logger(Config cfg) : cfg_{std::move(cfg)} {
    if (!cfg_.log_file.empty()) {
        file_.open(cfg_.log_file, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error{
                std::format("Logger: cannot open log file '{}'", cfg_.log_file.string())};
        }
    }
}

Logger::~Logger() {
    if (file_.is_open()) {
        file_.flush();
    }
}

void Logger::log(LogLevel level, std::string_view message) {
    if (level < cfg_.min_level)
        return;

    auto line = std::format("[{}] [{}] {}\n", timestamp_now(), level_str(level), message);

    std::lock_guard lock{mu_};
    if (cfg_.stdout_enabled) {
        std::cout << line;
    }
    if (file_.is_open()) {
        file_ << line;
    }
}

std::string_view Logger::level_str(LogLevel l) noexcept {
    switch (l) {
        case LogLevel::Debug:
            return "DEBUG";
        case LogLevel::Info:
            return "INFO ";
        case LogLevel::Warn:
            return "WARN ";
        case LogLevel::Error:
            return "ERROR";
    }
    return "";  // unreachable — all enum values covered above
}

std::string Logger::timestamp_now() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto dp = floor<days>(now);
    year_month_day ymd{dp};
    auto tod = now - dp;
    auto h = duration_cast<hours>(tod);
    auto m = duration_cast<minutes>(tod - h);
    auto s = duration_cast<seconds>(tod - h - m);
    auto ms = duration_cast<milliseconds>(tod - h - m - s);

    return std::format("{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}.{:03d}",
                       static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()),
                       static_cast<unsigned>(ymd.day()), h.count(), m.count(), s.count(),
                       ms.count());
}

}  // namespace kittybot
