//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_MENUNUEVOJUEGO_HPP
#define BOMBERMAN_MENUNUEVOJUEGO_HPP

#include "../../engine/interfaces/MenuListLabel.hpp"
#include "MenuModoMultijugador.hpp"

class MenuNuevoJuego : public MenuListLabel{

public:

    MenuNuevoJuego(GameManagerInterfazUI *game) : MenuListLabel(game) {
        SDL_Log("MenuNuevoJuego::MenuNuevoJuego");
        mMenuOpcionesText.push_back("Historia");
        mMenuOpcionesText.push_back("Multiplayer");
        mMenuOpcionesText.push_back("Conexion");
    }

    void ejecutarAccionOpcionResaltada() {
        switch(mOpcionMenuResaltadaActual){
            case MENU_OPCION_HISTORIA:
                //mGameManager->cambiarInterfaz(new JuegoHistoria(mGameManager));
                break;
            case MENU_OPCION_MULTIPLAYER:
                mGameManagerInterfaz->cambiarInterfaz(new MenuModoMultijugador(mGameManagerInterfaz));
                break;
            case MENU_OPCION_CONEXION:
                //cout << "MENU_OPCION_CONEXION"<< endl;
                break;
            default:break;
        }

    }

    ~MenuNuevoJuego() override {
        SDL_Log("MenuNuevoJuego::~MenuNuevoJuego");
    }

private:


    typedef enum{
        MENU_OPCION_HISTORIA,
        MENU_OPCION_MULTIPLAYER,
        MENU_OPCION_CONEXION,
    }MenuOption;

};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
