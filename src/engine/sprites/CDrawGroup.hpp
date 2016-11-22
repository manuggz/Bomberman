//
// Created by manuggz on 21/11/16.
//

#ifndef BOMBERMAN_CDRAWGROUP_HPP
#define BOMBERMAN_CDRAWGROUP_HPP

#include "CUpdateGrow.hpp"

class DrawGroup : public UpdateGroup{
public :

    //DrawGroup(InterfazSpriteGroup *parent) : UpdateGroup(parent) {}

    DrawGroup(InterfazSpriteGroup *parent) : UpdateGroup(parent) {}

    void draw(SDL_Renderer * gr){
        for (size_t i=0; i<v_personajes.size(); i++)
            v_personajes[i]->draw(gr);
    }

};


#endif //BOMBERMAN_CDRAWGROUP_HPP
