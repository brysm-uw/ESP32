#include <assert.h>
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/timer_group_reg.h"
#include <stdint.h>

#define GPIO_PIN 5
#define TIMER_DIVIDER_VALUE 80
#define TIMER_INCREMENT_MODE 1
#define TIMER_ENABLE 1
#define LED_TOGGLE_INTERVAL 1000000 // 1 second
#define GROUP 0

// This is just for personal organization and readability reasons
typedef struct {
    uint32_t prescaler_value;
    uint32_t increment_mode;
    uint32_t timer_enable;
} TimerConfig;

void update(int group, int value) {
    assert(group == 1 || group == 0);
    if (group == 0) {
        *((volatile uint32_t*)TIMG_T0UPDATE_REG(0)) = value;
    }
    else {
        *((volatile uint32_t*)TIMG_T1UPDATE_REG(0)) = value;
    }
}

void setup() {
  // Configure a MUX to assign the function to the GPIO pin
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);

    // Enable output driver for the GPIO pin
    *((volatile uint32_t *)GPIO_ENABLE_REG) |= (1 << GPIO_PIN);
    
    // Define a timer config, which sets all the values we need
    TimerConfig timer = {
        .prescaler_value = (TIMER_DIVIDER_VALUE << 13),
        .increment_mode = (TIMER_INCREMENT_MODE << 30),
        .timer_enable = ((volatile uint32_t)TIMER_ENABLE << 31)
    };
    
    // Represent our timer config with an unsigned 32 bit integer
    uint32_t timer_config = timer.prescaler_value;
    timer_config |= timer.increment_mode;
    timer_config |= timer.timer_enable;

    *((volatile uint32_t *)TIMG_T0CONFIG_REG(0)) = timer_config;
    
     // synchronize the timer hardware register
    update(GROUP, 1);
}

void loop() {
  assert(GROUP == 0 || GROUP == 1);
  
  //get current and previous times (direct register access)
  static uint32_t last_toggle_time = 0;
  uint32_t current_time = (GROUP == 0) ? *((volatile uint32_t *)TIMG_T0LO_REG(0)) : *((volatile uint32_t *)TIMG_T1LO_REG(0));
        
  // Flip the current state of the pin if time interval is up
  if ((current_time - last_toggle_time) >= LED_TOGGLE_INTERVAL) {
    uint32_t gpio_out = *((volatile uint32_t *)GPIO_OUT_REG);
    *((volatile uint32_t *)GPIO_OUT_REG) = gpio_out ^ (1 << GPIO_PIN);
    last_toggle_time = current_time;
  }
  // synchronize the timer hardware register
  update(GROUP, 1);
}