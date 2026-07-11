#include "atlas.h"
#include "atlas_data.h"

static const AtlasSprite atlas_sprites[] = {
    {0, 0, 202, 180, 208, 182, 0, 0, 0, 0}, // sans-11.png

    {208, 179, 15, 15, 15, 15, 5, 5, 5, 5}, // Window_Base.png

    {48, 180, 48, 48, 48, 48, 16, 16, 25, 16},  // Window_Header_Inactive.png
    {144, 180, 48, 48, 48, 48, 16, 16, 25, 16}, // Window_Header_Resizable_Inactive.png
    {96, 180, 48, 48, 48, 48, 16, 16, 25, 16},  // Window_Header_Resizable.png
    {0, 180, 48, 48, 48, 48, 16, 16, 25, 16},   // Window_Header.png

    {208, 209, 15, 15, 15, 15, 5, 4, 4, 5}, // Windows_Button_Focus_Outlined.png
    {208, 194, 15, 15, 15, 15, 5, 5, 5, 5}, // Windows_Button_Focus.png
    {211, 0, 15, 15, 15, 15, 5, 5, 5, 5},   // Windows_Button_Inactive.png
    {211, 30, 15, 15, 15, 15, 4, 5, 5, 4},  // Windows_Button_Pressed_Outlined.png
    {211, 15, 15, 15, 15, 15, 5, 5, 5, 5},  // Windows_Button_Pressed.png
    {208, 179, 15, 15, 15, 15, 5, 5, 5, 5}, // Windows_Button.png

    {202, 179, 1, 2, 1, 2, 1, 1, 2, 2}, // Windows_Divider_Line.png

    {202, 0, 104, 9, 150, 150, 0, 0, 0, 0}, // Windows_Icons.png

    {192, 196, 16, 16, 16, 16, 5, 5, 5, 5}, // Windows_Inner_Frame_Inverted.png
    {192, 180, 16, 16, 16, 16, 5, 5, 5, 5}, // Windows_Inner_Frame.png
    {192, 212, 16, 16, 16, 16, 0, 0, 0, 0}, // Windows_Progress_Fill.png

    {211, 58, 13, 13, 13, 13, 13, 13, 13, 13}, // Windows_Ratio_Inactive.png
    {211, 71, 13, 13, 13, 13, 13, 13, 13, 13}, // Windows_Ratio_Selected.png
    {211, 45, 13, 13, 13, 13, 13, 13, 13, 13}, // Windows_Ratio.png

    {202, 104, 16, 16, 16, 16, 5, 5, 5, 5},     // Windows_SideBar_Underside.png
    {208, 224, 12, 4, 12, 4, 3, 3, 0, 0},       // Windows_Slider_Background.png
    {202, 168, 11, 21, 11, 21, 11, 11, 21, 21}, // Windows_Slider_Handle.png

    {202, 120, 16, 16, 16, 16, 5, 5, 5, 5}, // Windows_Toggle_Active.png
    {202, 136, 16, 16, 16, 16, 5, 5, 5, 5}, // Windows_Toggle_Inactive.png
    {202, 152, 16, 16, 16, 16, 5, 5, 5, 5}, // Windows_Toggle_Selected.png
};

Atlas AtlasInit(void)
{
    Image img = {
        .data = UI_DATA,
        .width = UI_WIDTH,
        .height = UI_HEIGHT,
        .format = UI_FORMAT,
        .mipmaps = 1,
    };

    return (Atlas){
        .texture = LoadTextureFromImage(img),
        .sprites = atlas_sprites,
        .count = sizeof(atlas_sprites) / sizeof(atlas_sprites[0]),
    };
}

void AtlasRenderSprite(const Atlas *atlas, SpriteId id, i32 x, i32 y)
{
    AtlasSprite sprite = atlas->sprites[id];
    Rectangle src = {(float)sprite.x, (float)sprite.y, (float)sprite.w, (float)sprite.h};
    Rectangle dst = {(float)x, (float)y, (float)sprite.originalW, (float)sprite.originalH};
    DrawTexturePro(atlas->texture, src, dst, (Vector2){0, 0}, 0.0f, RAYWHITE);
}

