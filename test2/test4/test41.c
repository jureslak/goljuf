#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
   int st_met = 0;
   int st_pik = 0;
   int a;

   srand(time(NULL));

   do {
      st_pik = (rand()%6);
      st_pik = st_pik + 1;
      st_met += 1;
      printf("Padla je %d\n", st_pik);
   } while (st_pik != 6);

   printf("6 je padla v %d. poskusu", st_met);

   return 0;
}
