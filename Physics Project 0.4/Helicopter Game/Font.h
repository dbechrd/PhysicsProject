#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>

extern float score;
void makeRasterFont(void);
void init(void);
void printString(const char *s);

#endif // FONT_H_INCLUDED
