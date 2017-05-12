/* program that just runs the system's internal bell */

#include <X11/Xlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	Display *d = NULL;

	/* 1 - open a connection to the server */
	d = XOpenDisplay(NULL); // open the default display

	/* 2 - create a top level window */
	/* 3 - give the window manager hints */
	/* 4 - establish window resources */
	/* 5 - create all the other windows needed */
	/* 6 - select events for each window */
	/* 7 - map the windows */
	/* 8 - enter the event loop */

	XBell(d, 0); // run the system bell

	/* 9 clean up before exiting */ 
	XCloseDisplay(d);

	return 0;
}

