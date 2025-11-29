// сравнение алгоритмов сортировки
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 10000

// структура для статистики
typedef struct {
    const char *name;
    const char *complexity;
    long long comparisons;
    long long swaps;
    long long writes;
    double seconds;
} SortStats;

// подсчёт сравнений
#define CMP_LT(a, b, st) ((st)->comparisons++, (a) < (b))
#define CMP_GT(a, b, st) ((st)->comparisons++, (a) > (b))
#define CMP_LE(a, b, st) ((st)->comparisons++, (a) <= (b))
#define CMP_GE(a, b, st) ((st)->comparisons++, (a) >= (b))
#define CMP_EQ(a, b, st) ((st)->comparisons++, (a) == (b))

// обмен элементов с учётом статистики
void swap_int(int *a, int i, int j, SortStats *st) {
    if (i == j) return;
    int tmp = a[i];
    st->writes++;
    a[i] = a[j];
    st->writes++;
    a[j] = tmp;
    st->writes++;
    st->swaps++;
}

// сортировка вставками
void insertion_sort(int *a, int n, SortStats *st) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        st->writes++;
        int j = i - 1;
        while (j >= 0) {
            st->comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                st->writes++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
        st->writes++;
    }
}

// пузырьковая сортировка
void bubble_sort(int *a, int n, SortStats *st) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (CMP_GT(a[j], a[j + 1], st)) {
                swap_int(a, j, j + 1, st);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// быстрая сортировка (Hoare)
void quick_sort_rec(int *a, int left, int right, SortStats *st) {
    int i = left;
    int j = right;
    int pivot = a[(left + right) / 2];
    while (i <= j) {
        while (CMP_LT(a[i], pivot, st)) i++;
        while (CMP_GT(a[j], pivot, st)) j--;
        if (i <= j) {
            swap_int(a, i, j, st);
            i++;
            j--;
        }
    }
    if (left < j)  quick_sort_rec(a, left, j, st);
    if (i < right) quick_sort_rec(a, i, right, st);
}

void quick_sort(int *a, int n, SortStats *st) {
    if (n > 0) quick_sort_rec(a, 0, n - 1, st);
}

// слияние двух отсортированных частей
void merge(int *a, int left, int mid, int right, SortStats *st) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (!L || !R) {
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++) {
        L[i] = a[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = a[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (CMP_LE(L[i], R[j], st)) {
            a[k] = L[i];
            st->writes++;
            i++;
        } else {
            a[k] = R[j];
            st->writes++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        st->writes++;
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        st->writes++;
        j++;
        k++;
    }

    free(L);
    free(R);
}

// сортировка слиянием
void merge_sort_rec(int *a, int left, int right, SortStats *st) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    merge_sort_rec(a, left, mid, st);
    merge_sort_rec(a, mid + 1, right, st);
    merge(a, left, mid, right, st);
}

void merge_sort(int *a, int n, SortStats *st) {
    if (n > 0) merge_sort_rec(a, 0, n - 1, st);
}

// шейкерная сортировка (cocktail shaker)
void cocktail_sort(int *a, int n, SortStats *st) {
    int start = 0;
    int end = n - 1;
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (CMP_GT(a[i], a[i + 1], st)) {
                swap_int(a, i, i + 1, st);
                swapped = 1;
            }
        }
        if (!swapped) break;
        swapped = 0;
        end--;
        for (int i = end; i > start; i--) {
            if (CMP_LT(a[i], a[i - 1], st)) {
                swap_int(a, i, i - 1, st);
                swapped = 1;
            }
        }
        start++;
    }
}

// просеивание (heapify) для кучной сортировки
void heapify(int *a, int n, int i, SortStats *st) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && CMP_GT(a[left], a[largest], st)) {
        largest = left;
    }
    if (right < n && CMP_GT(a[right], a[largest], st)) {
        largest = right;
    }
    if (largest != i) {
        swap_int(a, i, largest, st);
        heapify(a, n, largest, st);
    }
}

// кучная сортировка
void heap_sort(int *a, int n, SortStats *st) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i, st);
    }
    for (int i = n - 1; i > 0; i--) {
        swap_int(a, 0, i, st);
        heapify(a, i, 0, st);
    }
}

// узел для tree sort
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// вставка в бинарное дерево поиска
Node *insert_node(Node *root, int value, SortStats *st) {
    if (root == NULL) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (!node) return root;
        node->value = value;
        node->left = node->right = NULL;
        return node;
    }
    if (CMP_LT(value, root->value, st)) {
        root->left = insert_node(root->left, value, st);
    } else {
        if (CMP_GT(value, root->value, st)) {
            root->right = insert_node(root->right, value, st);
        } else {
            // равные элементы кладём вправо без доп. сравнения
            root->right = insert_node(root->right, value, st);
        }
    }
    return root;
}

