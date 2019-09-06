

//  CatToy - Raspberry Pi Cat Toy


#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

#include "CatToy.h"
#include "MotionProfile.h"
#include "ServoUpdater.h"
#include "TerminalUI.h"


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
	
	ServoUpdater sUpdater;
	sUpdater.start();


	TerminalUI tUI(sUpdater);


	while (true) {
		delayMicroseconds(5000000);				// delay 5s
		cout << "main thread running..\n";
	}
	
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


