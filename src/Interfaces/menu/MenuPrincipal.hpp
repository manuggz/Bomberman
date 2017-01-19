//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_MENUPRINCIPAL_HPP
#define BOMBERMAN_MENUPRINCIPAL_HPP


#include "../../engine/util/EfectoSonido.hpp"
#include "../../engine/util/MusicaFondo.hpp"
#include "../../engine/util/BitmapFont.hpp"
#include "../InterfazConfiguracion.hpp"
#include "SpriteFlecha.hpp"
#include "MenuEscogerMapaBattle.hpp"
#include "MenuNetworkBattle.hpp"

class MenuPrincipal : public InterfazGrafica{

public:
    static const int N_OPCIONES_MENU = 3;

    MenuPrincipal(GameManagerInterfazUI *gameManager) : InterfazGrafica(gameManager) {
        SDL_Log("MenuPrincipal::MenuPrincipal");

    }

    void createUI(SDL_Renderer *renderer) override {
        InterfazGrafica::createUI(renderer);

        textureFondo = new LTexture();
        textureFondo->cargarDesdeArchivo("data/imagenes/fondos/fondo_menu.png",renderer,false);

        LTexture *pTextureFlechaDerecha = new LTexture();
        pTextureFlechaDerecha->cargarDesdeArchivo("data/imagenes/objetos/flecha_menu_apunta_hacia_izquierda.png",renderer,false);

        LTexture * pTextureFlechaIzquierda = new LTexture();
        pTextureFlechaIzquierda->cargarDesdeArchivo("data/imagenes/objetos/flecha_menu_apunta_hacia_derecha.png",renderer,false);

        flechaIzquierda = new FlechaDinamica(pTextureFlechaIzquierda);
        flechaIzquierda->move(85 - pTextureFlechaDerecha->getWidth(),108);
        flechaIzquierda->setYDestino(108);

        flechaDerecha = new FlechaDinamica(pTextureFlechaDerecha);
        flechaDerecha->move(230,108);
        flechaDerecha->setYDestino(108);

        mBitmapFont[FUENTE_NORMAL] = new BitmapFont(renderer,   "data/fuentes/fuente2_16_normal.png");
        mBitmapFont[FUENTE_RESALTADA] = new BitmapFont(renderer,"data/fuentes/fuente2_16_resaltado.png");

        for(int i = 0; i < N_OPCIONES_MENU;i++) {
            mpBitmapTexto[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 85, 108 + 20*i);
        }
        mpBitmapTexto[0]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);

        mpSfxCambiarOpcionResaltada = new EfectoSonido("data/sonidos/ping_3.wav",100);

        musicaFondoMenu = new MusicaFondo("data/sonidos/musica_1.mid");


        mpBitmapTexto[0]->setText("Battle Mode");
        mpBitmapTexto[1]->setText("Network Battle");
        mpBitmapTexto[2]->setText("Options");


    }

    virtual bool setOpcionResaltada(Uint8 nuevaOpcion) {
        if(nuevaOpcion < N_OPCIONES_MENU && nuevaOpcion != mOpcionMenuResaltadaActual){
            mpBitmapTexto[mOpcionMenuResaltadaActual]->setBitmapFont(mBitmapFont[FUENTE_NORMAL]);
            mpBitmapTexto[nuevaOpcion]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);
            mOpcionMenuResaltadaActual =  nuevaOpcion;
            flechaIzquierda->setYDestino(108 + 20*nuevaOpcion);
            flechaDerecha->setYDestino(108 + 20*nuevaOpcion);
            mpSfxCambiarOpcionResaltada->play();
            return true;
        }

        return false;
    }

    void resume() override {
        InterfazGrafica::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }
    }

    void start() override {
        InterfazGrafica::start();
    }

    void ejecutarAccionOpcionMenu(Uint8 opcion) {
        switch(opcion){
            case MENU_OPCION_BATTLE_MODE:
                mGameManagerInterfaz->cambiarInterfaz(new MenuEscogerMapaBattle(mGameManagerInterfaz));
                break;
            case MENU_OPCION_NETWORK_BATTLE_MODE:
                mGameManagerInterfaz->cambiarInterfaz(new MenuNetworkBattle(mGameManagerInterfaz));
                break;
            case MENU_OPCION_SETTINGS:
                mGameManagerInterfaz->cambiarInterfaz(new InterfazConfiguracion(mGameManagerInterfaz));
                break;
            default:break;
        }

    }

    void procesarEvento(SDL_Event *pEvento) override {
        InterfazGrafica::procesarEvento(pEvento);
        if(pEvento->type==SDL_KEYDOWN){
            switch(pEvento->key.keysym.sym){
                case SDLK_UP:
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual > 0 ? mOpcionMenuResaltadaActual - 1 : 0));
                    break;
                case SDLK_DOWN:
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual + 1));
                    break;
                case SDLK_RETURN:
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual);
                    break;
                default:
                    break;
            }
        }else if(pEvento->type == SDL_JOYAXISMOTION&&pEvento->jaxis.type == SDL_JOYAXISMOTION){
            if(pEvento->jaxis.axis != 0){
                if(pEvento->jaxis.value > 10){
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual + 1));
                }else if(pEvento->jaxis.value < -10){
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual > 0 ? mOpcionMenuResaltadaActual - 1 : 0));
                }
            }
        }else if(pEvento->type == SDL_JOYBUTTONDOWN){
            if(pEvento->jbutton.type == SDL_JOYBUTTONDOWN)
                if(pEvento->jbutton.button + 1==3) {
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual);
                }

        }
    }

    void update() override {
        InterfazGrafica::update();
        flechaIzquierda->update(nullptr);
        flechaDerecha->update(nullptr);
    }

    void draw(SDL_Renderer *gRenderer) override {
        textureFondo->draw(gRenderer);
        for(int i = 0; i < N_OPCIONES_MENU;i++){
            mpBitmapTexto[i]->draw(gRenderer);
        }
        flechaIzquierda->draw(gRenderer);
        flechaDerecha->draw(gRenderer);
    }

    ~MenuPrincipal() override {
        SDL_Log("MenuPrincipal::~MenuPrincipal");
        delete mpSfxCambiarOpcionResaltada;
        delete musicaFondoMenu;
        delete mBitmapFont[0];
        delete mBitmapFont[1];

        for(int i = 0; i < N_OPCIONES_MENU;i++) {
            delete mpBitmapTexto[i];
        }
        delete textureFondo;

        delete flechaDerecha;
        delete flechaIzquierda;
    }

private:
    typedef enum{
        MENU_OPCION_BATTLE_MODE,
        MENU_OPCION_NETWORK_BATTLE_MODE,
        MENU_OPCION_SETTINGS,
    }MenuOption;

    enum{
        FUENTE_NORMAL,
        FUENTE_RESALTADA
    };
    EfectoSonido * mpSfxCambiarOpcionResaltada;
    MusicaFondo *musicaFondoMenu;

    BitmapFont *mBitmapFont[2];
    BitmapFontRenderer *mpBitmapTexto[N_OPCIONES_MENU] {nullptr};

    //LayoutAbsolute *  mLayoutBackGround;
    LTexture * textureFondo;
    Uint8 mOpcionMenuResaltadaActual = 0;

    FlechaDinamica * flechaIzquierda;
    FlechaDinamica * flechaDerecha;
};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
