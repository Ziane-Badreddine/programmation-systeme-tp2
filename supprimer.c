#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) { fprintf(stderr, "Usage: %s <fichier>\n", argv[0]); return 1; }
    if (unlink(argv[1]) == -1) { perror("unlink"); return 1; }
    printf("Fichier '%s' supprime.\n", argv[1]);
    return 0;
}
