#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS  10000000

void merge(int a[], int i1, int j1, int i2, int j2);
void mergeSort(int a[], int i, int j);

int testa[MAX_ELEMENTS];
int testb[MAX_ELEMENTS - 1];

void mergeSort(int a[], int i, int j)
{
  int middle;

  if(i < j)
  {
    middle = (i+j)/2;
    mergeSort(a, i, middle);
    mergeSort(a, middle+1, j);
    merge(a, i, middle, middle + 1, j);
  }
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
  int i, j, k;
  i = i1;
  j = i2;
  k = 0;

  while(i <= j1 && j <= j2)
  {
    if(a[i] < a[j])
    {
      testb[k++]=a[i++];
    }
    else
    {
      testb[k++] = a[j++];
    }
  }

  while(i <= j1)
  {
    testb[k++] = a[i++];
  }

  while(j <= j2)
  {
    testb[k++] = a[j++];
  }

  j=0;
  for(i = i1; i <= j2; i++, j++)
  {
    a[i] = testb[j];
  }
}

int main()
{
  int i;
  srand(time(NULL));
  for(i = 0; i <= MAX_ELEMENTS; i++)
  {
    testa[i] = rand();
  }
  mergeSort(testa, 0, MAX_ELEMENTS - 1);
  printf("sorted array:\n");
  for(i = 0; i < MAX_ELEMENTS - 1; i++)
  {
    printf("%d\n",testa[i]);
  }
  return 0;
}
