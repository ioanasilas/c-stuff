#include <stdio.h>
#include <stdlib.h> 

// Modify the array in place, no need to return it
void next_r_permutation(int* array, int r, int n)
{
  for (int i = r - 1; i >= 0; i--)
  {
    if (array[i] < n)
    {
      array[i]++;
      return;
    }
    else
    {
      array[i] = 1;  // reset and continue carrying over
    }
  }
}

int main()
{
  int n, r;
  printf("Input n (The range of values the elements can take, from 1 to n): ");
  scanf("%d", &n);

  printf("Input r (the number of elements in the permutation): ");
  scanf("%d", &r);

  printf("Input array element (one at a time): ");
  int perm[r];

  for (int i = 0; i < r; i++)
  {
    scanf("%d", &perm[i]);
  }

  // get next permutation
  next_r_permutation(perm, r, n);
  
  printf("Next permutation: ");
  for(int i = 0; i < r; i++)
  {
    printf("%d ", perm[i]);
  }
  printf("\n");

  return 0;
}
