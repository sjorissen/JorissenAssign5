/* Sarah Jorissen
 * CSCI 3250
 * Assignment 5
 * Implements and tests six different sorting algorithms
 */

#include "SortStats.hpp"

using namespace std;

void insertionSort(int arr[], int size, SortStats &stats);
void selectionSort(int arr[], int size, SortStats &stats);
void bubbleSort(int arr[], int size, SortStats &stats);
void heapSort(int arr[], int size, SortStats &stats);
void quickSort(int arr[], int size, SortStats &stats);
void mergeSort(int arr[], int size, SortStats &stats);

int main()
{
    const int SIZE = 20;

    // Tests each algorithm using four different orderings.
    // Set the last argument to true to display contents of array before and after sorting
    testSort("insertion sort", SIZE, insertionSort, false);
    testSort("selection sort", SIZE, selectionSort, false);
    testSort("bubble sort", SIZE, bubbleSort, false);
    testSort("heapsort", SIZE, heapSort, false);
    testSort("quicksort", SIZE, quickSort, false);
    testSort("mergesort", SIZE, mergeSort, false);

    return 0;
}

void insertionSort(int arr[], int size, SortStats &stats) {
    // index i keeps track of values already sorted, ends loop when all values are in their right place
    for (int i = 1; i < size; i++) {
        int j; // index j goes through array to compare values
        stats.assign(j, i);
        // if a value at index j is less than the value prior to it, swap them
        while(stats.less(arr[j], arr[j-1]) && j != 0) {
            stats.swap(arr[j],arr[j-1]);
            j--;
        }
    }
}

void selectionSort(int arr[], int size, SortStats &stats) {
    for (int i = 0; i < size; i++) {
        int small;
        stats.assign(small, i);
        // finds smallest element in the array
        for (int j = i; j < size; j++) {
            if(stats.less(arr[j],arr[small])) {
                stats.assign(small, j);
            }
        }
        // places smallest element at next i iteration
        stats.swap(arr[i], arr[small]);
    }
}

void bubbleSort(int arr[], int size, SortStats &stats) {
    bool inorder; // checks to see if array is in order
    do {
        inorder = true;
        for(int i = 0; i < size - 1; i++) {
            // compares value in array with the value beside it, swap if the left value is higher
            if (stats.less(arr[i + 1], arr[i])) {
                stats.swap(arr[i+1], arr[i]);
                // if a swap is made, set inorder to false
                inorder = false;
            }
        }
    } while(!inorder); // when inorder is set to false
}

void heapSort(int arr[], int size, SortStats &stats) {
    int heap_arr[size + 1];
    int count; // counter to decrement our last index of arrays

    // Copies array into second "heap array" that starts at index 1
    for (int i = 1; i < size + 1; i++) {
        stats.assign(heap_arr[i], arr[i - 1]);
    }

    // Loops through and takes largest of heap and assigns it to end of array, then decrements
    // last index of both arrays
    for(count = size; count > 0; count--) {

        // Goes through heap array & pushes largest value to index 1
        for (int i = count / 2; i > 0; i--) {
            bool do_not_skip = !(i%2 == 0 && i == count);
            if (do_not_skip && stats.less(heap_arr[i * 2], heap_arr[i * 2 + 1])) {
                if (stats.less(heap_arr[i], heap_arr[i * 2 + 1]))
                    stats.swap(heap_arr[i], heap_arr[i * 2 + 1]);
            } else if (stats.less(heap_arr[i], heap_arr[i * 2])) {
                stats.swap(heap_arr[i], heap_arr[i * 2]);
            }
        }

        // Swaps first and last index to remove largest value and maintain heap structure
        stats.swap(heap_arr[count], heap_arr[1]);

        // Assign largest value to end of original array
        stats.assign(arr[count - 1], heap_arr[count]);
    }
}

