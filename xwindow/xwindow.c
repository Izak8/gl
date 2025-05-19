#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define SUCCESS 0
#define FAILURE 1

#define CONNECTION_ERROR 0xE1
#define XPROTO_ERROR 0xE2

int main(int argc, char** argv) {

	// Logical display
	Display* display;
	int screen;
	Window root;
	GC gc;

	// Window
	Window client;
	Visual* visual = CopyFromParent;

	const unsigned int x = 0;
	const unsigned int y = 0;
	const unsigned int width = 800;
	const unsigned int height = 600;
	
	XSetWindowAttributes attributes;
		// we will set these attributes
	unsigned long attribute_mask = CWEventMask | CWBackPixel;
		// we are interested in processing these events
	unsigned long event_mask = ExposureMask | ButtonPressMask | KeyPressMask;


	// Window manager hints
	XSizeHints size_hints;
	XClassHint class_hints;
	XWMHints wm_hints;
		// set WM_NAME to program name
	char* wm_name_string = argv[0];
		// set WM_CLASS
	char* wm_class_string = "example";
	
	// Event
	XEvent event;
	bool window_should_close = false;

	//////////////////////////////////
	// Open connection to X server //
	
	if((display = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "Error: Unable to establish connection to X server.\n");
		return CONNECTION_ERROR;
	}

	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	gc = DefaultGC(display, screen);
	
	//////////////////////////////
	// Create top-level window //

		// set desired window attributes
	attributes.event_mask = event_mask;
	attributes.background_pixel = WhitePixel(display, screen);

		// create the window resource
	client = XCreateWindow(display, root, 
		// geometry
		x, y, width, height,
		// border & depth
		2, CopyFromParent,
		// class, visual, and attributes
		InputOutput, visual, attribute_mask, &attributes
	);

	///////////////////////////////
	// Set window manager hints //

	size_hints.flags = USPosition | USSize | PMinSize | PBaseSize;
	size_hints.x = x;
	size_hints.y = y;
	size_hints.width = width;
	size_hints.height = height;
	size_hints.min_width = width;
	size_hints.min_height = height;
	size_hints.base_width = width;
	size_hints.base_height = height;

	class_hints.res_class = wm_class_string;
	class_hints.res_name = wm_name_string;

	wm_hints.flags = InputHint | StateHint;
	wm_hints.initial_state = NormalState;
	wm_hints.input = True;

	XSetWMNormalHints(display, client, &size_hints);
	XStoreName(display, client, wm_name_string);
	XSetWMHints(display, client, &wm_hints);
	
	//////////////////////////////
	// Create window resources //

		// string to be displayed
	char* message_string = "Hello World! -- From X client";
	size_t message_size = strlen(message_string);

	unsigned int current_width;
	unsigned int current_height;
	
	/////////////////////
	// Map the window //
	XMapRaised(display, client);
	XFlush(display);
	
	/////////////////
	// Event loop //
	while(!window_should_close) {
		// fetch and store next event in queue to event variable
		XNextEvent(display, &event);

		int type = event.type;

		switch(type) {
			case Expose:
				// get client window width and height to calculate position
				current_width = event.xexpose.width;
				current_height = event.xexpose.height;
				
				XDrawString(display, client, gc,
					// string position
					(current_width / 2), (current_height / 2),
					// string message
					message_string, message_size
				);
				break;
			case ButtonPress:
				window_should_close = true;
				break;
		}
	}
	///////////////////////////////////
	// Cleanup and close connection //
	XCloseDisplay(display);
	return SUCCESS;
}
