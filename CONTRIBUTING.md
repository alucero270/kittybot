# Contributing to KittyBot

## Branching

- One branch per issue: `feat/<scope>`, `fix/<scope>`, `chore/<scope>`, `docs/<scope>`
- Branch from `main`, PR back to `main`
- No direct pushes to `main`

## Commit Format

[Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <short summary>

[optional body]
```

Types: `feat`, `fix`, `chore`, `docs`, `test`, `refactor`, `ci`
Breaking changes: append `!` to the type (e.g. `feat!:`)

## Pull Requests

- Fill out the PR template
- CI must be green before merge
- Self-review before requesting review

## CI

Two required checks:

| Job | What it does |
|-----|-------------|
| `build` | CMake configure → build → `ctest` |
| `format` | `clang-format --dry-run --Werror` on all `.cpp`/`.hpp` |

Run locally before pushing:

```bash
# Build and test
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure

# Format check (dry run)
find . -name "*.cpp" -o -name "*.hpp" | grep -v build/ | xargs clang-format --dry-run --Werror

# Auto-fix formatting
find . -name "*.cpp" -o -name "*.hpp" | grep -v build/ | xargs clang-format -i
```

## Code Standards

- C++23, no exceptions in embedded-facing code
- All new logic modules need unit tests (Month 1 Week 4+)
- No Python in `src/` or `firmware/` — Python tooling lives in `tools/scripts/` only if needed
- Follow the `.clang-format` config — non-negotiable
- No secrets or credentials committed

## Architecture Decisions

Significant decisions go in `docs/decisions/` as ADRs before implementation.
See `docs/decisions/ADR-0000-template.md`.
