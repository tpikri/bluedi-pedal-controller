#include "src/dawcontroller/DawStatus.h"
#include "src/dawcontroller/DawInput.h"
#include "src/dawcontroller/DawOutput.h"
#include "src/lcdcontroller/LcdController.h"
#include "src/btncontroller/BtnController.h"
#include "src/ledcontroller/LedController.h"
#include <jled.h>

DawStatus* dawStatus = DawStatus::getInstance();
DawInput*  dawInput  = DawInput::getInstance();
DawOutput* dawOutput = DawOutput::getInstance();
LcdController* lcdController = LcdController::getInstance();
BtnController* btnController = BtnController::getInstance();
LedController* ledController = LedController::getInstance();

// Expression pedal stuff
// int oldval = 0;
// int val;
//Bounce button = Bounce(12, 95);

const byte ledPins[6] = {9, 10, 11, 14, 15, 16};
JLed leds[] = {
            JLed(ledPins[0]).FadeOn(100),
            JLed(ledPins[1]).FadeOn(100),
            JLed(ledPins[2]).On().DelayAfter(100),
            JLed(ledPins[3]).On().DelayAfter(100),
            JLed(ledPins[4]).On().DelayAfter(100),
            JLed(ledPins[5]).On().DelayAfter(100),
            JLed(ledPins[0]).FadeOff(100),
            JLed(ledPins[1]).FadeOff(100),
            JLed(ledPins[2]).Off().DelayAfter(100),
            JLed(ledPins[3]).Off().DelayAfter(100),
            JLed(ledPins[4]).Off().DelayAfter(100),
            JLed(ledPins[5]).Off()
        };
auto seq = JLedSequence(JLedSequence::eMode::SEQUENCE, leds).Repeat(1);

void setup() {
	usbMIDI.setHandleSystemExclusive(&DawInput::midiInputSysex);
	usbMIDI.setHandleControlChange(&DawInput::midiInputCC);
	btnController->setup();
	ledController->setup();
}

void loop() {
  seq.Update();
	ledController->update();
	byte *btnStatus = btnController->update();
  
	if (btnStatus != NULL)
		for (int i = 0; i < 9; i++)
      if (btnStatus[i] > 0)
        dawOutput->buttonPressed(i, btnStatus[i]);


 	// Expression pedal stuff
 	//val = analogRead(0);
	//if (abs(oldval - val) >= 8){
		//dawOutput->expressionSwitchChange(val);
	  //  oldval = val; 
	//}
	

	usbMIDI.read();
}
