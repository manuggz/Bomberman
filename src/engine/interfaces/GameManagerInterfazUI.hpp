//
// Created by manuggz on 26/11/16.
//

#ifndef BOMBERMAN_GAMEMANAGERINTERFAZ_HPP
#define BOMBERMAN_GAMEMANAGERINTERFAZ_HPP

#include "GameManagerPopUpInterfaz.hpp"

class InterfazUI;
class PopUpInterfaz;

class GameManagerInterfazUI: public GameManagerPopUpInterfaz{
public:
    virtual SDL_Rect getRectScreen()=0;
    virtual void goBack()=0;
    virtual void play(CodeMusicEfecto codeMusic) = 0;

    virtual void cambiarInterfaz(InterfazUI *pJuego) = 0;

    virtual void showPopUp(PopUpInterfaz * popUpInterfaz, const int codePopUp) = 0;

    virtual int getJoysActivos() = 0;

    virtual SDL_Joystick *getJoy(int i) = 0;
    virtual LTexture *getImagen(CodeImagen imagen) = 0;

    virtual void playSonido(CodeMusicSonido codigoSonido)=0;
};
#endif //BOMBERMAN_GAMEMANAGERINTERFAZ_HPP
