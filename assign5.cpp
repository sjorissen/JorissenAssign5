/* YOUR NAME HERE
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
//  testSort("insertion sort", SIZE, insertionSort, false);
//  testSort("selection sort", SIZE, selectionSort, false);
//  testSort("bubble sort", SIZE, bubbleSort, false);
//  testSort("heapsort", SIZE, heapSort, false);
  testSort("quicksort", SIZE, quickSort, false);
  testSort("mergesort", SIZE, mergeSort, false);

  return 0;
}

void insertionSort(int arr[], int size, SortStats &stats) {
  for (int i = 1; i < size; i++) {
    int j;
    stats.assign(j, i);
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
    for (int j = i; j < size; j++) {
      if(stats.less(arr[j],arr[small])) {
        stats.assign(small, j);
      }
    }
//    if(stats.less(arr[small], arr[i])) {
      stats.swap(arr[i], arr[small]);
//    }
  }
}

void bubbleSort(int arr[], int size, SortStats &stats) {
  bool inorder;
  do {
    inorder = true;
    for(int i = 0; i < size - 1; i++) {
      if (stats.less(arr[i + 1], arr[i])) {
        stats.swap(arr[i+1], arr[i]);
        inorder = false;
      }
    }
  } while(!inorder);
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
    stats.assign(pivot, arr[end]);
    int pindex = start;
    stats.assign(pindex,start);
    for(int i = start; i < end; i++) {
        if (!(stats.less(pivot, arr[i]))) {
            stats.swap(arr[i],arr[pindex]);
            pindex++;
        }
    }
    stats.swap(arr[pindex], arr[end]);
    return pindex;
}

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
    i = start;
    k = 0;
    j = mid + 1;

    int temp[end+1];

    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end) {
        temp[k] = arr[j];
        j++;
        k++;
    }
//    displayArray(temp, end - start + 1);
//    displayArray(arr, end - start + 1);

    int final = 0;
    for (i = start; i < end + 1; i++) {
        arr[i] = temp[final];
        final++;
    }
}

void msort(int arr[], int start, int end, SortStats &stats) {
    if (start < end) {
        int mid = (start + end) / 2;

        msort(arr, start, mid, stats);
        msort(arr, mid + 1, end, stats);
        merge(arr, start, end, mid, stats);
    }
}

void mergeSort(int arr[], int size, SortStats &stats) {
  msort(arr, 0, size - 1, stats);
}

