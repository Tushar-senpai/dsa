#include<stdio.h>

void bubblesort(int arr[],int size){
    int i, j ,temp;
    for(i=0;i<size-1;i++){
      for(j=0;j<size-1-i;j++){
        if(arr[j]>arr[j+1]){
           temp =arr[j];
              arr[j]=arr[j+1];
              arr[j+1]=temp;
        }
      }
    }
}

void display(int arr[],int  n){
    int i ;
    for(int i=0;i<n;i++)
    {
        printf("%d  ,",arr[i]);

    }
}

int main(){
int arr[] = {64, 34, 25, 12, 22, 11, 90};
int n = sizeof(arr)/sizeof(arr[0]);
bubblesort(arr, n);
display(arr, n);
return 0;

} 