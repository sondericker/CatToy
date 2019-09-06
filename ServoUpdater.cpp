
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "PWMDriver.h"
#include <wiringPi.h>
#include <sys/time.h>

#include "ServoUpdater.h"


using namespace std;


// ServoUpdater
//
// This class controls the motion for 2 servo axis and drives them
// using a thread from startPosition1,2 to endPosition1,2 at speed.
//
// All positions are doubles in the range of 0.0 - 1.0 representing the
// travel of the servo, which is abstracted and simplified in this class
//
// speed is also a double 0.0 - 1.0 with 1.0 representing the top speed
// of the servo. Both servos will always arrive simultaneously.
//
// Calling goToPos(endPos1, endPos2, speed) will initiate a movement
// which will continue until isMoving = false, indicating the move is complete.




ServoUpdater::ServoUpdater() {
	
	// init pwm driver which will handle both pwm outputs being used
	pwm.initPWM(0x40);			// default i2c hat address
	pwm.setPWMFreq(100);		// run the PWM at 100Hz	
	
	int lowVal = .5/10 * 0xfff;
	int highVal = 2.5/10 * 0xfff;
	cout << "lowVal = " << lowVal << " highVal = " << highVal << endl;
		
	curPosA = lowVal;
	curPosB = lowVal;
	goToPos (highVal, highVal, 1);
	
	pwm.setPWM(0,0x00, lowVal);				// send them back to the beginning to start
	pwm.setPWM(1,0x00, lowVal);
	delayMicroseconds(450000);				// delay 450ms	

}

void ServoUpdater::start() {
	
	// thread is started here via threadHelper
	int err = pthread_create(&myThread, NULL, threadHelper, this);
 
	if (err != 0)
	{
		cout << "Error in thread creation: " << err << endl;
    }
}

void ServoUpdater::stop() {
	
	running = false;
	
}

void* ServoUpdater::threadHelper(void* arg) {
	
	ServoUpdater* thisObject = reinterpret_cast<ServoUpdater*>(arg);
    thisObject->updater();
    
    cout << "ServoUpdater thread stopped" << endl;
    return(0);
	
}

void ServoUpdater::updater() {
	
	struct timeval start, end;

	running = true;
	
	while (running) {
		
		// grab the time we started the update loop
		gettimeofday(&start, NULL);			// time of the first run
		
		updateServos();
		
		// grab the time again and decide how long we want to sleep
		// pwm writes are significant
		gettimeofday(&end, NULL);
		
		long mtime = ((end.tv_sec) * 1000000000 + end.tv_usec * 1000) - ((start.tv_sec) * 1000000000 + start.tv_usec * 1000);		// number of nanoseconds
		struct timespec tp;
		if (mtime > 0) {
			tp.tv_sec = 0;
			tp.tv_nsec = (1000000000/UPDATER_FREQUENCY_HZ) - mtime;	// 1 billion nano seconds / update frequency - how long it took to run the loop
			cout << "Was gone for:" << mtime << " nanoseconds so sleeping for:" << tp.tv_nsec << " nanoseconds." << endl;

		} else {
			tp.tv_sec = 0;			// something went wrong with the timers so just sleep for 1us
			tp.tv_nsec = 1000;
		}
		nanosleep(&tp, NULL);		// updater runs every 1/UPDATE_FREQUENCY_HZ seconds

	}
}

void ServoUpdater::goToPos(double posA, double posB, double speed) {
	destPosA = posA;
	destPosB = posB;
	destSpeed = speed;
	
}


void ServoUpdater::updateServos() {
	
	if (curPosA < destPosA) {
		curPosA++;
		curPosB++;
		pwm.setPWM(0, 0x000, curPosA);		// it takes about 3ms to setPWM
		pwm.setPWM(1, 0x000, curPosB);
	} else {
		int lowVal = .5/10 * 0xfff;
		int highVal = 2.5/10 * 0xfff;
		cout << "lowVal = " << lowVal << " highVal = " << highVal << endl;
		
		curPosA = lowVal;
		curPosB = lowVal;		
		pwm.setPWM(0, 0x000, curPosA);		// it takes about 3ms to setPWM
		pwm.setPWM(1, 0x000, curPosB);
		delayMicroseconds(300000);				// delay 300ms	
	}
				
}




