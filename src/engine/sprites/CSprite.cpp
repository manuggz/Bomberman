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

bool Sprite::isKilled(){
     return mSelfKill;
}

void Sprite::kill(){

    mSelfKill=true;

    for(auto const& grupo: v_grupos) {
        grupo->erase(this);
    }

}
bool Sprite::colision(SDL_Rect & rect_coli){       
    return rects_colisionan(rect,rect_coli);
}

void Sprite::addGroup(SpriteContainer *pGroup) {
    v_grupos.push_back(pGroup);
}
