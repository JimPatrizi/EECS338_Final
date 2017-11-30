//Jim Patrizi
//EECS 338 Final
#include <stdio.h>
#include <omp.h>
#include <stdlib.h> // For atoi()
#include <sys/time.h>
#include <time.h>

#define MAX_ELEMENTS 2000000

int elementArray[MAX_ELEMENTS];
struct timeval start_time, stop_time, elapsed_time;  // timers

void merge(int arr[], int l, int m, int r);
void populateArray(int arr[]);
void printArray(int arr[], int array_size);

// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
   if (l < r)
   {
      int m = (l+r)/2;
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
   }
}


//Merge two halves of the original array
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    //create temp arrays for left and right sides of array
    int L[n1], R[n2];

    //copy data temp left and right array
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    //Merge the sorted data back into the original array
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        //if the left is <= right the put the left at the current index of k
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        //put the right index element at the index of k
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //Copy the remaining elements of the sub arrays
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
//Print array to console
void printArray(int arr[], int array_size)
{
  int i;
  for(i = 0; i < array_size; i++)
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
    elementArray[i] = rand()%MAX_ELEMENTS;//randomizes up to uint 32 max
  }
}

//Test finctions
int main()
{
    populateArray(elementArray);
    int size = sizeof(elementArray)/sizeof(elementArray[0]);
    gettimeofday(&start_time,NULL); // Unix timer
    mergeSort(elementArray, 0, size - 1);
    gettimeofday(&stop_time,NULL);
	  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
	  printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

    printf("\nSorted array is \n");
    //printArray(elementArray, size);
    return 0;
}
