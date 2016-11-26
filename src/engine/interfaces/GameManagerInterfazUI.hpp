//
// Created by manuggz on 26/11/16.
//

#ifndef BOMBERMAN_GAMEMANAGERINTERFAZ_HPP
#define BOMBERMAN_GAMEMANAGERINTERFAZ_HPP

#include "GameManagerPopUpInterfaz.hpp"
#include "../../galeria.hpp"

class InterfazUI;
class PopUpInterfaz;
/**
 * Esta es la interfaz que debe implemetar un GameManager si quiere utilizar interfaces.
 */
class GameManagerInterfazUI: public GameManagerPopUpInterfaz{
public:

    /**
     * Reproduce un efecto de sonido
     * @param codeMusic
     */
    virtual void play(Galeria::CodeMusicEfecto codeMusic) = 0;
    /**
     * Reproduce una musica de fondo
     * @param codigoSonido
     */
    virtual void playSound(Galeria::CodeMusicSonido codigoSonido)=0;

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
    virtual SDL_Joystick * getJoy(int i) = 0;
    virtual LTexture     * getTexture(Galeria::CodeImagen imagen) = 0;

    /**
     * Cambia la interfaz Actual, por la nueva referenciada.
     * Pausa la Actual y la deja en la pila, si se llama a goBack() se resumirá.
     * @param pJuego
     */
    virtual void cambiarInterfaz(InterfazUI * pInterfaz) = 0;

    /**
     * Regresa en la pila de navegación, si no hay nada en la pila se sale del juego.
     */
    virtual void goBack()=0;
};
#endif //BOMBERMAN_GAMEMANAGERINTERFAZ_HPP
