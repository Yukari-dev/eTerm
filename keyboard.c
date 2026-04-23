#include "keyboard.h"

void AddKey(Key *keys, int *count, int row, float widthMult, const char *l, const char *cl, int code, Region r) {
    int i = *count;
    float baseW = 50.0f;
    float baseH = 50.0f;
    float currentX = 0;

    for (int j = 0; j < i; j++) {
        if (keys[j].rect.y == (r.y + row * baseH)) {
            currentX += keys[j].rect.width;
        }
    }

    keys[i].rect = (Rectangle){ r.x + currentX, r.y + (row * baseH), baseW * widthMult, baseH };
    strcpy(keys[i].label, l);
    strcpy(keys[i].capLabel, cl);
    keys[i].keyCode = code;
    (*count)++;
}

void DrawKey(Key *key, Font font) {
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    bool pressed = IsKeyDown(key->keyCode);

    DrawRectangleRec(key->rect, pressed ? UI_WHITE : UI_DARK);

    const char *text = shift ? key->capLabel : key->label;
    Vector2 textSize = MeasureTextEx(font, text, FONT_SIZE, 1);
    
    Vector2 pos = {
        key->rect.x + (key->rect.width - textSize.x) / 2,
        key->rect.y + (key->rect.height - textSize.y) / 2
    };

    DrawTextEx(font, text, pos, FONT_SIZE, 1, pressed ? BLACK : UI_WHITE);
}

void BuildKeyboard(Font font) {
    Region r = { WIDTH / 2 - 350, HEIGHT - 300, 700, 250 };
    static Key keys[100];
    static int keyCount = 0;
    static bool init = false;

    if (!init) {
        AddKey(keys, &keyCount, 0, 1.0f, "`", "~", KEY_GRAVE, r);
        AddKey(keys, &keyCount, 0, 1.0f, "1", "!", KEY_ONE, r);
        AddKey(keys, &keyCount, 0, 1.0f, "2", "@", KEY_TWO, r);
        AddKey(keys, &keyCount, 0, 1.0f, "3", "#", KEY_THREE, r);
        AddKey(keys, &keyCount, 0, 1.0f, "4", "$", KEY_FOUR, r);
        AddKey(keys, &keyCount, 0, 1.0f, "5", "%", KEY_FIVE, r);
        AddKey(keys, &keyCount, 0, 1.0f, "6", "^", KEY_SIX, r);
        AddKey(keys, &keyCount, 0, 1.0f, "7", "&", KEY_SEVEN, r);
        AddKey(keys, &keyCount, 0, 1.0f, "8", "*", KEY_EIGHT, r);
        AddKey(keys, &keyCount, 0, 1.0f, "9", "(", KEY_NINE, r);
        AddKey(keys, &keyCount, 0, 1.0f, "0", ")", KEY_ZERO, r);
        AddKey(keys, &keyCount, 0, 1.0f, "-", "_", KEY_MINUS, r);
        AddKey(keys, &keyCount, 0, 1.0f, "=", "+", KEY_EQUAL, r);
        AddKey(keys, &keyCount, 0, 3.0f, "BKSP", "BKSP", KEY_BACKSPACE, r);

        AddKey(keys, &keyCount, 1, 1.5f, "TAB", "TAB", KEY_TAB, r);
        AddKey(keys, &keyCount, 1, 1.0f, "q", "Q", KEY_Q, r);
        AddKey(keys, &keyCount, 1, 1.0f, "w", "W", KEY_W, r);
        AddKey(keys, &keyCount, 1, 1.0f, "e", "E", KEY_E, r);
        AddKey(keys, &keyCount, 1, 1.0f, "r", "R", KEY_R, r);
        AddKey(keys, &keyCount, 1, 1.0f, "t", "T", KEY_T, r);
        AddKey(keys, &keyCount, 1, 1.0f, "y", "Y", KEY_Y, r);
        AddKey(keys, &keyCount, 1, 1.0f, "u", "U", KEY_U, r);
        AddKey(keys, &keyCount, 1, 1.0f, "i", "I", KEY_I, r);
        AddKey(keys, &keyCount, 1, 1.0f, "o", "O", KEY_O, r);
        AddKey(keys, &keyCount, 1, 1.0f, "p", "P", KEY_P, r);
        AddKey(keys, &keyCount, 1, 2.5f, "[", "{", KEY_LEFT_BRACKET, r);

        AddKey(keys, &keyCount, 2, 1.8f, "CAPS", "CAPS", KEY_CAPS_LOCK, r);
        AddKey(keys, &keyCount, 2, 1.0f, "a", "A", KEY_A, r);
        AddKey(keys, &keyCount, 2, 1.0f, "s", "S", KEY_S, r);
        AddKey(keys, &keyCount, 2, 1.0f, "d", "D", KEY_D, r);
        AddKey(keys, &keyCount, 2, 1.0f, "f", "F", KEY_F, r);
        AddKey(keys, &keyCount, 2, 1.0f, "g", "G", KEY_G, r);
        AddKey(keys, &keyCount, 2, 1.0f, "h", "H", KEY_H, r);
        AddKey(keys, &keyCount, 2, 1.0f, "j", "J", KEY_J, r);
        AddKey(keys, &keyCount, 2, 1.0f, "k", "K", KEY_K, r);
        AddKey(keys, &keyCount, 2, 1.0f, "l", "L", KEY_L, r);
        AddKey(keys, &keyCount, 2, 3.2f, "ENTER", "ENTER", KEY_ENTER, r);

        AddKey(keys, &keyCount, 3, 2.3f, "SHIFT", "SHIFT", KEY_LEFT_SHIFT, r);
        AddKey(keys, &keyCount, 3, 1.0f, "z", "Z", KEY_Z, r);
        AddKey(keys, &keyCount, 3, 1.0f, "x", "X", KEY_X, r);
        AddKey(keys, &keyCount, 3, 1.0f, "c", "C", KEY_C, r);
        AddKey(keys, &keyCount, 3, 1.0f, "v", "V", KEY_V, r);
        AddKey(keys, &keyCount, 3, 1.0f, "b", "B", KEY_B, r);
        AddKey(keys, &keyCount, 3, 1.0f, "n", "N", KEY_N, r);
        AddKey(keys, &keyCount, 3, 1.0f, "m", "M", KEY_M, r);
        AddKey(keys, &keyCount, 3, 1.0f, ",", "<", KEY_COMMA, r);
        AddKey(keys, &keyCount, 3, 3.7f, "SHIFT", "SHIFT", KEY_RIGHT_SHIFT, r);

        AddKey(keys, &keyCount, 4, 14.0f, " ", " ", KEY_SPACE, r);
        init = true;
    }

    for (int i = 0; i < keyCount; i++) DrawKey(&keys[i], font);
}
