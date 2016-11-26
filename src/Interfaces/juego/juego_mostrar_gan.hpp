#ifndef JUEGOMOSTRARGANADAS_HPP
#define JUEGOMOSTRARGANADAS_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include "../../constantes.hpp"
#include "../../engine/util/game_manager.hpp"
#include "../../engine/sprites/animacion/animacion.hpp"


/**
 * Popup que muestra el numero de rondas ganadas de los jugadores
 */
class JuegoMostrarGanadas:public PopUpInterfaz{
public:
    JuegoMostrarGanadas(GameManagerPopUpInterfaz *gameManager,int rondasGanadas[5]);
    void createUI(SDL_Renderer *gRenderer) override;
    void procesarEvento(SDL_Event * evento) override;
    void update();
    void draw(SDL_Renderer * ) override;
    ~JuegoMostrarGanadas();


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
