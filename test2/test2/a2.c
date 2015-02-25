#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100

int main(void){
int p=2;
int j=2;

printf("%d = ", n);
while(n!=1){
i=0;
	if(n%p!=0){
	p=p+1;
	j=2;
		while(j<p){
		if(p%j==0) {
			p=p+1;
			j=2;

			}
		else j=j+1;
			}
			}
	while (n%p==0){
n=n/p;
i=i+1;
}
if(i!=1 && i!=0) printf("%d^%d * ", p, i);
else if(i==1) printf("%d * ", p);
}

return 0;
}





