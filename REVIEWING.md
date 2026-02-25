# Reviews (kittybot)

## Review Checklist
### Scope & Architecture
- Does this change only what the issue intended?
- Are module boundaries respected (head vs sims vs firmware vs docs)?
- Is logic testable (pure functions where possible)?

### Correctness
- Are units consistent (degrees for PTZ)?
- Are protocol strings correct (PTZ/EYES/STATE)?
- Are limits/clamps applied to prevent unsafe targets?

### Security
- No secrets committed
- API key enforcement is correct (if enabled)
- Outbound requests have strict timeouts
- Logging does not leak sensitive values

### Quality
- Type hints added for new/modified code
- Reasonable error handling (no blanket except)
- Logging is structured and useful

### Tests & Docs
- Unit tests added/updated for new logic
- make test passes
- Docs/READMEs updated if behavior changed
- Troubleshooting updated if new failure modes are likely

## When to Request Changes
Request changes if:
- Unscoped refactors occurred
- Tests were not added for new logic
- Protocol/units changed without an ADR
- Any secrets are present
- Docker/dev workflow broke without documentation

## “Good Enough” Standard
This is a robotics project: prioritize
- clarity
- determinism at boundaries
- safe defaults
over cleverness.
