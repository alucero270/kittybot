.PHONY: install dev test lint docker-build

PYTHON ?= python
APP ?= head.app.main:app
IMAGE ?= kittybot-head:dev

install:
	$(PYTHON) -m pip install --upgrade pip
	$(PYTHON) -m pip install -e ".[dev]"

dev: install
	$(PYTHON) -m uvicorn $(APP) --host 0.0.0.0 --port 8000 --reload

test: install
	$(PYTHON) -m pytest -q

lint: install
	$(PYTHON) -m ruff check .

docker-build:
	docker build -t $(IMAGE) .
