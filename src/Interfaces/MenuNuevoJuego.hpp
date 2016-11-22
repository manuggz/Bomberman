//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_MENUNUEVOJUEGO_HPP
#define BOMBERMAN_MENUNUEVOJUEGO_HPP

#include "../engine/interfaces/MenuListLabel.hpp"
#include "MenuModoMultijugador.hpp"

class MenuNuevoJuego : public MenuListLabel{

public:

    MenuNuevoJuego(GameManager *game) : MenuListLabel(game) {
        mMenuOpcionesText.push_back("Historia");
        mMenuOpcionesText.push_back("Multiplayer");
        mMenuOpcionesText.push_back("Conexion");
    }

    void ejecutarAccionOpcionResaltada() {
        cout << "MenuNuevoJuego::ejecutarAccionOpcionResaltada" << endl;

        switch(mOpcionMenuResaltadaActual){
            case MENU_OPCION_HISTORIA:
                //mGameManager->cambiarInterfaz(new JuegoHistoria(mGameManager));
                break;
            case MENU_OPCION_MULTIPLAYER:
                cout << "MENU_OPCION_MULTIPLAYER"<< endl;
                mGameManager->cambiarInterfaz(new MenuModoMultijugador(mGameManager));
                break;
            case MENU_OPCION_CONEXION:
                //cout << "MENU_OPCION_CONEXION"<< endl;
                break;
            default:break;
        }

    }


private:


    typedef enum{
        MENU_OPCION_HISTORIA,
        MENU_OPCION_MULTIPLAYER,
        MENU_OPCION_CONEXION,
    }MenuOption;

};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
