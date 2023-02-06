#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "../dawcontroller/DawStatus.h"

struct ScreenPos {
    int row;
    int col;
};

class LcdController
{
    public:
    	static LcdController* getInstance();
    	
        void update();
        void updateTrackName(int trackNum);
        void updatePlayingStatus();
        void updateSelectedTrack();

    private:
		static LcdController* inst_;
        LcdController();
		LcdController(const LcdController&);
		LcdController& operator=(const LcdController&);

        void initScreen();
        ScreenPos calculateTrackNamePosition(int trackNum);

        DawStatus* dawStatus;
        hd44780_I2Cexp lcd;

        static const uint8_t LCD_COLS = 20;
        static const uint8_t LCD_ROWS = 4;
        static const uint8_t TRACK_COUNT = 6;

        static const uint8_t PLAYING_CHAR[4][8];
        static const uint8_t STOPPED_CHAR[4][8];
        static const uint8_t RECORDING_CHAR[4][8];
};

#endif