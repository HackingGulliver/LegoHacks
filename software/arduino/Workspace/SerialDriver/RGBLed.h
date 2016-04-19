/*
 * RGBLed.h
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#ifndef RGBLED_H_
#define RGBLED_H_

#include "PowerController.h"

class RGBLed: public PowerController {
public:
	RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
	virtual ~RGBLed();

	void setColor(uint8_t red, uint8_t green, uint8_t blue);

private:
	// Pins
	uint8_t redPin;
	uint8_t greenPin;
	uint8_t bluePin;

};

#endif /* RGBLED_H_ */
