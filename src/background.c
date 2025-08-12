#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Display *display;
    Window window;
    GC gc;
    XEvent event;
    int screen;

    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                 10, 10, 640, 480, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XStoreName(display, window, "Background");
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, NULL);
    XSetForeground(display, gc, BlackPixel(display, screen));

    while (1)
    {
        XNextEvent(display, &event);
        XDrawString(display, window, gc, 50, 30, "Hello World", 11);

    }

    XFreeGC(display, gc);
    XCloseDisplay(display);

    return 0;
}
