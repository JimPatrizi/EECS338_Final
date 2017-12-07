/**
* James Patrizi
* jdp99
* EECS 338 Final Project
* Parallel Merge Sort
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h> // For atoi()
#include <sys/time.h>
#include <time.h>

struct timeval start_time, stop_time, elapsed_time;  // timers

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
    free(L);//free temp arrays
    free(R);
}

//majority of the ideas of this algorithm are from Intro to Algorithms textbook
// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
  if(l < r)
  {
    //  printf("Thread %d is sorting %d through %d\n", omp_get_thread_num(), l, r);
      int middle = (l + r) / 2;

      //have both halves go in parallel
      #pragma omp parallel
      {
          //identifies a section of code that must be run by a single available thread
          #pragma omp single
          {
              //used to execute this region of code in parallel with code outside of this task region
              //ergo sort both halves of the array in parallel, only once!
              #pragma omp task
              mergeSort(arr, l, middle);

              #pragma omp task
              mergeSort(arr, middle + 1, r);
          }
      }

      /* merge the two halves */
      merge(arr, l, middle, r);
  }
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

//test functions
int main(int argc, char **argv) {
    //make sure there are 3 args to set appopriate settings
    if(argc != 3)
    {
      printf("Usage is ./a.out <# of random numbers to Sort> <# of threads>\n");
      return 0;
    }
    int i;
    //convert string to int
    int n = atoi(argv[1]);
    int threadNum = atoi(argv[2]);
    //set num of threads to use if available
    omp_set_num_threads(threadNum);
    //make array with addr starting at p and fill it with randomness
    int *p = randomish_array(n);
    if (!p)
    {
        return 1;
    }

    //disable recursive parallel blocks, or else new thread is used every level of recursion
    omp_set_nested(0);

    gettimeofday(&start_time,NULL); // Unix timer
    //start the merge
    mergeSort(p, 0, n - 1);
    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    /* print them again */
    // printf("\nSorted numbers: ");
    // for(i = 0; i < n; i++) {
    //     printf("%d ", p[i]);
    // }
    printf("\n");
    printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
    free(p);//free array that was sorted
    return 0;
}