int partition(int start, int end, int arr[], SortStats &stats) {
    int pivot;
    stats.assign(pivot, arr[end]); // chooses value at array end as pivot
    int pindex = start; // pivot index, to sort by swapping with values <= pivot
    stats.assign(pindex,start);

    // compares each value in array to pivot, and swaps it with pindex if it is less than or equal to pivot value
    // increments pivot until entire array is complete
    for(int i = start; i < end; i++) {
        if (!(stats.less(pivot, arr[i]))) {
            stats.swap(arr[i],arr[pindex]);
            pindex++;
        }
    }
    // once array is sorted into lesser & greater than halves, swap pindex with pivot
    stats.swap(arr[pindex], arr[end]);
    return pindex;
}

// recursively sort each side of array
void qsort(int start, int end, int arr[], SortStats &stats) {
    if (stats.less(start, end)) {
        int pindex = partition(start, end, arr, stats);
        qsort(start, pindex - 1, arr, stats);
        qsort(pindex + 1, end, arr, stats);
    }
}

void quickSort(int arr[], int size, SortStats &stats) {
    qsort(0, size - 1, arr, stats);
}

int merge(int arr[], int start, int end, int mid, SortStats &stats) {
    int i, j, k;
    stats.assign(i, start); // index i for left half of divided array
    stats.assign(k, 0); // index k for temp array
    stats.assign(j, mid + 1); // index j for right half of array

    int temp[end+1]; // temp array to sort values

    while (!(stats.less(mid, i)) && !(stats.less(end, j))) {
        // compare values in left and right arrays
        if (stats.less(arr[i], arr[j])) {
            // if left array value is smaller, store in temp array
            stats.assign(temp[k], arr[i]);
            i++;
        }
        else {
            // if right array value is smaller, store in temp array
            stats.assign(temp[k], arr[j]);
            j++;
        }
        k++;
    }

    // stores any extra values remaining in left array into temp
    while (!(stats.less(mid, i))) {
        stats.assign(temp[k], arr[i]);
        i++;
        k++;
    }

    // stores any extra values remaining in right array into temp
    while (!(stats.less(end, j))) {
        stats.assign(temp[k], arr[j]);
        j++;
        k++;
    }

    // copies temp into original array
    int final;
    stats.assign(final, 0);
    for (i = start; i < end + 1; i++) {
        stats.assign(arr[i], temp[final]);
        final++;
    }
}

// recursively divides array into smaller arrays, sorts each array then merges them
void msort(int arr[], int start, int end, SortStats &stats) {
    if (stats.less(start, end)) {
        int mid;
        stats.assign(mid, (start + end) / 2);

        msort(arr, start, mid, stats);
        msort(arr, mid + 1, end, stats);
        merge(arr, start, end, mid, stats);
    }
}

void mergeSort(int arr[], int size, SortStats &stats) {
    msort(arr, 0, size - 1, stats);
}

/*
 *                              ,+*^^*+___+++_
                       ,*^^^^              )
                    _+*                     ^**+_
                  +^       _ _++*+_+++_,         )
      _+^^*+_    (     ,+*^ ^          \+_        )
     {       )  (    ,(    ,_+--+--,      ^)      ^\
    { (@)    } f   ,(  ,+-^ __*_*_  ^^\_   ^\       )
   {:;-/    (_+*-+^^^^^+*+*<_ _++_)_    )    )      /
  ( /  (    (        ,___    ^*+_+* )   <    <      \
   U _/     )    *--<  ) ^\-----++__)   )    )       )
    (      )  _(^)^^))  )  )\^^^^^))^*+/    /       /
  (      /  (_))_^)) )  )  ))^^^^^))^^^)__/     +^^
 (     ,/    (^))^))  )  ) ))^^^^^^^))^^)       _)
  *+__+*       (_))^)  ) ) ))^^^^^^))^^^^^)____*^
  \             \_)^)_)) ))^^^^^^^^^^))^^^^)
   (_             ^\__^^^^^^^^^^^^))^^^^^^^)
     ^\___            ^\__^^^^^^))^^^^^^^^)\\
          ^^^^^\uuu/^^\uuu/^^^^\^\^\^\^\^\^\^\
             ___) >____) >___   ^\_\_\_\_\_\_\)
            ^^^//\\_^^//\\_^       ^(\_\_\_\)
              ^^^ ^^ ^^^ ^^

              Happy Turkey Day :)
 *
 */