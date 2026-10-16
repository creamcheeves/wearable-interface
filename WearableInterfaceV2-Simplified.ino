#include <Adafruit_CircuitPlayground.h>
#include "SimpleAnalog.h"
#include "SimpleTimer.h"

SimpleAnalog CapA1(A1);
SimpleAnalog CapA6(A6);

SimpleTimer Timer_1s(1000, 0);

float detection = 300;
uint8_t color = 100;

// for the tune of POWER POSING
// taking advantage of the fact that the notes can be represented as numbers in an array to play numerous of them in sequence
// uses '0' as a key to restart after a brief pause
// happy birthday in frequencies used from https://www.jk-quantized.com/blog/2013/11/22/tetris-theme-song-using-processing
float rawSequence[] = { 293.6648, 293.6648, 329.62756, 329.62756, 391.995, 369.99445 , 293.6648, 293.6648,
                        329.62756, 293.6648, 439.997, 391.995, 293.6648, 293.6648, 587.3294, 493.8834,
                        391.995, 369.9945, 329.62756, 523.2516, 523.2516, 493.8834, 391.995,
                        439.997, 391.995 , 0 };
int position = 0;

void setup() {
  Serial.begin(9600);

  CircuitPlayground.begin();
}

void loop() {
  CircuitPlayground.speaker.enable(false);

  // converting input to output logic
  if (CapA1.analogReading() < detection && CapA1.analogReading() < detection)
  {
    // sequence for power pose
    UpdateNeopixels(0, 10, color);
    color += 50;

    CircuitPlayground.speaker.enable(true);
    CircuitPlayground.playTone(rawSequence[position], 300);
    position++;
    if (rawSequence[position] == 0) position = 0;
  } 
  else if (CapA1.analogReading() < detection)
  {
    // sequence for A1 side
    color = 100;
    UpdateNeopixels(5, 10, color);
    DisableNeopixels(0, 5);
  }
  else if (CapA6.analogReading() < detection)
  {
    // sequence for A6 side
    color = 100;
    UpdateNeopixels(0, 5, color);
    DisableNeopixels(5, 10);
  }
  else 
  {
    // turn off all pixels
    DisableNeopixels(0, 10);
    color = 100;
  }

  // serial monitor for testing/tuning
  if (Timer_1s.isReady())
  {
    Serial.print("A1: "); Serial.println(CapA1.analogReading());
    Serial.print("A6: "); Serial.println(CapA6.analogReading());
  }
}

void UpdateNeopixels(int first, int last, uint8_t c)
{
  for (int i = first; i < last; i++)
  {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(c));
  }
}

void DisableNeopixels(int first, int last)
{
  for (int i = first; i < last; i++)
  {
    CircuitPlayground.setPixelColor(i, 0);
  }
}
