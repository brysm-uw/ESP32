#include "driver/ledc.h"
#include "soc/timer_group_reg.h"

#define FREQ 5000
#define GPIO_PIN_IN 5
#define GPIO_PIN_OUT 6
#define RESOLUTION 12
#define LEDC_CHANNEL 0
#define TIMER_DIVIDER_VALUE 80
#define TIMER_INCREMENT_MODE 1
#define TIMER_ENABLE 1
#define GROUP 0

const uint32_t interval = 500000;
const uint32_t intervalTwo = 1000000;
uint32_t last_toggle_time = 0;

enum LedState { OFF, ON };
bool ledState = OFF;

typedef struct {
  uint8_t pin_out;
  uint32_t freq;
  uint8_t resolution;
  uint8_t channel;
} PwmConfig;

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
  PwmConfig pwmSettings = {GPIO_PIN_OUT, FREQ, RESOLUTION, LEDC_CHANNEL};
  ledcAttachChannel(pwmSettings.pin_out, pwmSettings.freq, pwmSettings.resolution, pwmSettings.channel);
  Serial.begin(9600);
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
  update(GROUP, 1);
}

void loop() {
  uint32_t intensity = analogRead(GPIO_PIN_IN);
  uint32_t duty = map(intensity, 0, 4095, 0, (1 << RESOLUTION) - 1);
  Serial.println(intensity);
  if (intensity < 1000) {
    toggle(GPIO_PIN_OUT, interval, &last_toggle_time, &ledState, RESOLUTION);
  }
  else if (intensity < 3000 && intensity >= 1000) {
    toggle(GPIO_PIN_OUT, intervalTwo, &last_toggle_time, &ledState, RESOLUTION);
  }
  else {
    ledcWrite(GPIO_PIN_OUT, duty);
  }
}

// This function updates the LED at pin to its alternate state at a certain interval
void toggle(int pin, unsigned long interval, unsigned long *last_toggle_time, bool *state, uint8_t resolution) {
  update(GROUP, 1);
  uint32_t current_time = *((volatile uint32_t *)TIMG_T0LO_REG(0));
  if (current_time - *last_toggle_time >= interval) {
    *last_toggle_time = current_time;
    *state = (*state == OFF) ? ON : OFF;
    ledcWrite(pin, *state ? (1 << resolution) - 1 : 0);
  }
}