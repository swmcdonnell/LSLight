LSLight
=======

Arduino library for the Walgreens Living Solutions remote control lights

This is an Arduino library to control the Walgreens Living Solutions Indoor Wireless Remote Control
lamps. You can team up to three of them together to control devices in the same room. They sell for
about $10 a piece.

The Walgreens remote control devices operate at 433 MHz, so you need an RF transmitter that transmits
at 433 MHz. You can get one on eBay for about $1 or $2. The library uses the RCSwitch library to control
the RF transmitter.

Once you assign a code of 1, 2 or 3 to each device, you can turn the lights on or off using your Arduino
and this library. The library tracks whether it thinks a lamp is on or off. It provides functions to turn
on or off according to that status, or to force on or off regardless of that status.


LSLight(void):      I don't require any parameters when you create an instance of a class becauase if you're
                    declaring a static global variable, you might not know the parameters to pass, for example
                    if you're reading information from EEPROM. So you can create the class and then use the
                    init function below to set it up.

init(pin, status):  call the init function with the RF transmitter pin and whether you want to start with
                    lights on or off. 
                    
on(lamp):           call "on" to turn a lamp on, for example:  on(1); on(2); on(3);
                    returns the current status of the lamp

off(lamp):          call "off" to turn off a lamp, for example:  off(1); off(2); off(3);
                    returns the current status of the lamp (ON or OFF)

forceOn(lamp):      turn the lamp on even if the library believes it's already on, for example:
                    forceOn(1); forceOn(2); forceOn(3);
                    returns the current status of the lamp
                    
forceOff(lamp):     turn thelamp off even if the library believes it's already off, for example:
                    forceOff(1); forceOff(2); forceOff(3);
                    returns the current status of the lamp
                    
all(status):        turn all lamps on or off, for example: all(ON); all(OFF);
                    this function uses forceOn and forceOff
                    
status(lamp):       get the current status of a lamp, ON or OFF, for example:  status(1); status(2); status(3);
  
The Walgreens codes are as follows:

  Prefix:   01101010101101100000
  Suffix:   0
  
  \
     1 OFF:    0111 \
     1 ON:     1111 \
  
     2 OFF:    0011 \
     2 ON:     1011 \
  
     3 OFF:    0101 \
     3 ON:     1101 \
  
     All OFF:  0100 \
     All ON:   1000 \
  
The library doesn't use the All OFF and All ON codes. Instead, it loops through the lamps. 
