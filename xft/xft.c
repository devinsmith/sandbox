#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

static void draw_string(XftDraw *drawable, XftColor *color, XftFont *font, int x, int y, const char *str)
{
  XftDrawString8(drawable, color, font, x, y, (XftChar8 *)str, strlen(str));
}

int main(int argc, char *argv[])
{
  XftFont *font;
  XftDraw *draw;
  XRenderColor render_color;
  XftColor xft_color;
  const char *str = "Hello, World! (from Xft)";
  int x = 70;
  int y = 150;

  // Init X
  Display *dis = XOpenDisplay(0);
  int screen = DefaultScreen(dis);
  Window  w = XCreateSimpleWindow(dis, RootWindow(dis, screen),
                                   0, 0, 400, 300, 1,
                                   BlackPixel(dis, screen),
                                   WhitePixel(dis, screen));

  // Init Xft variables.
  render_color.red = 0;
  render_color.green =0;
  render_color.blue = 0;
  render_color.alpha = 0xffff;

  XftColorAllocValue(dis, DefaultVisual(dis, screen),
      DefaultColormap(dis, screen), &render_color, &xft_color);

  // There are two ways to load a font:
  //font = XftFontOpen(dis, screen,
  //                 XFT_FAMILY, XftTypeString, "verdana",
  //                 XFT_SIZE, XftTypeDouble, 20.0,
  //                 NULL);
  //
  // Use Fontconfig patten string.
  font = XftFontOpenName(dis,screen,"DejaVu Serif:style=Italic");

  // Create a drawable
  draw = XftDrawCreate(dis, w, DefaultVisual(dis, screen),
      DefaultColormap(dis, screen));

  XSelectInput(dis, w, ExposureMask);
  XMapWindow(dis, w);

  for (;;) {
    XEvent ev;
    XNextEvent (dis, &ev);
    if (ev.type == Expose) {
      draw_string(draw, &xft_color, font, x, y, str);
    }
  }
  return 0;
}
