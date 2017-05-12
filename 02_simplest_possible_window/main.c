/* simplist possible window example, without
 * window manager hints */

#include <X11/Xlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	Display              *d = NULL;
	XSetWindowAttributes  at;
	Window                w;
	XEvent                e;

	char *windowNameString = "Simplist Window";
	char *iconNameString   = "Simple";

	int screenNum, done;

	unsigned long valueMask;

	/* 1 - open connection to the server */
	d = XOpenDisplay(NULL); // open the default display

	/* 2 - create a top level window */
	screenNum = DefaultScreen(d);
	at.background_pixel = WhitePixel(d, screenNum);
	valueMask = CWBackPixel;

	w = XCreateWindow(d,                              // display
	                  RootWindow(d, screenNum),       // parent window
	                  200, 200,                       // x, y
	                  350, 250,                       // width, height
	                  2,                              // border width
	                  DefaultDepth(d, screenNum),     // screen depth (16bit or 24bit)
	                  InputOutput,                    // unsigned int class - which types of events it takes 
	                  DefaultVisual(d, screenNum),    // coloring/display information in a Visual * struct
	                  valueMask,                      // which attributes in the XSetWindowAttributes to use
	                  &at                             // XSetWindowAttributes struct with window information
	);

	/* 3 - give the window manager hints */
	/* 4 - establish window resources */
	/* 5 - create all the other windows needed */
	/* 6 - select events for each window */
	/* 7 - map the windows */
	XMapWindow(d, w);

	/* 8 - enter the event loop */
	XNextEvent(d, &e);

	/* 9 - clean up before exiting */
	XUnmapWindow(d, w);
	XDestroyWindow(d, w);
	XCloseDisplay(d);

	return 0;
}

