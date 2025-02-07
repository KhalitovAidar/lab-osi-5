#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void copy_file(const char *source, const char *destination) {
    FILE *src_file = fopen(source, "r");
    if (src_file == NULL) {
        perror("Ошибка открытия исходного файла");
        exit(EXIT_FAILURE);
    }

    FILE *dest_file = fopen(destination, "w");
    if (dest_file == NULL) {
        perror("Ошибка открытия целевого файла");
        fclose(src_file);
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = getc(src_file)) != EOF) {
        if (putc(ch, dest_file) == EOF) {
            perror("Ошибка записи в целевой файл");
            fclose(src_file);
            fclose(dest_file);
            exit(EXIT_FAILURE);
        }
    }

    if (fclose(src_file) != 0) {
        perror("Ошибка закрытия исходного файла");
        fclose(dest_file);
        exit(EXIT_FAILURE);
    }

    if (fclose(dest_file) != 0) {
        perror("Ошибка закрытия целевого файла");
        exit(EXIT_FAILURE);
    }

    struct stat file_stat;
    if (stat(source, &file_stat) == -1) {
        perror("Ошибка получения информации о файле");
        exit(EXIT_FAILURE);
    }

    if (chmod(destination, file_stat.st_mode) == -1) {
        perror("Ошибка установки прав доступа");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <исходный_файл> <целевой_файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *destination_file = argv[2];

    copy_file(source_file, destination_file);

    return EXIT_SUCCESS;
}

