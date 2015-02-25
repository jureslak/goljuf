#include <stdio.h>

char zamenjaj_besede(int i, int n, char tab[], char tab_1[]){
   for (i = 1; i <= n; i++){
      if (i%8 == 0) tab_1[i-1] = ' ';
      else if (i%8 == 1 || i%8 == 3) tab_1[i-1] = 'a';
      else if (i%8 == 2) tab_1[i-1] = 'l';
      else if (i%8 == 4) tab_1[i-1] = 'd';
      else if (i%8 == 5 || i%8 == 6) tab_1[i-1] = 'e';
      else if (i%8 == 7) tab_1[i-1] = 'n';
   }

   return tab_1[n];
}

int main(){
   char tab[100];
   int i=0;
   int n=0;
   int st_pre = 0;

   printf("Vnesi stavek, ki je manjsi od 100 znakov: ");
   gets(tab);

   for (i = 0; i < 100; i++){             //presteje "besede"
      if(tab[i] == ' ') st_pre = st_pre + 1;
   }

   n = 7*(st_pre+1)+st_pre;               //ustvari novo tabelo za preveden string
   char tab_1[n];


   zamenjaj_besede(i, n, tab, tab_1);

   printf("%s\n", tab_1);

   return 0;
}
