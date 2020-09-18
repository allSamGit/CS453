/**
 * CS453-2
 * Multi-threaded mergesort
 * @author Saman Rastgar
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>


#define TRUE 1
#define FALSE 0


typedef struct parameters{
    int *A;
    int start;
    int end;
    int numthreads;
}params;

// function prototypes
void serial_mergesort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
void multi_threaded_mergesort(int *A, int p, int r, int numberofthreads);
void *threaded_mergesort(void* data);

const int INSERTION_SORT_THRESHOLD = 100; //based on trial and error

/**
 * insertion_sort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void insertion_sort(int A[], int p, int r) 
{
	int j;

	for (j=p+1; j<=r; j++) {
		int key = A[j];
		int i = j-1;
		while ((i > p-1) && (A[i] > key)) {	
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

		


/**
 * serial_mergesort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void serial_mergesort(int A[], int p, int r) {

    if (r - p + 1 <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(A, p, r);
    } else {
        int q = (p + r) / 2;
        serial_mergesort(A, p, q);
        serial_mergesort(A, q + 1, r);
        merge(A, p, q, r);
    }
}


/**
 * Create thread if the numberthreads is greater than one, or call normal
 * serial_mergesort if the numberthreads is less than one or equal to one
 * @param A - Array
 * @param p - start point
 * @param r - end point
 * @param numberofthreads
 */
void multi_threaded_mergesort(int *A, int p, int r, int numberofthreads)
{
    if(numberofthreads == 1 || numberofthreads == 0) {
        int q = (p+r)/2;
        serial_mergesort(A, p, q);
        serial_mergesort(A, q+1, r);
        merge(A, p, q, r);
    } else {
        pthread_t pthread1=NULL, pthread2=NULL;
        params data1, data2;

		int q = (p+r)/2;

        //Left side data
        data1.A = A;
        data1.start = p;
        data1.end = q;
        if((numberofthreads/2) == 0){
            data1.numthreads = (numberofthreads/2)+1;
        } else {
         	data1.numthreads = numberofthreads/2;
        }

        //Right side data
        data2.A = A;
        data2.start = q+1;
        data2.end = r;
        if((numberofthreads/2) == 0){
            data2.numthreads = (numberofthreads/2)+1;
        } else {
            data2.numthreads = numberofthreads/2;
        }

        //Create pthreads
        pthread_create(&pthread1,NULL,threaded_mergesort,(void*)&data1);
        pthread_create(&pthread2,NULL,threaded_mergesort,(void*)&data2);

        //Join created pthreads
        pthread_join(pthread1, NULL);
        pthread_join(pthread2, NULL);

        merge(A, p, q, r);
	}
}


/**
 *Send arguments from the thread to multi_threaded_mergesort method
 * @param data
 */
void *threaded_mergesort(void* data) {
    params *args = (params *)data;
    int *array = args->A;
    int start = args->start;
    int end = args->end;
    int numberofthreads = args->numthreads;

    multi_threaded_mergesort(array, start, end, numberofthreads);
    pthread_exit(NULL);
}




/**
 * merge(int A[], int p, int q, int r):
 *
 * description: Merge two sorted sequences A[p..q] and A[q+1..r] 
 *              and place merged output back in array A. Uses extra
 *              space proportional to A[p..r].
 */     
void merge(int A[], int p, int q, int r) 
{
	int *B = (int *) malloc(sizeof(int) * (r-p+1));
		
	int i = p;
	int j = q+1;
	int k = 0;
	int l;
		
	// as long as both lists have unexamined elements
	// this loop keeps executing.
	while ((i <= q) && (j <= r)) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
		
	// now only at most one list has unprocessed elements.
		
	if (i <= q) { 
		// copy remaining elements from the first list
		for (l=i; l<=q; l++) {
			B[k] = A[l];
			k++;
		}
	} else {
		// copy remaining elements from the second list
		for (l=j; l<=r; l++) {
			B[k] = A[l];
			k++;
		}
	}
		
	// copy merged output from array B back to array A
	k=0;
	for (l=p; l<=r; l++) {
		A[l] = B[k];
		k++;
	}

	free(B);
}

