#pragma once

#include <functional>
#include <utility>

namespace kittybot {

/// RAII scope guard. Runs a callable unconditionally on destruction.
///
/// Use make_scope_guard() to create one — the [[nodiscard]] return type
/// forces binding to a named variable, which is the only correct usage.
///
/// Example:
///   auto guard = make_scope_guard([&] { cleanup(); });
///   // ... do work that might throw ...
///   guard.disarm();  // commit: prevent cleanup on success path
class ScopeGuard {
   public:
    explicit ScopeGuard(std::function<void()> fn) : fn_{std::move(fn)} {}

    ~ScopeGuard() {
        if (active_)
            fn_();
    }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    ScopeGuard(ScopeGuard&& o) noexcept : fn_{std::move(o.fn_)}, active_{o.active_} {
        o.active_ = false;
    }
    ScopeGuard& operator=(ScopeGuard&&) = delete;

    /// Prevent the cleanup action from running on destruction.
    void disarm() noexcept { active_ = false; }

   private:
    std::function<void()> fn_;
    bool active_ = true;
};

/// Factory for ScopeGuard. [[nodiscard]]: discarding the return value is a bug —
/// the guard fires immediately and never runs at scope exit.
template <typename Fn>
[[nodiscard]] ScopeGuard make_scope_guard(Fn&& fn) {
    return ScopeGuard{std::forward<Fn>(fn)};
}

}  // namespace kittybot
