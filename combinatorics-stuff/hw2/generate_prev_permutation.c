#include <stdio.h>
#include <stdlib.h>

int* generate_prev_perm(int* array, int n)
{
  int i = n - 1;
  // indetify first index where a[i-1] is larger than a[i]
  while (i > 0 && array[i] > array[i - 1])
  {
    i--;
  }
  if (i == 0) 
  {
      return NULL; // no prev permutation
  }
  // save the element that is greater than the one to its right
  int greater = array[i-1];
  // we want to switch this element with the greatest element smaller than it
  int j = n - 1;

  // no valid element found yet
  int *relative_min = NULL;
  // find biggest smallest element
  while (j >= i)
  {
    if (array[j] < greater && ((relative_min == NULL) || array[j] > *relative_min))
    {
      relative_min = &array[j];
    }
    j--;
  }
  // swap
  int temp = array[i-1];
  array[i-1] = *relative_min;
  *relative_min = temp;

  // now we must reorder elements to make them decreasing
  // so we know we got the biggest possible permutation
  // which is done by reversing the one we have
  for (int k = n - 1; i < k; k--, i++)
{
    int temp = array[i];
    array[i] = array[k];
    array[k] = temp;
}

  return array;

}

int main()
{
  int a[5] = {1, 2, 3, 4, 5};
  int* result = generate_prev_perm(a, 5);
  if (result == NULL)
  {
    printf("No previous permutation.\n");
  }
  else
  {
    printf("Res is:\n");
    for(int i = 0; i < 5; i++)
    {
      printf("%d ", result[i]);
    }
  }
  
  return 0;
}