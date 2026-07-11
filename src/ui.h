#ifndef IDLE_UI_H
#define IDLE_UI_H

#include "math.h"
#include "atlas.h"
#include "raylib.h"

typedef u64 UIID;

#define UI_KEY_COUNT 512

typedef struct UIInput
{
    float mouse_x;
    float mouse_y;

    bool mouse_down;
    bool mouse_pressed;
    bool mouse_released;

    i32 wheel;

    bool keys_down[UI_KEY_COUNT];
    bool keys_pressed[UI_KEY_COUNT];

    char chars[32];
    i32 char_count;
} UIInput;

typedef struct UITextState
{
    u32 cursor;

    u32 selection_start;
    u32 selection_end;

    float blink_timer;
} UITextState;

typedef enum UILayout
{
    UI_LAYOUT_VERTICAL,
    UI_LAYOUT_HORIZONTAL,
} UILayout;

typedef struct UIContainer
{
    Rectangle bounds;

    float cursor_x;
    float cursor_y;

    float spacing;
    float padding;

    UILayout layout;
} UIContainer;

typedef struct UIState
{
    Atlas *atlas;

    UIID hot_id;
    UIID active_id;
    UIID focused_id;

    UIInput input;

    UIContainer containers[32];
    i32 container_count;

    UIID id_stack[32];
    i32 id_stack_count;

    UITextState text_state;
} UIState;

void ui_begin(UIState *ui, float x, float y, float width, float height);
void ui_end(UIState *ui);
void ui_push_id(UIState *ui, UIID id);
void ui_pop_id(UIState *ui);
void debug_box(UIState *ui, float w, float h, Color c);

#endif