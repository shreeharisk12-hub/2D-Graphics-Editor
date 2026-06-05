# ░▒▓ ASCII CANVAS v2 ▓▒░
### *Now with memory. Your shapes don't disappear anymore.*

```
+--------------------------------------------------------------------------------+
|  _____*********************____________________________________________________  |
|  _____*____***____________*____________*****___________________________________  |
|  _____*_______***_________*___________*_____*__________________________________  |
|  _____*__________***______*__________*_______*_________________________________  |
|  _____*_____________**____*_________*_________*________________________________  |
|  _____*___________________*_________*_________*________________________________  |
|  _____*********************_________*_________*________________________________  |
|  ____________________________________*_______*_________________________________  |
+--------------------------------------------------------------------------------+
```

---

## What changed in v2?

v1 drew shapes directly onto the canvas and forgot them immediately.

v2 introduces an **object list** — every shape you add is stored in memory with its type and coordinates. The canvas is rebuilt from scratch every time you display it, by replaying all stored objects. This means you can add multiple shapes, delete one, and the rest remain intact.

| Feature | v1 | v2 |
|---|---|---|
| Menu structure | Draw directly | Add / Delete / Modify / Display / List |
| Shape memory | ❌ None | ✅ Object array (up to 100) |
| Delete a shape | ❌ Impossible | ✅ By index |
| Modify a shape | ❌ Impossible | ✅ By index |
| List all objects | ❌ | ✅ |
| Canvas rendering | Immediate | On-demand (option 4) |

---

## Build & Run

```bash
gcc -o canvas main.c -lm
./canvas
```

---

## Menu

```
2D Graphics Editor
Canvas size: 80 x 24
1. Add object
2. Delete object
3. Modify object
4. Display picture
5. List objects
0. Exit
Enter choice:
```

### 1. Add Object

Prompts a shape sub-menu, then takes coordinates:

```
Choose shape type:
1. Line
2. Rectangle
3. Circle
4. Triangle
Enter shape type:
```

| Shape | Input format |
|---|---|
| Line | `x1 y1 x2 y2` |
| Rectangle | `top-left x y` → `bottom-right x y` |
| Circle | `center x y radius` |
| Triangle | `x1 y1 x2 y2 x3 y3` |

Each added shape gets an index starting from `0`:
```
Object added with index 0.
Object added with index 1.
```

### 2. Delete Object

Enter the index to remove. Remaining objects shift down to fill the gap.

### 3. Modify Object

Enter an index, pick a new shape type, re-enter coordinates. The slot is updated in-place.

### 4. Display Picture

Clears the canvas, replays all stored objects, and prints the 80×24 grid.

### 5. List Objects

Prints a summary of every stored shape with its index and parameters.

---

## Coordinate System

```
(0,0) ──────────────────► x  (79)
  │
  │        canvas lives here
  │
  ▼
  y
(23)
```

Origin is **top-left**. x goes right, y goes down.

---

## Algorithms

**Lines → Bresenham's Line Algorithm**
Integer-only. Handles all slopes. No gaps. The same algorithm used to drive CRT electron guns in 1962.

**Circles → Midpoint Circle Algorithm**
Computes one octant, mirrors across all 8. 8× output for the same math. No `sin`/`cos` needed.

**Rectangles → 4× `drawLine`**
Top, right, bottom, left edges.

**Triangles → 3× `drawLine`**
Three vertices, three edges.

---

## Internal Structure

```c
typedef struct {
    int type;       // 1=Line 2=Rect 3=Circle 4=Triangle
    int params[6];  // coordinates (shape-dependent)
} Shape;

Shape objects[MAX_OBJECTS];  // stores up to 100 shapes
int objectCount = 0;
```

`renderAll()` iterates this array and redraws everything onto a freshly cleared canvas each time Display is called. This is a simple **retained mode** graphics model — the same concept used in modern UI frameworks like React or SwiftUI, just with `*` characters.

---

## Project Info

Built for **REVA University** — CS Advanced C Programming, Mini Project (ISE A/B).
Submitted via VPL (Virtual Programming Lab).

Written in C. No external libraries. No build system.
Just `gcc`, a terminal, and Bresenham.

---

*"First, solve the problem. Then, write the code."*
*— John Johnson*
