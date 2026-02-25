# Codex Prompt Wrapper (kittybot)

Copy/paste this block at the TOP of every Codex prompt.

## Operating Rules (must follow)
1. **Scope control**
   - Only modify files explicitly listed in the Scope section.
   - Do not refactor unrelated code.
   - Do not change folder structure unless the issue explicitly says so.

2. **Quality gate**
   - Ensure `make test` passes.
   - Add/update pytest unit tests for any new or changed logic.
   - Keep logic modular and testable (pure functions where possible).

3. **Project conventions**
   - Python: 3.11, type hints required.
   - Config: YAML for runtime config.
   - Logging: JSON structured logs.
   - Protocol: newline-delimited text commands using degrees:
     - `PTZ <yaw_deg> <pitch_deg>`
     - `EYES <mode>`
     - `STATE <state>`
   - Security: If `API_KEY` is configured, enforce `X-API-Key` on all endpoints except `/health`.

4. **Docs**
   - Update relevant READMEs and docs when behavior changes.
   - Add/extend Troubleshooting sections when you encounter likely failure modes.

5. **No secrets**
   - Never commit tokens, passwords, or API keys.
   - Use `.env.example` and environment variables for secrets.

## Output Requirements
At the end of your work:
- Provide a concise summary of files changed.
- Provide exact commands to run tests and start the service.
- If anything is uncertain, leave a TODO comment in code rather than guessing.
