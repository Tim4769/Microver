# Rover Motion Stack – Software Handoff
Date: January 28, 2026  
Target: Software engineer writing and testing rover motion code on Raspberry Pi + two Arduino Nano Every boards.

---

## 1) System at a Glance
- **MCUs:** 2× Arduino Nano Every.  
  - **Every 1** → 6 brushed DC motors (3 left, 3 right) + 4 encoders + link to Every 2.  
  - **Every 2** → 4 hobby servos.  
- **Host:** Raspberry Pi (USB CDC to Every 1).  
- **Motor drivers:** DRV8871 breakouts (per motor input pair). Default current limit ≈2 A unless Rlim changed. Supports up to ~45 V motor supply and ~3.6 A peak before limiting/thermal.

---

## 2) Pin Maps (authoritative)
### Arduino Every 1 — DC drive + encoders
- Left motor group (three drivers in parallel): D5, D6.  
- Right motor group: D9, D10.  
- Encoders:  
  - E1 A/B: D16 / D17  
  - E2 A/B: D14 / D15  
  - E3 A/B: D20 / D21  
  - E4 A/B: D18 / D19

### Arduino Every 2 — Servos
- D5 → Servo 1; D6 → Servo 2; D9 → Servo 3; D10 → Servo 4.  
Typical sweep used in tests: 40–140° around 90° center.

### Inter‑Arduino Link (Every1 ↔ Every2)
- SoftwareSerial, 38 400 baud, 8N1.  
- Every 1 TX/RX: D11/D12. Every 2 TX/RX: D12/D11.  
- Current messages: `PING,<seq>\n` ↔ `ACK,<seq>,<servoId>,<activeFlag>`.

### Pi ↔ Every 1
- USB CDC recommended.

---


## 3) Motor Control (Every 1)
- DRV8871 truth table (per side):  
  - IN1=LOW + PWM on IN2 → Forward.  
  - IN2=LOW + PWM on IN1 → Reverse.   
- Boot: set both pins LOW; ramp PWM to avoid kicks. Recommended PWM ≈20 kHz. Start ≤200/255 to respect ~2 A default limit.  

---

## 4) Encoders & Odometry (Every 1)
- Four quadrature channels; attach interrupts on both A/B for each pin (works on Nano Every).  
- Atomic read: copy counts inside `noInterrupts()` then zero to avoid race.  
- Two encoders per side; average (E1,E2) for left and (E3,E4) for right to reduce slip noise.  
- Use Δcounts per loop for wheel speed; feed differential‑drive odometry (Δs_left/right → pose).

---

## 5) Servo Control (Every 2)
- Center at 90°. Tested sweep 40–140°.  
- Move one servo at a time when possible; share 5 V rail with other loads.  
- Maintain `servoMotionActive` flag and include `servoId`+`activeFlag` in ACK so Every 1/Pi can queue or defer moves.

---

## 6) Validation Steps
1) **Inter‑Arduino link** – send `PING,0\n` from Every 1 over D11/D12; expect `ACK,0,<servoId>,<active>`.  
2) **Motors** – Command forward/reverse on each side; confirm encoders count up when wheels spin (hand‑spin OK).  
3) **Servos** – Sweep 40→140→40 on each pin (D5/D6/D9/D10) and verify current draw stays within rail budget.  
4) **Full chain** – Run loop: drive commands + servo command + health poll; verify watchdog brakes on removed link or pulled PGD.

---

## 7) Quick Reference (copy/paste friendly)
- Left pins: D5/D6. Right pins: D9/D10. Encoders: E1 D16/17, E2 D14/15, E3 D20/21, E4 D18/19.  
- Servos: D5 S1, D6 S2, D9 S3, D10 S4 on Every 2.  
- Link: D11/D12 @ 38 400 baud, `PING`/`ACK`.  


---

## 8) Suggested Next Coding Tasks
- Add CRC or checksum to messages.  
- Implement motor PID using encoder feedback.  
- Add Pi‑side watchdog that sends periodic `H`/`M` and halts if no ACK.  
