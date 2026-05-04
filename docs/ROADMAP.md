# KittyBot Roadmap

**Last updated:** 2026-05-03
**Status:** Phase 1, Week 0 (pre-start, awaiting parts)
**Target demo-able date:** Month 12 (~May 2027)
**Working deadline:** Month 15 (~Aug 2027)
**Hard ceiling:** Month 18 (~Nov 2027)

---

## You Are Here

> **Phase 1 — Foundations, Week 0**
> Awaiting Phase 1 hardware order. Starting Session 1 (RAII + Ownership) on desktop while parts ship.

---

## Goal

A battery-powered, untethered companion robot prototype with:

- Expressive head (pan/tilt + face tracking + OLED eyes)
- Articulated arms (4 servos, gesture behaviors)
- On-board compute (Jetson Orin Nano)
- STM32-based actuator control
- Modular C++23 runtime
- Telemetry, simulation, binary protocol, Kalman estimation

Designed as a portfolio piece for HPC / scientific simulation / aerospace / embedded R&D roles. Real toy for the builder's children.

---

## Constraints

- ~10 hrs/week build time
- $1,500 total budget (expected spend ~$1,000–1,200)
- Must be untethered (kids' constraint, treated as load-bearing)
- C++23 runtime only (no Python in core systems)
- No ROS, no SLAM, no biped, no manipulation in year 1
- Hybrid dev environment: Windows for STM32 work, Linux/WSL2 for everything else

---

## Phase 1 — Foundations (Months 1–4, ~160 hrs)

**Goal:** Type a command in a terminal, watch a servo move. Modular runtime skeleton in place.

### Month 1 — C++ Foundations Built Into Real KittyBot Code

Every deliverable is real production code, not throwaway exercises.

- **Week 1:** `kittybot::Logger` (RAII, scope guards, file + stdout, thread-safe)
- **Week 2:** `kittybot::Module` interface + `kittybot::Runtime` (ownership via unique_ptr, lifecycle orchestration)
- **Week 3:** `kittybot::Config` (JSON/TOML loading, optional/variant, std::expected error handling)
- **Week 4:** CMake structure, unit tests, GitHub Actions CI, clang-format, first ADRs

### Month 2 — STM32 Toolchain

- PlatformIO + VS Code + CubeMX setup on Windows
- Blink, UART echo, button read on Nucleo-F446RE
- **Deliverable:** STM32 echoes UART input cleanly, blinks on command

### Month 3 — First Servo

- PWM peripheral configuration on STM32
- Bench setup with separate servo power supply (common ground)
- **Deliverable:** Servo sweeps full range under STM32 firmware control

### Month 4 — Host ↔ STM32 Bridge

- Text protocol over USB serial (one-line commands like `PTZ 30`)
- Plug serial-protocol module into the Runtime built in Month 1
- **Deliverable:** End-to-end — type `PTZ 30` on host, servo moves to 30°, with logging on both ends

**Phase 1 exit criteria:** Working hardware-in-the-loop. Modular C++ scaffolding in place. Version-controlled repo.

---

## Phase 2 — Head + Vision + Estimation (Months 5–8, ~160 hrs)

**Goal:** Untethered head that tracks faces smoothly.

- **Month 5:** Pan-tilt mechanical assembly (3D printed). Two servos under STM32. USB camera into OpenCV on host. Face detection. **Buy:** Orin Nano 8GB Dev Kit, USB camera, IMU.
- **Month 6:** PTZ control loop. FSM (IDLE / TRACKING / SAFE / FAULTED). IMU integrated. **Deliverable:** Head tracks face on tethered host.
- **Month 7:** Kalman filter fusing camera angle measurements with IMU rates. **Deliverable:** Smooth tracking, predicts through brief occlusions. Measurable jitter reduction.
- **Month 8:** Port runtime to Orin Nano. Robot becomes untethered for vision + head. **Deliverable:** Untethered head tracking kids across the room.

**Phase 2 exit criteria:** Robot recognizable as KittyBot. Kids actively interact with it.

---

## Phase 3 — Protocol + Sim + Arms (Months 9–11, ~120 hrs)

**Goal:** Full expressive robot, hardened software stack.

- **Month 9:** Binary protocol (framing, CRC, versioning, ack/nack). STM32 watchdog and fault detection. Safe state on fault.
- **Month 10:** Simulation harness — fake camera frames, fake servo state, deterministic replay from logs, numerical integrator for servo dynamics. The HPC-bridge module.
- **Month 11:** Four arm servos. Joint-space trajectory planning with velocity/acceleration limits. Wave + lift + idle gestures driven by FSM.

**Phase 3 exit criteria:** All spec behaviors working. Hardened protocol. Real simulation.

---

## Phase 4 — Battery + Eyes + Polish (Month 12, ~40 hrs)

**Goal:** Demo-able robot. **THIS IS THE LOAD-BEARING MILESTONE.**

- LiPo battery + BMS + voltage regulators (separate servo and compute rails)
- OLED eyes
- Bug fix pass
- Rough demo video cut

**Exit criteria:** Robot demo-able. Untethered. Battery-powered. Tracks faces, gestures, expressive eyes.

---

## Phase 5 — Polish + Job Hunt (Months 13–15, ~120 hrs split)

- Profiling pass + benchmarks document
- Architecture writeup (the doc a hiring manager reads)
- Final demo video
- GitHub README, build instructions, code comments
- **Stretch:** CUDA module on RTX 4000 (face detection or particle filter). Cut without negotiation if Phase 4 ran late.
- Resume, applications, interviews

---

## Phase 6 — Year 2 (post-job)

- Mobile base (kids' request)
- Voice / LLM interaction on Orin
- FPGA exploration if targeting aerospace shops specifically
- Possible biped exploration

---

## Continuous Practices

- **ADRs in `docs/decisions/`** for every architecture decision, written in the moment
- **README evolves with code**, not a month-15 sprint
- **Atomic commits** with meaningful messages from day one
- **Test coverage** on logic modules (FSM, Kalman, trajectory, protocol parsing). Not on hardware-touching code where simulation is the substitute.

---

## Risk Register

| Risk | Likelihood | Impact | Mitigation | Status |
|------|-----------|--------|-----------|--------|
| OpenCV build on new platform eats a week | High | Medium | Buffer in Month 5–6 | Watching |
| Orin port surfaces ARM cross-compile issues | Medium | Medium | Build on target via SSH if cross-compile fails | Watching |
| Mechanical arm work overruns | Medium | Medium | Fallback: 1 arm (2 servos) instead of 2 | Accepted |
| Job hunt starts strong, build pace drops | Medium | High | CUDA stretch is first cut | Accepted |
| Servo current spikes brown out STM32 | High | Low | Separate power supply, common ground (always) | Mitigated |
| Burn out a servo learning | Near-certain | Low | Bought 2 from start | Mitigated |
| C++ rebuild slower than expected | Medium | Medium | Month 1 code is real KittyBot code, no wasted effort | Mitigated |

---

## Decision Log

| # | Date | Decision | Rationale | ADR |
|---|------|----------|-----------|-----|
| 1 | 2026-05 | Stationary year 1, mobile base year 2 | Portfolio targets don't reward mobile base; risk of not finishing the expressive parts | TBD |
| 2 | 2026-05 | Orin Nano 8GB over Pi 5 + AI HAT+ | CUDA toolchain transfers from RTX 4000 dev work; Jetson is industry standard for target roles | TBD |
| 3 | 2026-05 | PlatformIO + VS Code, not CubeIDE | Cross-platform, escapes Eclipse, same workflow for future MCUs | TBD |
| 4 | 2026-05 | Hybrid dev env: Windows for STM32, Linux for rest | WSL2 USB passthrough for STM32 is too flaky; Linux needed for OpenCV and CUDA | TBD |
| 5 | 2026-05 | Text protocol first, binary in Month 9 | Debuggability first; binary when serialization complexity earns its keep | TBD |
| 6 | 2026-05 | Month 1 builds real KittyBot classes | Project-connected learning; no throwaway code | TBD |

---

## Explicit Cuts (Things We Chose NOT To Build)

- Mobile base (year 2)
- Bipedal locomotion (not in any year)
- ROS (would dilute portfolio signal)
- SLAM (out of scope for stationary robot)
- Object manipulation / gripping
- Cloud connectivity
- Multi-agent
- CUDA on Jetson (CUDA stays on RTX 4000; Jetson runs CPU/standard inference)
- Hailo / Coral / Edge TPU acceleration (toolchain doesn't transfer to target roles)
- Custom PCB design (use breakout boards and modules)
- Voice / LLM interaction (year 2 candidate)
- FPGA work (year 2 candidate, only if aerospace targeting solidifies)

---

## Budget Tracker

| Category | Estimated | Spent | Remaining |
|----------|-----------|-------|-----------|
| Phase 1 (Nucleo, servos, breadboard) | $80 | $0 | — |
| Tools (multimeter, iron, etc.) | $200 | $0 | — |
| Phase 2 (camera, IMU, pan-tilt, filament) | $95 | $0 | — |
| Compute (Orin Nano 8GB Dev Kit) | $250 | $0 | — |
| Phase 3 (4 arm servos, misc) | $70 | $0 | — |
| Phase 4 (battery, BMS, regulators, OLED) | $90 | $0 | — |
| Contingency (burnouts, learning purchases) | $215 | $0 | — |
| **Total** | **$1,000** | **$0** | **$1,500 budget** |

---

## Update Protocol

This document updates whenever:
- A phase completes (mark deliverables, move "You Are Here")
- A risk materializes or fades
- A decision is made (add to log, write ADR)
- Scope changes (cut item moves to year 2, or vice versa)
- Budget category is spent

Edit in place. Commit with message `docs(roadmap): <what changed>`.
