




class CatToyAuto {

	public:	
	struct timeval start, end;
	
	CatToyAuto();
	void startUp();

	
	protected:
	
	private:
	void printTime();	
	ServoUpdater sUpdater;
};
