This project is an attempt to learn the basics of the X11 window system and the Xlib C library.


# OVERVIEW

## Basic Client Behaviour

### Events
Client programs are informed of events. Events may be generated via a request from the
client, or asynchronously (Like keyboard or mouse input). Other clients can send events
to a given client. 

Clients must ask to be informed of certain types of events. A client must be prepared to
handle events.

Input events are recieved asynchronously from the X server and are stored in a queue
until they are requested by an explicit call by the client (e.g. XNextEvent,
XWindowEvent).

Some calls to library functiosn can generate Expose and ConfigureRequest events which
also arrive asynchronously. A client can wait for these events by a call to XSync after
calling a function which causes the server to generate events.


### Creating a Client
A basic X client must open a connection to the X server via a call to XOpenDisplay.
From this point Xlib macros and functions can be called.


### Window Creation Without Toolkits
A top-level window being created directly using Xlib must follow a set of rules to allow
applications to interact in a reasonable way across different styles of window
management. (See Xlib - C Language X Interface, Section 3.3)

- Never fight with the window manager for the size or placement of a top-level
window.

- You must be able to deal with whatever size window is given. In the case of a window
which is too small, the application must handle this (A message could be sent to stdout).

- Top-level windows should only resize or move in direct response to user input.

- Top-level windows created without a toolkit that sets standard window properties
automatically should set these properties manually before mapping.

(See Xlib - C Language X Interface, Chapter 14 for information on ICCCM)

XCreateWindow creates a window with specific attributes. XCreateSimpleWindow creates a
window which inherits its attributes from it's parent window.



## Important Terminology (See Xlib - C Language X Interface, Glossary)

### Client
An application program that connects to the window system server via some IPC path.
This could be TCP or a shared memory buffer. This type of program is referred to as a
client of the window system server. More precisely, the client is the IPC path itself.
A single program with multiple paths to a server would be interpreted as multiple clients
by the X protocol. Resource lifetimes are controlled by connection lifetimes, not by the
program lifetimes. A program may still persist after a call to XCloseDisplay, but the
client (connection) will not.

### Server
The server, which is also referred to as the X server, provides the basic windowing
mechanism. It handles IPC connections from clients, multiplexes graphics requests onto
the screens, and demultiplexes input back to the appropriate clients.

### Display
A server, together with it's screens and input devices, is called a display. The Xlib
Display structure represents the state of the connection and holds information about
the display and associated screens.

### Screen
A server can provide several independent screens, which typically have physically
independent monitors. This would be the expected configuration when there is only a
single keyboard and pointer shared among the screens. An Xlib Screen structure contains
the information about that screen and is linked to the Display structure.



### Event
Clients are informated of information asynchronously via events. Events can be generated
asynchronously from devices or generated as side effects of client requrests. Events
are group into types. The server doesn't send an event to a client unless the client
explicitly asks to be informed of that specific type of event. Clients can force events
to be sent to other clients. Events are typically reported relative to a window.

### Event Mask
Events are requested relative to a window. The set of event types which a client requests
relative to a window is described by an event mask.

### Event propagation
Device-related events propagate from the source window to ancestor windows until some
client has expressed interest in handling that type of event or until the event is
disgarded explicitly.

### Event source
The deepest viewable window that the pointer is in is called the source of a device-
related event.

### Event synchronization
Demultiplexing device events to clients are capable of causing race conditions. Event
synchronization mechanisms allow events to be processed synchronously.

### Expose event
Servers do not guarantee to preserve the contents of windows when windows are obscured
or reconfigured. Exposure events are sent to clients to inform them when contents of
regions of windows have been lost.



### Parent window
If C is a child of P, then P is the parent of C.

### Children
The children of a window are its first-level subwindows.

### Inferiors
The subwindows of a given window. Includes children and children of children and so-on.

### Sibling
Children of the same parent window are known as sibling windows.

### Root window
Each screen has a root window covering it. The root window cannot be reconfigured or un-
mapped, but otherwise it acts as a full-fledged window. A root window has no parent.

### Top-level windows
Direct children of the root window. Most likely to be an application.


### Reply
Information requested by a client using the X protocol is sent back to the client with a
reply. Events and replies are multiplexed on the same connection. Most requests do not
generate replies, but some requests generate multiple replies.

### Request
A command to the X server is called a request. It is a single block of data sent over a
connection.

### Resource
Windows, pixmaps, cursors, fonts, graphics contexts, and colourmaps are known as
resources. They all have a unique integer identifier. The lifetime of a resource is
bounded by the lifetime of the coinnection over which the resource was created.
