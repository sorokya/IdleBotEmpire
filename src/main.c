#include "raylib.h"
#include "config.h"
#include "atlas.h"
#include "ui.h"
#include <stdio.h>

static float accumulator = 0.0f;

Atlas atlas;
Window test_window;

void update(float dt)
{
    accumulator += dt;
    while (accumulator > IDLE_STEP)
    {
        UpdateWindow(&test_window);
        accumulator -= IDLE_STEP;
    }
}

void render(void)
{
    BeginDrawing();
    ClearBackground((Color){0, 0x80, 0x80, 0xff});

    RenderWindow(&atlas, &test_window);

    EndDrawing();
}

int main(void)
{
    InitWindow(IDLE_WINDOW_WIDTH, IDLE_WINDOW_HEIGHT, IDLE_GAME_TITLE);

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(20);

    atlas = AtlasInit();
    test_window = InitIdleWindow(10, 10, 400, 400, "Hello World!");

    while (!WindowShouldClose())
    {
        update(GetFrameTime());
        render();
    }

    CloseWindow();

    return 0;
}