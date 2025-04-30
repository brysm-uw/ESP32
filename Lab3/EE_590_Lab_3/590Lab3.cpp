// Filename: 590Lab3.cpp
// Author: First Name Last Name
// Date: 04/23/25
// Description: Lab 3 cpp file.
// Intial Author: Gokul Nathan (TA)


#include "590Lab3.h"
#include "Special590functions.h"
#include "Arduino.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Demo Task 2.1: Fibonacci Sequence
// Observed Behavior: Generates a Fibonacci sequence of length N and stores it in a dynamic array.
// Commented Purpose: Illustrates recursive or iterative numerical computation.
// Edge Case Handling: Exit early if N <= 0.
// Error Handling: Assumes memory is properly allocated for sequence.
void fibonacci(int N, int **sequence) {
  // to do
  // task 2 step 1: Print the fibonacdi sequence upto digit n
  
}



// Demo Task 2.2: Factorial Calculation
// Observed Behavior: Computes the factorial of a given non-negative integer.
// Commented Purpose: Basic recursion/iteration exercise for mathematical operations.
// Edge Case Handling: For n = 0, result is 1.
// Error Handling: Returns -1 for negative input.
int factorial(int n, int *result) {
  // to do
  // task 2 step 1: Print the fibonacdi sequence upto digit n
}

// Demo Task 3.1: Initialize Dynamic Array
// Observed Behavior: Initializes a dynamic integer array with specified capacity.
// Commented Purpose: Teaches dynamic memory allocation.
// Edge Case Handling: Ensures zero-size start is not allowed.
// Error Handling: Returns on malloc failure.
void initArray(DynamicArray *arr, int initialCapacity) {
  // To do:

  // Allocate memory for initialCapacity integers.
  // Set the array’s size to 0.
  // Set the array’s capacity to the value of initialCapacity.
  // If memory allocation fails, print an error message to the Serial Monitor and exit the function.
}


// Demo Task 3.2: Add Element to Dynamic Array
// Observed Behavior: Adds an element to the array; resizes if needed.
// Commented Purpose: Demonstrates array growth logic.
// Edge Case Handling: Handles capacity overflow.
// Error Handling: Memory errors should be caught and reported.
void addElement(DynamicArray *arr, int element) {
  // To do:
  // Before inserting, check if the array has reached its capacity.
  // If so, reallocate memory to double the current capacity and update the internal capacity value.
  // After ensuring space is available, insert the new value at the current size index.
  // Increment the size field.
}


// Demo Task 3.3: Print Dynamic Array
// Observed Behavior: Prints each element of the array to the serial monitor.
// Commented Purpose: Provides output visibility of internal data.
// Edge Case Handling: Prints nothing if array is empty.
// Error Handling: Assumes array is initialized.
void printArray(DynamicArray *arr) {
  // To do:
  // Loop through the array and print each integer.
  // Separate values using commas or tabs.
  // Print a newline character after the last value for formatting.
}


// COMPLETED SAMPLE FUNCTION: Free Dynamic Array
// Observed Behavior: Frees memory and resets array fields.
// Commented Purpose: Demonstrates cleanup of dynamic structures.
// Edge Case Handling: Can be safely called multiple times.
void freeArray(DynamicArray *arr) {
  free(arr->data);
  arr->data = NULL;
  arr->size = 0;
  arr->capacity = 0;
}

// Demo Task 4.1: Pointer Distance
// Calculates the number of elements between two pointers within the same array.
// Returns INT_MAX if the pointers are out of bounds.
// Input: ptr1, ptr2 - pointers to compare; array_start, array_end - bounds of the array.
int pointer_distance(int *ptr1, int *ptr2, int *array_start, int *array_end) {
  // complete the function
  return INT_MAX;
}

// Demo Task 4.2: Memory Copy
// Copies `n` bytes from `src` to `dest`.
// Input: dest - destination pointer; src - source pointer; n - number of bytes to copy.
void mem_copy(void *dest, const void *src, size_t n) {
  // complete the function
}

// Demo Task 4.3: Array Modify
// Modifies each element of the array using a function pointer.
// Input: arr - array to modify; len - length of the array; mod_func - function to apply to each element.
// Returns -1 if inputs are invalid.
int array_modify(int *arr, size_t len, int (*mod_func)(int)) {
  // complete the function
  return 0;
}


