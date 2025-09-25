#pragma once
#include "Board.h"
#include <string>

namespace AN {
class Player {
public:
    Player(std::string name = "Jugador");
    std::string name() const;
    Board& board();
    const Board& board() const;
    void setName(const std::string &n);
    void serialize(std::ostream &os) const;
    void deserialize(std::istream &is);
private:
    std::string name_;
    Board board_;
};
}