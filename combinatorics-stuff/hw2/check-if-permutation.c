#include <stdio.h>
#include <stdbool.h>

bool valid_permutation(int *array, int n)
{
    // frequency array
    bool seen[n + 1];

    for (int i = 1; i <= n; i++) 
    {
        seen[i] = false;
    }

    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &array[i]);
        
        if (array[i] < 1 || array[i] > n || seen[array[i]]) 
        {
            return false;
        }
        seen[array[i]] = true;
    }

    return true;
}

int main() 
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int a[n];
    
    printf("Result: %s\n", valid_permutation(a, n) ? "Valid permutation" : "Not a permutation");

    return 0;
}
