/* 
Title:    SortingTests.cpp
Author:   Lawrence Gabriel Castillo
Date:     2018-Nov-19
Desc:     Sample usage of SortingTests class
Purpose:  To incrementally test the SortingTests class
Build:    Visual Studio Code 1.31.1; compile: g++ -std=c++11 main.cpp SortingTests.cpp
*/

#include <iostream>
#include "SortingTests.hpp"

int main() 
{
    int arr[100];
/*
    generateRandomArray(arr, 100);
    selectionSort(arr, 100);

    generateRandomArray(arr, 100);
    sortTest(&selectionSort, arr, 100);

    generateAscendingArray(arr, 100);
    sortTest(&selectionSort, arr, 100);

    generateDescendingArray(arr, 100);
    sortTest(&selectionSort, arr, 100);

    generateLastTenRandomArray(arr, 100);
    sortTest(&selectionSort, arr, 100);
*/
    generateFewRandomArray(arr, 100);
    sortTest(&selectionSort, arr, 100);

    generateRandomArray(arr, 100);
    sortTest(&insertionSort, arr, 100);

    generateRandomArray(arr, 100);
    mergeSortTest(arr, 100);
}