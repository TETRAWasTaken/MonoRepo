//
// Created by Anshumaan soni on 7/16/25.
//

#include <stdio.h>

int linearSearch(int n, int *arr, int k) {
    int i;
    for (i = 0; i < k; i++) {
        if (*(arr + i) == n) {
            printf("Match found at index %d", i);
            return 1;
        }
    }
    return -1;
}

void sort(int *arr, int k) {
    int i=0, j=0;
    for (i = 0; i < k; i++) {
        for (j = i+1; j < k; j++) {
            if (*(arr + i) > *(arr + j)) {
                int temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
            }
        }
    }
}

int binarySearch(int n, int *arr, int k) {
    int low = 0, high = k - 1, mid;
    
    sort(arr, k);
    
    while (low <= high) {
        mid = low + (high-low) / 2;
        if (*(arr + mid) == n) {
            printf("Match found at index %d", mid+1);
            return 1;
        } else if (*(arr + mid) < n) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int k, n, i;
    printf("Enter the no. of elements : \n");
    scanf("%d", &k);

    int arr[k];
    int select;

    for (i = 0; i < k; i++) {
        printf("Enter the element %d : \n", i+1);
        scanf("%d", arr + i);
    }

    printf("Enter the element to be searched : \n");
    scanf("%d", &n);

    printf("Enter 1 for linear search and 2 for binary search : \n");
    scanf("%d", &select);

    if (select==1) {
        if (linearSearch(n, arr, k)==-1)
            printf("No match found");
    } else if (select==2) {
        if (binarySearch(n, arr, k)==-1)
            printf("No match found");
    } else {
        printf("Invalid input");
    }
    return 0;
}