# Testing (kittybot)

This project uses pytest for unit and integration testing.

## Goals
- Unit test all new/changed logic.
- Keep tests fast and deterministic.
- Prefer pure functions for math/state so tests don't require hardware.

## Commands
- Run tests:
  - make test
- Run tests with coverage:
  - make test-cov
- Lint:
  - make lint

## What Must Be Unit Tested
Minimum expectations for new logic:
- Tracking math (PTZ) behavior:
  - clamping
  - smoothing
  - input validation
- State machine transitions and state->eye mapping
- Protocol formatting/validation (PTZ/EYES/STATE)
- Config parsing and default behavior
- API key auth behavior (when enabled)

## Integration Tests
Allowed but should be minimal.
Examples:
- FastAPI TestClient checks for /health and /state
- Mocking external AI calls

Avoid:
- Tests that require a webcam
- Tests that require real network services
- Slow model inference tests (keep those as manual/optional)

## Test Structure
- Unit tests live under: head/tests/
- Prefer one feature per test file:
  - test_ptz_math.py
  - test_state_machine.py
  - test_protocol.py

## Mocking Guidance
- Use dependency injection where possible.
- Mock outbound HTTP requests to AI services.
- If simulating TCP transport, use a local dummy server within the test.

## CI Expectations (when added)
- make lint
- make test
- make test-cov (optional threshold for core modules)
