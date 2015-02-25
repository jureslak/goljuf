#include <stdio.h>
#include <math.h>

int main(){
   int n=0;
   int i;
   int j;
   float k;
   int x = 0;
   int z;
   float pi = 0;
   float t = 0.0000;

   printf("Vnesi stevilo n, ki bo ustvarilo matriko n*n: ");
   scanf("%d", &n);

   int mat[n][n];

   k = n*n;

   for (i = 0; i<n; i++){                    //ustvari matriko
      for (j = 0; j<n; j++){
         z = (i*(i+1) + j*(j+1));
         mat[i][j] = z;
      }
   }

   for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
         z = mat[i][j];
         if (z < k) x = x+1;
      }
   }
   t = x/k;
   pi = 4*t;

   printf("Priblizek stevila Pi: %f\n", pi);

   return 0;

}
