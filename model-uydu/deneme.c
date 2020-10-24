#include <stdio.h>
int main()
{
  int c, k;
  int sayi1 = 8;
  int sayi2 = -8;

  for (c = 5; c >= 0; c--){
    k = sayi1 >> c;
    if (k & 1)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
  for (c = 5; c >= 0; c--){
    k = sayi2 >> c;
    if (k & 1)
      printf("1");
    else
      printf("0");
  }
  return 0;
}