#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int f(char* vhodna, int* s0, int* t0, char* r0, char* izhodna){

FILE *datoteka = fopen(vhod, "rt");
if (datoteka == NULL) return -1;

FILE *datoteka = fopen(izhod, "wt");
if (datoteka == NULL) return -2

int s,t;
char r;
int dolzina_tunela = 622.0;

while (fscanf(datoteka, "%d %d %s", &s, &t, &r) == 3){
*s0=s;
*t0=t;
int prehitri = 0;
double hitrost = ((t-s)/dolzina)*3.6;
if (hitrost >= 80){
	fprintf(izhodna, "%s %lf\n",r,hitrost);
	prehitri +=1;
}
fclose(datoteka);
}

return prehitri;

}


int main(void){


int s,t;
char r;
int prehitri

int n = f("podatki.txt", &s, &t, &r, "krsitve.txt");


if (n == -1) printf("Napaka pri odpiranju vhodne datotek.";
else if (n== -2) printf ("Napaka pri odpiranju izhodne datoteke:")
else printf("Stevilo prehitrih voznikov je %d.", prehitri);
return 0;
}



	
