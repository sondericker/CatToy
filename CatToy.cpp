

//  CatToy - Raspberry Pi Cat Toy


#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

#include "CatToy.h"
#include "PWMDriver.h"
#include "MotionProfile.h"
#include "ServoUpdater.h"



using namespace std;


int main(int argc, char **argv)
{

	cout << "into main.\n\n";
	
	CatToy ct;

	ct.startUp();
	
	cout << "back from startUp\n";
	
	MotionProfile mp1();

	return 0;
}


CatToy::CatToy()
{		
	
	
}


void CatToy::startUp() {
	
	cout << "Made it to startUp()\n";
	
	ServoUpdater sUpdater;
	sUpdater.start();

/*	
	PWMDriver pwm;
	
	pwm.initPWM(0x40);			// default i2c hat address
	pwm.setPWMFreq(100);		// run the PWM at 100Hz
	
	int lowVal = .5/10 * 0xfff;
	int highVal = 2.5/10 * 0xfff;
	cout << "lowVal = " << lowVal << " highVal = " << highVal << endl;
	

	while (true) {
		
		cout << "Starting again.\n";
		
		for (int i=lowVal; i< highVal; i++) {
			pwm.setPWM(0, 0x000, i);		// it takes about 3ms to setPWM
			pwm.setPWM(1, 0x000, i);
		}
		
		cout << "Done.\n";

		pwm.setPWM(0,0x00, lowVal);				// send them back to the beginning
		pwm.setPWM(1,0x00, lowVal);
		delayMicroseconds(450000);				// delay 450ms
	}	
	* 
	*/
	
	while (true) {
		delayMicroseconds(5000000);				// delay 5s
		cout << "main thread running..\n";
	}
	
}


void CatToy::printTime () {
	
    struct timeval start, end;

    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

//    seconds  = end.tv_sec  - start.tv_sec;
//    useconds = end.tv_usec - start.tv_usec; 
    
    seconds  = start.tv_sec;
    useconds = start.tv_usec;    

    mtime = ((seconds) * 1000000 + useconds);
    
    cout << "Time: " << mtime << endl;

   // printf("Elapsed time: %ld\n", mtime);
	
	
}


