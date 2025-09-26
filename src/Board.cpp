#include "Board.h"
#include <algorithm>
using namespace AN;

Board::Board(int w, int h) : w_(w), h_(h), cells_(w*h, (uint8_t)Cell::Empty), shipsRemaining_(0) {}
void Board::reset(){ std::fill(cells_.begin(), cells_.end(), (uint8_t)Cell::Empty); shipsRemaining_=0; }
bool Board::placeShip(const Point &s, const Point &e){
    if(s.x!=e.x && s.y!=e.y) return false;
    int dx=(e.x-s.x)==0?0:((e.x-s.x)>0?1:-1);
    int dy=(e.y-s.y)==0?0:((e.y-s.y)>0?1:-1);
    int len=std::max(abs(e.x-s.x),abs(e.y-s.y))+1;
    int x=s.x,y=s.y;
    for(int i=0;i<len;i++){ if(cells_[y*w_+x]!=(uint8_t)Cell::Empty) return false; x+=dx; y+=dy; }
    x=s.x; y=s.y;
    for(int i=0;i<len;i++){ cells_[y*w_+x]=(uint8_t)Cell::Ship; x+=dx; y+=dy; }
    shipsRemaining_++; return true;
}
bool Board::receiveShot(const Point &p){
    if(p.x<0||p.x>=w_||p.y<0||p.y>=h_) return false;
    uint8_t &c=cells_[p.y*w_+p.x];
    if(c==(uint8_t)Cell::Ship){ c=(uint8_t)Cell::Hit; return true; }
    if(c==(uint8_t)Cell::Empty){ c=(uint8_t)Cell::Miss; return false; }
    return false;
}
bool Board::allShipsSunk() const{ for(auto v:cells_) if(v==(uint8_t)Cell::Ship) return false; return true; }
int Board::width() const{return w_;} int Board::height() const{return h_;}
const std::vector<uint8_t>& Board::raw() const{return cells_;}
void Board::serialize(std::ostream &os) const{
    os.write((char*)&w_,sizeof(w_)); os.write((char*)&h_,sizeof(h_));
    size_t sz=cells_.size(); os.write((char*)&sz,sizeof(sz));
    if(sz) os.write((char*)cells_.data(),sz); os.write((char*)&shipsRemaining_,sizeof(shipsRemaining_));
}
void Board::deserialize(std::istream &is){
    size_t sz=0; is.read((char*)&w_,sizeof(w_)); is.read((char*)&h_,sizeof(h_));
    is.read((char*)&sz,sizeof(sz)); cells_.assign(sz,0);
    if(sz) is.read((char*)cells_.data(),sz); is.read((char*)&shipsRemaining_,sizeof(shipsRemaining_));
}