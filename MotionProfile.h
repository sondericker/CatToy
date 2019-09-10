

#define default_speed 0.8

class MotionProfile {
	
	public:
	MotionProfile();
	void addStep(double panPos, double tiltPos, double stepSpeed);
	int numSteps;
	double pan[150] = {0.0};
	double tilt[150] = {0.0};
	double speed[150] = {0.0};
	double pause[150] = {0.0};
	
	protected:
	
	private:

	
};
