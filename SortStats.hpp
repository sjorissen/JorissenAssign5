/* YOUR NAME HERE
 * CSCI 3250
 * Assignment 5
 * Header file containing code to analyze sorting algorithms
 */

#ifndef __SORT_STATS_H__
#define __SORT_STATS_H__

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>

// Used to indicate different orderings of an array to be sorted
const int ASCENDING = 0;
const int DESCENDING = 1;
const int RANDOM = 2;
const int MOSTLYSAME = 3;
std::string orders[] = {"ascending", "descending", "random", "mostly same"};

// Class to keep track of comparisons and assignments
class SortStats
{
public:
  // Constructor
  SortStats() {
    reset();
  }

  // Resets stats
  void reset() {
    mNumAssign = 0;
    mNumComp = 0;
  }

  // Performs and records an assignment
  void assign(int &var, int value) {
    var = value;
    mNumAssign++;
  }

  // Performs a swap and records three assignments
  void swap(int &var1, int &var2) {
    int temp = var1;
    var1 = var2;
    var2 = temp;
    mNumAssign += 3;
  }

  // Performs and records a comparison
  bool less(int value1, int value2) {
    mNumComp++;
    return value1 < value2;
  }

  // Gets the total number of assignments performed
  int getNumAssign( ) {
    return mNumAssign;
  }

  // Gets the total number of comparisons performed
  int getNumComp( ) {
    return mNumComp;
  }
  
private:
  // Number of assignments
  int mNumAssign;

  // Number of comparisons
  int mNumComp;
  
};

// Fill an array with elements in the specified order
void fillArray(int arr[], int size, int order) {
  switch(order) {
  case ASCENDING: // stores integers in ascending order from 1 up to size
    for(int i = 0; i < size; i++)
      arr[i] = i + 1;
    break;
  case DESCENDING: // stores integers in descending order from size down to 1
    for(int i = 0; i < size; i++)
      arr[i] = size - i;
    break;
  case RANDOM: // stores randomly selected integers in the array
    srand(time(NULL));
    for(int i = 0; i < size; i++)
      arr[i] = rand() % size;
    break;
  case MOSTLYSAME: // stores two different numbers repeatedly at random
    srand(time(NULL));
    for(int i = 0; i < size; i++)
      arr[i] = rand() % 2 + 42;
    break;
  }
}

// Display the contents of an array, 20 items per line
void displayArray(int arr[], int size) {
  for(int i = 0; i < size; i++) {
    if(i % 20 == 0 )
      std::cout << std::endl;
    std::cout << arr[i];
    if( i != size - 1)
      std::cout << ", ";
  }
  std::cout << std::endl << std::endl;
}

// Checks if an array is sorted
bool sorted(int arr[], int size) {
  for(int i = 0; i < size - 1; i++)
    if(arr[i] > arr[i + 1]) {
      return false;
    }
  return true;
}

// Displays the headings for the analysis
void displayHeadings() {
  std::cout << std::left
	    << std::setw(20) << "Algorithm"
	    << std::setw(15) << "Order"
	    << std::setw(10) << "Correct"
	    << std::right
	    << std::setw(15) << "Assignments"
	    << std::setw(20) << "Comparisons"
	    << std::endl;
  std::cout << std::left
	    << std::setw(20) << "---------"
	    << std::setw(15) << "-----"
	    << std::setw(10) << "-------"
	    << std::right
	    << std::setw(15) << "-----------"
	    << std::setw(20) << "------------"
	    << std::endl;
}

// Displays a row for the analysis
void displayRow(std::string algorithm, std::string order, bool correct, SortStats &stats ) {
  std::cout << std::left
	    << std::setw(20) << algorithm
	    << std::setw(15) << order
	    << std::setw(10) << (correct ? "yes" : "no")
	    << std::right
	    << std::setw(15) << stats.getNumAssign()
	    << std::setw(20) << stats.getNumComp()
	    << std::endl; 
}

// Tests a sorting algorithm
// If last argument is set to true, displays the contents of the array before and after sorting
void testSort(std::string algorithm, int size, void (*sort)(int [], int, SortStats &), bool displayContents) {
  int *arr = new int[size];
  SortStats stats;

  // Display headings for analysis if doing the short version of output
  if(!displayContents)
    displayHeadings();

  // Go through each of the four orderings
  for(int order = 0; order < 4; order++) {

    // Fill the array with items and display them if doing the long version
    fillArray(arr, size, order);
    if(displayContents) {
      std::cout << "Unsorted Array:" << std::endl;
      displayArray(arr, size);
    }

    // Sort the array and display the results if doing the long version
    (*sort)(arr, size, stats);
    if(displayContents) {
      std::cout << "Sorted Array:" << std::endl;
      displayArray(arr, size);
      displayHeadings();
    }

    // Display the algorithm used, the order of items, whether or not the sort worked correctly
    // and the number of assignments and comparisons made
    displayRow(algorithm, orders[order], sorted(arr, size), stats);
    if(displayContents) {
      std::cout << std::endl;
    }

    // Reset the statistics object for the next ordering
    stats.reset();
  }
  std::cout << std::endl;
}

#endif
