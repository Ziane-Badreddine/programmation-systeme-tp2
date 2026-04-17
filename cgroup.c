#include <stdio.h>
#include <sys/stat.h>
#include <grp.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat st;
    struct group *gr;

    if (argc != 3) { fprintf(stderr, "Usage: %s <fichier> <groupe>\n", argv[0]); return 1; }
    if (stat(argv[1], &st) == -1) { perror("stat"); return 1; }

    gr = getgrnam(argv[2]);
    if (!gr) { fprintf(stderr, "Groupe '%s' introuvable\n", argv[2]); return 1; }

    if (chown(argv[1], st.st_uid, gr->gr_gid) == -1) { perror("chown"); return 1; }
    printf("Groupe de '%s' -> %s\n", argv[1], argv[2]);
    return 0;
}