// обход дерева и запись в массив
void inorder_traverse(Node *root, int *a, int *index, SortStats *st) {
    if (!root) return;
    inorder_traverse(root->left, a, index, st);
    a[*index] = root->value;
    st->writes++;
    (*index)++;
    inorder_traverse(root->right, a, index, st);
}

// освобождение дерева
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// tree sort
void tree_sort(int *a, int n, SortStats *st) {
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert_node(root, a[i], st);
    }
    int index = 0;
    inorder_traverse(root, a, &index, st);
    free_tree(root);
}

// получение максимального значения (для radix sort)
int get_max(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

// один проход по разряду для radix sort
void counting_sort_digit(int *a, int n, int exp, SortStats *st) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (a[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
        st->writes++;
    }
    free(output);
}

// radix sort (LSD, по десятичным разрядам, только неотрицательные)
void radix_sort(int *a, int n, SortStats *st) {
    int max = get_max(a, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort_digit(a, n, exp, st);
    }
}

// запуск сортировки и измерение времени
void run_sort(void (*sort_func)(int *, int, SortStats *),
              int *src, int n, SortStats *st) {
    int *a = (int *)malloc(n * sizeof(int));
    if (!a) {
        printf("Не удалось выделить память\n");
        return;
    }
    memcpy(a, src, n * sizeof(int));

    st->comparisons = 0;
    st->swaps = 0;
    st->writes = 0;

    clock_t start = clock();
    sort_func(a, n, st);
    clock_t end = clock();

    st->seconds = (double)(end - start) / CLOCKS_PER_SEC;
    free(a);
}

int main(void) {
    int base[N];
    srand(12345);
    for (int i = 0; i < N; i++) {
        base[i] = rand() % 100000;
    }

    SortStats stats[8] = {
        {"Insertion Sort",       "O(n^2)",             0, 0, 0, 0.0},
        {"Bubble Sort",          "O(n^2)",             0, 0, 0, 0.0},
        {"Quick Sort",           "O(n log n)",         0, 0, 0, 0.0},
        {"Merge Sort",           "O(n log n)",         0, 0, 0, 0.0},
        {"Cocktail Shaker Sort", "O(n^2)",             0, 0, 0, 0.0},
        {"Heap Sort",            "O(n log n)",         0, 0, 0, 0.0},
        {"Tree Sort",            "O(n log n) avg",     0, 0, 0, 0.0},
        {"Radix Sort",           "O(d * (n + k))",     0, 0, 0, 0.0}
    };

    run_sort(insertion_sort, base, N, &stats[0]);
    run_sort(bubble_sort,    base, N, &stats[1]);
    run_sort(quick_sort,     base, N, &stats[2]);
    run_sort(merge_sort,     base, N, &stats[3]);
    run_sort(cocktail_sort,  base, N, &stats[4]);
    run_sort(heap_sort,      base, N, &stats[5]);
    run_sort(tree_sort,      base, N, &stats[6]);
    run_sort(radix_sort,     base, N, &stats[7]);

    for (int i = 0; i < 8; i++) {
        printf("%-22s | time = %.6f s | %s | cmp = %lld | swaps = %lld | writes = %lld\n",
               stats[i].name,
               stats[i].seconds,
               stats[i].complexity,
               stats[i].comparisons,
               stats[i].swaps,
               stats[i].writes);
    }

    return 0;
}
/*
1. Insertion Sort (сортировка вставками)

Шаг 1: i = 1 -> Шаг 2
Шаг 2: если i >= n, то переход на Шаг 9 -> иначе key = A[i], j = i−1 -> Шаг 3
Шаг 3: если j < 0, то переход на Шаг 7 -> иначе -> Шаг 4
Шаг 4: если A[j] <= key, то переход на Шаг 7 -> иначе -> Шаг 5
Шаг 5: A[j+1] = A[j] -> j = j−1 -> переход на Шаг 3
Шаг 7: A[j+1] = key -> Шаг 8
Шаг 8: i = i+1 -> переход на Шаг 2
Шаг 9: конец


2. Bubble Sort (пузырьковая сортировка)

Шаг 1: swapped = true -> Шаг 2
Шаг 2: если swapped = false, то переход на Шаг 9 -> иначе swapped = false -> i = 0 -> Шаг 3
Шаг 3: если i >= n−1, то переход на Шаг 6 -> иначе -> Шаг 4
Шаг 4: если A[i] <= A[i+1], то переход на Шаг 5 -> иначе swap(A[i], A[i+1]), swapped = true -> Шаг 5
Шаг 5: i = i+1 -> переход на Шаг 3
Шаг 6: n = n−1 -> Шаг 1
Шаг 7: конец


3. Cocktail Shaker Sort (шейкерная сортировка)

Шаг 1: start = 0, end = n−1, swapped = true -> Шаг 2
Шаг 2: если swapped = false, то переход на Шаг 13 -> иначе swapped = false -> Шаг 3
Шаг 3: i = start -> Шаг 4
Шаг 4: если i >= end, то переход на Шаг 7 -> иначе -> Шаг 5
Шаг 5: если A[i] <= A[i+1], то переход на Шаг 6 -> иначе swap(A[i], A[i+1]), swapped = true -> Шаг 6
Шаг 6: i = i+1 -> переход на Шаг 4
Шаг 7: если swapped = false, то переход на Шаг 13 -> иначе swapped = false -> end = end−1 -> Шаг 8
Шаг 8: i = end−1 -> Шаг 9
Шаг 9: если i < start, то переход на Шаг 12 -> иначе -> Шаг 10
Шаг 10: если A[i] >= A[i+1], то переход на Шаг 11 -> иначе swap(A[i], A[i+1]), swapped = true -> Шаг 11
Шаг 11: i = i−1 -> переход на Шаг 9
Шаг 12: start = start+1 -> Шаг 2
Шаг 13: конец


4. Quick Sort (быстрая сортировка)

Шаг 1: если left >= right, то переход на Шаг 9 -> иначе pivot = A[right], i = left−1 -> j = left -> Шаг 2
Шаг 2: если j >= right, то переход на Шаг 5 -> иначе -> Шаг 3
Шаг 3: если A[j] <= pivot, то i = i+1, swap(A[i], A[j]) -> Шаг 4 -> иначе -> Шаг 4
Шаг 4: j = j+1 -> переход на Шаг 2
Шаг 5: swap(A[i+1], A[right]) -> p = i+1 -> Шаг 6
Шаг 6: рекурсивный вызов QuickSort(left, p−1) -> Шаг 7
Шаг 7: рекурсивный вызов QuickSort(p+1, right) -> Шаг 8
Шаг 8: возврат -> Шаг 9
Шаг 9: конец


5. Merge Sort (сортировка слиянием)

Шаг 1: если n <= 1, то переход на Шаг 10 -> иначе -> Шаг 2
Шаг 2: mid = n / 2 -> Шаг 3
Шаг 3: рекурсивно вызвать MergeSort(left часть) -> Шаг 4
Шаг 4: рекурсивно вызвать MergeSort(right часть) -> Шаг 5
Шаг 5: i = 0, j = 0, k = 0 -> Шаг 6
Шаг 6: если i = sizeL, то переход на Шаг 8  
       если j = sizeR, то переход на Шаг 9  
       если L[i] <= R[j], то A[k] = L[i], i = i+1  
       иначе A[k] = R[j], j = j+1  
       -> k = k+1 -> переход на Шаг 6
Шаг 8: дописать остаток L -> Шаг 10
Шаг 9: дописать остаток R -> Шаг 10
Шаг 10: конец


6. Heap Sort (пирамидальная сортировка)

Шаг 1: построить кучу: i = n/2−1 -> Шаг 2
Шаг 2: если i < 0, то переход на Шаг 5 -> иначе heapify(i, n) -> i = i−1 -> Шаг 2
Шаг 5: i = n−1 -> Шаг 6
Шаг 6: если i <= 0, то переход на Шаг 10 -> иначе -> Шаг 7
Шаг 7: swap(A[0], A[i]) -> Шаг 8
Шаг 8: heapify(0, i) -> Шаг 9
Шаг 9: i = i−1 -> переход на Шаг 6
Шаг 10: конец


7. Tree Sort (сортировка бинарным деревом)

Шаг 1: создать пустое дерево -> Шаг 2
Шаг 2: i = 0 -> Шаг 3
Шаг 3: если i >= n, то переход на Шаг 4 -> иначе вставить A[i] в дерево -> i = i+1 -> Шаг 3
Шаг 4: выполнить in-order обход → записывать элементы обратно в массив -> Шаг 5
Шаг 5: конец

8. Radix Sort 

Шаг 1. найти максимальное число в массиве и определить количество его разрядов
Шаг 2. установить номер разряда i = 1 (единицы)
Шаг 3. подготовить 10 пустых корзин для цифр 0–9
Шаг 4. для каждого элемента массива выделить цифру в разряде i и поместить элемент в соответствующую корзину
Шаг 5. собрать элементы из корзин обратно в массив, начиная с корзины 0 и заканчивая корзиной 9
Шаг 6. увеличить разряд i = i + 1
Шаг 7. проверить, обработаны ли все разряды максимального числа
Шаг 8. если разряды ещё остались, повторить шаги 3–7
Шаг 9. конец