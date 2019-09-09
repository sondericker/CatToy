



class FileUtils {
	
	public:
	FileUtils();
	MotionProfile loadProfile();
	void saveProfile(MotionProfile pf);
	
	protected:
	
	private:
	void split_line(std::string& line, std::string delim, std::list<std::string>& values);
	
};



