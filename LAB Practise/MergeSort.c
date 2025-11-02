#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int high;
    int low; 
} subarr;

// Global Functions
void printarr(int arr[], int k){
    printf("array ->");
    for(int i=0; i<k; i++){
        printf(" %d,", arr[i]);
    }
    printf("\n");
}

// Merge Sort functions 
void merge(subarr left, subarr right) {
    int i, j ,k;
    int n1 = left.high-left.low+1;
    int n2 = right.high-right.low+1;

    int *L = (int*)malloc(sizeof(int)*n1);
    int *R = (int*)malloc(sizeof(int)*n2);

    if (L == NULL || R == NULL){
        perror("Allocation failed");
        free(L);
        free(R);
        return;
    }

    for(i=0; i<n1; i++){
        L[i] = left.arr[left.low+i];
    }
    for(i=0; i<n2; i++){
        R[i] = right.arr[right.low+i];
    }

    i=0,j=0;
    k = left.low;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            left.arr[k] = L[i];
            i++;
        }
        else {
            left.arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        left.arr[k] = L[i];
        i++;
        k++;
    }

    while(j<n2){
        left.arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeDivide(subarr arr) {
    if (arr.low < arr.high){
        int mid = arr.low + (arr.high - arr.low)/2;
        subarr left, right;

        left.arr = arr.arr;
        left.low = arr.low;
        left.high = mid;
        
        right.arr = arr.arr;
        right.low = mid + 1;
        right.high = arr.high;

        mergeDivide(left);
        mergeDivide(right);

        merge(left, right);
    }
    return;
}

void mergeSort(int arr[], int low, int high){
    subarr mergearr;
    mergearr.arr = arr;
    mergearr.high = high;
    mergearr.low = low;
    mergeDivide(mergearr);
    return;
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

    mergeSort(arr, 0, k-1);
    printarr(arr, k);

}
