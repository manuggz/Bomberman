//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_MENUPRINCIPAL_HPP
#define BOMBERMAN_MENUPRINCIPAL_HPP


#include "../../engine/util/EfectoSonido.hpp"
#include "../../engine/interfaces/MenuListLabel.hpp"
#include "MenuNuevoJuego.hpp"
#include "../InterfazConfiguracion.hpp"
#include "../InterfazCreditos.hpp"

class MenuPrincipal : public MenuListLabel{

public:

    MenuPrincipal(GameManagerInterfazUI *gameManager) : MenuListLabel(gameManager) {
        SDL_Log("MenuPrincipal::MenuPrincipal");
        mMenuOpcionesText.push_back("Nuevo Juego");
        //mMenuOpcionesText.push_back("Editor");
        mMenuOpcionesText.push_back("Configurar");
        mMenuOpcionesText.push_back("Creditos");

    }

    void createUI(SDL_Renderer *renderer) override {
        MenuListLabel::createUI(renderer);
        mLayoutBackGround->setBackgroundTexture(renderer,"data/imagenes/fondos/fondo_menu.bmp",false);
        mpSfxCambiarOpcionResaltada = new EfectoSonido("data/sonidos/ping_2.wav",100);
        musicaFondoMenu = new MusicaFondo("data/sonidos/musica_1.mid");
    }

    virtual bool setOpcionResaltada(int nuevaOpcion) override {
        if(MenuListLabel::setOpcionResaltada(nuevaOpcion)){
            mpSfxCambiarOpcionResaltada->play();
            return true;
        }
        return false;
    }

    void resume() override {
        MenuListLabel::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }
    }

    void start() override {
        InterfazGrafica::start();

    }

    void ejecutarAccionOpcionResaltada() {
        switch(mOpcionMenuResaltadaActual){
            case MENU_OPCION_NUEVO_JUEGO:
                mGameManagerInterfaz->cambiarInterfaz(new MenuNuevoJuego(mGameManagerInterfaz));
                break;
            //case MENU_OPCION_EDITOR:
                //cout << "MENU_OPCION_EDITOR"<< endl;
                //game->cambiarInterfaz(new Editor(game));
                //break;
            case MENU_OPCION_CONFIGURACION:
                mGameManagerInterfaz->cambiarInterfaz(new InterfazConfiguracion(mGameManagerInterfaz));
                break;
            case MENU_OPCION_CREDITOS:
                mGameManagerInterfaz->cambiarInterfaz(new InterfazCreditos(mGameManagerInterfaz));
                break;
            default:break;
        }

    }

    ~MenuPrincipal() override {
        SDL_Log("MenuPrincipal::~MenuPrincipal");
        delete mpSfxCambiarOpcionResaltada;
        delete musicaFondoMenu;
    }

private:
    typedef enum{
        MENU_OPCION_NUEVO_JUEGO,
        //MENU_OPCION_EDITOR,
        MENU_OPCION_CONFIGURACION,
        MENU_OPCION_CREDITOS,
    }MenuOption;

    EfectoSonido * mpSfxCambiarOpcionResaltada;
    MusicaFondo *musicaFondoMenu;
};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
