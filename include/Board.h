#pragma once
#include "Types.h"
#include <vector>
#include <string>
#include <optional>
#include <iostream>

namespace AN {
class Board {
public:
    Board(int w = 10, int h = 10);
    void reset();
    bool placeShip(const Point &start, const Point &end);
    bool receiveShot(const Point &p);
    bool allShipsSunk() const;
    int width() const;
    int height() const;
    const std::vector<uint8_t>& raw() const;
    void serialize(std::ostream &os) const;
    void deserialize(std::istream &is);
private:
    int w_, h_;
    std::vector<uint8_t> cells_;
    int shipsRemaining_;
};
}