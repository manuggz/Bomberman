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
class Player;
class Bloque;
class InterfazJuego{

public:
    virtual LTexture * getImagen(CodeImagen code) = 0;
    virtual SDL_Joystick * getJoy(int id) = 0;
    virtual int getJoysActivos()=0;
    virtual int colisionConMapa(SDL_Rect rect_coli, int *lado_colision = nullptr, bool solo_bloques_duros=false)= 0;

    virtual deque<Sprite *> colisionConBombas(SDL_Rect  rect) = 0;
    virtual deque<Sprite *> colisionBloqueEnLlamas(SDL_Rect  rect) = 0;
    virtual deque<Sprite *> colisionConItems(SDL_Rect  rect) = 0;

    virtual bool isOutOfMapBounds(SDL_Rect  rect) = 0;

    virtual Bomba * agregarBomba(Player *playerPropietario)= 0 ;

    virtual Bloque * agregarBloqueEnLlamas(int x, int y)= 0 ;

    virtual bool esBloqueSolido(int x, int y) = 0;
    virtual bool esBloqueRompible(int x, int y) = 0;
};
#endif //BOMBERMAN_INTERFAZGALERIA_HPP
