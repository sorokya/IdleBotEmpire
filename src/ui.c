#include "ui.h"

Window InitIdleWindow(i32 x, i32 y, i32 w, i32 h)
{
    return (Window){
        x,
        y,
        w,
        h,
        0,
        0,
    };
}

void UpdateWindow(Window *window)
{
    Vector2 mouse = GetMousePosition();
    window->x = mouse.x - (window->w >> 1);
    window->y = mouse.y - (window->h >> 1);
}

void RenderWindow(const Atlas *atlas, const Window *window)
{
    AtlasRenderNinePatch(atlas, ATLAS_WINDOW_HEADER_RESIZABLE_ACTIVE, (Rectangle){(float)window->x, (float)window->y, (float)window->w, (float)window->h});
}