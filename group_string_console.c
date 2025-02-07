#include <stdio.h>
#include <stdlib.h>

void print_file_content(const char *filename, int N) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    int ch;

    while ((ch = getc(file)) != EOF) {
        putc(ch, stdout);
        if (ch == '\n') {
            count++;
            if (N > 0 && count == N) {
                printf("Нажмите любую клавишу для продолжения...\n");
                getchar(); 
                count = 0; 
            }
        }
    }

    if (fclose(file) != 0) {
        perror("Ошибка закрытия файла");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <имя_файла> [N]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int N = (argc > 2) ? atoi(argv[2]) : 0;

    print_file_content(filename, N);

    return EXIT_SUCCESS;
}



