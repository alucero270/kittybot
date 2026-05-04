# ADR-0001: Reset main to C++23 architecture

**Status:** Accepted
**Date:** 2026-05-03
**Deciders:** Alex Lucero

## Context

The repository's first 15 commits explored a Python-based microservice
architecture: a head service with HTTP endpoints (/health, /metrics, /state)
talking to an external "Prometheus AI" stack, deployed via Docker Compose.

In re-evaluating the project goals — building a portfolio piece for HPC,
aerospace, and embedded R&D roles, while delivering a real toy for my
children — the Python service-mesh approach didn't fit. Specifically:

- Target roles want C++ proficiency, deterministic systems, modular
  embedded architectures. A Python web service does not demonstrate this.
- Hard requirement: untethered operation. The kids won't accept a USB-cable
  toy. This pulled compute on-robot, simplifying the architecture toward a
  single C++ runtime rather than distributed services.
- The original spec document (KittyBot Full System Specification) was
  written deliberately around C++23, STM32, no-cloud, no-ROS. The earlier
  prototype predated that spec.

## Decision

Reset `main` to a clean C++23 architecture. Archive the Python prototype
at the `v0-python-prototype` tag for historical reference.

The new architecture is described in `docs/ROADMAP.md`. Briefly:

- C++23 host runtime owning Modules via std::unique_ptr
- STM32 firmware for actuator control and safety
- Text protocol initially (Phase 1–2), binary with CRC in Phase 3
- On-robot compute (Jetson Orin Nano) — no host tether
- No cloud dependencies
- No ROS, no SLAM, no biped (year 1)

## Alternatives Considered

**Keep both architectures in one repo.** Rejected. Mixed Python/C++ confuses
the portfolio narrative. A hiring manager seeing 51% Python concludes the
project is Python.

**Throw away the v0 work entirely.** Rejected. The protocol contract
(`PTZ <yaw> <pitch>`, etc.) is good thinking and survives. The decision
record itself — that I tried service-mesh and chose differently — is a
positive signal when framed clearly.

**Start a new repository.** Rejected. Loses URL alignment, fragments work
history. The tag-and-reset accomplishes the same isolation with one repo.

## Consequences

- The Python prototype remains accessible via `git checkout v0-python-prototype`.
- `main` becomes the C++23 architecture from this commit forward.
- README and project description need to be rewritten (done in this commit).
- CI workflows need to be replaced (deferred to Month 1 Week 4).
- The protocol contract from v0 is salvaged and will reappear in ADR-0006
  (text protocol design) in Month 4.

## What Would Change This Decision

Nothing realistic. This is a one-way door. The reverse — going back to a
Python service-mesh — would not serve any of the project's stated goals.
