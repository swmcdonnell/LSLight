/**
 * LSLight.h - Library for turning Living Solutions lights on or off
 *
 * Steve McDonnell
**/
#ifndef LSLight_h
#define LSLight_h

#define MAX_OUTLETS 3
#define MAX_COMMAND 26
#define ON 1
#define OFF 0

#include <Arduino.h>

class LSLight {
    public:
		LSLight(void);
        void init(int pin, int startupMode);
        int on(unsigned int lamp);
		int forceOn(unsigned int lamp);
		int off(unsigned int lamp);
        int forceOff(unsigned int lamp);
        void all(int turnThem);
        int status(unsigned int lamp);
    private:
        int _pin;
		int _status[MAX_OUTLETS];
		char fullCmd[MAX_COMMAND+1];
};  
#endif

