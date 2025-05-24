#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Umgebungsvariable lesen
    const char *env = getenv("TOBEINVOKED");

    if (env == NULL) {
        fprintf(stderr, "Umgebungsvariable TOBEINVOKED ist nicht gesetzt.\n");
        return 1;
    }

    // Entscheidung: welchen Befehl ausführen
    if (strcmp(env, "date") == 0) {
        execlp("date", "date", (char *)NULL);
    } else if (strcmp(env, "cal") == 0) {
        execlp("cal", "cal", (char *)NULL);
    } else {
        fprintf(stderr, "Unbekannter Wert für TOBEINVOKED: %s\n", env);
        return 1;
    }

    // Falls execlp fehlschlägt
    perror("execlp");
    return 1;
}
