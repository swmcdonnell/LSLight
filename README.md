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

Functions
----

Function               |  Example                          | Description                                              |
--------               |  -----------                      | -----------                                              |
**LSLight(void)**          | `static LSLight light=LSLight();` | You might not know the parameters when you create a                                                                     static global variable for the class, I don't use any                                                                   parameters when you create the class. Call the "init"                                                                   function below after you create it to initialize it  |
**void init(pin,status)** |  `light.init(10, OFF);`            | initialize - pass the RF transmitter pin and if you                                                                     want to start with all lights ON or OFF.             |
**int on(lamp)**          |  `light.on(1);`                    | Turn ON a lamp if current status shows it OFF                                                                           _returns the current lamp status of the lamp_        |
**int off(lamp)**         |  `light.off(3);`                   | Turn OFF a lamp if current status show it ON                                                                            _returns the current lamp status of the lamp_        | 
**int forceOn(lamp)**     |  `light.forceOn(2);`               | Turn ON a lamp (unconditionally)                                                                                        _returns the current lamp status of the lamp_        |
**int forceOff(lamp)**    |  `light.forceOff(1);`              | Turn OFF a lamp (unconditionally)                                                                                        _returns the current lamp status of the lamp_       |  
**void all(status)**      |  `light.all(ON);`                  | Turn all lamps ON or OFF (unconditionally)           |
**int status(lamp)**      |  `int status2 = light.status(2);`  | Returns current status of a lamp, ON or OFF          |

Codes
------
  
The Walgreens codes are as follows:

  Prefix               | Suffix |
  ----                 | ---- |
  01101010101101100000 |  0
  
  Lamp   |    OFF   |  ON     |
  :----: |  :----:  | :----:  |
   1     |    0111  | 1111    |
   2     |    0011  | 1011    |
   3     |    0101  | 1101    |
  All    |    0100  | 1000    |

   * For example, to turn ON Lamp 1, the code is:  "0110101010110110000011110"
  
   The library doesn't use the All OFF and All ON codes. Instead, it loops through the lamps. 
