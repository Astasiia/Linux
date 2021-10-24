#include <stdio.h>
#include <stdlib.h>

int* arrayFromTo(int size, int start, int step) {
    int *arr = malloc(size * sizeof(int));
    int i;
    for (i = 0; i < size; i++)
        arr[i] = start + step * i;
    return arr;
}

void printArray(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%i\n", arr[i]);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("help\n");
        return 0;
    }
    int *arr = NULL, size = 0;
    if (argc == 2) {
        int n = atoi(argv[1]);
        size = n;
        arr = arrayFromTo(n, 0, 1);
    } else if (argc == 3) {
        int m = atoi(argv[1]), n = atoi(argv[2]);
        size = n - m;
        arr = arrayFromTo(size, m, 1);
    } else if (argc == 4) {
        int m = atoi(argv[1]), n = atoi(argv[2]), s = atoi(argv[3]);
        size = n - m;
        arr = arrayFromTo(size, m, s);
    }
    printArray(arr, size);
    return 0;
}