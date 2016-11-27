#ifndef BLOQUE_HPP
#define BLOQUE_HPP
#include <SDL2/SDL.h>
#include "../sprites/animacion/animacion.hpp"
#include "../../util/constantes.hpp"
#include "../../Interfaces/juego/juego.hpp"

class Juego;

class TileEnLlamas:public Animacion{
public:
    TileEnLlamas(SpriteSheet *spriteSheet, string frames, int x, int y, int delayCambioFrame);

//TileEnLlamas();
    //void disable();
    //void draw(SDL_Renderer * gRenderer);
    //void setAnimacion(SpriteSheet *pSheet, map<string, string> *pAnimacion);

private:
        //Juego * juego;
        //int idTileBloque;
};

#endif
