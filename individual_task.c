#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void search_files(const char *dir_path, long min_size, long max_size, FILE *output_file, int *file_count) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Ошибка открытия каталога");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode)) {
                search_files(full_path, min_size, max_size, output_file, file_count);
            } else if (file_stat.st_size >= min_size && file_stat.st_size <= max_size) {
                fprintf(output_file, "Путь: %s, Имя: %s, Размер: %ld байт\n", full_path, entry->d_name, file_stat.st_size);
            }
        }
        (*file_count)++;
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Использование: %s <каталог> <min_size> <max_size> <выходной_файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dir_path = argv[1];
    long min_size = atol(argv[2]);
    long max_size = atol(argv[3]);
    const char *output_file_path = argv[4];

    FILE *output_file = fopen(output_file_path, "w");
    if (output_file == NULL) {
        perror("Ошибка открытия выходного файла");
        return EXIT_FAILURE;
    }

    int file_count = 0;
    search_files(dir_path, min_size, max_size, output_file, &file_count);

    fclose(output_file);
    printf("Общее число просмотренных файлов: %d\n", file_count);

    return EXIT_SUCCESS;
}

