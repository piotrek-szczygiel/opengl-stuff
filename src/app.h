#pragma once

#include <stdint.h>

struct App {
    void init();
    void deinit();
    void frame();

    uint32_t buffer;
    uint32_t shader;
};
