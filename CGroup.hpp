#ifndef GROUP_HPP
#define GROUP_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include <deque>
#include "CSprite.hpp"
#include "interfaz.hpp"

using namespace std;
class Group{
    public :
        Group(Interfaz * parent);
        void add(Sprite *); //A�ade un sprite al grupo
        //void kill(Sprite *,bool del_mem=false);// elimina un sprite del grupo -si existe-
        //bool contain(Sprite *);
        //Sprite * collide(Sprite *); //detecta si un sprite colisiona con uno del grupo en el caso, regresa una referencia de con quien colisiona
        void erase(Sprite *);
        void update(Uint8 * keys=NULL); //llama a los metodos "update" de los Sprites
        void draw(SDL_Surface *); // llama a los metodos "draw" con la superficie pasada
        ~Group();
     
    protected:
        deque <Sprite * > v_personajes;
        Interfaz * parent;

};

#endif
