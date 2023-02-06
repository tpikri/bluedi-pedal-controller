#ifndef DAWINPUT_H
#define DAWINPUT_H

#include <Arduino.h>
#include "DawStatus.h"
#include "../lcdcontroller/LcdController.h"
#include "../ledcontroller/LedController.h"

class DawInput
{
    public:
    	static DawInput* getInstance();

        // These are static in order to be passed as a callback
        static void midiInputCC(byte channel, byte control, byte value);
        static void midiInputSysex(byte *data, unsigned int length);

    
    private:
		static DawInput* inst_;
        DawInput();
		DawInput(const DawInput&);
		DawInput& operator=(const DawInput&);

        void evaluateCommand();

        int huiZone;
        int huiPort;
        bool huiOnOff;
        
        LcdController* lcdCon;
        LedController* ledCon;
        DawStatus* dawStatus;
};

#endif