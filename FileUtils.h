

#include <list>
#include <string>

using namespace std;


class FileUtils {
	
	public:
	FileUtils();
	MotionProfile loadProfile();
	void saveProfile(MotionProfile pf);
	
	protected:
	
	private:
	void split_line(string& line, string delim, list<std::string>& values);
	
};



