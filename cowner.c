#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat st;
    struct passwd *pw;

    if (argc != 3) { fprintf(stderr, "Usage: %s <fichier> <user>\n", argv[0]); return 1; }
    if (stat(argv[1], &st) == -1) { perror("stat"); return 1; }

    pw = getpwnam(argv[2]);
    if (!pw) { fprintf(stderr, "User '%s' introuvable\n", argv[2]); return 1; }

    if (chown(argv[1], pw->pw_uid, st.st_gid) == -1) { perror("chown"); return 1; }
    printf("Owner de '%s' -> %s\n", argv[1], argv[2]);
    return 0;
}
