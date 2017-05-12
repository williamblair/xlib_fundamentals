/* program that just runs the system's internal bell 
 * modifed as per exercises from section 2.4.1 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if( argc != 2 ){
		fprintf(stderr, "Invalid number of arguments!\n");
		fprintf(stderr, "Usage: %s <volume>\n", argv[0]);
		fprintf(stderr, "Where volume is a number from -100 to 100 indicating the volume.\n");
		return 0;
	}

	Display *d = NULL;
	int volume = 0;

	/* 1 - open a connection to the server */
	d = XOpenDisplay(NULL); // open the default display

	/* 2 - create a top level window */
	/* 3 - give the window manager hints */
	/* 4 - establish window resources */
	/* 5 - create all the other windows needed */
	/* 6 - select events for each window */
	/* 7 - map the windows */
	/* 8 - enter the event loop */

	volume = atoi(argv[1]); // convert the input into an integer
	if( volume < -100 || volume > 100 ){
		fprintf(stderr, "Please enter a number between -100 and 100!\n");
		if(d) XCloseDisplay(d);
		return -1;
	}

	//XBell(d, 0); // run the system bell
	//XBell(d, 100); // run the system bell as loud as possible (takes a %)
	XBell( d, volume ); // run the system bell with the user's input

	/* 9 clean up before exiting */ 
	XCloseDisplay(d);

	return 0;
}

