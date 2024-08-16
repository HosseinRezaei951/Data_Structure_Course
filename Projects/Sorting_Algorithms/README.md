# Sorting Algorithms

This repository contains implementations of various sorting algorithms in C++. The goal is to provide a comprehensive set of sorting methods to compare and understand their performance. The algorithms implemented include Bubble Sort, Insertion Sort, Merge Sort, Quick Sort, Selection Sort, and Heap Sort.

## Data Structure

The system uses a `vector<int>` to manage and sort arrays. Various sorting algorithms are applied to these vectors to organize the elements in ascending order. 

## Features

- **Bubble Sort**: A simple comparison-based sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
- **Insertion Sort**: A comparison-based sorting algorithm that builds the final sorted array one item at a time.
- **Merge Sort**: A divide-and-conquer algorithm that divides the array into halves, recursively sorts each half, and then merges the sorted halves.
- **Quick Sort**: A divide-and-conquer algorithm that selects a 'pivot' element, partitions the array into elements less than the pivot and elements greater than the pivot, and recursively sorts the partitions.
- **Selection Sort**: A comparison-based sorting algorithm that repeatedly selects the smallest (or largest) element from the unsorted portion and moves it to the end of the sorted portion.
- **Heap Sort**: A comparison-based sorting algorithm that converts the array into a heap data structure and then sorts it by repeatedly removing the largest element from the heap and reconstructing the heap.

## How It Works

1. **Initialization**:
   - The `MyArray` class initializes an array of random integers between a given range.

2. **Sorting Algorithms**:
   - **BubbleSort**: Sorts the array by repeatedly swapping adjacent elements if they are in the wrong order.
   - **InsertionSort**: Sorts the array by building a sorted section at the beginning of the array, one element at a time.
   - **MergeSort**: Recursively divides the array into two halves, sorts each half, and then merges the sorted halves.
   - **QuickSort**: Uses a pivot to partition the array into elements less than and greater than the pivot and sorts the partitions recursively.
   - **SelectionSort**: Selects the smallest element from the unsorted portion and places it at the end of the sorted portion.
   - **HeapSort**: Builds a heap from the array and repeatedly extracts the largest element to sort the array.

## Code Structure

The code is organized into a single class `MyArray` with the following methods:

- **Constructor and Destructor**:
  - `MyArray(int lowest, int highest, int Length)`: Initializes the array with random numbers.
  - `~MyArray()`: Clears the array.

- **Sorting Methods**:
  - `BubbleSort(int &Swap, int &Check)`: Implements Bubble Sort.
  - `InsertionSort(int &Swap, int &Check)`: Implements Insertion Sort.
  - `MergeSort(int &Swap, int &Check)`: Implements Merge Sort.
  - `QuickSort(int &Swap, int &Check)`: Implements Quick Sort.
  - `SelectionSort(int &Swap, int &Check)`: Implements Selection Sort.
  - `HeapSort(int &Swap, int &Check)`: Implements Heap Sort.

- **Utility Methods**:
  - `swap(vector<int> &Array, int p, int q)`: Swaps two elements in the array.
  - `heapify(vector<int> &Array, int Heap_Size, int index, int &Swap, int &Check)`: Ensures the heap property.
  - `partition(vector<int> &Array, int Low, int High, int &Swap, int &Check)`: Partitions the array for Quick Sort.
  - `merge(vector<int> &Result, vector<int> &Left_Arr, vector<int> &Right_Arr, int &Swap, int &Check)`: Merges two sorted arrays for Merge Sort.
  - `do_MergeSort(vector<int> &Array, int &Swap, int &Check)`: Recursive helper function for Merge Sort.
  - `do_QuickSort(vector<int> &Array, int Low, int High, int &Swap, int &Check)`: Recursive helper function for Quick Sort.

## How to Use

1. **Compile the Code**:
   - Use a C++ compiler to compile the code. For example, with `g++`:
     ```bash
     g++ -o sorting_algorithms sorting_algorithms.cpp
     ```

2. **Run the Program**:
   - Execute the compiled program:
     ```bash
     ./sorting_algorithms
     ```