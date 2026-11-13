# hardware

Hardware design files, BOM references, and integration notes for kittybot.

## Contents

- [`bom.md`](bom.md) — the bill of materials, and the source of truth for what is
  owned, ordered, to-buy, deferred, or rejected. Read this first.
- [`bom.csv`](bom.csv) — the same rows in machine-readable form for spreadsheet import.
  Keep the two in sync; a status change should touch both in one commit.
- mechanical/electrical artifacts
- wiring and pinout references
- revision notes

## Procurement log

There is no separate procurement tracker. The commit history *is* the log: when a
part is bought, change its **Status** in `bom.md` and `bom.csv` and commit as
`chore(hardware): order nucleo f446re`. That keeps the record dated, reviewable, and
the same on every machine.

The interactive HTML board in `docs/plans/PHASE-01-PARTS.html` is a pretty view only.
Its checkmarks live in browser `localStorage`, so they reset per device — do not treat
it as the record.

## Conventions

- Do not buy a part before the **phase** column says it is needed. Deferrals are
  design decisions, not procrastination.
- When a part is considered and rejected, keep the row with status `rejected` and a
  reason. Rejected-part rationale is the knowledge most likely to be lost, and the
  most likely to be re-litigated.

## Troubleshooting

- If a hardware revision is ambiguous, document exact revision identifiers before changes.
- If pin mappings differ from firmware assumptions, update both this folder and related ADRs in `docs/`.
