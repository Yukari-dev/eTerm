#include "shell.h"

int main(void) {
    InitWindow(600, 400, "shell");
    SetTargetFPS(30);

    char input[100] = "";
    int length = 0;
    char output[MAX_OUTPUT][100] = { "" };
    int output_count = 0;

    while (!WindowShouldClose()) {
        int key = GetCharPressed();
        while (key > 0) {
            if (length < 99) {
                input[length] = (char)key;
                length++;
                input[length] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && length > 0) {
            length--;
            input[length] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && length > 0) {
            if (strcasecmp(input, "exit") == 0 || strcasecmp(input, "q") == 0) {
                break;
            }
            run_command(input, output, &output_count);
            input[0] = '\0';
            length = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Welcome to shell :3", 20, 10, 20, WHITE);
        DrawText(TextFormat(":> %s_", input), 20, 40, 20, GREEN);

        for (int i = 0; i < output_count; i++) {
            DrawText(output[i], 20, 80 + i * 20, 16, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void run_command(const char *cmd, char output[MAX_OUTPUT][100], int *count) {
    char copy[100];
    strcpy(copy, cmd);

    char *first_word  = strtok(copy, " ");
    char *second_word = strtok(NULL, " ");

    if (first_word == NULL) return;

    if (strcasecmp(first_word, "ls") == 0) {
        FILE *fp = popen("ls", "r");
        if (fp) {
            *count = 0;
            while (fgets(output[*count], 100, fp) && *count < MAX_OUTPUT) {
                output[*count][strcspn(output[*count], "\n")] = '\0';
                (*count)++;
            }
            pclose(fp);
        }
    }
    else if (strcasecmp(first_word, "cd") == 0) {
        if (second_word && chdir(second_word) == 0) {
            strcpy(output[0], "directory changed");
        } else {
            strcpy(output[0], "cd: failed");
        }
        *count = 1;
    }
    else if (strcasecmp(first_word, "clear") == 0) {
        *count = 0;
    }
    else {
        snprintf(output[0], 100, "unknown: %s", first_word);
        *count = 1;
    }
}
