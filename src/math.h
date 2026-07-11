#ifndef IDLE_NUMBERS
#define IDLE_NUMBERS

#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"

#define u8 uint8_t
#define i8 int8_t
#define u16 uint16_t
#define i16 int16_t
#define u32 uint32_t
#define i32 int32_t
#define u64 uint64_t
#define i64 int64_t

/*
static inline bool Vec2InRect(Vec2 vec, Rect rect)
{
    return vec.x >= rect.x &&
           vec.x < rect.x + rect.w &&
           vec.y >= rect.y &&
           vec.y < rect.y + rect.h;
}

static inline bool RectsIntersect(Rect a, Rect b)
{
    return (a.x < b.x + b.w) &&
           (a.x + a.w > b.x) &&
           (a.y < b.y + b.h) &&
           (a.y + a.h > b.y);
}
*/

#endif
