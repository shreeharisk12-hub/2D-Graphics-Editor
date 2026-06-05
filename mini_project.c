#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 24
#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];

void clearPicture() {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            picture[y][x] = EMPTY;
}

void displayPicture() {
    // Top border
    printf("+");
    for (int x = 0; x < WIDTH; x++) printf("-");
    printf("+\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < WIDTH; x++)
            printf("%c", picture[y][x]);
        printf("|\n");
    }

    // Bottom border
    printf("+");
    for (int x = 0; x < WIDTH; x++) printf("-");
    printf("+\n");
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        picture[y][x] = PIXEL;
}

// Bresenham's line algorithm
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        setPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1); // top
    drawLine(x2, y1, x2, y2); // right
    drawLine(x2, y2, x1, y2); // bottom
    drawLine(x1, y2, x1, y1); // left
}

// Midpoint circle algorithm
void drawCircle(int cx, int cy, int radius) {
    int x = 0, y = radius;
    int d = 1 - radius;

    // Helper lambda via macro to plot all 8 octants
    #define PLOT8(px, py) \
        setPixel(cx+(px), cy+(py)); setPixel(cx-(px), cy+(py)); \
        setPixel(cx+(px), cy-(py)); setPixel(cx-(px), cy-(py)); \
        setPixel(cx+(py), cy+(px)); setPixel(cx-(py), cy+(px)); \
        setPixel(cx+(py), cy-(px)); setPixel(cx-(py), cy-(px));

    while (x <= y) {
        PLOT8(x, y);
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    #undef PLOT8
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

int main() {
    int choice;
    clearPicture();

    printf("+---------------------------------+\n");
    printf("|    2D ASCII Graphics Editor     |\n");
    printf("+---------------------------------+\n");
    printf("Canvas: %d wide x %d tall\n", WIDTH, HEIGHT);
    printf("x: 0..%d  |  y: 0..%d\n\n", WIDTH - 1, HEIGHT - 1);

    while (1) {
        printf("--- Menu ---\n");
        printf("1. Line\n2. Rectangle\n3. Circle\n4. Triangle\n");
        printf("5. Display\n6. Clear\n0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int x1, y1, x2, y2;
            printf("x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            drawLine(x1, y1, x2, y2);
            printf("Line drawn.\n");
        } else if (choice == 2) {
            int x1, y1, x2, y2;
            printf("Top-left x y, bottom-right x y: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            drawRectangle(x1, y1, x2, y2);
            printf("Rectangle drawn.\n");
        } else if (choice == 3) {
            int cx, cy, r;
            printf("Center x y, radius: ");
            scanf("%d %d %d", &cx, &cy, &r);
            drawCircle(cx, cy, r);
            printf("Circle drawn.\n");
        } else if (choice == 4) {
            int x1, y1, x2, y2, x3, y3;
            printf("x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
            drawTriangle(x1, y1, x2, y2, x3, y3);
            printf("Triangle drawn.\n");
        } else if (choice == 5) {
            printf("Canvas:\n");
            displayPicture();
        } else if (choice == 6) {
            clearPicture();
            printf("Canvas cleared.\n");
        } else if (choice == 0) {
            printf("Goodbye.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}