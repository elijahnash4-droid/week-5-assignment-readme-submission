#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// include library that gives random numbers

#define MAX_NUMBERS 20
#define NUM_THREADS 4

int array[MAX_NUMBERS];
int part = 0;

void merge(int low, int mid, int high) {
    int left[mid - low + 1];
    int right[high - mid];

    int size_l = mid - low + 1;
    int size_r = high - mid;

    // stores values on the left part
    for (int i = 0; i < size_l; i++) {
        left[i] = array[i + low];
    }

    // stores values on the right part
    for (int i = 0; i < size_r; i++) {
        right[i] = array[i + mid + 1];
    }

    int k = low;

    int i = 0;
    int j = 0;

    // merge left and right 
    while (i < size_l && j < size_r) {
        if (left[i] <= right[j]) {
            array[k++] = left[i++];
        }

        else {
            array[k++] = right[j++];
        }
    }

    // insert remaining values from the left
    while (i < size_l) {
        array[k++] = left[i++];
    }

    // insert remaining values from the right
    while (j < size_r) {
        array[k++] = right[j++];
    }
}

void sort(int low, int high) {

    int mid = low + (high - low) / 2;
    if (low < high) {
        sort(low, mid);
        sort(mid + 1, high);
        merge(low, mid, high);
    }

}

void *merge_sort(void *arg) {
    
    // which part of for each thread
    int thread_part = part++;

    int low = thread_part * (MAX_NUMBERS / NUM_THREADS);
    int high = (thread_part + 1) * (MAX_NUMBERS / NUM_THREADS) - 1;

    int mid = low + (high - low) / 2;
    if (low < high) {
        sort(low, mid);
        sort(mid + 1, high);
        merge(low, mid, high);
    }
}

int main() {
    // uses a different seed each time to prevent the same numbers being used on generation
    srand(time(NULL));

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < MAX_NUMBERS; i++) {
        array[i] = rand() % MAX_NUMBERS;
    }

    printf("Array before sorting: ");
    for (int i = 0; i < MAX_NUMBERS - 1; i++) {
        printf("%d ", array[i]);
        if (array[i] > array[i+1]) {
        }
    }
    printf("\n");

    int count = 0;

    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);
    }

    // joining all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    merge(0, (MAX_NUMBERS / 2 - 1) / 2, MAX_NUMBERS / 2 - 1);
    merge(MAX_NUMBERS / 2, MAX_NUMBERS / 2 + (MAX_NUMBERS - 1 - MAX_NUMBERS / 2)/2, MAX_NUMBERS - 1);
    merge(0, (MAX_NUMBERS - 1)/2, MAX_NUMBERS - 1);

    int sorted = 1;
    printf("Array after sorting: ");
    for (int i = 0; i < MAX_NUMBERS - 1; i++) {
        printf("%d ", array[i]);
        if (array[i] > array[i+1]) {
            sorted = 0;
        }
    }
    printf("\n");

    if (sorted == 0) {
        printf("The array was not succesfully storted...\n");
    }

    else {
        printf("The array was successfully sorted!\n");
    }
    return 0;
}