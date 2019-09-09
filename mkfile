
CatToy:CatToy.o PWMDriver.o MotionProfile.o ServoUpdater.o TerminalUI.o FileUtils.o
	g++ -Wall -g -o CatToy CatToy.o PWMDriver.o MotionProfile.o ServoUpdater.o TerminalUI.o FileUtils.o -L/sw/lib/root -lwiringPi -lpthread


CatToy.o:CatToy.cpp CatToy.h
	g++ -Wall -g -c -pthread -I/sw/include/root CatToy.cpp
    
PWMDriver.o:PWMDriver.cpp PWMDriver.h
	g++ -Wall -g -c -pthread -I/sw/include/root PWMDriver.cpp    
    
MotionProfile.o:MotionProfile.cpp MotionProfile.h
	g++ -Wall -g -c -pthread -I/sw/include/root MotionProfile.cpp
    
ServoUpdater.o:ServoUpdater.cpp ServoUpdater.h
	g++ -Wall -g -c -pthread -I/sw/include/root -lpthread  ServoUpdater.cpp 

TerminalUI.o:TerminalUI.cpp TerminalUI.h
	g++ -Wall -g -c -pthread -I/sw/include/root TerminalUI.cpp

FileUtils.o:FileUtils.cpp FileUtils.h
	g++ -Wall -g -c -pthread -I/sw/include/root FileUtils.cpp
    

