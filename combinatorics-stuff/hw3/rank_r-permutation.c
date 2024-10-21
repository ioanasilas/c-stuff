#include <stdio.h>
#include <math.h>

int rank_r_permutation(int* array, int r, int n)
{
  // remove 1 from each el of the array to create base-n numbering
  for (int i = 0; i < r; i++)
  {
    array[i] = array[i] - 1;
  }

  // create actual base 10 number
  int base_factor = 0;
  int base_number = 0;
  for (int i = r - 1; i >= 0; i--)
  {
    int power = 1;
    for (int j = 0; j < base_factor; j++)
    {
      power *= n;
    }
    base_number = base_number + array[i] * power;
    base_factor += 1; 
  }

  return base_number;
}

int main()
{
  int n, r;
  printf("Input n (The range of values the elements can take, from 1 to n): ");
  scanf("%d", &n);

  printf("Input r (the number of elements in the permutation): ");
  scanf("%d", &r);

  printf("Input array element (one at a time): ");
  int perm[n];

  for (int i = 0; i < r; i++)
  {
    scanf("%d", &perm[i]);
  }

  int rank = rank_r_permutation(perm, r, n);
  printf("%d", rank);

  return 0;
}