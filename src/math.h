#ifndef IDLE_NUMBERS
#define IDLE_NUMBERS

#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"
#include "raylib.h"

#define u8 uint8_t
#define i8 int8_t
#define u16 uint16_t
#define i16 int16_t
#define u32 uint32_t
#define i32 int32_t
#define u64 uint64_t
#define i64 int64_t

static inline bool VecInRect(Vector2 vec, Rectangle rect)
{
    return vec.x >= rect.x &&
           vec.x < rect.x + rect.width &&
           vec.y >= rect.y &&
           vec.y < rect.y + rect.height;
}

static inline Rectangle i32Rect(i32 x, i32 y, i32 w, i32 h)
{
    return (Rectangle){(float)x, (float)y, (float)w, (float)h};
}

/*
static inline bool RectsIntersect(Rect a, Rect b)
{
    return (a.x < b.x + b.w) &&
           (a.x + a.w > b.x) &&
           (a.y < b.y + b.h) &&
           (a.y + a.h > b.y);
}
*/

#endif
