/*
 * PWMController.h
 *
 *  Created on: 18.04.2016
 *      Author: thomas
 */

#ifndef PWMCONTROLLER_H_
#define PWMCONTROLLER_H_

#include "Arduino.h"
#include "PowerController.h"
#include "PWMStateCalculator.h"
#include "TimedPowerController.h"
#include "TimerShare.h"

/**
 * This class is the main controller for all PWM outputs. It controls the timer that calls the controller in regular intervals
 * and contains the PWMStateCalculator that calculates all data that is sent to a serial device.
 */
class PWMController : public PowerController {
public:

	PWMController(uint8_t channels, uint8_t frequency = 100, uint8_t maxNumTimedPowerControllers = 16);
	virtual ~PWMController();

	void setDuty(uint8_t channel, uint8_t duty) {
		pwmStateCalculator->setDuty(channel, duty);
	}

	void allDutiesSet() {
		pwmStateCalculator->allDutiesSet();
	}

	void addTimedPowerController(TimedPowerController *tpc);

	void shareTimerOne(TimerShare* timerShare, uint32_t timerPeriod);

private:
	void tick();
	void timedPowerControllerTick();

	static void timerCallback();
	static void timedPowerControllerCallback();

	void initStateCalculator(uint8_t channels);
	void initTimer(uint8_t frequency);
	void initTimedPowerControllers(uint8_t maxNumTimedPowerControllers);

	static PWMController *instance;

	uint8_t numTimedPowerControllers;
	uint8_t maxNumTimedPowerControllers;

	PWMStateCalculator *pwmStateCalculator;
	TimedPowerController **timedPowerControllers;

	TimerShare *timerShare;
};

#endif /* PWMCONTROLLER_H_ */
