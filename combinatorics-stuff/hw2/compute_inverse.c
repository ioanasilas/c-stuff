#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void inverse_permutation(int* a, int n)
{
  int *b = malloc(sizeof(int) * (n + 1));
  for (int i = 0; i < n; i++)
  {
    b[a[i]] = i + 1;
  }

 for (int i = 1; i < n + 1; i++)
 {
   printf("%d ", b[i]);
 }
 printf("\n");

 free(b);
}


int main()
{
  int n;
  printf("Input n: ");
  scanf("%d", &n);
  
  // freq array to track els
  bool seen[n+1];
  int input;

  for(int i = 0; i <=n; i++)
  {
    seen[i] = false;
  }

  // store canonical perm
  int a[n];

  for (int i = 0; i < n; i++)
  {
    while (1)
    {
      printf("Input element %d: ", i + 1);
      scanf("%d", &input);
      if (input < 1 || input > n)
      {
        printf("Number must be between 1 and %d. Try again.\n", n);
      }
      else if (seen[input])
      {
        printf("Number %d has already been entered. Try again.\n", input);
      }
      else
      {
        a[i] = input;
        seen[input] = true;
        break;
      }

    }
  }

  inverse_permutation(a, n);


  return 0;
}