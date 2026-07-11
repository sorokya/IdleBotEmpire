#ifndef IDLE_ATLAS_H
#define IDLE_ATLAS_H

#include "raylib.h"
#include "math.h"

typedef struct AtlasSprite
{
    i32 x, y, w, h;
    i32 originalW, originalH;
    // Borders for 9patch
    i32 l, r, t, b;
} AtlasSprite;

typedef struct Atlas
{
    Texture2D texture;
    const AtlasSprite *sprites;
    size_t count;
} Atlas;

typedef enum SpriteId
{
    ATLAS_SANS_11,
    ATLAS_WINDOW_BASE,
    ATLAS_WINDOW_HEADER_INACTIVE,
    ATLAS_WINDOW_HEADER_RESIZABLE_INACTIVE,
    ATLAS_WINDOW_HEADER_RESIZABLE_ACTIVE,
    ATLAS_WINDOW_HEADER_ACTIVE,
    ATLAS_BUTTON_FOCUS_OUTLINED,
    ATLAS_BUTTON_FOCUS,
    ATLAS_BUTTON_INACTIVE,
    ATLAS_BUTTON_PRESSED_OUTLINED,
    ATLAS_BUTTON_PRESSED,
    ATLAS_BUTTON,
    ATLAS_DIVIDER_LINE,
    ATLAS_ICONS,
    ATLAS_INNER_FRAME_INVERTED,
    ATLAS_INNER_FRAME,
    ATLAS_PROGRESS_FILL,
    ATLAS_RADIO_INACTIVE,
    ATLAS_RADIO_SELECTED,
    ATLAS_RADIO,
    ATLAS_SIDEBAR_UNDERSIDE,
    ATLAS_SLIDER_BACKGROUND,
    ATLAS_SLIDER_HANDLE,
    ATLAS_TOGGLE_ACTIVE,
    ATLAS_TOGGLE_INACTIVE,
    ATLAS_TOGGLE_SELECTED,
} SpriteId;

Atlas AtlasInit(void);

void AtlasRenderSprite(const Atlas *atlas, SpriteId id, i32 x, i32 y);
void AtlasRenderNinePatch(const Atlas *atlas, SpriteId id, Rectangle rect);

#endif