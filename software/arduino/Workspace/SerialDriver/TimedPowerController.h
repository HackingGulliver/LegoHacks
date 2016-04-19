/*
 * TimedPowerController.h
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#ifndef TIMEDPOWERCONTROLLER_H_
#define TIMEDPOWERCONTROLLER_H_

#include "PowerController.h"

class TimedPowerController: public PowerController {

public:
	virtual void tick(unsigned long milliSeconds) = 0;

protected:
	TimedPowerController();
};

#endif /* TIMEDPOWERCONTROLLER_H_ */
