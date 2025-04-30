// Filename: EE_590_Lab_3.ino
// Author: First Name Last Name
// Date: 04/23/25
// Description: Lab 3 arduino ESP 32 File.
// Intial Author: Gokul Nathan (TA)



#include "590Lab3.h"
#include "Special590functions.h"


DynamicArray processedData;
CircularBuffer cb;

#define INITIAL_BUFFER_SIZE 5

void setup() {
  Serial.begin(9600);

  printString("Starting Arduino Tasks\n");
}
// Task 2: Fibonacci and Factorial test cases. Use as needed
//   printString("Task 1: Fibonacci and Factorial\n");
//   int *fibSequence;
//   fibonacci(10, &fibSequence);

//ATTENTION: This is a to do task.
//Submitting this code as is without editing, will not give you full credit
//Remove the precceeding two lines, this line and the following line in your final submission.
//To do: Optimize for memory usage. This is not an effcient method.
//   for (int i = 0; i < 10; i++) { 
//     char buffer[10];
//     sprintf(buffer, "%d", fibSequence[i]);
//     printString(buffer);
//     if (i < 9) printString(", ");
//   }
//   free(fibSequence);
//   printString("\n");




//   int factorialResult;
//   factorial(5, &factorialResult);

//ATTENTION: This is a to do task.
//Submitting this code as is without editing, will not give you full credit
//Remove the precceeding two lines, this line and the following line in your final submission.
//To do: Optimize for memory usage. This is not an effcient method.
//   printString("Factorial(5): ");
//   char factBuffer[10];
//   sprintf(factBuffer, "%d", factorialResult);
//   printString(factBuffer);
//   printString("\n");

// Task 4: Dynamic Array sample test cases. Use as needed
//   printString("Task 2: Dynamic Array\n");
//   DynamicArray arr;
//   initArray(&arr, 2);
//   addElement(&arr, 10);
//   addElement(&arr, 20);
//   addElement(&arr, 30);
//   printArray(&arr);
//   freeArray(&arr);

// Task 5: Reverse String and Circular Buffer
//   printString("Task 3: Reverse String and Circular Buffer\n");
//   char str[] = "embedded";
//   reverseString(str);
//   printString("Reversed String: ");
//   printString(str);
//   printString("\n");

//   initBuffer(&cb, BUFFER_SIZE);
//   writeBuffer(&cb, 50);
//   writeBuffer(&cb, 150);
//   writeBuffer(&cb, 250);
//   writeBuffer(&cb, 350);
//   writeBuffer(&cb, 450);

//   char CBbuffer[10];
//   sprintf(CBbuffer, "%d", readBuffer(&cb));
//   printString("Buffer Read: ");
//   printString(CBbuffer);
//   printString("\n");
//   memset(CBbuffer, 0, 10);

//   sprintf(CBbuffer, "%d", readBuffer(&cb));
//   printString("Buffer Read: ");
//   printString(CBbuffer);
//   printString("\n");
//   memset(CBbuffer, 0, 10);

//   sprintf(CBbuffer, "%d", readBuffer(&cb));
//   printString("Buffer Read: ");
//   printString(CBbuffer);
//   printString("\n");
//   memset(CBbuffer, 0, 10);

//   sprintf(CBbuffer, "%d", readBuffer(&cb));
//   printString("Buffer Read: ");
//   printString(CBbuffer);
//   printString("\n");
//   memset(CBbuffer, 0, 10);


// Task 4: Test Pointer Operations
// Use and modify as needed
void testPointerOperations() {
  Serial.println("\nTask 1: Pointer Operations");

  int array[] = { 10, 20, 30, 40, 50 };

  int distance = pointer_distance(&array[1], &array[4], array, array + 5);
  Serial.print("Pointer Distance (array[1] to array[4]): ");
  Serial.println(distance);  // Expected: 3

  distance = pointer_distance(&array[4], &array[1], array, array + 5);
  Serial.print("Pointer Distance (array[4] to array[1]): ");
  Serial.println(distance);  // Expected: -3

  distance = pointer_distance(&array[0], &array[5], array, array + 5);
  Serial.print("Pointer Distance (array[0] to out-of-bounds): ");
  Serial.println(distance == INT_MAX ? "INT_MAX (out-of-bounds)" : String(distance));  // Expected: INT_MAX

  Serial.println("\nTask 1 completed.");
}


