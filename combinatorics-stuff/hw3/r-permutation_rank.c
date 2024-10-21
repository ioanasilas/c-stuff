#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

int* r_permutation_rank(int rank, int r, int n)
{
  int* perm = malloc(sizeof(int) * r);

  // go from base 10 to base n
  for (int i = r - 1; i >= 0; i--)
  {
    // add 1 to get back to original elements
    perm[i] = rank % n + 1;
    rank = rank / n;
  }

  return perm;
}

int main()
{
  int n, r;
  printf("Input n (The range of values the elements can take, from 1 to n): ");
  scanf("%d", &n);

  printf("Input r (the number of elements in the permutation): ");
  scanf("%d", &r);

  int rank;
  printf("Input rank: ");
  scanf("%d", &rank);

  int *perm = r_permutation_rank(rank, r, n);

  for (int i = 0; i < r; i++)
  {
    printf("%d ", perm[i]);
  }

  free(perm);

  return 0;
}