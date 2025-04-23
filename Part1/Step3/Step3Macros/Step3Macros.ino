#define GPIO_PIN 5

// Timing variables
uint32_t accumulatedTime = 0;

void setup() {
  pinMode(GPIO_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ctr = 0;
  while(ctr < 1000) {
    accumulatedTime += toggle(GPIO_PIN);
    ctr++;
    Serial.println("Total Time for 1000 toggles: ");
    Serial.print("Toggle ");
    Serial.print(ctr);
    Serial.print(": ");
    Serial.print(accumulatedTime);
    Serial.print("\n\n");
  }
  delay(1000);
}

// Function to blink an LED
uint32_t toggle(int pin) {
  uint32_t startTime, endTime;
  startTime = micros();
  digitalWrite(pin, !digitalRead(pin));
  endTime = micros();
  return endTime - startTime;
}