// Task 5: Test Circular Buffer Operations
// Use and modify as needed
void testCircularBuffer() {
  Serial.println("\nTask 3: Circular Buffer Operations");

  // Initialize buffer
  initBuffer(&cb, INITIAL_BUFFER_SIZE);
  Serial.println("Initialized Circular Buffer with size 5");

  // Write elements into the buffer
  Serial.println("Writing elements [1, 2, 3, 4, 5]:");
  for (int i = 1; i <= 5; i++) {
    writeBuffer(&cb, i);
  }
  Serial.println("Expected buffer contents: [1, 2, 3, 4, 5]");
  Serial.print("Actual buffer contents: ");
  for (int i = 0; i < cb.count; i++) {
    Serial.print(cb.buffer[(cb.tail + i) % cb.max_size]);
    Serial.print(" ");
  }
  Serial.println();

  // Read the oldest element without modifying the buffer
  int readValue = readBuffer(&cb);
  Serial.print("\nRead the oldest element (before pop): ");
  Serial.println(readValue);  // Expected: 1

  // Pop the oldest element
  int poppedValue = popBuffer(&cb);

  // Read the oldest element again without modifying the buffer
  readValue = readBuffer(&cb);
  Serial.print("Read the oldest element (after pop): ");
  Serial.println(readValue);  // Expected: 2

  // Resize the buffer
  Serial.println("\nResizing buffer from size 5 to 10...");
  resizeBuffer(&cb, 10);

  // Fill buffer with values counting down from 99
  Serial.println("\nFilling buffer with values counting down from 99:");
  for (int i = 99; i >= 90; i--) {
    writeBuffer(&cb, i);
  }
  Serial.println("Expected buffer contents: [2, 3, 4, 5, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90]");
  Serial.print("Actual buffer contents: [");
  for (int i = 0; i < cb.count; i++) {
    Serial.print(cb.buffer[(cb.tail + i) % cb.max_size]);
    Serial.print(", ");
  }
  Serial.print("]");


  // Pop and print all values
  Serial.println("\nPopping values:");
  int break_count = 0;
  while (!isEmpty(&cb)) {
    int value = popBuffer(&cb);
    break_count += 1;
    if (break_count > 30) break;
  }

  Serial.println("Expected buffer contents: []");
  Serial.print("Actual buffer contents: [");
  for (int i = 0; i < cb.count; i++) {
    Serial.print(cb.buffer[(cb.tail + i) % cb.max_size]);
    Serial.print(" ");
  }
  Serial.print("]");


  // Free buffer memory
  freeBuffer(&cb);
  Serial.println("\nCircular Buffer test completed.");
}


void loop() {
  //To do: Task 6
  // Observed Behavior: Simulates environmental sensing via an LDR, processes the readings, updates LED state, and stores averaged results.
  // Commented Purpose: Demonstrates integration of string manipulation, dynamic memory, and circular buffers in a real-time sensing and control task.
  // Edge Case Handling: Handles buffer wrap-around, buffer full condition, and dynamic array resizing automatically.
  // Error Handling: Assumes sensor and LED GPIO are properly initialized elsewhere as direct register access is used.


  // Here is some guiding logic and psuedo code.
  // 1. Setup:
  //    - Create a circular buffer that can hold 10 LDR readings (5 seconds at 2 Hz).
  //    - Create a dynamic array to store brightness averages.
  //    - Initialize two timing variables:
  //      a. One for sampling every 500 milliseconds.
  //      b. One for averaging and brightness update every 1000 milliseconds.
  //    - Enable output for the LED (via register control).

  // 2. Inside the main loop:
  //    a. Check if 500 milliseconds have passed since the last sample:
  //       - If yes:
  //          • Read the current value from the LDR sensor.
  //          • Store this value into the circular buffer.
  //          • Reset the 500 ms timer.

  //    b. Check if 1000 milliseconds have passed since the last average:
  //       - If yes:
  //          • Compute the average of the values currently in the circular buffer.
  //          • Store this average in the dynamic array.
  //          • Map this average to a brightness level.
  //          • Apply this brightness level to the LED using PWM register logic.
  //          • Print the contents of the dynamic array to the serial monitor.
  //          • Reset the 1000 ms timer.

  // 3. Do not use any blocking function calls (no delays).
  // 4. Do not use pinMode() or digitalWrite(); use direct register access instead.
  // 5. Ensure that your code does not interfere with other running tasks in the .ino file.
}
