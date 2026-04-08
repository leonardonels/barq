#pragma once
#include <cstdint>

struct __attribute__((packed)) BARQPoint {
    float    x;
    float    y;
    float    z;
    float    intensity;   // promoted from uint8_t on write
    uint16_t ring;
    double   timestamp;
};  // 26 bytes

struct __attribute__((packed)) BARQFrameHeader {
    uint32_t width;       // number of valid points
    uint32_t height;      // always 1
    uint32_t point_step;  // always sizeof(BARQPoint) = 26
    double   timestamp;   // frame start timestamp (seconds)
};  // 20 bytes