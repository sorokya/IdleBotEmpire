#ifndef IDLE_H_FONT
#define IDLE_H_FONT

#include "math.h"
#include "atlas.h"

void RenderTextColor(const Atlas *atlas, const char *text, float x, float y, Color color);
void RenderText(const Atlas *atlas, const char *text, float x, float y);

#endif
