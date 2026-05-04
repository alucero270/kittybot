---
name: Feature / Task
about: A scoped task with acceptance criteria
title: "[feat]<scope>: <short title>"
labels: enhancement
assignees: alucero270

---

## Summary
Describe what we are building in 1–3 sentences.

## Context
Why this exists (architecture, phase, dependency). Link to related issues/ADRs if any.

## Scope
What should be implemented. Be explicit about modules/files.
- File(s) to create/modify:
  - `...`
- Behaviors to add/change:
  - ...

## Non-Goals
What must NOT be done in this issue (prevents Codex drift).
- Do not ...
- Do not ...

## Technical Requirements
- Language/runtime: C++23 (host) / C (STM32 firmware)
- Logging: `kittybot::Logger` for structured output
- Transport: PTZ/EYES/STATE protocol, units always degrees
- Tests: Catch2 unit tests required for new logic modules

## Acceptance Criteria
- [ ] Implements only the scope described above
- [ ] CI passes (`build` + `format` jobs green)
- [ ] Unit tests added/updated for new logic
- [ ] Documentation updated (READMEs + relevant docs)
- [ ] No secrets committed (no tokens/keys in repo)

## Notes for Codex
Paste any specific constraints, pseudo-code, or examples here.
