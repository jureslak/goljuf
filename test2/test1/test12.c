#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 1000;
void function(char* si,char* so){
FILE* input=fopen(si,"r");
FIlE* output=fopen(so,"w");
if(input==NULL)(
return -1;)
if(output==NULL)(
return -2;)
int t;
int s;
double speed;
char r[7];
int numOffen=0;
while(!feof(input)){
fscanf(input,"%d %d %c",&s,&t,r);
if(0<=s<t||0<t<86400){
speed=(622)*(3.6)/(t-s);
if (80<speed){
fprintf(output,"%s: %lf\n",r,speed)
numOffen++;
}
else return -1;
}
}
printf("%d",&numOffen)
return 0;
}
int main(void){
char* si;
char* so;
printf("Enter the name of the files")
scanf("%s,%s",si,so);
void* a=function(input,output);
if(function(input,output)==-1){
printf("There is a problem with input");
}
if(function(input,output)==-2){
printf("There is a problem with ou");
}
return 0;
}