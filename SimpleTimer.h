// SimpleTimer class
// this makes timers using millis() way easier to make and manage

#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

class SimpleTimer 
{
  private:
    unsigned long _lastTime;
    unsigned long _interval;

  public:
    // constructor, defaults to 100ms interval
    // _interval: frequency of the timer
    // for _lastTime: 
    // 0 -> results in the first trigger happening after _interval seconds from boot
    // millis() - interval -> results in the first trigger happening immediately
    SimpleTimer(unsigned long interval = 100, unsigned long lastTime = 0)
      : _interval(interval), _lastTime(lastTime) {}

    void setInterval(unsigned long interval)    // if you wanted to change the timer rate midway
    {
      _interval = interval;
    }

    // determines if the timer has concluded
    // for use in if statements mostly, do things if true sorta deal
    bool isReady() 
    {
      if (millis() - _lastTime >= _interval) 
      {
        reset();
        return true;
      }

      return false;
    }

    void reset() 
    {
      _lastTime = millis();
    }
};

#endif