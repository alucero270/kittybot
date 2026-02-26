# head

Control-plane service entry point for kittybot. This directory contains the API surface and server-side coordination logic.

## Contents

- `app/`: FastAPI application package
- `tests/`: API tests for head service behavior

## Troubleshooting

- If imports fail, run `python -m pip install -e ".[dev]"` from repo root.
- If local startup fails, verify the app target is `head.app.main:app`.
