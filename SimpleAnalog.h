// SimpleAnalog class
// this class allows for creating and reading an analog sensor 

#ifndef SIMPLEANALOG_H
#define SIMPLEANALOG_H

class SimpleAnalog 
{
  public:
    int _sensorPin;     // select the input pin
    int _sensorValue;   // variable to store the value coming from the sensor
    int _lastReading;   // store the last reading from the sensor

    // constructor
    SimpleAnalog(int sensorPin)
    : _sensorPin(sensorPin), _sensorValue(0), _lastReading(0) {}

    int analogReading()
    {
      updateReading();

      return _sensorValue;
    }

    void updateReading()
    {
      _lastReading = _sensorValue;
      _sensorValue = analogRead(_sensorPin);
      // Serial.println(_sensorValue);
    }

    int rollingAverage() {
      int newReading = analogReading();

      const int NUM_SAMPLES = 10;

      static int samples[NUM_SAMPLES];
      static int index  = 0;
      static int total  = 0;
      static bool filled = false;

      // Subtract the oldest reading from the running total
      total -= samples[index];

      // Store the new reading and add it to the total
      samples[index] = newReading;
      total += newReading;

      // Advance the index, wrapping back to 0 after the last slot
      index = (index + 1) % NUM_SAMPLES;

      // If the buffer is not yet full, average only the filled slots
      if (!filled && index == 0) filled = true;

      int count = filled ? NUM_SAMPLES : index;
      if (count == 0) return newReading;

      return total / count;
    }
};

#endif