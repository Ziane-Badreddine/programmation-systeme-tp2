#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat st;
    struct passwd *pw;
    char buf[64];

    if (argc != 2) { fprintf(stderr, "Usage: %s <fichier>\n", argv[0]); return 1; }
    if (stat(argv[1], &st) == -1) { perror("stat"); return 1; }

    printf("Type  : %s\n", S_ISDIR(st.st_mode) ? "Repertoire" : S_ISLNK(st.st_mode) ? "Lien" : "Fichier");
    printf("Droits: %o\n", st.st_mode & 0777);
    printf("Taille: %ld octets\n", (long)st.st_size);
    printf("Liens : %ld\n", (long)st.st_nlink);

    pw = getpwuid(st.st_uid);
    printf("Owner : %s\n", pw ? pw->pw_name : "inconnu");

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&st.st_mtime));
    printf("Date  : %s\n", buf);

    return 0;
}
