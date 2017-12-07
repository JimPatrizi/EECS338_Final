/**
* James Patrizi
* jdp99
* EECS 338 Final Project
* Normal Merge Sort
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h> // For atoi()
#include <sys/time.h>
#include <time.h>

struct timeval start_time, stop_time, elapsed_time;  // timers

void merge(int arr[], int l, int m, int r);


// l is for left index and r is right index of the sub-array of arr to be sorted
//majority of the ideas of this algorithm are from Intro to Algorithms textbook
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


//Merge two halves of the original array
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    //create temp arrays for left and right sides of array
  //  int L[n1], R[n2];
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

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
    free(L); //free temp arrays
    free(R);
}

//randomize array, used heap instead of stack so we are limited in size
int *randomish_array(int n) {
    srand(time(NULL));
    int *rand_arr = (int *)malloc(n * sizeof(int));
    if (rand_arr) {
        int i = 0;
        for (i = 0; i < n; ) {
            rand_arr[i++] = rand()%n;
        }
    }
    return rand_arr;
}

//Test finctions
int main(int argc, char **argv)
{
    if(argc != 2)
    {
      printf("Usage is ./a.out <# of random numbers to Sort>\n");
      return 0;
    }
    int n = atoi(argv[1]);
    //make array with addr starting at p and fill it with randomness
    int *p = randomish_array(n);
    if (!p)
    {
        return 1;
    }
    //int size = sizeof(elementArray)/sizeof(elementArray[0]);
    gettimeofday(&start_time,NULL); // Unix timer
    mergeSort(p, 0, n - 1);
    gettimeofday(&stop_time,NULL);
	  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
	  printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
    printf("\nSorted array is \n");
    int i;
    // for(i = 0; i < n; i++)
    // {
    //   printf("%d\n",p[i]);
    // }
    free(p);
    return 0;
}
