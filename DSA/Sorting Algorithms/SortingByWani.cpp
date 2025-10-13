//
// Created by Anshumaan soni on 8/3/25.
//

/*
#include<stdio.h>

void merge(int arr[],int l,int m,int r){
    int i,j,k;
    int n1,n2;
    n1=m-l+1;
    n2=r-m;
    int L[n1],R[n2];
    for(i=0;i<n1;i++){
        L[i]=arr[l+i];
    }
    for(j=0;j<n2;j++){
        R[j]=arr[m+1+j];
    }
    i=0;
    j=0;
    k=l;
    while(i<n1 && j<n2){
        if(L[i]<= R[j]){
            arr[k]=L[i];
            i++;
        }
        else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[],int l,int r){
    int m;
    if(l<r){
        m=(l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}
int main(){
    int arr[20],n,i;
    printf("Enter the size of the array- ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter the %d element- ",i+1);
        scanf("%d",&arr[i]);
    }
    mergeSort(arr,0,n-1);
    printf("Sorted Array- \n");
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}

*/

#include<stdio.h>

int swap(int *low,int *right){
    int temp=*low;
    *low=*right;
    *right=temp;
}
int partition(int arr[],int low,int high){
    int pivot=arr[low];
    int left =low;
    int right=high;
    while(left<=right){
        while(left<=right && arr[left]<=pivot){
            left++;
        }
        while(left<=right && arr[right]>pivot){
            right--;
        }
        if(left<right){
            swap(&arr[left],&arr[right]);
        }
    }
    swap(&arr[low],&arr[right]);
    return right;
}
void quickSort(int arr[], int low, int high){
    if (low < high) {
        int pivotindex;
        pivotindex = partition(arr, low, high);
        quickSort(arr,low,pivotindex - 1);
        quickSort(arr,pivotindex +1,high);
    }
}
int main() {
    int arr[20],n,i;
    printf("Enter the size of the array- ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter %d element- ",i+1);
        scanf("%d",&arr[i]);
    }
    printf("Original Array\n");
    for(i=0;i<n;i++){
        printf("%d",arr[i]);
    }
    quickSort(arr, 0, n - 1);
    printf("\nSorted Array\n");
    for(i=0;i<n;i++){
        printf("%d",arr[i]);
    }
    return 0;
}