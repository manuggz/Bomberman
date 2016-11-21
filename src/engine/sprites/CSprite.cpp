#include "CSprite.hpp"
/*
Sprite::Sprite(Sint16 x,Sint16 y):
        rect(x,y){
}*/
/*
void Sprite::add(Group * nu){
    v_grupos.push_back(nu);
    nu->add(this);
}*/

bool Sprite::isMuerto(){
     return self_kill;
}

void Sprite::kill(){
    self_kill=true;
}
bool Sprite::colision(SDL_Rect & rect_coli){       
    return rects_colisionan(rect,rect_coli);
}
