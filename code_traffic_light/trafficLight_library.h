#pragma once
enum color
{
	red,
	green,
	yellow
};
class trafficLight
{
public:
	uint8_t time_left_sec; // time left of state.
	uint16_t time_left_ms;
	//uint8_t time_in; // time transmit from main code.
	color colorstate;

	void begin(uint8_t, uint8_t, uint8_t);
	void update(uint16_t, bool);
	uint8_t time_left();

private:

	uint8_t redLedPin;
	uint8_t greenLedPin;
	uint8_t	yellowLedPin;
};
void trafficLight::update(uint16_t time_in, bool state) {
	if (state) {
		colorstate = red;
		time_left_ms = 3000 - time_in;
		digitalWrite(redLedPin, HIGH);
		digitalWrite(yellowLedPin, LOW);
		digitalWrite(greenLedPin, LOW);
	}

	else if (time_in>=0 && time_in<2500) {
		colorstate = green;
		time_left_ms = 2500 - time_in;
		digitalWrite(redLedPin, LOW);
		digitalWrite(yellowLedPin, LOW);
		digitalWrite(greenLedPin, HIGH);
	}

	else if (time_in >= 2500 && time_in < 3000){
		colorstate = yellow;
		time_left_ms = 3000 - time_in;
		digitalWrite(redLedPin, LOW);
		digitalWrite(yellowLedPin, HIGH);
		digitalWrite(greenLedPin, LOW);
	}

	switch (colorstate) {
	case red:
		
		break;
	case green:
		
		break;
	case yellow:
		
		break;
	default:
		break;
	}
}
void trafficLight::begin(uint8_t ledRed, uint8_t ledGreen, uint8_t ledYellow) {
	redLedPin = ledRed;
	pinMode(redLedPin, OUTPUT);

	yellowLedPin = ledYellow;
	pinMode(yellowLedPin, OUTPUT);

	greenLedPin = ledGreen;
	pinMode(greenLedPin, OUTPUT);
}
uint8_t trafficLight::time_left() {
	return time_left_ms / 100;
}

