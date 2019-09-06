

#define UPDATER_FREQUENCY_HZ	   	200		// frequency the updater runs at
#define PWM_HAT_ADDRESS 		0x40		// address of PWM hat hardware
#define PWM_FREQ				100

#include <pthread.h>
#include "PWMDriver.h"


class ServoUpdater {
	
	public:
	
	ServoUpdater();
	void start();
	void stop();
	void goToPos(double posA, double posB, double speed);	

	protected:
	
	private:
	void updater();							// looping thread method
	static void* threadHelper(void* arg);	// static method to launch thread
	void updateServos();					// method to actually update servo pwms
	
	pthread_t myThread;
	PWMDriver pwm;	
	double destPosA;
	double destPosB;
	double destSpeed;
	double curPosA;
	double curPosB;
	bool running;

};
