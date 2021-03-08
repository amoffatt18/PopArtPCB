#include <Adafruit_NeoPixel.h>
#include "frames.h"
#include <Bounce2.h>

Bounce button1 = Bounce();

Adafruit_NeoPixel strip(25, 0);

int colors[6][3] {
  {255, 0, 255},
  {0, 0, 255},
  {255, 0 , 0},
  {0, 255, 0},
  {255, 50, 0},
  {255, 255, 0}
};

int whichFrame = 0;
int switchVal = 0;

int startTime = 0;
int tVal = 500;

int mapTime = 0;
int mapInterval = 300;

void setup() {

  strip.begin();
  strip.show();
  button1.attach(1, INPUT);
  button1.interval(5);
}

void loop() {

  button1.update();

  if (button1.rose()) {
    switchVal = (switchVal + 1) % 4;
  }

  switch (switchVal) {

    case 0: off();
      break;

    case 1: on();
      break;

    case 2: simpAnimation();
      break;

    case 3: mapped();
      break;
  }
}

void off() {

  strip.clear();
  strip.show();
}

void on() {

  for (int i = 0; i < strip.numPixels(); i++) {
    int orange = 255;
    strip.setPixelColor(i, orange, 40, 0);
  }
  strip.show();
}
void simpAnimation() {

  uint16_t i, j;
  for (j = 255; j < 255; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, j, j, 0);
    }
    strip.show();
  }
  if (millis() - startTime > tVal) {
    for (j = 255; j > 45; j--) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, j, j, 0);
      }
      strip.show();
    }
  }
}


void mapped() {
  if (millis() - mapTime > mapInterval) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int whichColor = animation [whichFrame][i];
      int pixAddress = pixelMap[i];

      int red = colors[whichColor][0];
      int green = colors[whichColor][1];
      int blue = colors[whichColor][2];

      strip.setPixelColor(pixAddress, red, green, blue);

    }
    strip.show();
    whichFrame = (whichFrame + 1) % 2;
    mapTime = millis();
  }

}
