#include "LedController.h"

LedController* LedController::inst_ = NULL;

LedController* LedController::getInstance() {
   if (inst_ == NULL) {
      inst_ = new LedController();
   }
   return(inst_);
}



LedController::LedController(){
	dawStatus = DawStatus::getInstance();
}

void LedController::setup(){
	//intro();
}

void LedController::intro(){
	// static JLed leds[] = {
 //            JLed(ledPins[0]).FadeOn(250),
 //            JLed(ledPins[1]).FadeOn(250),
 //            JLed(ledPins[2]).On().DelayAfter(250),
 //            JLed(ledPins[3]).On().DelayAfter(250),
 //            JLed(ledPins[4]).On().DelayAfter(250),
 //            JLed(ledPins[5]).On().DelayAfter(250),
 //            JLed(ledPins[0]).FadeOff(250),
 //            JLed(ledPins[1]).FadeOff(250),
 //            JLed(ledPins[2]).Off().DelayAfter(250),
 //            JLed(ledPins[3]).Off().DelayAfter(250),
 //            JLed(ledPins[4]).Off().DelayAfter(250),
 //            JLed(ledPins[5]).Off()
 //        };
	// static auto s = JLedSequence(JLedSequence::eMode::SEQUENCE, leds).Repeat(1);
	// seq = &s;
}



void LedController::update(){
	// bool running = seq->Update();
	// if (running) return;

	for (int i = 0; i < 6; i++)
		leds[i].Update();
}

void LedController::setLed(byte led, byte state){
	if ((led < 0) || (led > 5)) return;

	if (state == 0)
		leds[led].Off();
	else if (state == 1)
		leds[led].On();
	else if (state == 2)
		leds[led].Blink(500, 500).Forever();
}

void LedController::updateTracks(){
	for (int i = 0; i < 6; i++)
		if (dawStatus->isTrackMuted(i))
			setLed(i, 2);
		else if (dawStatus->getSelectedTrack() == i)
			setLed(i, 1);
		else
			setLed(i, 0);
}
