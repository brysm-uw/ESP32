#include "driver/ledc.h"

#define FREQ 5000
#define GPIO_PIN_IN 5
#define GPIO_PIN_OUT 6
#define RESOLUTION 12
#define LEDC_CHANNEL 0

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
  if (ledcWrite(GPIO_PIN_OUT, duty)){
    Serial.println("success");
  }
  else {
    Serial.println("failed");
  }
  delay(100);
}