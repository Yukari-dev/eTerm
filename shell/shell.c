#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

void ls_command(void);
void cd_command(char *path);
void input_usr(void);

int main(void) {
    printf("welcome to  shell :3  \n");
    input_usr();
    return 0;
}

void input_usr(void) {
    while (true) {
        printf(":> ");

        char command[100];
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0';

        char *first_word  = strtok(command, " ");
        char *second_word = strtok(NULL, " ");

        if (first_word == NULL) {
            continue;
        }

        if (strcasecmp(first_word, "ls") == 0) {
            ls_command();
        }
        else if (strcasecmp(first_word, "cd") == 0) {
            cd_command(second_word);
        }
        else if (strcasecmp(first_word, "exit") == 0 || 
                 strcasecmp(first_word, "q") == 0) {
            printf("goodbye :3\n");
            break;
        }
        else {
            printf("unknown command: %s\n", first_word);
        }
    }
}

void ls_command(void) {
    pid_t pid = fork();

    if (pid == 0) {
        execlp("ls", "ls", NULL);
        perror("ls");
        _exit(1);
    }
    else if (pid > 0) {
        waitpid(pid, NULL, 0);
    }
    else {
        perror("fork");
    }
}

void cd_command(char *path) {
    if (path == NULL) {
        printf("cd: where do you want to go?\n");
        return;
    }
    if (chdir(path) != 0) {
        perror("cd");
    }
}
