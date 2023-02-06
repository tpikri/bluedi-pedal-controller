#include "BtnController.h"

BtnController* BtnController::inst_ = NULL;

BtnController* BtnController::getInstance() {
   if (inst_ == NULL) {
      inst_ = new BtnController();
   }
   return(inst_);
}



BtnController::BtnController(){
}

void BtnController::setup(){
	for (int i = 0; i < 9; i++){
		pinMode(buttonPins[i], INPUT_PULLUP);
		
		buttons[i] = ButtonEvents();
		buttons[i].attach(buttonPins[i]);
		buttons[i].activeLow();

		buttons[i].debounceTime(15);
		buttons[i].doubleTapTime(50);
		buttons[i].holdTime(2000);
	}
}



byte* BtnController::update(){
	static byte btnStatus[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	int c = 0;
	int e;

	for (int i = 0; i < 9; i++){
		buttons[i].update();
		e = buttons[i].event();
		btnStatus[i] = e;
		c += e;
	}

	if (c>0) return btnStatus;
	else return NULL;
}
