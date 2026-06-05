# ░▒▓ ASCII CANVAS ▓▒░
### *A terminal graphics editor written in C — because pixels are overrated.*

```
+--------------------------------------------------------------------------------+
|  ____________________________*_______________________                          |
|  _______________________*_________*__________________                          |
|  ___________*__________/ \________/ \________________                          |
|  __________/ \________/   \______/   \_______________                          |
|  _________/   \______/     \____/     \______________   ← your masterpiece     |
|  ________/     \____/       \__/       \*____________                          |
|  _______*_______\__/    *    \/    *    \____________                          |
+--------------------------------------------------------------------------------+
```

---

## What is this?

A 2D graphics editor that runs entirely in your terminal. No GPU. No OpenGL. No 500MB framework. Just a `char` array, some clever integer math, and your imagination.

You draw shapes. They appear as `*` characters on an `80×24` canvas. That's the whole deal.

---

## Features

| Shape | Algorithm used |
|---|---|
| Line | Bresenham's Line Algorithm (integer-only, gap-free) |
| Rectangle | Four calls to `drawLine` |
| Circle | Midpoint Circle Algorithm (8-way symmetry) |
| Triangle | Three calls to `drawLine` |

**Why Bresenham?**
Because `y = mx + b` with floats gives you ugly gaps and rounding errors. Bresenham's works entirely in integers — the same algorithm that was used to drive CRT electron guns in the 1960s. Your terminal deserves that heritage.

**Why the Midpoint Circle?**
Computing `sin`/`cos` for every pixel is slow and wasteful. The midpoint algorithm figures out one octant and mirrors it across all 8 — 8× the output for the same work.

---

## Build & Run

```bash
# Compile
gcc -o canvas main.c -lm

# Run
./canvas
```

> Requires a C compiler (gcc/clang) and a terminal that's at least 82 columns wide.

---

## Usage

```
2D ASCII Graphics Editor
Canvas size: 80 x 24
x range: 0 to 79
y range: 0 to 23

--- Menu ---
1. Line
2. Rectangle
3. Circle
4. Triangle
5. Display
6. Clear
0. Exit
```

Coordinates start at `(0, 0)` in the **top-left** corner.
`x` goes right → and `y` goes down ↓.

### Example session

```
Choice: 3
Center x y, radius: 39 11 8
Circle drawn.

Choice: 2
Top-left x y, bottom-right x y: 30 3 50 20
Rectangle drawn.

Choice: 5
The picture is:
+---[canvas renders here]---+
```

---

## Project Structure

```
.
└── main.c          # Everything. One file. Old school.
```

This is C. We don't need a `src/`, `lib/`, `dist/`, `node_modules/`, or a config file named after a planet.

---

## Canvas Coordinate System

```
(0,0) ──────────────────► x  (79)
  │
  │        your art lives here
  │
  ▼
  y
(23)
```

---

## Known Limitations (aka *features*)

- The canvas does **not** auto-display after drawing. Call option `5` yourself — this is not a GUI babysitter.
- Overlapping shapes overwrite each other. No layers. No undo. Commit to your art.
- Canvas is `char` array in stack memory. It will not survive a power cut.
- Circles look slightly squished. Terminal characters are taller than they are wide. This is a terminal problem, not a math problem.

---

## The Philosophy

> *"Any fool can use a computer. Many do."*
> — Ted Nelson

This project exists at the intersection of:
- **Low-level C** — direct memory, no abstractions
- **Classical algorithms** — Bresenham (1962), Midpoint Circle (1967)
- **Constraints as creativity** — 80 columns, 24 rows, two characters

No dependencies. No build system. No bloat. Just `gcc main.c` and a blinking cursor.

---

## Author

Built for **REVA University** C Programming coursework.
Written by hand. Debugged with `printf`. Perfected through suffering.

---

*"The art of programming is the art of organizing complexity."*
*— Edsger W. Dijkstra*