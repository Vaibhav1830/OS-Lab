#include<Stdio.h>
#include<stdlib.h>
int main(){
int arr[5] = {1,3,5,7,11};
int max = INT_MIN;
int second_max=INT_MIN;
for(int i=0;i<5;i++){
    if(arr[i]>max){
        max=arr[i];
    }
}
for(int i=0;i<5;i++){
   if(arr[i]>second_max && arr[i]!=max){
    second_max = arr[i];
   }
}
printf("%d",second_max);

return 0;
}
