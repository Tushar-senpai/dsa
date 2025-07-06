#include<stdio.h>


void merge(int arr[],int left,int mid,int right);

void mergesort(int arr[],int left,int right){
    if(left<right){
        int mid = left + (right-left)/2;
        mergesort(arr,left,mid);
        mergesort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}
void merge(int arr[],int left,int mid,int right){
    int i,j,k;
    int n1 = mid-left+1;
    int n2 =right-mid;
     int l[n1],r[n2];

     for(i=0;i<n1;i++){
        l[i]=arr[left+i];
     }
     for(j=0;j<n2;j++){
        r[j]=arr[mid+1+j];
     }

     i=0;
     j=0;
     k=left;

while(i<n1 && j<n2){
    if(l[i]<=r[j]){
        arr[k]=l[i];
        i++;
    }
    else{
        arr[k]=r[j];
        j++;
    }
    k++;
}

 while(i<n1){
 arr[k]=l[i];
 i++;
 k++;
 }


 while(j<n2){
    arr[k]=r[j];
    j++;
    k++;
 }



}
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
mergesort(arr,0,n);
printf("\n");
display(arr,n);
return 0;
}

