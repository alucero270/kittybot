from fastapi import FastAPI

from .logging_config import configure_logging

configure_logging()

app = FastAPI(title="kittybot-head")


@app.get("/health")
def health() -> dict[str, str]:
    return {"status": "ok"}
