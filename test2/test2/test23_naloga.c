#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
int jepalindrom(char niz1 []){
	char niz2[MAX];
	int ena;
	ena=strlen(niz1);
	for(int i=0; i!='\0'; i++){
			niz2[i]=niz1[ena-i];
			}
	if(strcmp(niz1, niz2)==0) return 1;
	else return 0;
	}
	
char *palindromniziraj(char *ime, int *n){
	char *palindrom;
	int l=strlen(ime);
	palindrom = (char *) malloc((l+l+1) * sizeof(*palindrom));
	for(int i=0; i<l; i++){
	*(palindrom+i)=*(ime+i);
	}
	if(jepalindrom(ime)==1) {
	*(palindrom+l)='\0';
	*n=0;
	return palindrom;
	}
	
	else {
	int i=0;
	*n=l;
	int o=l;

	for(int j=l; j<2*l; j++){
		*(palindrom+j)=*(ime+o);
		o=o-1;
		}
		//dobimo palindrom ki ima najvec dodanih crk; sedaj pa brisemo crke dokler je beseda s evedno palindrom
		while(jepalindrom(palindrom)==1){
		*(palindrom+l)=*(palindrom+l+1);
		l=l+1;
		
		*n=*n-1;
		}
		*(palindrom+l+*n)='\0';
	return palindrom;
	}
	}
	int main(void){
		printf("Vnesi ime:");
	char ime  [MAX];
	gets(ime);
	int n;
	char *palindrom;
	palindrom=palindromniziraj(ime, &n);
	
	printf("Ime: %s\n", ime);
	printf("Novo ime: %s\n", palindrom);
	printf("Podaljsano za %d znakov", n);
	free(palindrom);
	return 0;
	}
	
	
	
	