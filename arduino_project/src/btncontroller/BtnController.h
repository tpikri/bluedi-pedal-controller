#ifndef BTNCONTROLLER_H
#define BTNCONTROLLER_H

#include <Arduino.h>
#include <ButtonEvents.h>

class BtnController
{
    public:
    	static BtnController* getInstance();
        void   setup();
        byte*  update();
    
    private:
		static BtnController* inst_;
        BtnController();
		BtnController(const BtnController&);
		BtnController& operator=(const BtnController&);

        ButtonEvents buttons[9];
        const byte buttonPins[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
};

#endif