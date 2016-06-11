/*
 * PowerController.cpp
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#include "PowerController.h"

void PowerController::setDuty(uint8_t channel, uint8_t duty) {
	if (chainedController) {
		chainedController->setDuty(channel, duty);
	}
}

void PowerController::allDutiesSet() {
	if (chainedController) {
		chainedController->allDutiesSet();
	}
}
