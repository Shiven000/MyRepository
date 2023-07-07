#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// bubble sort array: {97, 16, 45, 63, 13, 22, 7, 58, 72}

void printNumArray(int arr[])
{
    for(int i = 0; i < 9; i++)
    {
        printf("%d\n", arr[i]);
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}




int bubblesort(int arr[], int size)
{
    int swaps;
    for(int j = 0; j < size; j++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] > arr[i + 1]) // Corrected comparison for ascending order sorting
            {
                swap(&arr[i], &arr[i + 1]);
                swaps++;
            }
        }
    
    }

    return swaps;
}






int main()
{
    

    int array[9] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    printNumArray(array);
    printf("\n\n\n");
    printf("There were %d swaps in this array\n\n", bubblesort(array, 9));
    printNumArray(array);


}