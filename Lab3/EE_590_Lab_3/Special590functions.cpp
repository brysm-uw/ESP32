// Filename: Special590functions.cpp
// Author: First Name Last Name
// Date: 04/23/25
// Description: custom EEP 590 cpp file for custome functions.
// Intial Author: Gokul Nathan (TA)

#include "Special590functions.h"
#include <Arduino.h>

#define BUFFER_SIZE 128          // Define buffer size for all strings
char stringBuffer[BUFFER_SIZE];  // Declare a global buffer for strings

// Function to print a single character
void printChar(const char *c) {
  Serial.print(*c);
}


// Function to copy the string into the buffer and print each character
void printString(const char *str) {
  //task 1 step 2
  // This is a fully completed function for you to study.

  // Iterate through the memory locations of the input string
  char *dest = stringBuffer;  // Pointer to the destination buffer
  const char *src = str;      // Pointer to the source string

  // Copy characters from src to dest until null terminator or buffer limit
  while (*src != '\0' && (dest - stringBuffer) < BUFFER_SIZE - 1) {
    *dest = *src;     // Copy character
    printChar(dest);  // Print the copied character
    if (*dest == '\n') {
      break;  // Stop at newline character
    }
    src++;   // Move source pointer to next character
    dest++;  // Move destination pointer to next position
  }

  // Null terminate the buffer
  *dest = '\0';

  // Reset the buffer (clear all data)
  for (int i = 0; i < BUFFER_SIZE; i++) {
    stringBuffer[i] = '\0';
  }
}

// Function to convert a float to a string using sprintf and print its characters
void printFloat(float f) {
  // to do
  // task 1 step 3: Print the given float value 'f'
  // 'f' can be upto 8 digits long
  // 'f' should always be printed out to 2 decimal places
  char buffer[(sizeof(char) * 8) + 4]; // buffer should hold 8 char(1 byte each) + '.' + 2 numbers and a null terminator
  sprintf(buffer, "%.2f", f);
  printString(buffer);
  return 0;
}
