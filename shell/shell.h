#ifndef SHELL_H
#define SHELL_H

#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT 100
#define MAX_OUTPUT 20
#define OUTPUT_LINE_LENGTH 100

void run_command(const char *cmd, char output[MAX_OUTPUT][OUTPUT_LINE_LENGTH], int *count);
void draw_shell(const char *input, char output[MAX_OUTPUT][OUTPUT_LINE_LENGTH], int output_count);

#endif
