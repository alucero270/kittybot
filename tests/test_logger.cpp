#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <format>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

#include "kittybot/logger.hpp"
#include "kittybot/scope_guard.hpp"

namespace fs = std::filesystem;

// ─── helpers ──────────────────────────────────────────────────────────────────

static std::string read_file(const fs::path& p) {
    std::ifstream f{p};
    return {std::istreambuf_iterator<char>{f}, {}};
}

// ─── ScopeGuard ───────────────────────────────────────────────────────────────

TEST_CASE("ScopeGuard: runs cleanup on scope exit", "[scope_guard]") {
    bool ran = false;
    {
        auto guard = kittybot::make_scope_guard([&ran] { ran = true; });
        CHECK(!ran);
    }
    CHECK(ran);
}

TEST_CASE("ScopeGuard: disarm prevents cleanup", "[scope_guard]") {
    bool ran = false;
    {
        auto guard = kittybot::make_scope_guard([&ran] { ran = true; });
        guard.disarm();
    }
    CHECK(!ran);
}

// ─── Logger ───────────────────────────────────────────────────────────────────

TEST_CASE("Logger: RAII - file created on construction, flushed on destruction", "[logger]") {
    auto tmp = fs::temp_directory_path() / "kb_test_raii.log";
    auto cleanup = kittybot::make_scope_guard([&] { fs::remove(tmp); });

    {
        kittybot::Logger logger{{
            .min_level = kittybot::LogLevel::Debug,
            .stdout_enabled = false,
            .log_file = tmp,
        }};
        CHECK(fs::exists(tmp));
        logger.info("hello raii");
    }  // RAII: logger destroyed here, file flushed and closed

    CHECK(read_file(tmp).find("hello raii") != std::string::npos);
}

TEST_CASE("Logger: messages below min_level are suppressed", "[logger]") {
    auto tmp = fs::temp_directory_path() / "kb_test_filter.log";
    auto cleanup = kittybot::make_scope_guard([&] { fs::remove(tmp); });

    {
        kittybot::Logger logger{{
            .min_level = kittybot::LogLevel::Warn,
            .stdout_enabled = false,
            .log_file = tmp,
        }};
        logger.debug("suppressed");
        logger.info("suppressed");
        logger.warn("visible");
        logger.error("visible");
    }

    auto contents = read_file(tmp);
    CHECK(contents.find("suppressed") == std::string::npos);
    CHECK(contents.find("visible") != std::string::npos);
}

TEST_CASE("Logger: all log levels produce distinct tags", "[logger]") {
    auto tmp = fs::temp_directory_path() / "kb_test_levels.log";
    auto cleanup = kittybot::make_scope_guard([&] { fs::remove(tmp); });

    {
        kittybot::Logger logger{{
            .min_level = kittybot::LogLevel::Debug,
            .stdout_enabled = false,
            .log_file = tmp,
        }};
        logger.debug("d");
        logger.info("i");
        logger.warn("w");
        logger.error("e");
    }

    auto contents = read_file(tmp);
    CHECK(contents.find("DEBUG") != std::string::npos);
    CHECK(contents.find("INFO") != std::string::npos);
    CHECK(contents.find("WARN") != std::string::npos);
    CHECK(contents.find("ERROR") != std::string::npos);
}

TEST_CASE("Logger: stdout-only mode does not throw", "[logger]") {
    CHECK_NOTHROW([] {
        kittybot::Logger logger{{
            .min_level = kittybot::LogLevel::Info,
            .stdout_enabled = false,
            .log_file = {},
        }};
        logger.info("no file, no problem");
    }());
}

TEST_CASE("Logger: thread-safe under concurrent writes", "[logger]") {
    auto tmp = fs::temp_directory_path() / "kb_test_threads.log";
    auto cleanup = kittybot::make_scope_guard([&] { fs::remove(tmp); });

    constexpr int kThreads = 8;
    constexpr int kMsgs = 50;

    {
        kittybot::Logger logger{{
            .min_level = kittybot::LogLevel::Debug,
            .stdout_enabled = false,
            .log_file = tmp,
        }};

        std::vector<std::jthread> threads;
        threads.reserve(kThreads);
        for (int t = 0; t < kThreads; ++t) {
            threads.emplace_back([&logger, t] {
                for (int i = 0; i < kMsgs; ++i) {
                    logger.info(std::format("t{} msg{}", t, i));
                }
            });
        }
        // std::jthread joins on destruction — RAII, no explicit join needed
    }

    int lines = 0;
    std::string line;
    std::ifstream f{tmp};
    while (std::getline(f, line))
        ++lines;
    CHECK(lines == kThreads * kMsgs);
}
