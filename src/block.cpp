#include "block.hpp"

Block::Block(Vector2 position){ 
    this->position = position;
}
void Block::Draw(){
    if(active) DrawRectangle(position.x,position.y,3,3,{243,216,63,255});
}

Rectangle Block::GetRect() const {
    return Rectangle{position.x, position.y, 3, 3};
}