/* edit on main.c to use XMoveWindow instead, makes more since and
 * is easier to understand in my opinion */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <unistd.h> // for sleep()

int main(int argc, char *argv[])
{
	Display              *d = NULL;
	XSetWindowAttributes  at;
	Window                w, square; // square is what's drawn inside w
	//XWindowChanges        moveChange; // don't need this since calling XMoveWindow instead
	XSizeHints            wmsize;
	XWMHints              wmhints;
	XTextProperty         windowName, iconName;
	XEvent                e;

	char *windowNameString = "A Moving Square!";
	char *iconNameString   = "Sqr Icon!";

	int           screenNum, done;
	unsigned long valueMask;
	int           x, y; // the x and y coordinates of the square 

	/* 1 - open the display */
	d = XOpenDisplay(NULL);

	/* 2 - create the main window */
	screenNum = DefaultScreen(d);
	at.background_pixel = WhitePixel(d, screenNum);
	at.border_pixel = BlackPixel(d, screenNum);
	at.event_mask = ExposureMask | StructureNotifyMask | ButtonPressMask; // structure notify is given when the window's structure changes

	valueMask = CWBackPixel | CWBorderPixel | CWEventMask;

	w = XCreateWindow(d,                               // display
	                  RootWindow(d, screenNum),        // parent
	                  200, 300,                        // x, y
	                  350, 250,                        // width, height
	                  2,                               // border width
	                  DefaultDepth(d, screenNum),      // display depth (16 | 24)
	                  InputOutput,                     // which events to take
	                  DefaultVisual(d, screenNum),     // Visual information about the display
	                  valueMask,                       // which attributes to use
	                  &at                              // attributes structure
	);

	/* 3 - give the window manager hints */
	wmsize.flags = USPosition | USSize;
	XSetWMNormalHints(d, w, &wmsize);

	wmhints.initial_state = NormalState;
	wmhints.flags = StateHint;
	XSetWMHints(d, w, &wmhints);

	XStringListToTextProperty(&windowNameString, 1, &windowName);
	XStringListToTextProperty(&iconNameString, 1, &iconName);
	XSetWMName(d, w, &windowName);
	XSetWMIconName(d, w, &iconName);

	/* 4 - establish window resources */
	at.background_pixel = BlackPixel(d, screenNum); // now we're setting attributes for the internal square window, so it's going to be drawn black 

	/* 5 create all other windows needed */	
	square = XCreateWindow(d,                            // display
	                       w,                            // parent window - in this case our previously created window
	                       100, 30,                      // x, y
	                       50, 70,                       // width, height
	                       2,                            // border width
	                       DefaultDepth(d, screenNum),   // display depth (16 | 24)
	                       InputOutput,                  // which events to take
	                       DefaultVisual(d, screenNum),  // visual information about the display
	                       valueMask,                    // which attributes to use - same as the previous window's
	                       &at                           // same attributes structure as parent, except we changed the background to black instead of white
	);

	/* 6 - select events for each window */
	valueMask = CWX | CWY; // take x change and y change events since the internal window will be moving

	/* 7 - map the windows */
	XMapWindow(d, w);

	/* 8 - enter the event loop */
	done = 0;
	x = 11; y = 12;
	do
	{
		//moveChange.x = x; moveChange.y = y; // set the window change properties to our calculated x
		//XConfigureWindow(d, square, valueMask, &moveChange); // reconfigure the square window

		XMoveWindow(d, square, x, y); // much simpler

		XFlush(d); // clear the window

		XNextEvent(d, &e); // get the next event

		switch(e.type)
		{
			case ButtonPress:
				done = 1; // exit the program
				break;
			case Expose:
				break; // the window is just being viewed / is currently active
			case ConfigureNotify:
				//printf("Configure Notify Event!\n");

				/* is this needed? 
				 * edit - yes it is! */
				XMapWindow(d, square); // a window change has been processed, so redraw it


				sleep(3);              // wait 3 seconds
				x += 1; y += 1; // move the x and y coordinates a bit

			default:
				break;
		}

	} while( !done );

	/* clean up before exit */
	XUnmapWindow(d, w);
	XDestroyWindow(d, w);
	XCloseDisplay(d);

	return 0;
}

