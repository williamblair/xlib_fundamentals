/* example from xlibbook-0.5.pdf */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Display *d = NULL; // the display to draw the window on
	XSetWindowAttributes at; // structure containing window information
	Window w; // the application window
	XSizeHints sh; // structure containing size information
	XWMHints wmh; // various window properties
	XTextProperty wname, iconname; // title and icon of the window
	XEvent e; // contains event information

	char *window_name = "Hello World";
	char *icon_name = "Hello Icon";

	int screen_num; // which screen the display is on
	int done;       // while loop holder?
	unsigned long value_mask; // OR'd properties about the window

	/* 1 - open a connection to th server */
	d = XOpenDisplay(NULL); // takes a string - null makes it use default display

	/* 2 - create a top level window */
	screen_num = DefaultScreen(d);
	at.background_pixel = WhitePixel(d, screen_num);
	at.border_pixel = BlackPixel(d, screen_num);
	at.event_mask = ButtonPressMask; // get button press events

	value_mask = CWBackPixel | CWBorderPixel | CWEventMask; // which parts of the XSetAttributes struct to use

	w = XCreateWindow(d,                              // Display *d
	                  RootWindow(d, screen_num),      // parent window
	                  200, 200,                       // x,y
	                  350, 250,                       // width, height
	                  2,                              // border width
	                  DefaultDepth(d, screen_num),    // 'Depth' of the window - color attributes (16 or 24)  
	                  InputOutput,                    // the window accepts both input and can produce output
	                  DefaultVisual(d, screen_num),   // contains color information
	                  value_mask,                     // which values from the XSetWindowAttributes struct to use
	                  &at                             // the XSetWindowAttributes struct
	);

	/* 3 - give the window manager hints */
	sh.flags = USPosition | USSize;
	XSetWMNormalHints(d, w, &sh);

	wmh.initial_state = NormalState;
	wmh.flags = StateHint;
	XSetWMHints(d, w, &wmh);

	XStringListToTextProperty(&window_name, 1, &wname);
	XSetWMName(d, w, &wname);

	XStringListToTextProperty(&icon_name, 1, &iconname);
	XSetWMIconName(d, w, &iconname);

	/* 4 - establish window resources */
	/* 5 - create all the other windows needed */
	/* 6 - select events for each window */
	/* 7 - map the windows */
	XMapWindow(d, w);

	/* 8 - event loop */
	done = 0;
	do
	{
		XNextEvent(d, &e);
		switch(e.type)
		{
			case ButtonPress:
				done = 1;
				break;
			default:
				break;
		}
	} while( !done );

	/* clean up before exiting */
	XUnmapWindow(d, w);
	XDestroyWindow(d, w);
	XCloseDisplay(d);

	return 0;
}




