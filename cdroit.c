#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat st;
    mode_t mode;
    int val;
    char who;

    if (argc != 4) { fprintf(stderr, "Usage: %s <fichier> <U|G|O> <0-7|E>\n", argv[0]); return 1; }
    if (stat(argv[1], &st) == -1) { perror("stat"); return 1; }

    who = argv[2][0];
    val = strcmp(argv[3], "E") == 0 ? 0 : atoi(argv[3]);
    mode = st.st_mode & 0777;

    if      (who == 'U') mode = (mode & ~0700) | (val << 6);
    else if (who == 'G') mode = (mode & ~0070) | (val << 3);
    else if (who == 'O') mode = (mode & ~0007) |  val;
    else { fprintf(stderr, "Type invalide: U, G ou O\n"); return 1; }

    if (chmod(argv[1], mode) == -1) { perror("chmod"); return 1; }
    printf("Droits mis a jour: %o\n", mode);
    return 0;
}
