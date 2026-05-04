# KittyBot

A C++23 hardware-integrated companion robot platform. Modular runtime, STM32 actuator
control, OpenCV-based perception, designed to demonstrate end-to-end robotics systems
engineering.

> **Status:** Phase 1 / Month 1 — under active construction. Not yet runnable.

---

## Project Vision

A battery-powered, untethered companion robot featuring an expressive head with face
tracking, articulated arms with gesture behaviors, on-board compute, and a hardened
software stack including binary protocol with CRC, Kalman estimation, simulation with
deterministic replay, and watchdog-based fault detection.

Year 1 scope is intentionally stationary. Mobile base is a year 2 goal.

## Architecture (Target)

```
Camera → Perception (OpenCV)
       → Behavior FSM
       → Control (PTZ + arm logic)
       → Protocol (text now, binary later)
       → STM32 (PWM + safety + watchdog)
       → Servos
       → Telemetry / logs
```

Host compute: NVIDIA Jetson Orin Nano (on-robot)
MCU: STM32 F446RE (Nucleo dev board)

## Build (Coming Soon)

The build system isn't wired up yet. Check back at the end of Month 1.

## Documents

- `docs/ROADMAP.md` — phased plan, deliverables, risk register
- `docs/decisions/` — Architecture Decision Records (ADRs)

## History

The original Python prototype is preserved at the `v0-python-prototype` tag. To browse:

```bash
git checkout v0-python-prototype
```

## License

MIT — see `LICENSE`.
