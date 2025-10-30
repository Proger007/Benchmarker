//
// Created by root on 5/10/25.
//

#include "board.h"

#include <cstdint>

auto FCACHEE {reinterpret_cast<uint32_t*>(0x04001C100)};
auto FCACHEIV {reinterpret_cast<uint32_t*>(0x04001C104)};
auto FLWT {reinterpret_cast<uint32_t*>(0x04001C11C)};
auto CCACTL {reinterpret_cast<uint32_t*>(0x040007000)};
auto SCACTL {reinterpret_cast<uint32_t*>(0x040007040)};

void board::init()
{
    *FLWT = 1;
}


void board::disableCache()
{
    *CCACTL = 0U;
    *SCACTL = 0U;
    *FCACHEE = 0U;
}

void board::enableCache()
{
    *FCACHEIV = 1U;
    while (*FCACHEIV != 0U) {}
    *FCACHEE = 1U;

    *CCACTL = 0x1;
    // *SCACTL = 0x1;
}