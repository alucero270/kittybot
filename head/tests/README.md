# head/tests

Tests for the `head` FastAPI service.

## Contents

- endpoint tests
- integration-style API sanity checks

## Troubleshooting

- If tests fail on import, ensure the package is installed in editable mode: `python -m pip install -e ".[dev]"`.
- If `TestClient` errors, verify `httpx` is installed from dev dependencies.
