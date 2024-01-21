#include <stdio.h>
#include <stdlib.h>

int subsetEqualZero(int* arr, int arrLength);

int main()
{
    int arr1[] = {1,2,-8,4};
    int n1 = 4;
    int arr2[] = {1,2,-7,4};
    int n2 = 4;

    printf("%d\n", subsetEqualZero(arr1, n1));
    printf("%d\n", subsetEqualZero(arr2, n2));
    
    return 0;
}


int subsetEqualZero(int* arr, int arrLength)
{
    int subsetEqualZero_r(int* arr, int arrLength, int index, int sum);
    return subsetEqualZero_r(arr, arrLength, 0, 0);
}

int subsetEqualZero_r(int* arr, int arrLength, int index, int sum)
{
    if (index >= arrLength || index < 0)
    {
        return 0;
    }


    int curr = arr[index];
    // printf("%d + %d = %d\n", sum, curr, sum+curr );
    if (sum + curr == 0 || curr == 0)
    {
        return 1;
    }

    return subsetEqualZero_r(arr, arrLength, index+1, curr) || subsetEqualZero_r(arr, arrLength, index+1, sum+curr);

}