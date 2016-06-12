// Do not remove the include below
#include "VirtualWireReceiverTimerOne.h"
#include "lib/VirtualWireTimerOne/VirtualWire.h"
#include "lib/SerialPWM/PWMController.h"
#include "lib/SerialPWM/Pulse.h"
#include "lib/SerialPWM/RGBLed.h"
#include "VirtualWireTimerShare.h"

const uint8_t NUM_PINS = 8;


PWMController *pwmController;
Pulse *pulse;
RGBLed *rgbLed;
RGBLed *rgbLed2;
RGBLed *rgbLed3;

uint32_t start = millis();
uint32_t messages = 0;

void setupLightShow() {

	pwmController = new PWMController(NUM_PINS, 100);

	pulse = new Pulse(8, 1000, Pulse::TRIANGLE);
	pulse->chain(pwmController);
	pwmController->addTimedPowerController(pulse);

	rgbLed = new RGBLed(NUM_PINS-1, NUM_PINS-2, NUM_PINS-3);
	rgbLed->chain(pulse);
	rgbLed->setColor(255, 128, 128);

	rgbLed2 = new RGBLed(NUM_PINS-4, NUM_PINS-5, NUM_PINS-6);
	rgbLed2->chain(pulse);
	rgbLed2->setColor(64, 128, 255);

	rgbLed3 = new RGBLed(NUM_PINS-7, NUM_PINS-8, NUM_PINS-8);
	rgbLed3->chain(pulse);
	rgbLed3->setColor(64, 128, 255);

}

void setupReceiver() {
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100

    vw_set_rx_pin(9);
    vw_set_tx_pin(10);
    vw_set_ptt_pin(8);
    uint32_t timerPeriod = vw_setupTO(2000);

    vw_rx_start();       // Start the receiver PLL running

}


void lightShow() {
	rgbLed->setColor(rand(), rand(), rand());
//	pulse->changePulseWidth(1000);
}

void receive() {
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	vw_wait_rx(); // Block until message is received
	if (vw_get_message(buf, &buflen)) { // Non-blocking

		int i;
		++messages;
		uint32_t duration = millis() - start;
		uint32_t msgPerSec = messages * 10000 / duration;
		Serial.print(msgPerSec);

//		// Message with a good checksum received, dump it.
//		Serial.print("Got: ");
//
//		for (i = 0; i < buflen; i++) {
//			Serial.print(buf[i], HEX);
//			Serial.print(" ");
//		}
//		Serial.println("");
		Serial.print('.');
	}
}

void setup()
{
    Serial.begin(57600);	// Debugging only
    Serial.println("setup");

    setupLightShow();
    VirtualWireTimerShare *vwts = new VirtualWireTimerShare();
    setupReceiver();
    pwmController->shareTimerOne(vwts, 62);
}

void loop()
{

	lightShow();
	receive();
}

