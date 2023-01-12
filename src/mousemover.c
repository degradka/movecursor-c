#include "mousemover.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xinerama.h>
#include <stdio.h>
#include <stdlib.h>

void moveMouseTo(int monitorNum, int x, int y) {
    Display *dpy;
    dpy = XOpenDisplay(NULL);

    if(dpy == NULL) {
        printf("Cannot open display\n");
        return;
    }

    int event_base, error_base;
    if (!XineramaQueryExtension(dpy, &event_base, &error_base)) {
        printf("Error: Xinerama extension not available\n");
        return;
    }

    int numScreens;
    XineramaScreenInfo *screens = XineramaQueryScreens(dpy, &numScreens);
    if (monitorNum < 0 || monitorNum >= numScreens) {
        printf("Error: Invalid monitor number\n");
        return;
    }

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, screens[monitorNum].x_org + x, screens[monitorNum].y_org + y);
    XFlush(dpy);
    XCloseDisplay(dpy);
    XFree(screens);
}
