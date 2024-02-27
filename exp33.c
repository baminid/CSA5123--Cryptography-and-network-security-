#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void bubbleSort(int arr[], int n) 
{
    for (int i=0;i<n;i++) 
	{
        int swapped = 0;
        for (int j=0;j<n-i-1;j++) 
		{
            if (arr[j]>arr[j+1]) 
			{
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped=1;
            }
        }
        if(swapped==0)
		{
            break;
        }
    }
}
double testBubbleSort(int arr[],int n) 
{
    clock_t start_time=clock();
    bubbleSort(arr,n);
    clock_t end_time=clock();
    double elapsed_time =((double)(end_time-start_time))/CLOCKS_PER_SEC;
    return elapsed_time;
}
int main() 
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    int *arr=(int *)malloc(n*sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i=0;i<n;i++) 
	{
        scanf("%d", &arr[i]);
    }
    double elapsedTime=testBubbleSort(arr,n);
    printf("Sorted array: ");
    for(int i=0;i<n;i++) 
	{
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
