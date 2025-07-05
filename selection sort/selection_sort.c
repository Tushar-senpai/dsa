#include<stdio.h>
 void selectionsort(int arr[], int n ){
    int i , j , min,temp;
    for (i=0;i<n;i++){
        min = i;
        for(j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                min = j;
                temp=arr[i];
                arr[i]= arr[min];
                arr[min]=temp;
            }
        }
    }
 }

    void display(int arr[], int n){
        for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }

    int main(){
        int arr[] = {64, 25, 12, 22, 11};
        int n = sizeof(arr)/sizeof(arr[0]);
        printf("Unsorted array: \n");
        display(arr, n);
        
        selectionsort(arr, n);
        
        printf("Sorted array: \n");
        display(arr, n);
        
        return 0;
    }