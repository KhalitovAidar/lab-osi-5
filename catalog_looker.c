#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Ошибка открытия каталога");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }

    if (closedir(dir) != 0) {
        perror("Ошибка закрытия каталога");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    printf("Содержимое текущего каталога:\n");
    list_directory(".");

    if (argc < 2) {
        fprintf(stderr, "Использование: %s <каталог>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("\nСодержимое каталога '%s':\n", argv[1]);
    list_directory(argv[1]);

    return EXIT_SUCCESS;
}

