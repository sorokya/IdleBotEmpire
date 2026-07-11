#ifndef IDLE_WINDOW_H
#define IDLE_WINDOW_H

#include "math.h"
#include "atlas.h"

typedef struct Window
{
    i32 x, y, w, h;
    bool active;
    bool resizable;
} Window;

Window InitIdleWindow(i32 x, i32 y, i32 w, i32 h);

void UpdateWindow(Window *window);
void RenderWindow(const Atlas *atlas, const Window *window);

#endif