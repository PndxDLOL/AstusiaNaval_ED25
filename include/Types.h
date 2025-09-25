#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

namespace AN{
    enum class Cell : uint8_t { Empty = 0, Ship = 1, Hit = 2, Miss = 3 };
    struct Point { int x; int y; };
}