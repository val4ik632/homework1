#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* inputArray(int* size) {
    printf("Введите количество элементов массива (1-100): ");
    if (scanf("%d", size) != 1 || *size < 1 || *size > 100) {
        printf("Ошибка: введите корректное число от 1 до 100.\n");
        return NULL;
    }
    
    int* arr = (int*)malloc((*size) * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка: не удалось выделить память.\n");
        return NULL;
    }

    printf("Введите %d целых чисел:\n", *size);
    for (int i = 0; i < *size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Ошибка: введено не целое число.\n");
            free(arr);
            return NULL;
        }
    }
    return arr;
}

void printArray(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void shiftLeft(int* arr, int size, int k) {
    if (size <= 1) return;
    k = k % size;
    if (k < 0) k += size;
    
    if (k == 0) return;
    
    for (int i = 0; i < k / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[k - 1 - i];
        arr[k - 1 - i] = temp;
    }
    for (int i = 0; i < (size - k) / 2; i++) {
        int temp = arr[k + i];
        arr[k + i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void shiftRight(int* arr, int size, int k) {
    
    shiftLeft(arr, size, size - (k % size));
}

void analyzeArray(const int* arr, int size) {
    if (size == 0) return;
    
    int sum = 0;
    int min = arr[0];
    int max = arr[0];
    
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    double average = (double)sum / size;
    
    printf("\n--- Анализ массива ---\n");
    printf("Сумма элементов: %d\n", sum);
    printf("Среднее арифметическое: %.2f\n", average);
    printf("Минимальное значение: %d\n", min);
    printf("Максимальное значение: %d\n", max);
    
    int duplicates_found = 0;
    printf("Повторяющиеся значения: ");
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                duplicates_found = 1;
                break;
            }
        }
    }
    if (!duplicates_found) {
        printf("отсутствуют");
    }
    printf("\n");
}

int main() {
    int size;
    int* arr = inputArray(&size);
    
    if (arr == NULL) {
        return 1;
    }

    printf("\nИсходный массив: ");
    printArray(arr, size);
    
    analyzeArray(arr, size);
    
    int k;
    printf("\nВведите количество позиций для сдвига: ");
    if (scanf("%d", &k) != 1) {
        printf("Ошибка ввода.\n");
        free(arr);
        return 1;
    }

    int* temp_arr_left = (int*)malloc(size * sizeof(int));
    memcpy(temp_arr_left, arr, size * sizeof(int));
    shiftLeft(temp_arr_left, size, k);
    printf("\nМассив после циклического сдвига ВЛЕВО на %d позиций: ", k);
    printArray(temp_arr_left, size);
    free(temp_arr_left);

    int* temp_arr_right = (int*)malloc(size * sizeof(int));
    memcpy(temp_arr_right, arr, size * sizeof(int));
    shiftRight(temp_arr_right, size, k);
    printf("Массив после циклического сдвига ВПРАВО на %d позиций: ", k);
    printArray(temp_arr_right, size);
    free(temp_arr_right);

    free(arr);
    return 0;
}