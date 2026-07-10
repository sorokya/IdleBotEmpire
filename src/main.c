#include "raylib.h"
#include "config.h"

int main(void)
{
    InitWindow(IDLE_WINDOW_WIDTH, IDLE_WINDOW_HEIGHT, IDLE_GAME_TITLE);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){0, 0x80, 0x80, 0xff});
        EndDrawing();
    }

    CloseWindow();

    return 0;
}