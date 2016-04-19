/*
 * PWMController.cpp
 *
 *  Created on: 18.04.2016
 *      Author: thomas
 */

#include "PWMController.h"
#ifndef DEBUG
#include <TimerOne.h>
#include <MsTimer2.h>
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

	MsTimer2::set(1, timedPowerControllerCallback);
	MsTimer2::start();
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

void PWMController::timedPowerControllerCallback() {
	static uint8_t val = 0;
	instance->setDuty(7, val++);
	instance->allDutiesSet();
}

