#include "DawInput.h"

DawInput* DawInput::inst_ = NULL;

DawInput* DawInput::getInstance() {
   if (inst_ == NULL) {
      inst_ = new DawInput();
   }
   return(inst_);
}



DawInput::DawInput(){
	dawStatus = DawStatus::getInstance();
	lcdCon = LcdController::getInstance();
	ledCon = LedController::getInstance();
	huiZone = -1;
}


// This is static in order to be passed as a callback
void DawInput::midiInputCC(byte channel, byte control, byte value){
	DawInput* di = DawInput::getInstance();

	// CC to set zone
	if (control == 0x0c) {
	    di->huiZone = (int)value;
	    return;
	}

	// CC to set port + onoff
	if ((control == 0x2c) && (di->huiZone >= 0)) {
		di->huiPort  = (value & 0x0f);
		di->huiOnOff = ((value & 0xf0) == 0x40);

		di->evaluateCommand();
		di->huiZone = -1;
	}
}

// This is static in order to be passed as a callback
void DawInput::midiInputSysex(byte *data, unsigned int length){
	DawInput* di = DawInput::getInstance();

	//LCD header for a trackname with 4 chars
	byte lcdTrackHeader[7]={0xf0,0x00,0x00,0x66,0x05,0x00,0x10};

	//LCD track name: has 13 bytes, starts with above header, ends with 0xf7
	bool isLcdmsg = ((length == 13) && (memcmp(data, lcdTrackHeader, 7) == 0) && (data[12] == 0xf7));
	if (!isLcdmsg) return;

	int trackNum = data[7];
	if (trackNum >= 6) return;

	char trackName[] = {char(data[8]),char(data[9]),char(data[10]),char(data[11]), '\0'};
	di->dawStatus->setTrackName(trackNum, trackName);
	Serial.println(trackNum);
	di->lcdCon->updateTrackName(trackNum);
}




void DawInput::evaluateCommand(){
	if (huiZone < 8){
		//Command is about a track
		String trackCommands[8] = {"fader", "select", "mute", "solo", "auto", "monitor", "insert", "rec"};

		int trackNum = huiZone;
		String command  = trackCommands[huiPort];

		if (huiOnOff && (command == "rec")){
			//When rec-on lights on a track means track is selected
			dawStatus->setSelectedTrack(trackNum);
			lcdCon->updateSelectedTrack();
			ledCon->updateTracks();
		}

		// mporei
		if ((!huiOnOff) && (command == "rec")){
			dawStatus->setSelectedTrack(-1);
			lcdCon->updateSelectedTrack();
			ledCon->updateTracks();
		}

		if (command == "mute"){
			dawStatus->setTrackMuted(trackNum, huiOnOff);
			ledCon->updateTracks();
		}
	}


	if (huiZone == 14){
		//Command is about the playing status
		if (huiPort == 4) 
			dawStatus->setIsPlaying(huiOnOff);
		else if (huiPort == 5) 
			dawStatus->setIsRecording(huiOnOff);

		lcdCon->updatePlayingStatus();
    }
}