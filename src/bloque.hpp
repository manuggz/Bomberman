#ifndef BLOQUE_HPP
#define BLOQUE_HPP
#include <SDL2/SDL.h>
#include "animacion.hpp"
#include "constantes.hpp"
#include "juego.hpp"

class Juego;

class Bloque:public Animacion{
    public:
        Bloque(Juego * juego,int x,int y,int id);
        void disable();
        void draw(SDL_Renderer * gRenderer);
    private:
        Juego * juego;
        int idTileBloque;
};

#endif
