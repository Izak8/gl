#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
// Include Xproto to get opcode defines for error handling
#include <X11/Xproto.h>

// Basic macros
#define SUCCESS 0
#define FAILURE 1

// Return status
#define XPROTO_ERROR 		0xE1
#define CONNECTION_ERROR	0xE2
#define CREATE_WINDOW_ERROR	0xE3
#define MAP_WINDOW_ERROR	0xE4


#define X_ERROR_TEXT_BUFFER_SIZE 255

void printScreenInfo(Screen* screen);
void printDisplayInfo(Display* display);

int handler(Display* display, XErrorEvent* error);

int main(int argc, char** argv) {

	/* 	Open display based on display name.

		NOTE: NULL defaults to DISPLAY environment variable on POSIX systems.

		Returns a pointer to a Display structure which represents the connection
		to the X server through either TCP, DECnet (what?),or some local IPC
		mechanism.

		If the connection fails then XOpenDisplay returns NULL.
	*/

	// Get a pointer to display (X server connection state)
	Display* display;

	// Handle failure to open a connection.
	if((display = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr,
			"Error: Connection to X server failed.\n");
		return CONNECTION_ERROR;
	}

	// All Xlib macros and functions can be used from here.

	// Set a custom error handler.
	XSetErrorHandler(handler);

	// Get the resource ID of the root window.
	Window root = DefaultRootWindow(display);

	// Get black and white pixel values for screen.
	const unsigned long BLACK = BlackPixel(display, DefaultScreen(display));
	const unsigned long WHITE = WhitePixel(display, DefaultScreen(display));
	
	// Print info about the display to stdout.
	printDisplayInfo(display);

	// Create an simple unmapped top-level window (subwindow of root).
	// The custom error handler will act on protocol errors.
	Window client = XCreateSimpleWindow(display, root,
		0, 0, 800, 600, 1, BLACK, WHITE);	

	// Map the window
	
	
	// Destroy the window
	XDestroyWindow(display, client);
	
	/*	Close connection to X server for specified display.

		NOTE: Destroys all windows, resource IDs, and other resources created by
		the client (this program), unless specified otherwise by a resource's
		close-down mode via XSetCloseDownMode.
	*/
	XCloseDisplay(display);

	return SUCCESS;
}

int handler(Display* display, XErrorEvent* error) {
	// Set an output buffer of a static size.
	char outputBuffer[X_ERROR_TEXT_BUFFER_SIZE];

	// Store error text description into buffer.
	XGetErrorText(display, error->error_code,
		outputBuffer, X_ERROR_TEXT_BUFFER_SIZE);

	// Print error description to stderr.
	fprintf(stderr, "Error: %s\n", outputBuffer);

	// Switch on request opcode to determine program return value.
	switch(error->request_code) {
		case X_CreateWindow:
			exit(CREATE_WINDOW_ERROR);
			break;
		case X_MapWindow:
			exit(MAP_WINDOW_ERROR);
			break;
		default:
			exit(XPROTO_ERROR);
	}
}

void printDisplayInfo(Display* display) {
	// X protocol version
	const int major = ProtocolVersion(display);
	const int minor = ProtocolRevision(display);

	printf("X Protocol Version %d.%d\n\n", major, minor);

	// X server information
	const char* vendor	= ServerVendor(display);
	const int release	= VendorRelease(display);

	printf("Vendor: %s\n", vendor);
	printf("Release: %d\n", release);
	
	// Screen Information
	const int nscreens = ScreenCount(display);
	// Iterate over screens in the display and print info
	for(int i = 0; i < nscreens; i++) {
		Screen* screen = ScreenOfDisplay(display, i);
		printScreenInfo(screen);
	}	
}

void printScreenInfo(Screen* screen) {

	// Return values from the screen struct.
	const int width = WidthOfScreen(screen);
	const int height = HeightOfScreen(screen);
	const int widthmm = WidthMMOfScreen(screen);
	const int heightmm = HeightMMOfScreen(screen);

	const unsigned long black = BlackPixelOfScreen(screen);
	const unsigned long white = WhitePixelOfScreen(screen);

	const int depth = DefaultDepthOfScreen(screen);

	const int backingStore = DoesBackingStore(screen);
	const Bool saveUnders = DoesSaveUnders(screen);

	// Pretty-print them.
	printf("\n====== Screen Information ============\n");

	printf("Dimensions: %dx%d px (%dx%d mm)\n", width, height, widthmm, heightmm);
	
	printf("Black Pixel Value: %lx\n", black);
	printf("White Pixel Value: %lx\n", white);
	printf("Pixel Depth: %d\n", depth);

	switch(backingStore) {
		case WhenMapped:
			printf("Backing Store: When mapped\n");
			break;
		case NotUseful:
			printf("Backing Store: Not useful\n");
			break;
		case Always:
			printf("Backing Store: Always\n");
			break;
		default:
			printf("Backing Store: N/a\n");
	}

	switch(saveUnders) {
		case True:
			printf("Save Unders: True\n");
			break;
		case False:
			printf("Save Unders: False\n");
			break;
		default:
			printf("Save Unders: N/a\n");
	}
}
