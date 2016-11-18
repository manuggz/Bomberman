#ifndef BOMBA_HPP
#define BOMBA_HPP
#include <SDL2/SDL.h>
#include "animacion.hpp"
#include "constantes.hpp"

class Bomba:public Animacion{
    public:

        Bomba(SDL_Surface *imgBomba,int x,int y,int alcance,int lanzador,int id);
        int getLanzador(){return lanzador;};
        int getAlcance(){return alcance;};
        void setRepeticion(int nuevo){loop=nuevo;};
    private:
        Uint8 alcance;//alcance de la bomba en los ejes
        int lanzador;
//        bool estaMoviendose
};

#endif
