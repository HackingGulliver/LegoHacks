/*
 * RGBLed.cpp
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#include "RGBLed.h"

RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
	this->redPin   = redPin;
	this->greenPin = greenPin;
	this->bluePin  = bluePin;
}

RGBLed::~RGBLed() {
	// TODO Auto-generated destructor stub
}

void RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue) {
	setDuty(redPin, red);
	setDuty(greenPin, green);
	setDuty(bluePin, blue);
	allDutiesSet();
}

