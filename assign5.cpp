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
  testSort("insertion sort", SIZE, insertionSort, false);
  testSort("selection sort", SIZE, selectionSort, false);
  testSort("bubble sort", SIZE, bubbleSort, false);
//  testSort("heapsort", SIZE, heapSort, false);
//  testSort("quicksort", SIZE, quickSort, false);
//  testSort("mergesort", SIZE, mergeSort, false);

  return 0;
}

void insertionSort(int arr[], int size, SortStats &stats) {
  for (int i = 1; i < size; i++) {
    int j = i;
    while(stats.less(arr[j], arr[j-1]) && j != 0) {
      stats.swap(arr[j],arr[j-1]);
      j--;
    }
  }
}

void selectionSort(int arr[], int size, SortStats &stats) {
  for (int i = 0; i < size; i++) {
    int small = i;
    for (int j = i; j < size; j++) {
      if(stats.less(arr[j],arr[small])) {
        small = j;
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
  /* YOUR CODE HERE */
}

void quickSort(int arr[], int size, SortStats &stats) {
  /* YOUR CODE HERE */
}

void mergeSort(int arr[], int size, SortStats &stats) {
  /* YOUR CODE HERE */
}

