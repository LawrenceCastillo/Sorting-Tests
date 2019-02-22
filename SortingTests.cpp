/* 
Title:    SortingTests.cpp
Author:   Lawrence Gabriel Castillo
Author:   Header created by Prof. Tiziana Ligorio for Hunter College
Date:     2018-Nov-19
Desc:     Sorting tests: selection, insertion, merge
Purpose:  To create solutions for and implement 3 sorting algorithms 
          and test efficiency.
Build:    Visual Studio Code 1.31.1; compile: g++ -std=c++11 main.cpp SortingTests.cpp
*/

#include "SortingTests.hpp"
#include <chrono>
#include <iostream>

using namespace std::chrono;

/*****************************************************************/
/********************* SORTING FUNCTIONS *************************/
/*****************************************************************/

/*
 @post Sorts an array in ascending order using the selection sort algorithm.
 @param a[] to sort
 @param size the number of elements in a[]
 */
void selectionSort(int a[], size_t size)
{ 
    int i, j;
    
    // compares a[i] to rem a[j]; updates for a[j] < a[i]
    for (i = 0; i < size; i++)
        { int minValue = a[i]; int minIndex = i;

        for (j = (i + 1); j < size; j++)
            { if (a[j] < minValue) { minValue = a[j]; minIndex = j; }}

        if (minValue != a[i]) // if a[j] < a[i], swap a[i], a[j]; no update= a[i] in order
            { a[minIndex] = a[i]; a[i] = minValue; }}
}

/*
 @post Sorts an array in ascending order using insertion sort.
 @param a[] to sort
 @param size of the array
 */
void insertionSort(int a[], size_t size)
{
    int i, j;

    // places each value (keyValue) at correct index
    for (i = 0; i < (size - 1); i++)
        { int keyValue = a[i + 1]; int nextIndex = i + 1; j = i;

        while (j > -1 && keyValue < a[j]) // determines keyValue placement by checking front of loop
            { a[nextIndex] = a[j]; nextIndex--; j--; } // slides array back for a[j] > keyValue
        
        a[j + 1] = keyValue; }
}

/*
 @post Sorts the elements in a range of a array.
 @param a[] with the elements to sort
 @param from the first position in the range to sort
 @param to the last position in the range to sort (included)
 */
void mergeSort(int a[], int from, int to)
{
    // arrays for splitting a[]; in odd cases, right gets the extra space
    int *left = new int[(to+1)/2]; int lSize = (to+1)/2;
    int *right = new int[(to+1)/2+(to+1)%2]; int rSize = (to+1)/2+(to+1)%2;

    // copy data to left, right
    for (int i = 0; i < (to+1)/2; i++)
        { left[i] = a[i]; }
    for (int i = 0; i < (to+1)/2+(to+1)%2; i++)
        { right[i] = a[i+(to+1)/2]; }

    if (to+1 <= 1) { return; } // base case
    
    else // split the array
        { mergeSort(left, 0, (to+1)/2-1);
        mergeSort(right, 0, (to+1)/2-1+(to+1)%2); }

    //***** merge left, right in ascending order *****//

    int lIndex = 0; int rIndex = 0;
    int i = 0;

    // update a[] with values in ascending order
    while (lIndex < (to+1)/2 || rIndex < (to+1)/2+(to+1)%2) // while left, right not empty
        { if (lIndex < (to+1)/2 && rIndex < (to+1)/2+(to+1)%2) // if left, right both have values
            // compare left, right; update a[] with lesser value
            { if (left[lIndex] < right[rIndex])
                { a[i] = left[lIndex];
                i++; lIndex++; }

            else
            { a[i] = right[rIndex];
                i++; rIndex++; }}

        // update a[] with remaining values from left or right
        else if (lIndex < (to+1)/2)
            { a[i] = left[lIndex];
            i++; lIndex++; }

        else 
            { a[i] = right[rIndex];
            i++; rIndex++; }}

    delete[] left;
    delete[] right;
}

