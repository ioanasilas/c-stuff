#include <stdio.h>
#include <stdlib.h>
int factorial(int n)
{
  if (n == 0 || n == 1)
  {
    return 1;
  }
  int result = 1;
  for (int i = 2; i <= n; i++)
  {
    result *= i;
  }
  return result;
}

int permutation_rank(int* array, int n)
{
  // if one el, rank is 0
  if (n == 1)
  {
    return 0;
  }
  // counter for els bigger than the first
  else
  { // how many blocks of permutations we look at
    int count = 0;
    for (int i = 1; i < n; i++)
    {
      if (array[0] > array[i])
      {
        count++;
      }
    }
    // decrease els bigger than first
    // but we start from i = 1 to skip first el
    int *one_less_el_array = malloc((n-1) * sizeof(int));
    for (int i = 1; i < n; i++)
    {
      if (array[i] > array[0])
      {
        one_less_el_array[i-1] = array[i] - 1;
      }
      else
      {
        one_less_el_array[i-1] = array[i];   
      }
    }
    // compute rank recursively based on the rest of the altered elements
    int rank = count * factorial(n-1) + permutation_rank(one_less_el_array, n - 1); 
    free(one_less_el_array);
    return rank;
  }

}

int main()
{
  int a[5] = {2, 1, 4, 3};
  printf("Perm rank is: %d\n", permutation_rank(a, 4));

  return 0;
}