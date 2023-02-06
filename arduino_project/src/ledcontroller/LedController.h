#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>
#include <jled.h>
#include "../dawcontroller/DawStatus.h"

class LedController
{
    public:
    	static LedController* getInstance();
        void   setup();
        void  update();
        void  setLed(byte led, byte state);
        void  updateTracks();
    
    private:
		static LedController* inst_;
        LedController();
		LedController(const LedController&);
		LedController& operator=(const LedController&);

        void intro();

        DawStatus* dawStatus;

        const byte ledPins[6] = {9, 10, 11, 14, 15, 16};
        JLed leds[6] = {
            JLed(ledPins[0]),
            JLed(ledPins[1]),
            JLed(ledPins[2]),
            JLed(ledPins[3]),
            JLed(ledPins[4]),
            JLed(ledPins[5]),
        };

        jled::TJLedSequence<jled::JLed>* seq;
};

#endif