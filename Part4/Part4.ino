#include "driver/ledc.h"

#define FREQ 5000
#define GPIO_PIN_IN 5
#define GPIO_PIN_OUT 6
#define RESOLUTION 12
#define LEDC_CHANNEL 0

const uint32_t interval = 500;
const uint32_t intervalTwo = 1000;
uint32_t previousMillis = 0;

enum LedState { OFF, ON };
bool ledState = OFF;

typedef struct {
  uint8_t pin_out;
  uint32_t freq;
  uint8_t resolution;
  uint8_t channel;
} PwmConfig;

void setup() {
  PwmConfig pwmSettings = {GPIO_PIN_OUT, FREQ, RESOLUTION, LEDC_CHANNEL};
  ledcAttachChannel(pwmSettings.pin_out, pwmSettings.freq, pwmSettings.resolution, pwmSettings.channel);
  Serial.begin(9600);
}

void loop() {
  uint32_t intensity = analogRead(GPIO_PIN_IN);
  uint32_t duty = map(intensity, 0, 4095, 0, (1 << RESOLUTION) - 1);
  Serial.println(intensity);
  if (intensity < 1000) {
    toggle(GPIO_PIN_OUT, interval, &previousMillis, &ledState, RESOLUTION);
  }
  else if (intensity < 3000 && intensity >= 1000) {
    toggle(GPIO_PIN_OUT, intervalTwo, &previousMillis, &ledState, RESOLUTION);
  }
  else {
    ledcWrite(GPIO_PIN_OUT, duty);
  }
}

// This function updates the LED at pin to its alternate state at a certain interval
void toggle(int pin, unsigned long interval, unsigned long *previousMillis, bool *state, uint8_t resolution) {
  unsigned long currentMillis = millis();
  if (currentMillis - *previousMillis >= interval) {
    *previousMillis = currentMillis;
    *state = (*state == OFF) ? ON : OFF;
    ledcWrite(pin, *state ? (1 << resolution) - 1 : 0);
  }
}