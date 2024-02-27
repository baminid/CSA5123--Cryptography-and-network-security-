#include <stdio.h>
void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void permute(int arr[], int left, int right) 
{
    if (left == right) 
	{
        for (int i = 0; i <= right; i++) 
		{
            printf("%d", arr[i]);
            if (i != right) 
			{
                printf(", ");
            }
        }
        printf("\n");
    } 
	else 
	{
        for (int i = left; i <= right; i++)
		 {
            swap(&arr[left], &arr[i]);
            permute(arr, left + 1, right);
            swap(&arr[left], &arr[i]);
        }
    }
}
int main() 
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) 
	{
        scanf("%d", &arr[i]);
    }
    printf("All possible permutations:\n");
    permute(arr, 0, n - 1);
    return 0;
}
