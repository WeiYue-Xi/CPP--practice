//
// Created by 24242 on 2026/10/21.
//

#include "Score.h"

Score& Score::operator=(const Score& other)
{
    if (this == &other)
        return *this;
    value = other.value;

    return *this;
}
