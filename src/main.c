#include "raylib.h"
#include "config.h"
#include "atlas.h"
#include "ui.h"
#include <stdio.h>

static float accumulator = 0.0f;

Atlas atlas;
UIState ui;

void update(float dt)
{
    accumulator += dt;
    while (accumulator > IDLE_STEP)
    {
        accumulator -= IDLE_STEP;
    }
}

void render(void)
{
    BeginDrawing();
    ClearBackground((Color){0, 0x80, 0x80, 0xff});

    ui_update_input(&ui);
    ui_begin(&ui, 0, 0, IDLE_WINDOW_WIDTH, IDLE_WINDOW_HEIGHT);

    ui_begin_window(&ui, 800, 600, "Test Window");
    ui_end_window(&ui);

    ui_end(&ui);

    EndDrawing();
}

int main(void)
{
    InitWindow(IDLE_WINDOW_WIDTH, IDLE_WINDOW_HEIGHT, IDLE_GAME_TITLE);

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(20);

    atlas = AtlasInit();
    ui = (UIState){0};
    ui.atlas = &atlas;

    while (!WindowShouldClose())
    {
        update(GetFrameTime());
        render();
    }

    CloseWindow();

    return 0;
}