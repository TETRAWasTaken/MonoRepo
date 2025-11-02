#include <stdio.h>
#include <stdlib.h>

// Global Function 
void printarr(int arr[], int k){
    printf("array ->");
    for(int i=0; i<k; i++){
        printf(" %d,", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quick Sort Functions
int divide(int arr[], int low, int high, int pivot_index){
    swap(arr + pivot_index, arr + high);

    int pivot_value = arr[high];
    int i = low - 1;

    for (int j=low; j<high; j++){
        if (arr[j] < pivot_value){
            i++;
            swap(arr+i, arr+j);
        }
    }
    swap(arr+i+1, arr+high);
    return i+1;
}

void quickSort(int arr[], int low, int high, int pivot_strategy){
    if (low<high){
        int pivot_index;
        if(pivot_strategy == 1){
            pivot_index=low;
        }
        else if (pivot_strategy == 2){
            pivot_index=high;
        }
        else {
            pivot_index = low + (high-low)/2;
        }

        int pi = divide(arr, low, high, pivot_index);

        quickSort(arr, low, pi-1, pivot_strategy);
        quickSort(arr, pi+1, high, pivot_strategy);
    }
}

int main(){
    int *arr, k;

    printf("Enter the size of array : ");
    scanf("%d", &k);
    arr = (int *)malloc(sizeof(int)*k);
    if(arr==NULL){
        printf("Allocation Fault");
        return 0;
    }
    for(int i=0; i<k; i++){
        printf("Enter the element for position %d : ", i);
        scanf("%d", &arr[i]);
    }

    quickSort(arr, 0, k-1, 1);
    printarr(arr, k);
}
