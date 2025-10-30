//
// Created by root on 5/10/25.
//

#include "board.h"

#include <cstdint>

auto ICACHE_S_ENABLE {reinterpret_cast<uint32_t*>(0xE0082404)};

void board::init()
{

}

void board::disableCache()
{
    *ICACHE_S_ENABLE = 0;
}

void board::enableCache()
{
    *ICACHE_S_ENABLE = 1;
}
