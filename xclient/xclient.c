#include <stdio.h>

#include <X11/Xlib.h>

// Basic macros
#define SUCCESS 0
#define FAILURE 1

#define X_SERVER_CONNECTION_ERROR 0xF0

int main(int argc, char** argv) {

	/* 	Open display based on display name.

		NOTE: NULL defaults to DISPLAY environment variable on POSIX systems.

		Returns a pointer to a Display structure which represents the connection
		to the X server through either TCP, DECnet (what?), or some local IPC.
		
		If the connection fails then XOpenDisplay returns NULL.
	*/

	// Get a pointer to display (X server connection state)
	Display* display;

	// Handle failure to open a connection	
	if((display = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr,
			"Error: Connection to X server failed.\n");
			
		return X_SERVER_CONNECTION_ERROR;
	}

	// All Xlib macros and functions can be used from here.

	// Print protocol version
	const int major = ProtocolVersion(display);
	const int minor = ProtocolRevision(display);
	
	printf("X Protocol Version %d.%d\n", major, minor);


	/*	Close connection to X server for specified display.

		NOTE: Destroys all windows, resource IDs, and other resources created by
		the client (this program), unless specified otherwise by a resource's
		close-down mode via XSetCloseDownMode.
	*/

	XCloseDisplay(display);

	return SUCCESS;
}
