# head/app

Minimal FastAPI app for the kittybot head service.

## Contents

- `main.py`: API application and routes
- `logging_config.py`: logging bootstrap placeholder

## Troubleshooting

- If `/health` is missing, confirm `main.py` defines `@app.get("/health")`.
- If startup logging looks plain-text, this is expected until structured JSON logging is fully implemented.
