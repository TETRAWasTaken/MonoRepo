#include <stdio.h>
#include <stdlib.h>

void print(int *arr, int k) {
    int i;
    printf("{ ");
    for (i = 0; i < k; i++) {
        printf("%d ", *(arr + i));
    }
    printf("}\n");
}

// Call By Refrence
void bubbleSort(int *arr, int k){
    int i,j;
    for(i=0; i<k-1; i++){
        for(j=0; j<k-i-1; j++){
            if(*(arr+j)>*(arr+j+1)){
                int var;
                var = *(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = var;
            }
            else{
                continue;
            }
        }
    }
}

void selectionSort(int *arr, int k) {
    int i, var, j, temp;
    for(i=0; i<k; i++){
        var=i;
        for(j=i; j<k; j++){
            if(*(arr+j)<=*(arr+var)){
                var = j;
            }
        }
        temp = *(arr+i);
        *(arr+i) = *(arr+var);
        *(arr+var) = temp;
    }
}

void insertionSort(int *arr, int k) {
    int i, key;
    for (i = 1; i < k; i++) {
        key = *(arr + i);
        int j;
        for (j = i-1; j >= 0 && *(arr + j) > key; j--) {
            *(arr + j + 1) = *(arr + j);
        }
        *(arr + j + 1) = key;
    }
}


// Call by Value
void valuebubbleSort(int* original_arr, int k) {
    int arr[k];
    int i, j;

    for (i = 0; i < k; i++) {
        arr[i] = original_arr[i];
    }

    for (i = 0; i < k - 1; i++) {
        for (j = 0; j < k - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int var = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = var;
            }
        }
    }

    print(arr, k);
}

void valueselectionSort(int* original_arr, int k) {
    int arr[k];
    int i, j;

    for (i = 0; i < k; i++) {
        arr[i] = original_arr[i];
    }

    for (i = 0; i < k; i++) {
        int var = i;
        for (j = i; j < k; j++) {
            if (arr[j] <= arr[var]) {
                var = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[var];
        arr[var] = temp;
    }

    print(arr, k);
}

void valueinsertionSort(int* original_arr, int k) {
    int arr[k];
    int i;

    for (i = 0; i < k; i++) {
        arr[i] = original_arr[i];
    }

    for (i = 1; i < k; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    print(arr, k);
}

int main(){
    int *arr, k, i, select, n;
    int sort=1;
    printf("Enter the number of elements : ");
    scanf("%d",&k);

    if (k <= 0) {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    arr = (int*)malloc(k*sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(i=0; i<k; i++){
        printf("Enter the element for the position %d : ",i+1);
        scanf("%d",arr+i);
    }

    printf("Unsorted array : ");
    print(arr, k);
    printf("\n");

    for(n=0; n<=2; n++){
        printf("Unsorted array : ");
        print(arr, k);
        printf("\n");

        printf("Which Sort you wanna do : \n");
        printf("1 - Bubble Sort ( Refrence ) \n");
        printf("2 - Selection Sort ( Refrence ) \n");
        printf("3 - Insertion Sort ( Refrence )\n");
        printf("4 - Bubble Sort ( Value ) \n");
        printf("5 - Selection Sort ( Value ) \n");
        printf("6 - Insertion Sort ( Value )\n");
        scanf("%d",&select);


        if(select==1){
            bubbleSort(arr, k);
            printf("Sorted array : \n");
            print(arr, k);
            printf("\n");
        }
        else if(select==2){
            selectionSort(arr, k);
            printf("Sorted array : \n");
            print(arr, k);
            printf("\n");
        }
        else if(select==3) {
            insertionSort(arr, k);
            printf("Sorted array : \n");
            print(arr, k);
            printf("\n");
        }
        else if(select==4) {
            valuebubbleSort(arr, k);
        }
        else if(select==5) {
            valueselectionSort(arr, k);
        }
        else if(select==6) {
            valueinsertionSort(arr, k);
        }
        else{
            printf("Invalid Input");
            sort=0;
        }
    }

    free(arr);
    return 0;
}
