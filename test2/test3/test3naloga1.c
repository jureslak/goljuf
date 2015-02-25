#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){

printf ("Vpisi stevilo: "); scanf ("%d",&n);
printf ("%d = "; n);
int tab[n];
//tabela praštevil, v poštev pridejo le ta manjša od n/2
//Program sprejme stevila, ki zadoscajo n<=2
for(int i =2;i<=n/2;i++){
	int x = 0;
	int j =2;
	while (j<=sqrt(n)){
		if (n%j==0){
		x = 1;
		break;
		}
	}
	if (x==0) tab[i]=j;
	j++;
}
for(int i=2;i<=n/2;i++){
	if (n%tab[i]==0){
		int potenca=1;
		while (n%tab[i]==0){
		n/tab[i];
		potenca +=1;
		}
	}
		


return 0;
}