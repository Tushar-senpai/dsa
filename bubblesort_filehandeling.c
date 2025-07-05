#include<stdio.h>


void  bubblesort(int arr[],int size){
int i,j,temp;
for(i=0;i<size-1;i++){
    for(j=0;j<size-1;j++){
        if(arr[j]>arr[j+1]){
                    
        temp =arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;

    }
}
}}

void display(int arr[] ,int n){
int i;
for(i=0;i<n;i++){
    printf("%d",arr[i]);

}

}


int main(){

   FILE *file;
   int arr[100];
   int n=0;
   char ch;

   file =fopen("input.txt","r");
   if(file==NULL){
    printf("file not found");
    return 1;
   }

   else{
    printf("file opend\n");
   }


   while((ch =fgetc(file))!=EOF){
    printf("%c",ch);
if(ch>='0'&&ch<='9'){
    arr[n]=ch-'0';
    n++;
}
  
   }
   fclose(file);
   
   printf("\n");
    
display(arr,n);
printf("\n");
bubblesort(arr,n);
printf("\n");
display(arr,n);
}