// Demo Task 4.4: String Array
// Converts a string representing a positive unsigned integer into its numeric equivalent
// String representing a positive unsigned integer into its numeric equivalent
// Input: str: const char* – pointer to the input null-terminated string.
// int – the numeric equivalent of the string, or -1 on error.
int str_to_int(const char *str) {
  return INT_MAX;
}

// Demo Task 4.5: Print Truth Table
// Observed Behavior: Computes and displays a truth table from two binary strings.
// Commented Purpose: Explains bitwise operations and string parsing.
// Edge Case Handling: Limits output to 16 bits max.
// Function to print the truth table for bitwise operations
void print_truth_table(const char *a, const char *b) {
  int binary_a = str_to_int(a);
  int binary_b = str_to_int(b);

  // Print table header using Special590functions
  printString("\nTruth Table for Bitwise Operations\n");
  printString("------------------------------------------\n");
  printString("Index\tA\tB\tA AND B\tA OR B\tA XOR B\tNOT A\tNOT B\n");
  printString("------------------------------------------\n");

  // Loop through each bit position (up to 16 bits)


  printString("------------------------------------------\n");
}




// Demo Task 5.1: String Manipulation
// Parameters:
//   str: char* – pointer to the null-terminated string to reverse.
// Returns:
//   void – the operation modifies the input string in place.
void reverseString(char *str) {
  //To Do:

  // Set a pointer or index to the beginning of the string.
  // Set another pointer/index to the end of the string (just before the null terminator).
  // Swap characters at the two ends.
  // Move both pointers toward the center.
  // Repeat until the pointers meet or cross.
}


// Demo Task 5.2: Circular Buffer
//COMPLETED SAMPLE FUNCTION
void initBuffer(CircularBuffer *cb, size_t size) {
  cb->buffer = (int *)malloc(size * sizeof(int));
  cb->head = 0;
  cb->tail = 0;
  cb->count = 0;
  cb->max_size = size;
}

//COMPLETED SAMPLE FUNCTION
void freeBuffer(CircularBuffer *cb) {
  free(cb->buffer);
  cb->buffer = NULL;
  cb->head = 0;
  cb->tail = 0;
  cb->count = 0;
  cb->max_size = 0;
}


//To DO
bool isFull(CircularBuffer *cb) {
  // Return true if size equals capacity.
  // Return false otherwise.
  return false;
}

//To DO
bool isEmpty(CircularBuffer *cb) {
  // Return true if size is zero.
  // Return false otherwise.
  return false;
}

//To DO
void writeBuffer(CircularBuffer *cb, int value) {
  //If the buffer is full, do not write. Throw an error.
  // Otherwise:
  // Write value at head.
  // Advance head (wrap if needed).
  // Increment size of the buffer.
}

//To DO
int readBuffer(CircularBuffer *cb) {
  // If buffer is empty, return -1.
  // Otherwise:
  // Read value at tail.
  // Return value.
  return -1;
}

//To DO
int popBuffer(CircularBuffer *cb) {
  // If buffer is empty, return -1.
  // Read value at tail.
  // Advance tail, reduce size.
  // Return value.
  return -1;
}

//To DO
// Push an element into the buffer
void pushBuffer(CircularBuffer *cb, int value) {
  // If buffer is full:
  // Overwrite at tail and advance tail.
  // Write at head.
  // Advance head.
  // If not full, increment size.
}

//To DO
void resizeBuffer(CircularBuffer *cb, size_t new_size) {
  // Allocate a new array with the new capacity.
  // Copy the old values (in correct FIFO order) into the new buffer.
  // Free the old buffer.
  // Update buffer pointers and capacity.
}


//To do:
// Demo Task 6: Buffer Operations
// Observed Behavior: Reads LDR sensor values at 2 Hz and computes averaged brightness at 1 Hz.
// Commented Purpose: Integrates sensor input, buffer management, and real-time processing.
// Edge Case Handling: Ensures LED brightness updates only on valid data.
// Error Handling: Assumes circular buffer and dynamic array are initialized.
void simulateSensorData(CircularBuffer *cb, DynamicArray *processedData) {
  //This function prototype is predefined. You are allowed to modify the function as needed.
}
