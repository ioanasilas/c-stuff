#include <stdio.h>

int* generate_next_perm(int* array, int n)
{
  int i = n - 1;
  // find longest decreasing subseq
  while (i > 0 && array[i] < array[i - 1])
  {
    i--;
  }
  if (i == 0) 
  {
      return NULL; // no next permutation
  }
  // save the element that stops this seq
  int ruiner = array[i-1];
  // we want to switch the element to the left of this subseq with the smallest element bigger than it from the subseq
  int j = n - 1;
  int *relative_max = &array[j];
  // find smallest biggest element
  while (j > i)
  {
    if (array[j] > ruiner && array[j] < array[i])
    {
      relative_max = &array[j];
    }
    j--;
  }
  // swap
  int temp = array[i-1];
  array[i-1] = *relative_max;
  *relative_max = temp;

  // now we must reorder elements in the new descreasing subseq, we need to make it increasing
  // so we know we got the smallest possible permutation
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
  int a[5] = {5, 4, 3, 1, 2};
  int* result = generate_next_perm(a, 5);
  if (result == NULL)
  {
    printf("No next permutation.\n");
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