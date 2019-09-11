

#define default_speed 0.8

class MotionProfile {
	
	public:
	MotionProfile();
	void addStep(double panPos, double tiltPos, double stepSpeed, double pause);
	int numSteps;
	double pan[200];
	double tilt[200];
	double speed[200];
	double pause[200];
	
	protected:
	
	private:

	
};
