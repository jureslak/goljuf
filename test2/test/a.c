int main(void) {
  int i, j, produkt;

  produkt = 1;
  for (i=2; i*i<=MAX; i++) {
    if (praSt[i] == 1) continue;
    for (j=i*i; j<=MAX; j+=i) praSt[j] = 1;
  }

  int n;
  printf("Vnesi naravno stevilo, večje od 2: ");
  scanf("%d", &n);

   for (praSt[j]=2; produkt<=n; j++)
  {
   if  (n % praSt[j] = 0) stevec [j]++
   else continue

  printf(" %d.^%d. * \n", praSt[j] ,stevec [j] ,);

  }
  return 0;
}
