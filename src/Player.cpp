#include "Player.h"
using namespace AN;
Player::Player(std::string name): name_(std::move(name)), board_() {}
std::string Player::name() const{return name_;}
Board& Player::board(){return board_;}
const Board& Player::board() const{return board_;}
void Player::setName(const std::string &n){name_=n;}
void Player::serialize(std::ostream &os) const{
    size_t len=name_.size(); os.write((char*)&len,sizeof(len));
    if(len) os.write(name_.data(),len); board_.serialize(os);
}
void Player::deserialize(std::istream &is){
    size_t len=0; is.read((char*)&len,sizeof(len));
    name_.assign(len,'\0'); if(len) is.read(&name_[0],len); board_.deserialize(is);
}