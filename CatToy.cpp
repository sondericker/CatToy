

//  CatToy - Raspberry Pi Cat Toy


#include <iostream>
#include <stdlib.h>
#include "CatToy.h"
#include "PWMDriver.h"
#include <wiringPi.h>


using namespace std;


int main(int argc, char **argv)
{

	cout << "into main.\n\n";
	
	CatToy ct;

	ct.startUp();

	return 0;
}


CatToy::CatToy()
{		
	
	
}


void CatToy::startUp() {
	
	cout << "Made it to startUp()\n";
	
	PWMDriver pwm;
	
	pwm.initPWM(0x40);			// default i2c hat address
	pwm.setPWMFreq(100);		// run the PWM at 100Hz
	
	int lowVal = .5/10 * 0xfff;
	int highVal = 2.5/10 * 0xfff;
	cout << "lowVal = " << lowVal << " highVal = " << highVal << endl;
	
	while (true) {
		for (int i=lowVal; i< highVal; i++) {
			pwm.setPWM(0, 0x000, i);		// should be 50% PWM value
			pwm.setPWM(1, 0x000, i);
			delayMicroseconds(1000);	
		}
					cout << "Done.\n";
					pwm.setPWM(0,0x00, lowVal);				// send them back to the beginning
					pwm.setPWM(1,0x00, lowVal);
					delayMicroseconds(500000);
	}	
	
}


