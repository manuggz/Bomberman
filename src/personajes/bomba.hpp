#ifndef BOMBA_HPP
#define BOMBA_HPP
#include <SDL2/SDL.h>
#include "../engine/sprites/animacion/animacion.hpp"
#include "../util/constantes.hpp"
#include "player.hpp"

class Bomba:public Animacion{
public:

    Bomba(SDL_Renderer * gRenderer,Player * propietario):
            Animacion(new SpriteSheet(gRenderer,"data/imagenes/objetos/bomba.bmp",1,3,true),
                      "0,0,0,1,1,1,2,2,2,2,2,2,1,1,1,0,0,0"){

        mPlayerPropietario = propietario;
        //this->alcance= (Uint8) alcance;
        //type=BOMBA;
        mRepeticiones=2;
    }

    Player * getPlayerPropietario(){return mPlayerPropietario;};
    void setRepeticion(int nuevo){mRepeticiones=nuevo;};
private:
    Player * mPlayerPropietario;
    //Uint8 alcance;//alcance de la bomba en los ejes
    //int lanzador;
//        bool estaMoviendose
};

#endif
