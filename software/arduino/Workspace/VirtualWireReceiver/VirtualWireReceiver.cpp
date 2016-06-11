// Do not remove the include below
#include "VirtualWireReceiver.h"

#include "VirtualWire.h"

uint32_t start = millis();
uint32_t messages = 0;

void setup()
{
    Serial.begin(57600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_rx_pin(12);
    vw_set_tx_pin(10);
    vw_set_ptt_pin(9);

    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;

		++messages;
		uint32_t duration = millis() - start;
		uint32_t msgPerSec = messages * 10000 / duration;
		Serial.print(msgPerSec);
//        digitalWrite(13, true); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
//	Serial.print("Got: ");
//
//	for (i = 0; i < buflen; i++)
//	{
//	    Serial.print(buf[i], HEX);
//	    Serial.print(" ");
//	}
//	Serial.println("");
    Serial.print(".");

//        digitalWrite(13, false);
    }
}
