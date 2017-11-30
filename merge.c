#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS  10

void merge(int arr[], int p, int q, int r);
void mergeSort(int arr[], int i, int j);
void printArray(int arr[]);
void populateArray(int arr[]);

int elementArray[MAX_ELEMENTS];

//l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
   if (l < r)
   {
      int middle = (l+r)/2;
      mergeSort(arr, l, middle);
      mergeSort(arr, middle+1, r);
      merge(arr, l, middle, r);
   }
}

//
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int Left[n1];
    int Right[n2];

    //Copy data into temp arrays for sub arrays (left and right, broken about the middle)
    for(i=0; i < n1; i++)
    {
      Left[i] = arr[l+i];
    }

    for(j=0; j < n2; j++)
    {
      Right[j] = arr[m+j+1];
    }

    i = 0;
    j = 0;
    k = 1;

    //Go through and compare the left and right indexes of the sub array to sort biggest through smallest
    while (i < n1 && j < n2)
    {
      if(Left[i] <= Right[j])
      {
        arr[k]= Left[i];
        i++;
      }
      else
      {
        arr[k] = Right[j];
        j++;
      }
      k++;
    }

    //Copy the rest of the elements from the subarrays
    while(i<n1)
    {
      arr[k] = Left[i];
      i++;
      k++;
    }

    while(j < n2)
    {
      arr[k] = Right[j];
      j++;
      k++;
    }

}

//Print array to console
void printArray(int arr[])
{
  int i;
  printf("sorted array:\n");
  for(i = 0; i < MAX_ELEMENTS; i++)
  {
    printf("%d\n",elementArray[i]);
  }
}

//Populates array with random numbers
void populateArray(int arr[])
{
  int i;
  //get seed based on current time
  srand(time(NULL));
  for(i = 0; i <= MAX_ELEMENTS; i++)
  {
    elementArray[i] = rand()%100;//randomizes up to uint 32 max
  }
}

int main()
{
  populateArray(elementArray);
  mergeSort(elementArray, 0, MAX_ELEMENTS - 1);
  printArray(elementArray);

  return 0;
}
