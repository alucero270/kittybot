# KittyBot — Bill of Materials

**Status:** Active tracker. This file is the source of truth for what KittyBot is made of, what it costs, and what's been bought.
**Owner:** Alex Lucero
**Last reviewed:** 2026-11-12
**Machine-readable twin:** [`bom.csv`](bom.csv) (same rows, for spreadsheet import)

Prices are the ones quoted during planning (mid-2026 quotes, mixed USD/EUR). **Re-verify at checkout** — see [Price confidence](#price-confidence) before trusting any number.

---

## How to use this file

| Column | Meaning |
|---|---|
| Status | `owned` · `ordered` · `to-buy` · `deferred` · `rejected` |
| Phase | When it is actually needed. Do not buy earlier. |
| Depends on | Purchases or decisions gated by this row |

Update the **Status** column in a PR. The commit history is the procurement log: `chore(hardware): order nucleo f446re`.

> The interactive HTML procurement board (`docs/plans/PHASE-01-PARTS.html`) keeps its checkmarks in browser `localStorage`, so it resets per device. This file does not. Treat HTML as the pretty view and this as the record.

---

## Phase 1 — Foundations (Months 1–4)

Target: type `PTZ 30` on the host, watch a servo move.

### Electronics

| ID | Part | MPN / search term | Qty | Unit | Ext | Status | Source | Notes |
|---|---|---|---:|---:|---:|---|---|---|
| H1 | STM32 dev board | `NUCLEO-F446RE` | 1 | $15–30 | $15–30 | to-buy | **DigiKey / Mouser only** | Cortex-M4F. FPU matters for the Month 7 Kalman filter. Built-in ST-Link. Amazon listings carry clones with different USB-serial chips. This board is the agreed answer after rejecting F429ZI (obsolete), F439ZI (over-specced Nucleo-144), and N657X0-Q (NPU/camera redundant with the compute board). |
| H2 | Head servos | **see [Servo decision](#servo-decision-unresolved)** | 2 | $5–11 | $10–22 | to-buy | Amazon | Two options with different PSUs, brackets, and safety profiles. Blocking decision. |
| H3 | Servo power supply | 5V brick | 1 | $10–20 | $10–20 | to-buy | Amazon | **Sized by H2**, not by taste: 5V 3A for MG90S, 5V 10A for MG996R. Never power servos from the Nucleo 5V pin — spikes brown out the MCU. Separate rail, common ground. |
| H4 | Barrel jack → breadboard | 5.5×2.1 mm adapter | 1 | $5 | $5 | to-buy | Amazon | Gets the brick onto the breadboard power rail. |
| H5 | Breadboard | half-size, power rail | 1 | $5 | $5 | to-buy | Amazon | Second one likely needed at Month 5 for head wiring. |
| H6 | Jumper kit | M-M / M-F / F-F, 120 pc | 1 | $8 | $8 | to-buy | Amazon | Used every session for 18 months. |
| H7 | Micro-USB cable | data-capable | 1 | $0–5 | $0–5 | to-buy | owned-verify | Many cables are charge-only. If the Nucleo does not enumerate, this is the cause. Mark known-good cables. |
| H8 | Eye displays | `SSD1306 0.96" 128x64 I2C` | 2 | $7 | $14 | deferred | Amazon.de | Repo roadmap puts eyes at **Month 12**. A planning conversation put them in the first order. Unresolved — see [Open decisions](#open-decisions). Not 0.91" 128×32; too short for expressive eyes. |

### Safety and power control

| ID | Part | MPN / search term | Qty | Unit | Ext | Status | Source | Notes |
|---|---|---|---:|---:|---:|---|---|---|
| S1 | E-stop switch | `16mm mushroom head emergency stop latching NC` | 1 | $5 | $5 | to-buy | Amazon.de | **NC, not NO.** NC means the circuit is closed while healthy and *opening* it stops the robot, so a severed wire fails safe. An NO E-stop goes silently dead when its wire falls out. Latching: stays stopped until twisted free. |
| S2 | Servo-rail switch | `IRLZ44N` logic-level N-ch MOSFET | 5 | $5 | $5 | to-buy | Amazon | Logic-level gate (the "L") so 3.3V GPIO fully enhances it. A plain IRF540 will not. Switch the **servo ground**, keep MCU ground upstream so logic reference never floats. ~100k gate pulldown, ~100Ω gate resistor. |
| S3 | Master power switch | slide or rocker | 1 | $5 | $5 | to-buy | Amazon | A momentary button cannot *hold* a rail off. Or accept "unplug it" for now. |
| S4 | User-input buttons | 7 mm momentary | 4 | $2 | $8 | to-buy | Amazon | Correct for pet/wake inputs. If illuminated, pick the 3 V–12 V variant; a 230 V LED will not light at 5 V. |

### Tools (buy once, lifetime)

| ID | Part | MPN | Qty | Unit | Ext | Status | Source | Notes |
|---|---|---|---:|---:|---:|---|---|---|
| T1 | Multimeter | Klein MM325 (or AstroAI) | 1 | $22–30 | $22–30 | to-buy | Amazon | **Buy before anything gets powered.** Auto-ranging + continuity buzzer. CAT II 300V if probing mains or car wiring. Sub-$15 meters lie and you chase ghost faults for weeks. |
| T2 | Soldering iron | Pinecil V2 | 1 | $26 | $26 | to-buy | **Pine Store direct** | USB-C PD powered, 9–20 V DC. This is what makes the iron US/EU-proof: no mains voltage involved. A fixed-voltage mains iron is the classic two-region failure. |
| T3 | PD supply for iron | 65 W USB-C PD | 1 | $0–15 | $0–15 | to-buy | Amazon | Skip if a modern laptop PD charger is owned. A PD power bank is even better: zero mains, solder next to the OM606. |
| T4 | Solder | 60/40 leaded, 0.6–0.8 mm rosin core | 1 | $15 | $15 | to-buy | Amazon | Leaded is easier to learn on. Ventilate. |
| T5 | Flush cutters | Hakko CHP-170 | 1 | $8 | $8 | to-buy | Amazon | Lead trimming. Don't cut steel with them. |
| T6 | Wire strippers | Klein 11061 self-adjusting | 1 | $25 | $25 | to-buy | Amazon | 10–24 AWG without measuring. |
| T7 | Screwdriver kit | iFixit Mako 64-bit | 1 | $35 | $35 | to-buy | iFixit | Servo cases, Nucleo hardware, kids' toys. |
| T8 | Calipers | digital, 150 mm | 1 | $15 | $15 | to-buy | Amazon | Needed for the Month 5 printed brackets. |
| T9 | Helping hands | with magnifier | 1 | $15 | $15 | to-buy | Amazon | Soldering needs three hands. |
| T10 | Hookup wire | 22 AWG solid, multi-color | 1 | $15 | $15 | to-buy | Amazon | Color discipline = faster debugging. |
| T11 | Heat shrink | assortment | 1 | $10 | $10 | to-buy | Amazon | Battery wiring at Month 12; cheap to have early. |
| T12 | Fasteners | M2.5 + M3 screw/nut/washer assortment | 1 | $12 | $12 | to-buy | Amazon | Pan-tilt brackets in the current cart ship **"Without Screws"** — nothing assembles without them. Machine screw + nut, never self-tapping: MG996R/MG90S cases are plastic with thin tabs that crack. |

### Phase 1 totals

| Bucket | Low | High |
|---|---:|---:|
| Electronics (H1–H7; H8 deferred) | $53 | $95 |
| Safety / power (S1–S4) | $23 | $23 |
| Tools (T1–T12) | $198 | $221 |
| **Phase 1 to-buy total** | **$274** | **$339** |
| If eyes are pulled forward to Month 1 (H8) | +$14 | +$14 |

Repo procurement board ceiling: ~$270. A later planning cart (2026-11) landed near **$238** with tools. Both are inside the $1,500 envelope.

---

## Buy-later list (do NOT order yet)

Deferrals are a design decision, not procrastination. Months 1–4 change what you will actually want in Month 5.

| ID | Part | ~Cost | Unlock | Notes |
|---|---|---:|---|---|
| F1 | Compute board (on-robot) | $0–499 | Month 5 | **Open decision.** Roadmap says Jetson Orin Nano 8GB (~$499 quoted). A later conversation concluded: use the **owned BeagleBone Black** ($0) with vision on Nomad, and if an SBC is eventually needed, RK3588-class (~$180 Orange Pi 5 Max, ~$103 Banana Pi CM5-Pro) beats Jetson on price-per-TOPS. Roadmap is stale on this — see proposal. |
| F2 | Pan-tilt bracket | $0–18 | Month 5 | Roadmap says 3D print. The planning cart contains 5 pairs of MG996R robot-car brackets. Contradiction; brackets also need T12. |
| F3 | USB camera | $20–80 | Month 5 | |
| F4 | IMU | $10–35 | Month 5 | BNO055 (fused) vs MPU6050 (raw, cheaper). Needed for the Month 7 Kalman fusion. |
| F5 | Logic analyzer | $15 | Month 5–6 | 8-ch Saleae clone. Get this before any oscilloscope. |
| F6 | Arm servos ×4 | $20–44 | Month 9 | Matches the 4-servo arm spec. |
| F7 | LiPo + BMS + regulators | $50–120 | Month 12 | Only now that current draw is measured. Separate servo and compute rails. |
| F8 | Bench PSU / oscilloscope | $60–120 | as-needed | Deferred; the 5V brick + buck converters cover current needs. |
| F9 | Buck converters | $10–14 | Month 12 | **Not needed now.** A regulated 5V brick feeds 4.8–6.0 V servos directly. Only needed for 12 V battery → 5 V. Avoid LM2596 for servo rails (2–3 A rating is marginal against spike current). |
| F10 | RP2040 (Pico) | $4 | optional | PIO state machines: real industrial concept, good interview material. Side experiments only; does not replace the STM32. |

## Explicitly rejected

| ID | Part | Why |
|---|---|---|
| X1 | `NUCLEO-F429ZI` | Obsolete part; ~$70 listings are scalper pricing. Its only advantage (256 KB SRAM) solves a constraint that does not exist — SPI bandwidth, not RAM, caps eye refresh. |
| X2 | `NUCLEO-F439ZI` | In stock and a mild upgrade (268 KB), but it is Nucleo-144 money for Ethernet and pins this project will not use. |
| X3 | `NUCLEO-N657X0-Q` (STM32N6) | Its differentiators (NPU, MIPI CSI, GPU, 4.2 MB SRAM) duplicate the compute board's job and add nothing to servo PWM. First-gen toolchain with documented CubeMX/FSBL breakage. Revisit at Month 5–6 **only** if the conclusion is "no SBC at all" — N6 + camera as a vision coprocessor is a legitimate year-two architecture. |
| X4 | Black Pill / F407ZGT6 clones | Savings vanish once you add an ST-Link; clone boot/reset quirks burn hours you are spending on C++23. |
| X5 | Teensy 4.x | Good hardware, niche tooling, weaker industry signal. |
| X6 | PCA9685 servo driver | STM32 timers drive these servos directly. A layer you do not need. |
| X7 | ESP32 6-pack | Homelab telemetry dashboards, not KittyBot. WiFi does not belong inside the control loop. Separate budget line. |
| X8 | Round "OLED" displays | No such thing at hobby price — the round panels everyone calls round OLEDs are GC9A01 round TFT LCDs. Real round OLEDs (SSD1336, 96×96) are dimmer, lower-res, and costlier. |
| X9 | 16×2 character LCD (HD44780) | No pixels. Wrong tool for eyes. |
| X10 | Arduino Uno as co-processor | You own two. Genuinely good use: an *independent* servo-rail safety supervisor watching an STM32 heartbeat line. Bad use: motion control or I/O expansion. Deliberately left out of Phase 1. If used, Uno→Nucleo only on FT (5 V-tolerant) pins. |

---

## Servo decision (unresolved)

Two different answers are live in your own records, and they are not interchangeable.

| | MG90S (repo plan) | MG996R (planning cart) |
|---|---|---|
| Size / mass | ~14 g, 23×30×34 mm | ~55 g, 40×38×15 mm |
| Torque | ~2.2 kg·cm | ~21–40 kg·cm |
| Stall current | ~1.1–1.6 A | ~2.5–3 A each |
| PSU needed | 5 V 3 A | 5 V 10 A |
| Brackets | 3D-print at Month 5 | off-the-shelf robot-car set in cart |
| Kid-safety posture | Low energy; a drooping neck is a light object | **40 kg·cm at a child's face is a pinch hazard**; needs torque limits and mechanical stops designed in |
| Cost, 6-pack | ~$10 | ~$22 |

MG996R is the cheaper-per-torque hobby default and is already in the cart. MG90S is the safer and mechanically saner choice for a head that lives near children, and it is what the roadmap and bracket plan assume. Pick one before ordering, because H2 sets H3, F2, and the safety spec.

Note that "cut servo power = safe" is false for a neck: an unpowered MG996R goes limp and the head droops under gravity. Decide the safe behavior explicitly — limp against a mechanical stop, or hold-last-position with zero-rate commands.

---

## Initialization resources

Per part, what you read before it works. URLs given only at the level of the canonical document, since deep links rot.

| Part | Reference to pull | Notes |
|---|---|---|
| Nucleo-F446RE | **RM0390** (F446 reference manual) + **DS9711** (F446 datasheet), user manual for the Nucleo-64 board | RM0390 is the timer/ADC/GPIO detail source. Board pinout diagram is what tells you which pins are **FT (5 V tolerant)**. |
| STM32 toolchain | **STM32CubeMX** (code gen) + **STM32CubeF4** MCU package + **PlatformIO `ststm32`** | Month 2 plan is PlatformIO + VS Code on Windows, CubeMX as a separate generator. ST-Link is onboard, so no debugger purchase. |
| Timer/PWM for servos | Timer sections of RM0390 (advanced + general timers, ARR/PSC, PWM channels) | Servo refresh is 50 Hz with 500–2500 µs pulses; compute the prescaler by hand once so it is understood, not copied. |
| MG996R / MG90S | Generic datasheet for the model (varies by vendor) + measured numbers | Spec sheets lie about stall current and backlash. Sweep and measure deadband at the bench; feed the real numbers into PTZ limits. |
| SSD1306 | SSD1306 controller datasheet; I2C address usually 0x3C | 1 KB framebuffer (128×64/8), so SRAM is a non-issue. Two wires. Mature driver ecosystem. |
| GC9A01 (if TFTs chosen) | GC9A01 datasheet; SPI 4-wire mode 0/3 | 240×240×16-bit ≈ **115 KB per frame**, so two eyes cannot be fully buffered on 128 KB SRAM — dirty-rectangle rendering is mandatory. Buy the version **pre-soldered to a breakout with header pins**; bare 0.5 mm FPC is unusable on a breadboard. "SPI and I2C" on a Waveshare round module means SPI for pixels, I2C for the touch controller. |
| IRLZ44N | IRZ44N datasheet, logic-level gate charge curve | Confirm V_GS(th) and R_DS(on) at 4.5 V, not 10 V. |
| BeagleBone Black | AM335x Technical Reference Manual; the board's **PRU**, eHRPWM, eCAP, eQEP chapters | If BBB becomes the compute node, PRU + CAN + encoder hardware is the differentiator. Boot from microSD; keep the 4 GB eMMC free. Check your revision (Black / Black Wireless / Green) for which images are maintained. |
| Safety / E-stop | IEC 60204-1 stop-category ideas (informative, not required reading) | The practical rule that matters: NC fails safe, NO fails hidden. |

---

## Price confidence

Numbers here come from planning conversations, not live lookups. Two of them were already corrected mid-thread (an F429ZI quoted at $70 that turned out to be obsolete-part markup; a $22 F446RE that sold out on Amazon). Known market pressure: 2026 memory pricing inflated SBC prices badly (a Pi 5 16 GB was quoted at $385, Jetson Orin Nano at $499) while MCUs and passives stayed flat.

Rules that survived verification: authorized distributor for STM32 boards, Pine Store direct for the iron, Amazon for commodity passives, and buy small light parts (displays, MOSFETs, buttons, E-stop) in-region to avoid transatlantic shipping on pennies-per-part items.

---

## Open decisions

| # | Decision | Blocks | Recommended |
|---|---|---|---|
| 1 | Servo family: MG90S or MG996R | H2, H3, F2, safety spec | **MG90S.** Mass and torque are the right shape for a head near children, it matches the existing roadmap and bracket plan, and 5 V 3 A is enough. |
| 2 | Compute node: owned BBB, Jetson, or RK3588 | F1, roadmap Months 5–8 | **BBB now ($0), vision on Nomad.** Decide SBC at Month 5 with real frame-rate data. |
| 3 | Eyes in Phase 1 or Month 12 | H8 | **Month 12**, per roadmap. Eyes are the least load-bearing item and the loop is what needs proving. |
| 4 | Bracket: 3D print or off-the-shelf set | F2, T12 | Print at Month 5; buy the set only if printing slips. |
| 5 | Uno safety supervisor in or out | none | Out for Phase 1; revisit at Month 9 when watchdog and fault states are real. |
