/*
 * VirtualWireTimerShare.h
 *
 *  Created on: 10.06.2016
 *      Author: thomas
 */

#ifndef VIRTUALWIRETIMERSHARE_H_
#define VIRTUALWIRETIMERSHARE_H_

#include "lib/SerialPWM/TimerShare.h"

class VirtualWireTimerShare: public TimerShare {
	void callback();
};

#endif /* VIRTUALWIRETIMERSHARE_H_ */
