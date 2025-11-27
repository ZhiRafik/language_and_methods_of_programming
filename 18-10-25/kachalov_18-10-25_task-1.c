#include <stdio.h>
#include <stdlib.h> // malloc, free, realloc
#include <string.h> // strlen, strcpy
#include <ctype.h>  // isalpha
#include <time.h>

typedef struct Node {
    char *word; // указатель на строку слова
    int length; // длина слова
    struct Node *next; // следующий элемент списка
} Node;

// проверка, можно ли символ считать частью слова
int is_word_char(int ch) {
    return isalpha((unsigned char)ch) || ch == '-' || ch == '\''; // допускаем буквы, дефис и апостроф
}

// добавление нового слова в конец списка
void add_word(Node **head, const char *word) {
    Node *new_node = malloc(sizeof(Node)); // выделяем память под узел
    new_node->word = malloc(strlen(word) + 1); // выделяем память под слово
    strcpy(new_node->word, word); // копируем строку
    new_node->length = (int)strlen(word); // сохраняем длину
    new_node->next = NULL; // пока нет следующего
    if (*head == NULL) *head = new_node; // если список пуст — это первый элемент
    else {
        Node *current = *head; // иначе идём в конец
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node; // добавляем новый элемент
    }
}

// освобождает память всего списка
void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next; // сохраняем ссылку на следующий
        free(current->word); // освобождаем слово
        free(current); // освобождаем сам узел
        current = next; // двигаемся дальше
    }
}

// обрабатывает файл
void process_file(FILE *f) {
    Node *head = NULL; // начало списка
    int ch; // текущий символ
    char *word_buf = NULL; // временный буфер для слова
    size_t buf_size = 0; // длина текущего слова
    size_t buf_cap = 0; // ёмкость буфера

    while ((ch = fgetc(f)) != EOF) { // читаем файл посимвольно
        if (is_word_char(ch)) { // если символ — часть слова
            if (buf_size + 1 >= buf_cap) { // если не хватает места
                buf_cap = buf_cap ? buf_cap * 2 : 16; // увеличиваем буфер
                word_buf = realloc(word_buf, buf_cap);
            }
            word_buf[buf_size++] = (char)ch; // добавляем символ
        } else { // если разделитель
            if (buf_size > 0) { // если есть накопленное слово
                word_buf[buf_size] = '\0'; // завершаем строку
                add_word(&head, word_buf); // добавляем слово в список
                buf_size = 0; // сбрасываем длину
            }
        }
    }

    if (buf_size > 0) { // если файл закончился на слове
        word_buf[buf_size] = '\0';
        add_word(&head, word_buf);
    }

    free(word_buf); // освобождаем временный буфер

    if (head == NULL) { // если слов нет
        printf("Файл не содержит слов.\n");
        return;
    }

    Node *current = head; // текущий элемент списка
    Node *min_word = head; // минимальное слово
    Node *max_word = head; // максимальное слово
    long total_words = 0; // общее количество слов

    while (current != NULL) { // проход по списку
        total_words++;
        if (current->length < min_word->length) min_word = current;
        if (current->length > max_word->length) max_word = current;
        current = current->next;
    }

    printf("Общее количество слов: %ld\n", total_words);
    printf("Минимальное слово: \"%s\", длина: %d\n", min_word->word, min_word->length);
    printf("Максимальное слово: \"%s\", длина: %d\n", max_word->word, max_word->length);

    free_list(head); // очищаем список
}

int main(void) {
    clock_t start = clock(); // начало измерения времени
    char filename[260];

    printf("Введите имя файла: ");
    if (scanf("%259s", filename) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    FILE *fp = fopen(filename, "r"); // открываем файл
    if (fp == NULL) {
        perror("Не удалось открыть файл");
        clock_t end_err = clock();
        double seconds_err = (double)(end_err - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds_err);
        return 1;
    }

    process_file(fp); // обработка
    fclose(fp); // закрытие файла

    clock_t end = clock(); // конец измерения времени
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}