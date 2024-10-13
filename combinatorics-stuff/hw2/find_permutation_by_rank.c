#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
  if (n == 0 || n == 1)
  {
    return 1;
  }
  else
  {
    return n * factorial(n-1);
  }
}

int* permutation_by_rank(int r, int n, int a_i)
{
  static int* q = NULL;

  if (q == NULL)
  {
    q = malloc(n * sizeof(int));
  }
  if (n == 1)
  {
    q[a_i] = 1;
    return q;
  }
  // find first element of the permutation
  int p1 = r / factorial(n-1) + 1;

  q[a_i] = p1;
  // get new rank of permutation without first el
  r = r - (p1-1) * factorial(n-1);
  // now we want to deal with the remainder of the permutation

  permutation_by_rank(r, n-1, a_i+1);
  return q;
}

int* correct_index_of_perm(int r, int n)
{
  int array_index = 0;
  int *perm_before_correction = permutation_by_rank(r, n, array_index);

  for (int j = n - 2; j >= 0; j--)
  {
    for (int i = n - 1; i > j; i--)
    {
      if (perm_before_correction[i] >= perm_before_correction[j])
      {
        perm_before_correction[i] += 1;
      }
    }
  }
  return perm_before_correction;
}

int main()
{
  int r = 7;
  int n = 4;

  int *perm = malloc(4 * sizeof(int));
  perm = correct_index_of_perm(r, n);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", perm[i]);
  }

  return 0;
}