#ifndef GROUP_HPP
#define GROUP_HPP
#include <SDL2/SDL.h>
#include <deque>
#include "CSprite.hpp"
#include "SpriteContainer.hpp"

class Group: public SpriteContainer{
    public :
        void add(Sprite *); //A�ade un sprite al grupo
        //bool contain(Sprite *);
        //Sprite * collide(Sprite *); //detecta si un sprite colisiona con uno del grupo en el caso, regresa una referencia de con quien colisiona
        void erase(Sprite *);
        void kill(Sprite *);// elimina un sprite del grupo -si existe-
        //void update(const Uint8 *keys= nullptr); //llama a los metodos "update" de los Sprites
        //void draw(SDL_Renderer *); // llama a los metodos "draw" con la superficie pasada
        ~Group();
     
    protected:
        std::deque <Sprite * > v_personajes;

};

#endif
