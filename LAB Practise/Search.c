#include <stdio.h>
#include <stdlib.h>

// Linear Search
int linearSearch(int a, int arr[], int k) {
    for (int i = 0; i < k; i++) {
        if (arr[i] == a) {
            printf("Match Found\n");
            return i;
        }
    }
    return -1;
}

int binarySearch(int a, int arr[], int k) {
    int low = 0, high = k - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (*(arr + mid) == a) {
            return mid;           
        } else if (a < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int main(){
    int *arr;
    arr = (int *)malloc(sizeof(int) * 8);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int n = 8;
    int a = 0;

    for (int i = 0; i < n; i++){
        printf("Enter the element %d: ", i);
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return 1;
        }
    }

    printf("Enter the element to search: ");
    if (scanf("%d", &a) != 1) {
        fprintf(stderr, "Invalid input\n");
        free(arr);
        return 1;
    }

    // Calling the functions
    int idx = linearSearch(a, arr, n);
    if (idx >= 0) {
        printf("Element %d found at index %d\n", a, idx);
    } else {
        printf("Element %d not found\n", a);
    }

    int bidx = binarySearch(a, arr, n);
    if (bidx >= 0) {
        printf("Binary search: Element %d found at index %d\n", a, bidx);
    } else {
        printf("Binary search: Element %d not found\n", a);
    }

    free(arr);
    return 0;
}