#include<Stdio.h>
#include<stdlib.h>
int main(){
int arr[5] = {1,3,5,7,11};
int min = INT_MAX;
int second_min=INT_MAX;
for(int i=0;i<5;i++){
    if(arr[i]<min){
        min=arr[i];
    }
}
for(int i=0;i<5;i++){
   if(arr[i]<second_min && arr[i]!=min){
    second_min = arr[i];
   }
}
printf("%d",second_min);

return 0;
}
