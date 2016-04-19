/*
 * Pulse.h
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#ifndef PULSE_H_
#define PULSE_H_

#include "TimedPowerController.h"

class Pulse: public TimedPowerController {

public:
	Pulse();
	virtual ~Pulse();

	virtual void tick(unsigned long milliSeconds);
};

#endif /* PULSE_H_ */
