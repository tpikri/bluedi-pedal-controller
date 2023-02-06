#ifndef DAWOUTPUT_H
#define DAWOUTPUT_H

#include <Arduino.h>
#include "DawStatus.h"

class DawOutput
{
    public:
    	static DawOutput* getInstance();
        void   buttonPressed(int button, int event);
        void   expressionSwitchChange(int value);
    
    private:
		static DawOutput* inst_;
        DawOutput();
		DawOutput(const DawOutput&);
		DawOutput& operator=(const DawOutput&);
        DawStatus* dawStatus;

        void    selectTrack(int trackNumber);
        void    muteTrack(int trackNumber);
        void    playStop();
        void    toStart();
        void    record();
        void    setLocatorStart();
        void    setLocatorEnd();
        void    setCycle(bool onOff);
};

#endif