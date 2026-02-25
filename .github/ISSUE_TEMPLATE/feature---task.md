---
name: Feature / Task
about: A scoped task with acceptance criteria
title: "[feat]<scope>: <short title>"
labels: enhancement
assignees: alucero270

---

---
name: "Feature / Task (Codex-ready)"
about: "A scoped task with acceptance criteria that can be pasted into Codex"
title: "[kittybot] <short title>"
labels: ["enhancement"]
assignees: []
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
- Language/runtime: Python 3.11 (head) / C (STM32 later)
- Config: YAML (`config.yaml`) if needed
- Logging: JSON structured logs
- Security: respect API key rules (X-API-Key) if touching HTTP
- Transport: PTZ/EYES/STATE protocol and degrees units if touching transport
- Tests: pytest required for new logic

## Acceptance Criteria
- [ ] Implements only the scope described above
- [ ] `make test` passes
- [ ] Unit tests added/updated for new logic
- [ ] Documentation updated (READMEs + relevant docs)
- [ ] No secrets committed (no tokens/keys in repo)

## Notes for Codex
Paste any specific constraints, pseudo-code, or examples here.
