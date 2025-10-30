//
// Created by root on 5/10/25.
//

#include "board.h"

#include <cstdint>

auto ICACHECNF {reinterpret_cast<uint32_t*>(0x4001E540)};

void board::init()
{

}

void board::disableCache()
{
    *ICACHECNF = 0;
}

void board::enableCache()
{
    *ICACHECNF = 1;
}
