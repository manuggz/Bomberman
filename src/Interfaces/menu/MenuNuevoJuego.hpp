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

    void createUI(SDL_Renderer *renderer) override {
        MenuListLabel::createUI(renderer);
        mLayoutBackGround->setBackgroundTexture(renderer,"data/imagenes/fondos/fondo_menu.bmp",false);
        mpSfxCambiarOpcionResaltada = new EfectoSonido("data/sonidos/ping_2.wav",100);
    }

    void start() override {
        InterfazGrafica::start();

    }

    virtual bool setOpcionResaltada(int nuevaOpcion) override {
        if(MenuListLabel::setOpcionResaltada(nuevaOpcion)){
            mpSfxCambiarOpcionResaltada->play();
            return true;
        }
        return false;
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
        delete mpSfxCambiarOpcionResaltada;
    }

private:


    typedef enum{
        MENU_OPCION_HISTORIA,
        MENU_OPCION_MULTIPLAYER,
        MENU_OPCION_CONEXION,
    }MenuOption;
    EfectoSonido * mpSfxCambiarOpcionResaltada;

};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
