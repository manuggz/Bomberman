//
// Created by manuggz on 25/11/16.
//

#ifndef BOMBERMAN_POPUPCOUNTDOWN_HPP
#define BOMBERMAN_POPUPCOUNTDOWN_HPP

#include "PopUpMostrarMensajeTexto.hpp"

class PopUpCountDown : public PopUpMostrarMensajeTexto{
public:
    PopUpCountDown(GameManager *gameManager,std::string mensaje,Uint8 tiempoDeMuestraSegundos)
            : PopUpMostrarMensajeTexto(
            gameManager,
            mensaje + std::to_string(tiempoDeMuestraSegundos) + "!",
            tiempoDeMuestraSegundos) {
        mpMensajeCrudo = mensaje;
    }

    void update() override {
        PopUpMostrarMensajeTexto::update();
        mpMensajeTexto->setText(
                mpMensajeCrudo + std::to_string(mTiempoDeMuestraSegundos - mControlTimer.getTicks()/1000) + " !"
        );
    }

    std::string mpMensajeCrudo;
};
#endif //BOMBERMAN_POPUPCOUNTDOWN_HPP
