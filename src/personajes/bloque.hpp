#ifndef BLOQUE_HPP
#define BLOQUE_HPP
#include <SDL2/SDL.h>
#include "../engine/sprites/animacion/animacion.hpp"
#include "../constantes.hpp"
#include "../Interfaces/juego/juego.hpp"

class Juego;

class Bloque:public Animacion{
public:
    Bloque(SpriteSheet *spriteSheet, string frames, int x, int y, int delayCambioFrame);

//Bloque();
    //void disable();
    //void draw(SDL_Renderer * gRenderer);
    //void setAnimacion(SpriteSheet *pSheet, map<string, string> *pAnimacion);

private:
        //Juego * juego;
        //int idTileBloque;
};

#endif
