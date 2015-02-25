#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100

int funkcija(char *vhod, char *izhod){
FILE *in=fopen(vhod, "rt");
if(in==NULL) return -1;

FILE *out=fopen(izhod, "wt");
if(out==NULL){
fclose(in);
return -2;
}
int s;
int t;
char niz [MAX];
double v;
int k=0;
double h;
while(fscanf(in, "%d %d %s", &s, &t, niz)==3){
	 h=(double)((t-s)/3600);
	v=(0.622/h);
	if(v>80){
		k=k+1;
		fputs(niz, out);
		fprintf(out, ": %f km/h\n", v);
		}
		}
	fclose(in);
	fclose(out);
return k;
}

int main (void){
int k=funkcija("podatki.txt", "krsitve.txt");
if(k==-1) printf("Tezave pri odpiranju 1. datoteke");
else if(k==-2) printf("Tezave pri odpiranju 2, datoteke.");
else printf("Zaznanih je bilo %d krsitev.", k);

return 0;
}