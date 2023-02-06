#include "DawOutput.h"
#include "DawStatus.h"
#include <Arduino.h>

DawOutput* DawOutput::inst_ = NULL;

DawOutput* DawOutput::getInstance() {
   if (inst_ == NULL) {
      inst_ = new DawOutput();
   }
   return(inst_);
}



DawOutput::DawOutput(){
	dawStatus = DawStatus::getInstance();
}

void DawOutput::buttonPressed(int button, int event){
	switch (button) {
		case 0 ... 5:
			if (event == 1)
				selectTrack(button+1);
			else if (event == 3)
				muteTrack(button+1);
			break;
		case 6:
			if (event == 1) playStop();
			else if (event == 3) toStart();
			break;
		case 7:
			record();
			break;			
		// case 9:
		// 	record();
		// 	break;
		// case 17 ... 22://A,B,C,D,E,F
		// 	muteTrack(button-16);
		// 	break;
		// case 23://G
		// 	setLocatorStart();
		// 	break;
		// case 24://H
		// 	setLocatorEnd();
		// 	break;
		// case 25://I
		// 	setCycle(true);
		// 	break;
		// case 26://J
		// 	setCycle(false);
		// 	break;
	}
}

void DawOutput::expressionSwitchChange(int value){
	//value is 0-1023, make it 0-127
	value = value / 8;
	usbMIDI.sendControlChange(11, value, 1);
}

void DawOutput::selectTrack(int trackNumber){
	if ((trackNumber < 1) || (trackNumber > 6)) return;

	//Select that track
	usbMIDI.sendControlChange(16, 127, trackNumber);
	usbMIDI.send_now();

	//Turn off monitor for other tracks (1-16)
	for (int i = 1; i <= 16; i++)
    	if (i != trackNumber)
      		usbMIDI.sendControlChange(17, 0, i);

    //Turn on monitor for that track
    usbMIDI.sendControlChange(17, 127, trackNumber);
    usbMIDI.send_now();
}

void DawOutput::muteTrack(int trackNumber){
	if ((trackNumber < 1) || (trackNumber > 6)) return;

	//Select that track
	usbMIDI.sendControlChange(64, 127, trackNumber);
    usbMIDI.send_now();
}

void DawOutput::playStop() {
  	usbMIDI.sendControlChange(18, 127, 1);
	usbMIDI.send_now();
}

void DawOutput::toStart() {
	usbMIDI.sendControlChange(19, 127, 1);
	usbMIDI.send_now();
}

void DawOutput::record() {
	//Looper stuff
	String prevStatus = dawStatus->getPlayingStatus();
	if (dawStatus->getSelectedTrack() == 0){
		if (prevStatus != "RECORDING"){
			setCycle(false);
			setLocatorStart();
		}
	}
	//------------

	usbMIDI.sendControlChange(20, 127, 1);
	usbMIDI.send_now();


	//Looper stuff
	if (dawStatus->getSelectedTrack() == 0){
		if (prevStatus == "RECORDING"){
			setLocatorEnd();
			toStart();
			delay(100);
			setCycle(true);
		}
	}

	if (prevStatus == "RECORDING")
		selectTrack(dawStatus->getSelectedTrack()+2);
	//------------
}

void DawOutput::setLocatorStart() {
	usbMIDI.sendControlChange(21, 127, 1);
	usbMIDI.send_now();
}

void DawOutput::setLocatorEnd() {
	usbMIDI.sendControlChange(22, 127, 1);
	usbMIDI.send_now();
}

void DawOutput::setCycle(bool onOff){
	int val = onOff ? 127 : 0;
	usbMIDI.sendControlChange(23, val, 1);
	usbMIDI.send_now();
}