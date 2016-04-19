/*
 * PowerController.h
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#ifndef POWERCONTROLLER_H_
#define POWERCONTROLLER_H_

#include "Arduino.h"

class PowerController {

public:

	virtual void setDuty(uint8_t channel, uint8_t duty) = 0;
	virtual void allDutiesSet() = 0;

	void chain(PowerController *chainedController) {
		this->chainedController = chainedController;
	}

protected:
	PowerController *chainedController;

};

#endif /* POWERCONTROLLER_H_ */
