/**
 * LSLight.cpp
 * 
 * Author: Steve McDonnell
 * Version: 1.1  2013-12-15
 *
 * Library to turn up to three remote-controlled lights on or off
 * with the Living Solutions Wirless Indoor Lighting Remote Control
 * modules from Walgreens.
 *
 * Requires a 433MHz RF Transmitter
 * Uses the RCSwitch Library
**/
/**
 * The Living Solutions Wireless Indoor Lighting Remote Control units
 * from Walgreens can control up to three lamps or other devices. When
 * you plug in the unit, you have to set it up as either Lamp 1, 2 or 3.
 * When you refer to a lamp using this library, you refer to it by 
 * its number, either 1, 2 or 3
 *
 * The library keeps track of whether a lamp is on or off. If you call
 * the library to turn a lamp on and it's already on, it won't send the
 * codes so you're not constantly messaging the remote receiver.
 *
 * The library also provides a function to force a lamp on or off regardless
 * of what it believes the status is. 
**/

/**
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.* 
 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**/

#define DEBUG 0

#include "LSLight.h"
#include <RCSwitch.h>

// RF 433Mhz Control
static RCSwitch remote = RCSwitch();
// RF Commands
static const char *prefix = "01101010101101100000";
static const char *suffix = "0";
static const char *command[MAX_OUTLETS][2] = { { "0111", "1111" }, { "0011", "1011" }, { "0101", "1101" } };

LSLight::LSLight(void) {
}

/*******************************************
 * Initialize Light Control
 * 
 * Parameters:
 *    pin:			RF Transmit Pin
 *    startupMode:	ON or OFF to start
 *
********************************************/
void LSLight::init(int pin, int startupMode) {
	_pin = pin;

	// Set up RF Configuration
	pinMode(_pin, OUTPUT);
	remote.enableTransmit(_pin);
	remote.setProtocol(1);
	remote.setPulseLength(302);
	remote.setRepeatTransmit(5);

	// Turn lights on or off to start
	if (startupMode == ON)
		all(ON);
	else
		all(OFF);
}

/*******************************************
 * Force a light to be on
 *
 * Parameter:
 *     lamp: 1, 2 or 3
 *
********************************************/
int LSLight::forceOn(unsigned int lamp) {
	if (lamp < 1 || lamp > MAX_OUTLETS) return OFF;
	--lamp;
	sprintf(fullCmd, "%20s%4s%1s", prefix, command[lamp][ON], suffix);
	remote.send(fullCmd);
	_status[lamp] = ON;
	if (DEBUG) {
		Serial.print("lamp on: ");
		Serial.println(fullCmd);
	}
	return _status[lamp];
}

/*******************************************
 * Turn lamp on
 *
 * Parameter:
 *     lamp: 1, 2 or 3
 *
 * Returns:
 *		ON or OFF
********************************************/
int LSLight::on(unsigned int lamp) {
	if (lamp < 1 || lamp > MAX_OUTLETS) return OFF;
	if (_status[lamp-1] == OFF) {
		forceOn(lamp);
	}
	return _status[lamp-1];
}

/*******************************************
 * Force a light to be off
 *
 * Parameter:
 *     lamp: 1, 2 or 3
 *
********************************************/

int LSLight::off(unsigned int lamp) {
	if (lamp < 1 || lamp > MAX_OUTLETS) return OFF;
	if (_status[lamp-1] == ON) {
		forceOff(lamp);
	}
	return _status[lamp-1];
}

/*******************************************
 * Force a light to be off
 *
 * Parameter:
 *     lamp: 1, 2 or 3
 *
********************************************/
int LSLight::forceOff(unsigned int lamp) {
	if (lamp < 1 || lamp > MAX_OUTLETS) return OFF;
	--lamp;
	sprintf(fullCmd, "%20s%4s%1s", prefix, command[lamp][OFF], suffix);
	remote.send(fullCmd);
	_status[lamp] = OFF;
	if (DEBUG) {
		Serial.print("lamp off: ");
		Serial.println(fullCmd);
	}
	return _status[lamp];
}


/*******************************************
 * Turns all lights on or off
 *
 * Parameter:
 *     whichWay:  ON or OFF
 *
********************************************/
void LSLight::all(int turnThem) {
	for (int lamp=1; lamp<=MAX_OUTLETS; lamp++) {
		if (turnThem == ON) 
			forceOn(lamp);
		else
			forceOff(lamp);
	}
}

/*******************************************
 * Returns the current status of a lamp
 *
 * Parameter:
 *     lamp: 1, 2 or 3
 *
 * Returns:
 *		ON or OFF
********************************************/

int LSLight::status(unsigned int lamp) {
	if (lamp < 1 || lamp > MAX_OUTLETS) return OFF;
	return _status[lamp-1];
}

