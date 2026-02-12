# LM5050 Redundant Supply Board (High Side ORing) - Rev A

**Project:** LM5050 Redundant Supply Board  
**Owner / Contact:** Tim Wang - timwang007@outlook.com  
**Revision:** Rev A  
**Date:** 2026-02-11

## 1) Overview
This board implements the LM5050-1 Typical Redundant Supply Configuration to auto-select between two power sources for one output rail:
- `18 V` battery input
- `36 V` boost-converter input (when enabled)

The goal is seamless source switchover while preventing backfeed into the inactive source.

## 2) Source Selection Behavior
- The LM5050 ideal-diode ORing behavior prioritizes the higher available source.
- With both rails present, the `36 V` boost path supplies the load.
- If the boost rail is off or unavailable, the board falls back to the `18 V` battery path.
- Reverse current into the inactive source path is blocked.

## 3) Electrical Notes
- Validate all components for worst-case voltage, current, and thermal conditions.
- Confirm MOSFET SOA and thermal rise at full expected load.
- Verify startup and switchover behavior with the real upstream battery and boost converter.

## 4) Files Included
- `Gerber/`
- `Gerber.zip`
- `High Side OR ing-top-pos.csv`
- `High Side OR ing-bottom-pos.csv`
- `README.md`

## 5) Bring-up Checklist
1) Power each input separately with a current-limited bench supply and confirm correct output behavior.  
2) Test both inputs active and verify clean source handoff under no-load and loaded conditions.  
3) Confirm no reverse current into the inactive source during all operating states.  

## 6) References
- TI LM5050-1 datasheet (`lm5050-1.pdf`)
- Local reference copy: `/Users/a1/Downloads/lm5050-1.pdf`
