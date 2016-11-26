/**
 * @file InterfazJuego.hpp
 * @author manuelggonzalezm@gmail.com
 * @date 26/11/2017
 */

#ifndef BOMBERMAN_INTERFAZGALERIA_HPP
#define BOMBERMAN_INTERFAZGALERIA_HPP

#include "../../niveles/NivelMapa.hpp"

class Bomba;
class Player;
class Bloque;

/**
 * Esta clase contiene las funciones que un
 */
class InterfazJuego{

public:

    virtual LTexture * getImagen(CodeImagen code) = 0;
    virtual SDL_Joystick * getJoy(int id) = 0;
    virtual int getJoysActivos()=0;
    virtual NivelMapa::ExtremoColision colisionConMapa(SDL_Rect rect_coli,
                                                       int *lado_colision = nullptr,
                                                       bool soloBloquesNoTraspasables = false)= 0;

    virtual deque<Sprite *> colisionConBombas(SDL_Rect  rect) = 0;
    virtual deque<Sprite *> colisionBloqueEnLlamas(SDL_Rect  rect) = 0;
    virtual deque<Sprite *> colisionConItems(SDL_Rect  rect) = 0;
    virtual deque<Sprite *> colisionConExplosiones(SDL_Rect  rect) = 0;

    virtual bool isOutOfMapBounds(SDL_Rect  rect) = 0;

    virtual Bomba * agregarBomba(Player *playerPropietario)= 0 ;

    virtual Bloque * agregarBloqueEnLlamas(int x, int y)= 0 ;

    virtual bool esBloqueSolido(int x, int y) = 0;
    virtual bool esBloqueRompible(int x, int y) = 0;
    virtual void playerMuerto(Player *pPlayer, Sprite *pPlayerCausante)=0;
};
#endif //BOMBERMAN_INTERFAZGALERIA_HPP
