

//  CatToy - Raspberry Pi Cat Toy


#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <unistd.h>
#include "MotionProfile.h"
#include "ServoUpdater.h"
#include "TerminalUI.h"
#include "CatToy.h"


using namespace std;


int main(int argc, char **argv)
{
	cout << "into main.\n\n";
	CatToy ct;
	ct.startUp();
	cout << "back from startUp\n";

	return 0;
}


CatToy::CatToy()
{		
	
	
}


void CatToy::startUp() {
	
	cout << "Made it to startUp()\n";
	//ServoUpdater sUpdater;
	sUpdater.start();

	sUpdater.goToPos(0.1, 0.1, 3); // go to mid-point at 3x speed for starters
sleep(1);
	sUpdater.goToPos(0.9, 0.9, 3); // go to mid-point at 3x speed for starters
sleep(1);	

	sUpdater.goToPos(0.5, 0.5, 3); // go to mid-point at 3x speed for starters
sleep(1);	

	TerminalUI tUI(&sUpdater);		// this is a loop that runs until we quit
	
	
	cout << "EXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxiting for some reason." << endl;
	sleep(2);
	sUpdater.stop();				// kill the updater thread
	cout << "exiting.." << endl;
	sleep(2);
	exit(0);						// exit the application
	
}


void CatToy::printTime () {
	
    struct timeval start, end;

    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

//    seconds  = end.tv_sec  - start.tv_sec;
//    useconds = end.tv_usec - start.tv_usec; 
    
    seconds  = start.tv_sec;
    useconds = start.tv_usec;    

    mtime = ((seconds) * 1000000 + useconds);
    
    cout << "Time: " << mtime << endl;

   // printf("Elapsed time: %ld\n", mtime);
	
	
}


