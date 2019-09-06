

class TerminalUI {

	public:
	TerminalUI(ServoUpdater sUp);

	protected:


	private:
	double panPos;
	int panPosTicks;
	double tiltPos;
	int tiltPosTicks;
	
	ServoUpdater sUpdater;
	
	void driveToPosition();
	void clearTerminal();


};
