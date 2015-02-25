#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(void){
int n;
int d;
int c=0;
printf("Input number:");
scanf("%d",&n);
d=n;
if (n>=2){
printf("%d = ",n);
for(int i=2;i<n;i++){
if(d%i==0){
while(d%i==0){
d=d/i;
c++;
}
if(c!=1) printf("%d^%d * ",i,c);
if(c==1) printf("%d * ",i);
if(d==n) printf("%d * ",n);
c=0;
}
else {
i++;
}
}
}
return 0;
}
