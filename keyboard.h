#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <raylib.h>
#include <string.h>

#define WIDTH 1200
#define HEIGHT 700
#define FONT_SIZE 18

#define UI_WHITE     (Color){ 255, 255, 255, 255 }
#define UI_DARK      (Color){ 10, 10, 10, 255 }
#define UI_GRAY      (Color){ 10, 10, 10, 255 }

typedef struct {
    int x, y, w, h;
} Region;

typedef struct {
    Rectangle rect;
    char label[16];
    char capLabel[16];
    int keyCode;
} Key;

void DrawKey(Key *key, Font font);
void AddKey(Key *keys, int *count, int row, float widthMult, const char *l, const char *cl, int code, Region r);
void BuildKeyboard(Font font);

#endif
