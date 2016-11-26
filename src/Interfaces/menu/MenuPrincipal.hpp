//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_MENUPRINCIPAL_HPP
#define BOMBERMAN_MENUPRINCIPAL_HPP


#include "../../engine/interfaces/MenuListLabel.hpp"
#include "MenuNuevoJuego.hpp"

class MenuPrincipal : public MenuListLabel{

public:

    MenuPrincipal(GameManagerInterfazUI *gameManager) : MenuListLabel(gameManager) {

        mMenuOpcionesText.push_back("Nuevo Juego");
        mMenuOpcionesText.push_back("Editor");
        mMenuOpcionesText.push_back("Configurar");
        mMenuOpcionesText.push_back("Creditos");
    }

    virtual bool setOpcionResaltada(int nuevaOpcion) override {
        if(MenuListLabel::setOpcionResaltada(nuevaOpcion)){
            mGameManagerInterfaz->play(Galeria::CodeMusicEfecto::SFX_TONO_ACUATICO);
            return true;
        }
        return false;
    }

    void ejecutarAccionOpcionResaltada() {
        switch(mOpcionMenuResaltadaActual){
            case MENU_OPCION_NUEVO_JUEGO:
                //cout << "MENU_OPCION_NUEVO_JUEGO"<< endl;
                mGameManagerInterfaz->cambiarInterfaz(new MenuNuevoJuego(mGameManagerInterfaz));
                break;
            case MENU_OPCION_EDITOR:
                //cout << "MENU_OPCION_EDITOR"<< endl;
                //game->cambiarInterfaz(new Editor(game));
                break;
            case MENU_OPCION_CONFIGURACION:
                //cout << "MENU_OPCION_CONFIGURACION"<< endl;
                break;
            case MENU_OPCION_CREDITOS:
                //cout << "MENU_OPCION_CREDITOS"<< endl;
                break;
            default:break;
        }

    }


private:
    typedef enum{
        MENU_OPCION_NUEVO_JUEGO,
        MENU_OPCION_EDITOR,
        MENU_OPCION_CONFIGURACION,
        MENU_OPCION_CREDITOS,
    }MenuOption;
};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
