#include <stdio.h>
#include <stdlib.h>

void printarr(int arr[], int k){
    printf("array ->");
    for(int i=0; i<k; i++){
        printf(" %d,", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int k){
    int flag;
    for(int i=0; i<k; i++){
        flag = 0;
        for(int j=0; j<k-i-1; j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag++;
            }
        }

        if (flag==0){
            break;
        }
    }
}

int main() {
    int *arr, k;
    printf("Enter the Number of elements : ");
    scanf("%d", &k);

    arr = (int*)malloc(sizeof(int)*k);
    if (arr==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    for (int i=0; i<k; i++){
        printf("Enter the number for position %d : ", i);
        scanf("%d", &arr[i]);
    }

    // Calling the functions 
    bubbleSort(arr, k);
    printarr(arr, k);r
}