#include "ui.h"
#include "font.h"
#include "inttypes.h"
#include "stdio.h"

UIContainer *ui_current_container(UIState *ui)
{
    return &ui->containers[ui->container_count - 1];
}

void ui_update_input(UIState *ui)
{
    UIInput *input = &ui->input;

    Vector2 mouse = GetMousePosition();

    input->mouse_x = mouse.x;
    input->mouse_y = mouse.y;

    input->mouse_down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    input->mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    input->mouse_released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    input->wheel = (i32)GetMouseWheelMove();

    for (int key = 0; key < UI_KEY_COUNT; key++)
    {
        input->keys_down[key] = IsKeyDown(key);
        input->keys_pressed[key] = IsKeyPressed(key);
    }

    input->char_count = 0;

    i32 c;
    while ((c = GetCharPressed()) != 0)
    {
        if (input->char_count < 32)
            input->chars[input->char_count++] = c;
    }
}

void ui_begin(UIState *ui, float x, float y, float width, float height)
{
    UIContainer *c = &ui->containers[ui->container_count++];

    c->bounds = (Rectangle){x, y, width, height};

    c->cursor_x = x;
    c->cursor_y = y;

    c->spacing = 4;

    c->layout = UI_LAYOUT_VERTICAL;
}

void ui_end(UIState *ui)
{
    if (ui->container_count <= 0)
        return;

    ui->container_count--;
}

void ui_push_id(UIState *ui, UIID id)
{
    if (ui->id_stack_count > 32)
        return;

    ui->id_stack[ui->id_stack_count++] = id;
}

void ui_pop_id(UIState *ui)
{
    if (ui->id_stack_count <= 0)
        return;

    ui->id_stack[ui->id_stack_count--] = 0;
}

#define UI_FNV_OFFSET 14695981039346656037ULL
#define UI_FNV_PRIME 1099511628211ULL

UIID ui_hash_bytes(UIID seed, const void *data, size_t size)
{
    const u8 *bytes = data;

    UIID hash = seed;

    for (size_t i = 0; i < size; i++)
    {
        hash ^= bytes[i];
        hash *= UI_FNV_PRIME;
    }

    return hash;
}

UIID ui_hash_string(const char *str)
{
    UIID hash = UI_FNV_OFFSET;

    while (*str)
    {
        hash ^= (u8)*str++;
        hash *= UI_FNV_PRIME;
    }

    return hash;
}

UIID ui_hash_combine(UIID a, UIID b)
{
    return ui_hash_bytes(a, &b, sizeof(b));
}

UIID ui_make_id(UIState *ui, const char *label)
{
    UIID id = ui_hash_string(label);

    for (int i = 0; i < ui->id_stack_count; i++)
    {
        id = ui_hash_combine(ui->id_stack[i], id);
    }

    return id;
}

Rectangle ui_next_rect(UIState *ui, float w, float h)
{
    UIContainer *c = ui_current_container(ui);

    Rectangle result = {
        c->cursor_x,
        c->cursor_y,
        w,
        h};

    if (c->layout == UI_LAYOUT_VERTICAL)
    {
        c->cursor_y += h + c->spacing;
    }
    else
    {
        c->cursor_x += w + c->spacing;
    }

    return result;
}

void ui_push_container(UIState *ui, UILayout layout)
{
    UIContainer *parent = ui_current_container(ui);

    UIContainer *child = &ui->containers[ui->container_count++];

    child->bounds = parent->bounds;
    child->cursor_x = parent->cursor_x;
    child->cursor_y = parent->cursor_y;
    child->spacing = parent->spacing;
    child->layout = layout;
}

void debug_box(UIState *ui, float w, float h, Color c)
{
    Rectangle r = ui_next_rect(ui, w, h);

    UIID id = ui_make_id(ui, "DEBUG");
    id = ui_hash_combine(id, ColorToInt(c));

    DrawRectangle(
        r.x,
        r.y,
        r.width,
        r.height,
        c);

    char str[32];

    snprintf(str, sizeof(str), "%" PRIx64, id);

    RenderText(ui->atlas, str, r.x + 10, r.y + 10);
}

UIWindowState *ui_get_window_state(UIState *ui, UIID id, float default_w, float default_h)
{
    for (int i = 0; i < ui->window_count; i++)
    {
        if (ui->windows[i].id == id)
            return &ui->windows[i];
    }

    Rectangle bounds = ui_next_rect(ui, default_w, default_h);

    ui->windows[ui->window_count++] = (UIWindowState){
        .id = id,
        .bounds = bounds,
        .active = true,
        .dragging = false,
        .drag_start = (Vector2){0.0, 0.0},
    };

    return &ui->windows[ui->window_count - 1];
}

void ui_begin_window(UIState *ui, float w, float h, const char *title)
{
    UIID id = ui_make_id(ui, "window");
    id = ui_hash_combine(id, ui_hash_string(title));

    ui_push_id(ui, id);

    UIWindowState *win = ui_get_window_state(ui, id, w, h);

    bool hovered = XYInRect(ui->input.mouse_x, ui->input.mouse_y, win->bounds);
    if (hovered && ui->input.mouse_pressed)
    {
        for (int i = 0; i < ui->window_count; i++)
        {
            ui->windows[i].active = false;
        }

        win->active = true;

        if (!win->dragging && ui->input.mouse_y < win->bounds.y + UI_WINDOW_TITLE_HEIGHT)
        {
            win->dragging = true;
            win->drag_start.x = ui->input.mouse_x;
            win->drag_start.y = ui->input.mouse_y;
        }
    }

    if (win->dragging)
    {
        if (ui->input.mouse_released)
        {
            win->dragging = false;
            ui->active_id = 0;
        }
        else
        {
            win->bounds.x = win->bounds.x - (win->drag_start.x - ui->input.mouse_x);
            win->bounds.y = win->bounds.y - (win->drag_start.y - ui->input.mouse_y);
            win->drag_start.x = ui->input.mouse_x;
            win->drag_start.y = ui->input.mouse_y;
        }
    }

    AtlasRenderNinePatch(ui->atlas, ATLAS_WINDOW_HEADER_RESIZABLE_ACTIVE, win->bounds);
    RenderText(ui->atlas, title, win->bounds.x + 10, win->bounds.y + 10);
}

void ui_end_window(UIState *ui)
{
    ui_pop_id(ui);
}
