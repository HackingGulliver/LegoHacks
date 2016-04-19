/*
 * Pulse.cpp
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#include "Pulse.h"

Pulse::Pulse() {
	// TODO Auto-generated constructor stub

}

Pulse::~Pulse() {
	// TODO Auto-generated destructor stub
}

void Pulse::tick(unsigned long milliSeconds) {

	setDuty(7, milliSeconds & 0xff);
	allDutiesSet();
}