void AtlasRenderNinePatch(const Atlas *atlas, SpriteId id, Rectangle dst)
{
    AtlasSprite sp = atlas->sprites[id];

    float W = dst.width;
    float H = dst.height;

    int l = sp.l, r = sp.r, t = sp.t, b = sp.b;

    // No borders -> draw normally
    if (l == 0 && r == 0 && t == 0 && b == 0)
    {
        Rectangle src = {(float)sp.x, (float)sp.y, (float)sp.w, (float)sp.h};
        DrawTexturePro(atlas->texture, src, dst, (Vector2){0, 0}, 0.0f, RAYWHITE);
        return;
    }

    // Clamp so edges don't exceed destination
    if (W < (float)(l + r))
    {
        float s = W / (float)(l + r);
        l = (int)(l * s);
        r = (int)(r * s);
    }
    if (H < (float)(t + b))
    {
        float s = H / (float)(t + b);
        t = (int)(t * s);
        b = (int)(b * s);
    }

    float midW = W - l - r;
    float midH = H - t - b;

    Rectangle src = {(float)sp.x, (float)sp.y, (float)sp.w, (float)sp.h};

    // Source rectangles (relative to atlas texture)
    Rectangle sTL = {src.x, src.y, (float)l, (float)t};
    Rectangle sTR = {src.x + src.width - (float)r, src.y, (float)r, (float)t};
    Rectangle sBL = {src.x, src.y + src.height - (float)b, (float)l, (float)b};
    Rectangle sBR = {src.x + src.width - (float)r, src.y + src.height - (float)b, (float)r, (float)b};

    Rectangle sTM = {src.x + (float)l, src.y, (float)(src.width - l - r), (float)t};
    Rectangle sBM = {src.x + (float)l, src.y + src.height - (float)b, (float)(src.width - l - r), (float)b};
    Rectangle sLM = {src.x, src.y + (float)t, (float)l, (float)(src.height - t - b)};
    Rectangle sRM = {src.x + src.width - (float)r, src.y + (float)t, (float)r, (float)(src.height - t - b)};
    Rectangle sMM = {src.x + (float)l, src.y + (float)t, (float)(src.width - l - r), (float)(src.height - t - b)};

    // Destination rectangles
    Rectangle dTL = {dst.x, dst.y, (float)l, (float)t};
    Rectangle dTR = {dst.x + W - (float)r, dst.y, (float)r, (float)t};
    Rectangle dBL = {dst.x, dst.y + H - (float)b, (float)l, (float)b};
    Rectangle dBR = {dst.x + W - (float)r, dst.y + H - (float)b, (float)r, (float)b};

    Rectangle dTM = {dst.x + (float)l, dst.y, midW, (float)t};
    Rectangle dBM = {dst.x + (float)l, dst.y + H - (float)b, midW, (float)b};
    Rectangle dLM = {dst.x, dst.y + (float)t, (float)l, midH};
    Rectangle dRM = {dst.x + W - (float)r, dst.y + (float)t, (float)r, midH};
    Rectangle dMM = {dst.x + (float)l, dst.y + (float)t, midW, midH};

    // 9 tiles
    DrawTexturePro(atlas->texture, sTL, dTL, (Vector2){0, 0}, 0.0f, RAYWHITE);
    DrawTexturePro(atlas->texture, sTM, dTM, (Vector2){0, 0}, 0.0f, RAYWHITE);
    DrawTexturePro(atlas->texture, sTR, dTR, (Vector2){0, 0}, 0.0f, RAYWHITE);

    DrawTexturePro(atlas->texture, sLM, dLM, (Vector2){0, 0}, 0.0f, RAYWHITE);
    DrawTexturePro(atlas->texture, sMM, dMM, (Vector2){0, 0}, 0.0f, RAYWHITE);
    DrawTexturePro(atlas->texture, sRM, dRM, (Vector2){0, 0}, 0.0f, RAYWHITE);

    DrawTexturePro(atlas->texture, sBL, dBL, (Vector2){0, 0}, 0.0f, RAYWHITE);
    DrawTexturePro(atlas->texture, sBM, dBM, (Vector2){0, 0}, 0.0f, RAYWHITE);
    DrawTexturePro(atlas->texture, sBR, dBR, (Vector2){0, 0}, 0.0f, RAYWHITE);
}
