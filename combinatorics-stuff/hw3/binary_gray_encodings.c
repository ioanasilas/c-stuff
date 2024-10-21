#include <stdio.h>
#include <stdlib.h>

int rankGray(int* A, int* B, int n, int b_size)
{
  // we must first get binary encoding of B
  int* bin_enc = calloc(n, sizeof(int));
  for(int i = 0; i < n; i++)
  {
    for (int j = 0; j < b_size; j++)
    {
      if (A[i] == B[j])
      {
        bin_enc[i] = 1;
      }
    }
  }

  // get gray encoding based on binary
  int* gray_enc = calloc(n, sizeof(int));
  // copy first bit
  gray_enc[0] = bin_enc[0];
  for (int i = 1; i < n; i++)
  {
    gray_enc[i] = (bin_enc[i - 1] + bin_enc[i]) % 2;
  }

  // now get rank by doing base 10 conversion
  int rank = 0;
  for (int i = 0; i < n; i++) 
  {
     // use bit shifting
      rank += gray_enc[i] * (1 << i);
  }

  // Free allocated memory
  free(bin_enc);
  free(gray_enc);

  return rank;  // Return the calculated rank
}

int* unRankGray(int *A, int n, int r, int* b_size)
{
  int gray = r;
  // first bit remains the same
  int binary = gray;
  // using formula that b[i] = g[i] xor b[i-1] since xor is reversible
  // shift calculates the number of bits that were successfully calculated
  // with 0 indexing
  for(int shift = 0; gray > 0; shift++)
  {
    // get binary encoding of gray code by xor
    gray >>= 1;
    binary ^= gray;
  }

  //now we can construct subset B with binary encoding
  int* B = calloc(n, sizeof(int));
  *b_size = 0;

  for (int i = 0; i < n; i++)
  {
    // go from lsb to msb
    if ((binary >> i) & 1)
    {
      B[*b_size] = A[i];
      *b_size += 1;
    }
  }
  return B;
}

int main() 
{
  int n, i, b_size;
  int choice;

  printf("Unranking / ranking of Gray / compute next Gray subset? (1 for ranking, 2 for unranking, 3 for next G subset): ");
  scanf("%d", &choice);

  switch(choice) 
  {
      case 1:
          // for A
          printf("Enter the size of set A: ");
          scanf("%d", &n);

          int* A = malloc(n * sizeof(int));
          printf("Elements of A: \n");
          for(i = 0; i < n; i++) 
          {
              A[i] = i + 1;
              printf("%d ", A[i]);
          }
          printf("\n");

          // for B
          printf("Enter the size of subset B: ");
          scanf("%d", &b_size);

          int* B = malloc(b_size * sizeof(int));
          printf("Enter the elements of subset B one by one: \n");
          for(i = 0; i < b_size; i++) 
          {
              printf("Element %d: ", i + 1);
              scanf("%d", &B[i]);
          }

          int rank = rankGray(A, B, n, b_size);
          printf("The Gray code rank of subset B is: %d\n", rank);
          break;

      case 2: 
      {
          // for A
          printf("Enter the size of set A: ");
          scanf("%d", &n);

          int* A = malloc(n * sizeof(int));
          printf("Elements of A: \n");
          for(i = 0; i < n; i++) 
          {
              A[i] = i + 1;
              printf("%d ", A[i]);
          }
          printf("\n");

          // get rank
          int rank;
          printf("Enter the rank of the Gray code: ");
          scanf("%d", &rank);

          // get subset B
          b_size = 0;
          int *B = unRankGray(A, n, rank, &b_size);

          printf("Subset B corresponding to the Gray code rank: ");
          for (i = 0; i < b_size; i++) 
          {
              printf("%d ", B[i]);
          }
          printf("\n");
          break;
      }

      case 3: 
      {
          // for A
          printf("Enter the size of set A: ");
          scanf("%d", &n);

          int* A = malloc(n * sizeof(int));
          printf("Elements of A: \n");
          for(i = 0; i < n; i++) 
          {
              A[i] = i + 1;
              printf("%d ", A[i]);
          }
          printf("\n");

          // for B
          printf("Enter the size of subset B: ");
          scanf("%d", &b_size);

          int* B = malloc(b_size * sizeof(int));
          printf("Enter the elements of subset B one by one: \n");
          for(i = 0; i < b_size; i++) 
          {
              printf("Element %d: ", i + 1);
              scanf("%d", &B[i]);
          }

          // based on rank of current subset, we compute the next subset
          int rank_current_subset = rankGray(A, B, n, b_size);
          int rank_new_subset = rank_current_subset + 1;

          int b_new_size = 0;
          int *B_new = unRankGray(A, n, rank_new_subset, &b_new_size);

          printf("New subset corresponding to new Gray code rank: ");
          for (i = 0; i < b_new_size; i++) 
          {
              printf("%d ", B_new[i]);
          }
          printf("\n");
          break;
      }

      default:
          printf("Invalid option. Please enter 1 for ranking, 2 for unranking or 3 for new subset.\n");
          break;
  }

  return 0;
}
