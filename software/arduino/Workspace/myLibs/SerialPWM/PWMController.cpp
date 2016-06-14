/*
 * PWMController.cpp
 *
 *  Created on: 18.04.2016
 *      Author: thomas
 */

#include "PWMController.h"
#include <stdlib.h>
#ifndef DEBUG
#include <TimerOne.h>
#include <MsTimer2.h>
#endif
#include "TimedPowerController.h"

PWMController *PWMController::instance = NULL;

PWMController::PWMController(uint8_t channels, uint8_t frequency, uint8_t maxNumTimedPowerControllers) {

	instance = this;
	timerShare = NULL;

	initStateCalculator(channels);
	initTimedPowerControllers(maxNumTimedPowerControllers);
	initTimer(frequency);
}

PWMController::~PWMController() {
	// TODO Auto-generated destructor stub
}

void PWMController::initStateCalculator(uint8_t channels) {
	pwmStateCalculator = new MovingStartPWMStateCalculator(channels);
}

void PWMController::initTimer(uint8_t frequency) {
#ifndef DEBUG
	Timer1.initialize();
	uint32_t timerPeriod = (1000000 / frequency) >> 8;
	Timer1.setPeriod(timerPeriod);
	Timer1.attachInterrupt(timerCallback);

	MsTimer2::set(TimedPowerControllerConstants::UPDATE_INTERVAL, timedPowerControllerCallback);
	MsTimer2::start();
#endif
}

void PWMController::initTimedPowerControllers(uint8_t maxNumTimedPowerControllers) {
	this->maxNumTimedPowerControllers = maxNumTimedPowerControllers;
	numTimedPowerControllers = 0;
	timedPowerControllers = new TimedPowerController*[maxNumTimedPowerControllers];
}

void PWMController::addTimedPowerController(TimedPowerController* tpc) {
	if (numTimedPowerControllers < maxNumTimedPowerControllers) {
		timedPowerControllers[numTimedPowerControllers] = tpc;
		++numTimedPowerControllers;
	}
}

void PWMController::tick() {
	if (timerShare != NULL) {
		timerShare->callback();
	}
	pwmStateCalculator->tick();
}

void PWMController::timedPowerControllerTick() {
	unsigned long now = millis();

	for (uint8_t i = 0; i < numTimedPowerControllers; ++i) {
		timedPowerControllers[i]->tick(now);
	}
}

void PWMController::timerCallback() {
	instance->tick();
}

void PWMController::timedPowerControllerCallback() {
	instance->timedPowerControllerTick();
}

void PWMController::shareTimerOne(TimerShare* timerShare, uint32_t timerPeriod) {
	this->timerShare = timerShare;
#ifndef DEBUG
	Timer1.setPeriod(timerPeriod);
#endif
}
