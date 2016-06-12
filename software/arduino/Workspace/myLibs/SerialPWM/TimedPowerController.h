/*
 * TimedPowerController.h
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#ifndef TIMEDPOWERCONTROLLER_H_
#define TIMEDPOWERCONTROLLER_H_

#include "PowerController.h"

namespace TimedPowerControllerConstants {
	const uint16_t UPDATE_INTERVAL = 10; // Time in milliseconds between two ticks
}

class TimedPowerController: public PowerController {

public:
	virtual void tick(unsigned long milliSeconds) = 0;

protected:
	TimedPowerController();
};

#endif /* TIMEDPOWERCONTROLLER_H_ */
