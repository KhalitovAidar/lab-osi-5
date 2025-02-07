#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Нет нужных аргументов");
        return 1;
    }

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    printf("Введите текст. Для завершения ввода нажмите Ctrl + F:\n");

    int ch;
    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == 6) {
            printf("\nЗавершение ввода...\n");
            break;
        }

        if (fputc(ch, file) == EOF) {
            perror("Ошибка при записи в файл");
            fclose(file);
            return 1;
        }
    }

    if (fclose(file) == EOF) {
        perror("Ошибка при закрытии файла");
        return 1;
    }

    printf("Записано в файл '%s'.\n", argv[1]);
    return 0;
}
