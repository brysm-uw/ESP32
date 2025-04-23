#include <assert.h>
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include <stdint.h>

#define GPIO_PIN 5

// Timing variables
uint32_t accumulatedTime = 0;

void setup() {
  // Configure a MUX to assign the function to the GPIO pin
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);

    // Enable output driver for the GPIO pin
    *((volatile uint32_t *)GPIO_ENABLE_REG) |= (1 << GPIO_PIN);

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

uint32_t toggle(int pin) {
  uint32_t start,end;
  uint32_t gpio_out = *((volatile uint32_t *)GPIO_OUT_REG);
  start = micros();
  *((volatile uint32_t *)GPIO_OUT_REG) = gpio_out ^ (1 << pin);
  end = micros();
  return end - start;
}