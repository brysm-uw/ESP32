#include <assert.h>
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include <stdint.h>

#define GPIO_PIN 5

void setup() {
  // Configure a MUX to assign the function to the GPIO pin
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);
    
    // Enable output driver for the GPIO pin
    *((volatile uint32_t *)GPIO_ENABLE_REG) |= (1 << GPIO_PIN);
}

void loop() {
  delay(1000);
  uint32_t gpio_out = *((volatile uint32_t *)GPIO_OUT_REG);
  *((volatile uint32_t *)GPIO_OUT_REG) = gpio_out ^ (1 << GPIO_PIN);
  delay(1000);
}