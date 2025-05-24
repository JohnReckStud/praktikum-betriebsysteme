#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {
    const char *prog = getenv("TOBEINVOKED");

    if (prog == NULL) {
        fprintf(stderr, "Fehler: Umgebungsvariable TOBEINVOKED ist nicht gesetzt.\n");
        return 1;
    }

    if (strcmp(prog, "date") != 0 && strcmp(prog, "cal") != 0) {
        fprintf(stderr, "Fehler: TOBEINVOKED muss entweder \"date\" oder \"cal\" sein.\n");
        return 1;
    }

    if (argc != 2) {
        fprintf(stderr, "Benutzung: %s <Anzahl>\n", argv[0]);
        return 1;
    }

    int anzahl = atoi(argv[1]);
    if (anzahl <= 0) {
        fprintf(stderr, "Ungültige Anzahl: %s\n", argv[1]);
        return 1;
    }

    for (int i = 0; i < anzahl; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Kindprozess
            execlp(prog, prog, (char *)NULL);
            perror("execlp"); // wird nur erreicht, wenn execlp fehlschlägt
            exit(1);
        } else if (pid > 0) {
            wait(NULL); // Elternprozess wartet
        } else {
            perror("fork");
            return 1;
        }
    }

    return 0;
}
