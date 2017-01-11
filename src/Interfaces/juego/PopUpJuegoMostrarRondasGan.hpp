#ifndef JUEGOMOSTRARGANADAS_HPP
#define JUEGOMOSTRARGANADAS_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include "../../engine/sprites/animacion/animacion.hpp"
#include "../../engine/interfaces/GameManagerPopUpInterfaz.hpp"
#include "../../engine/interfaces/PopUpInterfaz.hpp"
#include "../../util/constantes.hpp"


/**
 * Popup que muestra el numero de rondas ganadas de los jugadores
 */
class PopUpJuegoMostrarGanadas:public PopUpInterfaz{
public:
    PopUpJuegoMostrarGanadas(GameManagerPopUpInterfaz *gameManager,int rondasGanadas[5]);
    void createUI(SDL_Renderer *gRenderer) override;
    void procesarEvento(SDL_Event * evento) override;
    void update();
    void draw(SDL_Renderer * ) override;
    ~PopUpJuegoMostrarGanadas();


private:
    Animacion * animaCuadro;
    Animacion * animaTexto,**animaTrofeos;

    int mRondasGanadas[_PLAYERS];
    int conteo;
    int animacion;
    int totalTrofeosCreados;
    SpriteSheet *mSpriteSheetCarasBomberman;
};

#endif
