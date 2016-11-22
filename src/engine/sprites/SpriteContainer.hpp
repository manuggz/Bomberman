//
// Created by manuggz on 22/11/16.
//

#ifndef BOMBERMAN_CONTAINER_HPP
#define BOMBERMAN_CONTAINER_HPP

class Sprite;
class SpriteContainer{
public:
    virtual void add(Sprite *)=0; //A�ade un sprite al grupo
    //bool contain(Sprite *);
    //Sprite * collide(Sprite *); //detecta si un sprite colisiona con uno del grupo en el caso, regresa una referencia de con quien colisiona
    virtual void erase(Sprite *) = 0;
};
#endif //BOMBERMAN_CONTAINER_HPP
