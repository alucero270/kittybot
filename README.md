# kittybot

A modular, containerized companion robot head project designed for professional-grade
software and embedded development practices.

kittybot is built to evolve from:

* 🧠 Laptop-based development (Nomad)
* 🖥 Prometheus AI stack integration
* 🤖 Jetson deployment
* 🔧 STM32-based actuator control

This project emphasizes:

* Clean architecture
* Deterministic boundaries
* Strong commit discipline
* Unit testing
* CI enforcement
* Hardware/software separation of concerns

---

# 🚀 Project Vision

Final goal:
A mobile "Hello Kitty"-styled companion robot capable of:

* Face tracking
* Conversational interaction
* Expressive animated eyes
* Object manipulation (future)

Phase 1 (Milestone 1):
Head Service MVP running fully in software with:

* Camera-based face detection
* PTZ (pan/tilt) target calculation
* Deterministic state machine
* Structured logging
* Prometheus AI integration
* Transport abstraction (no hardware required yet)

---

# 🧱 Architecture Overview

## High-Level Structure

* `head/` → High-level robot head service (Python)
* `tracking/` → PTZ math and smoothing logic
* `state/` → Deterministic behavior state machine
* `vision/` → Camera + perception
* `transport/` → PTZ/EYES/STATE protocol abstraction
* `ai/` → Prometheus AI client integration
* `firmware/` → STM32 embedded firmware (future)
* `hardware/` → BOM, wiring, CAD (future)
* `sims/` → Actuator simulators

The head service is fully testable without hardware.

---

# 📦 Development Workflow

## 1️⃣ Clone the Repository

```bash
git clone <repo-url>
cd kittybot
```

## 2️⃣ Local Development (Fast Loop)

```bash
make dev
```

Service runs locally and exposes:

* `GET /health`
* `GET /state`
* `GET /metrics`
* `GET /deps`
* `POST /demo/talk`

## 3️⃣ Run Tests

```bash
make test
```

With coverage:

```bash
make test-cov
```

## 4️⃣ Linting

```bash
make lint
```

---

# 🐳 Docker Usage

## Development Profile

```bash
docker compose -f head/docker/compose.dev.yml up
```

## Server Profile (Prometheus)

```bash
docker compose -f head/docker/compose.server.yml up
```

Refer to `docs/dev-runbook.md` for Portainer stack deployment steps.

---

# 🔐 Security Model

* API key optional via `API_KEY`
* If configured, all endpoints except `/health` require header:
  `X-API-Key`
* No secrets committed to repository
* Strict timeout on outbound AI requests

---

# 📡 Protocol Contract (Transport Layer)

Newline-delimited text commands.

Units are always **degrees**.

```
PTZ <yaw_deg> <pitch_deg>
EYES <mode>
STATE <state>
```

Any change to protocol requires an ADR.

---

# 🧪 Testing Philosophy

* All core logic must be unit tested
* Tracking math must be deterministic
* State transitions must be validated
* Protocol formatting must be verified
* CI must pass before merging

Tests live under `head/tests/`.

---

# 🌐 Prometheus AI Integration

Head service can call external AI endpoint:

```
POST {AI_BASE_URL}/chat
{
  "text": "...",
  "session_id": "..."
}
```

* Strict timeout
* Fallback canned response if unavailable
* `/deps` endpoint shows integration health

---

# 🛣 Roadmap

### Milestone 1 — Head Service MVP

* Repo structure
* Config + logging
* PTZ math
* State machine
* Transport layer
* Camera + tracking
* AI client

### Milestone 2 — Simulation Layer

* MCU simulator
* Eyes simulator

### Milestone 3 — Audio Interaction

* Wake word
* STT
* TTS

### Milestone 4 — Hardware Bring-Up

* STM32 firmware
* Display drivers
* Servo integration

### Milestone 5 — Jetson Deployment

* Performance tuning
* Systemd integration
* GPU acceleration

---

# 🧭 Engineering Standards

* Conventional commit format
* One branch per issue
* PR required for merge
* Unit tests required for new logic
* JSON structured logging
* YAML runtime configuration
* PTZ units always degrees

See:

* `CONTRIBUTING.md`
* `TESTING.md`
* `REVIEWING.md`

---

# 📌 Design Principles

1. Deterministic boundaries
2. Hardware abstraction
3. Testable pure logic
4. Small, scoped changes
5. No premature optimization
6. Clean upgrade path to embedded hardware

---

# 🧠 Why This Project Exists

kittybot is both:

* A companion robot platform
* A professional robotics software portfolio project

It is designed to mirror real robotics engineering workflows while
remaining approachable and modular.

---

# ⚠️ Current Status

Early development.

Head service MVP under active construction.
No hardware required yet.

---

# 📜 License

(To be determined)

---

End of README
