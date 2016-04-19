/*
 * PWMController.cpp
 *
 *  Created on: 18.04.2016
 *      Author: thomas
 */

#include "PWMController.h"
#ifndef DEBUG
#include <TimerOne.h>
#endif

PWMController *PWMController::instance = NULL;

void PWMController::initStateCalculator(uint8_t channels) {
	pwmStateCalculator = new PWMStateCalculator(channels);
}

void PWMController::initTimer(uint8_t frequency) {
	Timer1.initialize();
	uint32_t timerPeriod = (1000000 / frequency) >> 8;
	Timer1.setPeriod(timerPeriod);
	Timer1.attachInterrupt(timerCallback);
}

PWMController::PWMController(uint8_t channels, uint8_t frequency) {

	instance = this;

	initStateCalculator(channels);
	initTimer(frequency);
}

PWMController::~PWMController() {
	// TODO Auto-generated destructor stub
}

void PWMController::tick() {
	pwmStateCalculator->tick();
}

void PWMController::timerCallback() {
	instance->tick();
}
