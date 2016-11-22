#ifndef BOMBA_HPP
#define BOMBA_HPP
#include <SDL2/SDL.h>
#include "../engine/sprites/animacion/animacion.hpp"
#include "../constantes.hpp"

class Bomba:public Animacion{
public:

    Bomba(SpriteSheet *spriteSheet,int x,int y,int alcance,int lanzador,int id):
            Animacion(spriteSheet,"0,0,0,1,1,1,2,2,2,2,2,2,1,1,1,0,0,0",x,y,id){
        this->lanzador=lanzador;
        this->alcance= (Uint8) alcance;
        //type=BOMBA;
        mRepeticiones=2;
    }

    int getLanzador(){return lanzador;};
    int getAlcance(){return alcance;};
    void setRepeticion(int nuevo){mRepeticiones=nuevo;};
private:
    Uint8 alcance;//alcance de la bomba en los ejes
    int lanzador;
//        bool estaMoviendose
};

#endif
