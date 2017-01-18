//
// Created by manuggz on 16/01/17.
//

#ifndef BOMBERMAN_MENUESCOGERMAPABATTLE_HPP
#define BOMBERMAN_MENUESCOGERMAPABATTLE_HPP

#include "MenuEscogerMapa.hpp"
#include "../juego/ModoJuegoMultiPlayer.hpp"

class MenuEscogerMapaBattle: public MenuEscogerMapa {
public:
    MenuEscogerMapaBattle(GameManagerInterfazUI *gameManagerInterfaz) : MenuEscogerMapa(gameManagerInterfaz) {}

    bool configuracionAceptada() override {
        int total_players = mIsPlayerActivado[PLAYER_1] + mIsPlayerActivado[PLAYER_2] + mIsPlayerActivado[PLAYER_3] +
                            mIsPlayerActivado[PLAYER_4] + mIsPlayerActivado[PLAYER_5];
        if (total_players >= 2) {
            ModoJuegoMultiPlayer *nuevoJuego = new ModoJuegoMultiPlayer(
                    mGameManagerInterfaz,
                    "data/niveles/batalla/" + mNombreMapas[indiceTerrenoActual],
                    victoriasEscogidas,
                    minutosEscogidos,
                    mIsPlayerActivado
            );
            mGameManagerInterfaz->cambiarInterfaz(
                    nuevoJuego); //iniciamos en modo batalla, le pasamos el array con los players seleccionados por el usuario
            return true;
        }
        return false;
    }
};
#endif //BOMBERMAN_MENUESCOGERMAPABATTLE_HPP
