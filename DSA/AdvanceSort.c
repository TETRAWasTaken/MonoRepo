//
// Created by Anshumaan soni on 7/28/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int high;
    int low;
} dividedarr;

// Global Functions
void print(int *arr, int k) {
    int i;
    printf("{ ");
    for (i = 0; i < k; i++) {
        printf("%d, ", *(arr + i));
    }
    printf("\b\b }\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


// Quick Sorting Algorithm
int divide(int *arr, int low, int high, int pivot_index) {
    swap(arr + pivot_index, arr + high);
    
    int pivot_value = *(arr + high);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (*(arr + j) < pivot_value) {
            i++;
            swap(arr + i, arr + j);
        }
    }
    swap(arr + i + 1, arr + high);
    return i + 1;
}

void quickSort(int *arr, int low, int high, int pivot_strategy) {
    if (low < high) {
        int pivot_index;
        if (pivot_strategy == 1) {
            pivot_index = low;
        } else if (pivot_strategy == 2) {
            pivot_index = high;
        } else {
            pivot_index = low + (high - low) / 2;
        }

        int pi = divide(arr, low, high, pivot_index);

        quickSort(arr, low, pi - 1, pivot_strategy);
        quickSort(arr, pi + 1, high, pivot_strategy);
    }
}


// Merge Sorting Algorithm
void merge(dividedarr left, dividedarr right) {
    int i, j, k;
    int n1 = left.high - left.low + 1;
    int n2 = right.high - right.low + 1;

    int *L = (int*)malloc(sizeof(int) * n1);
    int *R = (int*)malloc(sizeof(int) * n2);

    if (L == NULL || R == NULL) {
        perror("Failed to allocate memory for merge");
        free(L);
        free(R);
        return;
    }

    for (i = 0; i < n1; i++) {
        L[i] = left.arr[left.low + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = right.arr[right.low + j];
    }

    i = 0;
    j = 0;
    k = left.low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            left.arr[k] = L[i];
            i++;
        } else {
            left.arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        left.arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        left.arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeDivide(dividedarr arr) {
    if (arr.low < arr.high) {
        int mid = (arr.low + arr.high) / 2;
        dividedarr left, right;

        left.arr = arr.arr;
        left.low = arr.low;
        left.high = mid;
        mergeDivide(left);

        right.arr = arr.arr;
        right.low = mid+1;
        right.high = arr.high;
        mergeDivide(right);

        merge(left, right);
    }
    return;
}

void mergeSort(int *arr, int low, int high) {
    dividedarr margearr;
    margearr.arr = arr;
    margearr.low = low;
    margearr.high = high;
    mergeDivide(margearr);
    return;
}

int main() {
    int *arr, k, i, select, *oriarr, m;

    printf("Enter the number of elements : ");
    scanf("%d",&k);

    arr = (int*)malloc(sizeof(int) * k);
    oriarr = (int*)malloc(sizeof(int) * k);
    if (arr == NULL || oriarr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i=0; i<k; i++) {
        printf("Enter the element for the position %d : ",i+1);
        scanf("%d",arr+i);
    }
    for (i=0; i<k; i++) {
        *(oriarr+i) = *(arr+i);
    }

    for (m=0; m<4; m++) {
        printf("\nUnsorted array : ");
        print(arr, k);

        printf("\n Which Algorithm ?\n");
        printf("1 - Quick Sort\n");
        printf("2 - Merge Sort\n");
        scanf("%d", &select);

        int validInput = 1;

        if (select == 1) {
            int pivot;
            printf("Enter the position of the pivot : \n");
            printf("1 - First\n");
            printf("2 - Last\n");
            printf("3 - Mid\n");
            scanf("%d", &pivot);

            if (pivot >= 1 && pivot <= 3) {
                printf("\nQuick Sort");
                quickSort(arr, 0, k - 1, pivot);
            } else {
                printf("Invalid pivot choice\n");
                validInput = 0;
            }
        }
        else if (select == 2) {
            printf("\nMerge Sort");
            mergeSort(arr, 0, k-1);
        }
        else {
            printf("Invalid sort choice\n");
            validInput = 0;
        }

        if (validInput) {
            printf("\nSorted array : \n");
            print(arr, k);
        }

        for (i=0; i<k; i++) {
            *(arr+i) = *(oriarr+i);
        }
        printf("##################\n");
    }
    free(arr);
    free(oriarr);

    return 0;
}