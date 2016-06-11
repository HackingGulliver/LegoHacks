/*
 * VirtualWireTimerShare.cpp
 *
 *  Created on: 10.06.2016
 *      Author: thomas
 */

#include "VirtualWireTimerShare.h"
#include "lib/VirtualWireTimerOne/VirtualWire.h"

void VirtualWireTimerShare::callback() {
	vwTimerCallback();
}