/*********************************************************************/
/****************** ARRAY POPULATING FUNCTIONS ***********************/
/*********************************************************************/

/*
 @post Populates values with randomly generated numbers in range size
 @param values the array to populate
 @param size of the array to be populated
 */
void generateRandomArray(int values[], size_t size)
{
    srand(static_cast<unsigned>(time(0))); // generates seed using timestamp
    
    for (int i = 0; i < size; i++) { values[i] = rand() % size; } // initializes array with random values
}

/*
 @post Populates values with integers in ascending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateAscendingArray(int values[], size_t size)
{
    selectionSort(values, size);
}

/*
 @post Populates values with integers in descending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateDescendingArray(int values[], size_t size)
{
    selectionSort(values, size);
    
    for (int i = 0; i < (size /2); i++) { std::swap(values[i], values[size -1 -i]); } // reverses sorted order
}

/*
 @post Populates values with integers in ascending order except for the last 10 that are randomly generated
 @param values the array to populate
 @param size of the array to be populated
 */
void generateLastTenRandomArray(int values[], size_t size)
{
    generateRandomArray(values, size); 
    selectionSort(values, size-10); // utilizes function to sort all but last 10 values
}

/*
 @post Populates values with integers in randomly generated in range size/10
 @param values the array to populate
 @param size of the array to be populated
 */
void generateFewRandomArray(int values[], size_t size)
{
    srand(static_cast<unsigned>(time(0))); // generates seed using timestamp
    
    for (int i = 0; i < size; i++) { values[i] = rand() % size/10; } // truncates possible values for random selection
}

/*****************************************************************/
/****************** RUNTIME TEST FUNCTIONS ***********************/
/*****************************************************************/

/*
 @post Sorts values in ascending order and averages its runtime over 10 runs
 @param sortingFunction the function used to sort the array
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double sortTest(void (*sortingFunction)(int a[], size_t size), int values[], size_t size)
{
    int *dupValues = new int[size];
    double runtime_sum;

    for (int i = 0; i < 10; i++)
        { for (int i = 0; i < size; i++) { dupValues[i] = values[i]; } // array copy
        auto startTime = high_resolution_clock().now();
        sortingFunction(dupValues, size); // sorts copy
        auto endTime = high_resolution_clock().now();
        duration<float, std::micro> run_time = duration_cast<microseconds>(endTime - startTime); // determines runtime duration
        runtime_sum += run_time.count(); } // accumulates total runtime over 10 runs

    for (int i = 0; i<size; i++) { std::cout << dupValues[i] << std::endl; } // print last array sort
    delete[] dupValues; // deallocate array copy

    runtime_sum = runtime_sum / 10; // divides by 10 to get average
    std::cout << "The average runtime is: " << runtime_sum << std::endl; // print sort function runtime
    return runtime_sum;
}

/*
 @post Sorts values in ascending order using mergeSort and averages its runtime over 10 runs
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double mergeSortTest(int values[], size_t size)
{
    int *dupValues = new int[size];
    double runtime_sum;

    for (int i = 0; i < 10; i++)
        { for (int i = 0; i < size; i++) { dupValues[i] = values[i]; } // array copy
        auto startTime = high_resolution_clock().now();
        mergeSort(dupValues, 0, size-1); // sorts copy
        auto endTime = high_resolution_clock().now();
        duration<float, std::micro> run_time = duration_cast<microseconds>(endTime - startTime); // determines runtime duration
        runtime_sum += run_time.count(); } // accumulates total runtime over 10 runs

    for (int i = 0; i<size; i++) { std::cout << dupValues[i] << std::endl; } // print last array sort
    delete[] dupValues; // deallocate array copy

    runtime_sum = runtime_sum / 10; // divides by 10 to get average
    std::cout << "The average runtime is: " << runtime_sum << std::endl; // print sort function runtime
    return runtime_sum;
}
