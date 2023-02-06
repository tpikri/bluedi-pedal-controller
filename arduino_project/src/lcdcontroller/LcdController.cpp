#include "LcdController.h"

LcdController* LcdController::inst_ = NULL;

LcdController* LcdController::getInstance() {
   if (inst_ == NULL) {
      inst_ = new LcdController();
   }
   return(inst_);
}

const uint8_t LcdController::STOPPED_CHAR[4][8]  = {
	{0x00,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E},
	{0x00,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E},
	{0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x00},
	{0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x0E,   0x00}
};

const uint8_t LcdController::PLAYING_CHAR[4][8]  = {
	{0x08,   0x0C,   0x0E,   0x0F,   0x0F,   0x0F,   0x0F,   0x0F},
	{0x00,   0x00,   0x00,   0x00,   0x10,   0x18,   0x1C,   0x1E},
	{0x0F,   0x0F,   0x0F,   0x0F,   0x0F,   0x0E,   0x0C,   0x08},
	{0x1E,   0x1C,   0x18,   0x10,   0x00,   0x00,   0x00,   0x00}
};

const uint8_t LcdController::RECORDING_CHAR[4][8]  = {
	{0x00,   0x00,   0x00,   0x01,   0x07,   0x0F,   0x1F,   0x1F},
	{0x00,   0x00,   0x00,   0x10,   0x1C,   0x1E,   0x1F,   0x1F},
	{0x1F,   0x1F,   0x0F,   0x07,   0x01,   0x00,   0x00,   0x00},
	{0x1F,   0x1F,   0x1E,   0x1C,   0x10,   0x00,   0x00,   0x00}
};


LcdController::LcdController(){
	dawStatus = DawStatus::getInstance();
	lcd.begin(LCD_COLS, LCD_ROWS);

	for (int i = 0; i < 4; i++)
		lcd.createChar(i, STOPPED_CHAR[i]);

	initScreen();
}

void LcdController::initScreen(){
	lcd.clear();
	lcd.noCursor();

	// lcd.setCursor(5, 1);
	// lcd.print("Tasos");
	// delay(250);
	// lcd.setCursor(11, 1);
	// lcd.print("MIDI");
	// delay(250);
	// 
	
	char name[6] = {'B', 'l','u', 'e', 'D', 'i'};
	for (int i = 0; i < 6; i++){
		lcd.setCursor(7+i, 1);
		lcd.print(name[i]);
		delay(100);
	}
	delay(200);

	lcd.setCursor(2, 2);
	lcd.print("Pedal");
	delay(250);
	lcd.setCursor(8, 2);
	lcd.print("Controller");
	delay(3000);
	lcd.clear();

	//lcd.setBacklight(255);
	//lcd.setContrast(255);
	//
	for (int r = 0; r < 2; r++)
		for (int c = 18; c < 20; c++){
			lcd.setCursor(c, r);
			lcd.write((2*r) + (c-18));
		}
}


void LcdController::update(){
	lcd.clear();
	lcd.noCursor();

	for (int i = 0; i < TRACK_COUNT; i++)
		updateTrackName(i);

	updateSelectedTrack();

	updatePlayingStatus();
}


void LcdController::updatePlayingStatus(){
	uint8_t statusChar[4][8];

	String st = dawStatus->getPlayingStatus();
	if (st == "PLAYING")
		memcpy(statusChar, PLAYING_CHAR, 4*8*sizeof(uint8_t));
	else if (st == "STOPPED")
		memcpy(statusChar, STOPPED_CHAR, 4*8*sizeof(uint8_t));
	else if (st == "RECORDING")
		memcpy(statusChar, RECORDING_CHAR, 4*8*sizeof(uint8_t));
	else return;

	for (int i = 0; i < 4; i++)
		lcd.createChar(i, statusChar[i]);

	//updateSelectedTrack();
}

void LcdController::updateTrackName(int trackNum){
	String trackName = dawStatus->getTrackName(trackNum);
	ScreenPos position = calculateTrackNamePosition(trackNum);
	lcd.setCursor(position.col, position.row);
	lcd.print(trackName);
	updateSelectedTrack();
}

void LcdController::updateSelectedTrack(){
	int trackNum = dawStatus->getSelectedTrack();
	if ((trackNum < 0) || (trackNum >= TRACK_COUNT)){
		lcd.noCursor();
		return;
	}

	ScreenPos position = calculateTrackNamePosition(trackNum);
	lcd.setCursor(position.col, position.row);
	lcd.cursor();
}

ScreenPos LcdController::calculateTrackNamePosition(int trackNum){
	ScreenPos res;
	res.col = 8 * (trackNum % 3);
	res.row = (trackNum > 2) ? 3 : 2;
	return res;
}
