

#define UPDATER_FREQUENCY_HZ	   	50		// frequency the updater runs at
#define PWM_HAT_ADDRESS 		0x40		// address of PWM hat hardware
#define PWM_FREQ				100

class ServoUpdater {
	
	public:
	
	ServoUpdater();
	void start();
	void stop();
	void goToPos(double posA, double posB, double speed);	

	protected:
	
	private:
	pthread_t myThread;
	PWMDriver pwm;
	void updater();							// looping thread method
	static void* threadHelper(void* arg);	// static method to launch thread
	void updateServos();					// method to actually update servo pwms
	
	double destPosA;
	double destPosB;
	double destSpeed;
	double curPosA;
	double curPosB;
	bool running;

};
