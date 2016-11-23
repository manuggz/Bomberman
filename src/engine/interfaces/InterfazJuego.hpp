//
// Created by manuggz on 22/11/16.
//

#ifndef BOMBERMAN_INTERFAZGALERIA_HPP
#define BOMBERMAN_INTERFAZGALERIA_HPP

//#include "../util/LTexture.hpp"
//#include "../../constantes.hpp"

//class LTexture;
///enum CodeImagen;

class Bomba;

class InterfazJuego{

public:
    virtual LTexture * getImagen(CodeImagen code) = 0;
    virtual SDL_Joystick * getJoy(int id) = 0;
    virtual int getJoysActivos()=0;
    virtual int colision(SDL_Rect  rect_coli,int * lado_colision,bool solo_bloques_duros)= 0;
    virtual Bomba * colisionConBombas(SDL_Rect  rect) = 0;
    virtual bool isOutOfMapBounds(SDL_Rect  rect) = 0;
};
#endif //BOMBERMAN_INTERFAZGALERIA_HPP
