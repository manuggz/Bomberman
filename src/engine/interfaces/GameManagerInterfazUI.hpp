//
// Created by manuggz on 10/01/17.
//

#ifndef BOMBERMAN_GAMEMANAGERINTERFAZUI_HPP
#define BOMBERMAN_GAMEMANAGERINTERFAZUI_HPP
#include <SDL2/SDL_mixer.h>
#include "GameManagerPopUpInterfaz.hpp"

class InterfazGrafica;
class PopUpInterfaz;
/**
 * Esta es la interfaz que debe implemetar un GameManager si quiere utilizar interfaces.
 */
class GameManagerInterfazUI: public GameManagerPopUpInterfaz{
public:

    virtual float getScaleRatioW() const = 0;

    virtual void setScaleRatioW(float scaleRatioW) = 0;

    virtual float getScaleRatioH() const = 0;

    virtual void setScaleRatioH(float scaleRatioH) = 0;
    /**
     * Reproduce un efecto de sonido
     * @param codeMusic
     */
    virtual void play(Mix_Chunk *  pSfxChunk) = 0;
    /**
     * Reproduce una musica de fondo
     * @param codigoSonido
     */

    /**
     * Hace que se muestre un PopUp en la pantalla
     * @param popUpInterfaz Puntero al PopUp
     * @param codePopUp Codigo que usa el PopUp
     *
     * @note Cuando se cierra el PopUp, se pasa el codePopUp a la interfaz que esté corriendo
     */
    virtual void showPopUp(PopUpInterfaz * popUpInterfaz, const int codePopUp) = 0;

    /**
     * Obtiene el numero de Joysticks activos
     * @return
     */
    virtual int getActiveJoys() = 0;

    /**
     * Obtiene el Joystic en la posición I
     * @param i
     * @return
     */
    virtual SDL_Joystick * getJoy(int device_index) = 0;
    /**
     * Cambia la interfaz Actual, por la nueva referenciada.
     * Pausa la Actual y la deja en la pila, si se llama a goBack() se resumirá.
     * @param pJuego
     */
    virtual void cambiarInterfaz(InterfazGrafica * pInterfaz) = 0;

    /**
     * Regresa en la pila de navegación, si no hay nada en la pila se sale del juego.
     */
    virtual void goBack()=0;

    virtual void playSound(Mix_Music * pMusic,Uint8 volumen) = 0;
    virtual void playFadeInSound(Mix_Music *music, Uint8 volumen) = 0;
};
#endif //BOMBERMAN_GAMEMANAGERINTERFAZ_HPP
