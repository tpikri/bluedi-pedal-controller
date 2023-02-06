#include "DawStatus.h"

DawStatus* DawStatus::inst_ = NULL;

DawStatus* DawStatus::getInstance() {
   if (inst_ == NULL) {
      inst_ = new DawStatus();
   }
   return(inst_);
}



DawStatus::DawStatus(){
	isPlaying = false;
	isRecording = false;
	for (int i = 1; i <= 6; i++){
		trackNames[i-1] = "TRK"+i;
		trackMute[i-1] = false;
	}
	selectedTrack = -1;
}



void DawStatus::setTrackName(int track, String name){
	if ((track < 0) || (track > 5)) return;
	trackNames[track] = name;
}

String DawStatus::getTrackName(int track){
	return trackNames[track];
}

void DawStatus::setSelectedTrack(int track){
	selectedTrack = track;
}

void DawStatus::setTrackMuted(int track, bool muted){
	if ((track < 0) || (track > 5)) return;
	trackMute[track] = muted;
}

bool DawStatus::isTrackMuted(int track){
	if ((track < 0) || (track > 5)) return false;
	return trackMute[track];
}

int DawStatus::getSelectedTrack(){
	return selectedTrack;
}

String DawStatus::getSelectedTrackName(){
	if ((selectedTrack < 0) || (selectedTrack > 5)) return "";
	else return trackNames[selectedTrack];
}

void DawStatus::setIsPlaying(bool onOff){
	isPlaying = onOff;
}

void DawStatus::setIsRecording(bool onOff){
	isRecording = onOff;
}

String DawStatus::getPlayingStatus(){
	if (isRecording) return "RECORDING";
	else return isPlaying ? "PLAYING" : "STOPPED";
}