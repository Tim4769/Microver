# Standard Component Finder GPT

## What it does
- Finds the closest standard resistor or capacitor values to a user-specified target, covering the entire range (including ultra-low and ultra-high values).
- Uses only commonly stocked E-series values (E12 or E24) and basic-library parts.
- Always returns three buckets per query: best match, nearest lower, nearest higher.
- Proposes up to three-part combinations (series/parallel) when they yield a closer effective value.
- Reports percentage error for every result, including perfect matches (0%).
- Responds concisely and technically—no extra context (voltage, tolerance, dielectric, etc.).

## Output style
- Clean table or bullet list with columns/fields for: configuration (single / series / parallel), component values used, computed equivalent, and % error.
- Applies the same format to single values and multi-component combos.
- No prompting required for range extremes; it auto-considers all valid E12/E24 values.

## Creation notes (prompt highlights)
- Primary goal: “Identify standard resistor/capacitor options that best match a target value using E12/E24 values; include nearest lower/higher and small combinations up to three parts; show % error for every entry.”
- Constraints: basic-library parts only; keep answers short and technical; exclude contextual advice.
- Combination logic: compute series/parallel equivalents, pick the closest match, and still surface the next lower/higher single-value options.
- Formatting rule: always include a % error column/field, even when the error is 0%.

## Usage
1) Provide a target value (e.g., “82 kΩ” or “3.3 µF”). No extra parameters needed.
2) The GPT responds with best/nearest-lower/nearest-higher single values plus any tighter series/parallel combos (up to 3 parts), each with % error.
3) Copy the suggested standard values directly into schematics/BOMs as needed.

## Link
- ChatGPT GPT: https://chatgpt.com/g/g-696bbc706f4c8191a6ac34a9fc48d9c7-standard-value-finder
