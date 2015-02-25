#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

int jePalindrom (char niz[]){
	int strlen(niz) = n;
	char niz1[n];
	for (int i = 0; i < n; ++i){
		niz1[i]=niz[n];
	}
//Nov niz, kjer so elementi navedeni v obratnem vrstnem redu
//niza se morata ujemati v vseh znakih
	int jePalindrom = 1;
	for (int i = 0; i < n; ++i){
		if (niz[i]!=niz1[i]){
		jePalindrom = 0;
		break;
		}
	}
(jePalindrom==1)?return 1:return 2; //Funkcija vrne 1, če je niz palindrom in 2, če ni.
//Niz dolzine 1 je vedno palindrom.
}
/*Če želimo poiskati najkrajši polinom, moramo pogledati, koliko znakov na koncu niza
tvori palindrom. Npr pri Michele so to znaki ele.*/
int palindromiziraj(char niz[]){
int strlen(niz) = n;
	for (int i = 0; i < n; ++i){
		if(int jePalindrom (char niz[i])==1){
		int dodatni = n-i; //Stevilo dodatnih znakov. Torej od i-tega indeksa do konca niza
		}
	}	
return dodatni;
}		
int main (void){
	printf ("Ime: ");
	gets(niz);
	char niz1[MAX];
	for (int i = 0; i < n; ++i){
	char niz1[i]= niz[i];
	}
	for (int i=n;i<=(n+int palindromiziraj(char niz[]));i++){
	char niz1[i]=niz[n-int palindromiziraj(char niz[])-j]
	}
	printf ("Novo ime: %s",niz1);
	
return 0;
}		
	