# Contributing to kittybot

kittybot follows strict commit conventions and disciplined change control to keep the
project readable, maintainable, and portfolio-grade.

Codex may assist with implementation, but all changes must follow these conventions.

---

# Git Commit Guidelines

Each commit message consists of:
- Header (required)
- Body (strongly encouraged)
- Footer (optional)

No line may exceed 100 characters.

## Commit Message Format

type(scope): subject

Body (optional but strongly encouraged)

Footer (optional)

The header is mandatory.
The scope is required for this project.

## Revert

If reverting a commit:

revert: <original header>

Body must include:
This reverts commit <hash>.

## Type

Must be one of:
* feat:     A new feature
* fix:      A bug fix
* refactor: Code change without feature or bug fix
* perf:     Performance improvement
* test:     Add or update tests
* docs:     Documentation-only changes
* style:    Formatting only (no logic changes)
* chore:    Tooling, build, or dependency changes
* ci:       CI/CD workflow changes

## Scope

Scope describes the subsystem affected.

Approved scopes for kittybot:
* head        High-level robot head service
* tracking    PTZ math and control logic
* state       State machine
* vision      Camera and perception
* transport   PTZ/EYES/STATE protocol and transport
* ai          Prometheus AI integration
* api         FastAPI endpoints
* config      Runtime configuration
* firmware    STM32 or embedded code
* hardware    BOM, wiring, CAD
* docs        Documentation updates
* repo        Repository structure changes
* ops         Docker/compose/deployment
* ci          CI workflow changes

Use lowercase.

Examples:
* feat(head): add state machine integration
* feat(tracking): implement yaw clamp limits
* fix(api): enforce api key authentication
* chore(ops): add compose.server profile

## Subject Rules

The subject must:
- Use imperative present tense ("add", not "added")
- Not capitalize the first letter
- Not end with a period
- Be concise and descriptive

Correct:
✔ add ptz smoothing logic
✔ enforce api key on state endpoint

Incorrect:
✘ Added smoothing logic.

## Body

Use imperative tense.
Explain:
- What changed
- Why it changed
- How it differs from previous behavior

Keep lines under 100 characters.

Example:
Add exponential smoothing to yaw and pitch targets.

Previously tracking snapped directly to face center which caused visible jitter.
Smoothing improves perceived motion stability.

Closes #12

## Footer

Used for:
- Referencing issues: "Closes #12", "Refs #14"
- Breaking changes: must begin with "BREAKING CHANGE:"

---

# Branching Strategy

- One branch per issue
- Branch name format:
  issue/<number>-short-description

Examples:
issue/4-ptz-math
issue/8-ai-client
issue/12-tcp-transport

Rules:
- Merge via Pull Request
- Squash only if commits are noisy
- Do not push directly to main

---

# Code Style

## Python
- Python 3.11
- Type hints required for new/modified functions
- Prefer small pure functions for logic (testable units)

## Formatting / Linting
- Use ruff for linting (and formatting if enabled in pyproject)
- Keep imports sorted
- Avoid unused variables and overly broad exception handling

## Naming
- Modules: snake_case
- Classes: PascalCase
- Functions/vars: snake_case
- Constants: UPPER_SNAKE_CASE

## Logging
- Use structured JSON logs (via the project logging module)
- Do not log secrets (API keys, tokens)
- Avoid logging raw transcripts by default (unless explicitly enabled)

## Config
- Runtime config is YAML (config.yaml)
- Do not hardcode environment-specific paths or addresses
- Prefer env vars for secrets

## Protocol Conventions
- Units are degrees for PTZ
- Newline-delimited text commands:
  - PTZ <yaw_deg> <pitch_deg>
  - EYES <mode>
  - STATE <state>

Changing the protocol requires an ADR.

---

# Security Basics

- No secrets in git (use .env and .env.example)
- If API_KEY is configured, enforce X-API-Key on all endpoints except /health
- Add strict timeouts for all outbound HTTP calls (AI integration)

---

# Example Commits

feat(tracking): implement yaw and pitch smoothing

Add configurable exponential smoothing to ptz_math.
Improve head stability during face tracking.

Closes #6

fix(api): enforce api key when configured

Previously endpoints allowed access even when API_KEY was set.
Now require X-API-Key header if configured.

Closes #9

chore(ops): add compose.server profile for prometheus

Add server mode compose file without webcam dependency.
Document portainer deployment steps.

Closes #3
