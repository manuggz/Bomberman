//
// Created by manuggz on 06/12/16.
//

#ifndef TETRIS_MENU_HPP
#define TETRIS_MENU_HPP

#include "TetrisInterfaz.hpp"

class Menu:public  InterfazUI{

public:

    Menu(GameManagerInterfazUI *gameManagerInterfaz) : InterfazUI(gameManagerInterfaz) {

    }

    void prepare() override {
        InterfazUI::prepare();


    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazUI::createUI(gRenderer);

        mTextureFondo = new LTexture();
        mTextureFondo->loadFromFile("resources/background_menu_principal.png",gRenderer,false);


        for(int i = 1;i <= 2;i++){
            mpBitmapFont[i - 1] = new BitmapFont(gRenderer,"resources/fuentes/fuente_" + std::to_string(i) + ".png");
        }

        xIni = 400;
        yIni = 364;
        mpBitFntRendOpsMenuPausa[OpcionesMenu::CONTINUE] = new BitmapFontRenderer(
                mpBitmapFont[EstadoOpcionMenu::NORMAL],0,0);
        mpBitFntRendOpsMenuPausa[OpcionesMenu::CONTINUE]->setText("CONTINUE");

        mpBitFntRendOpsMenuPausa[OpcionesMenu::NEW_GAME] = new BitmapFontRenderer(
                mpBitmapFont[EstadoOpcionMenu::RESALTADO],0,0);
        mpBitFntRendOpsMenuPausa[OpcionesMenu::NEW_GAME]->setText("NEW GAME");
        mEsOpcionVisible[OpcionesMenu::NEW_GAME] = true;

        mpBitFntRendOpsMenuPausa[OpcionesMenu::SCORES] = new BitmapFontRenderer(
                mpBitmapFont[EstadoOpcionMenu::NORMAL],0,0);
        mpBitFntRendOpsMenuPausa[OpcionesMenu::SCORES]->setText("SCORES");

        mpBitFntRendOpsMenuPausa[OpcionesMenu::EXIT] = new BitmapFontRenderer(
                mpBitmapFont[EstadoOpcionMenu::NORMAL],0,0);
        mpBitFntRendOpsMenuPausa[OpcionesMenu::EXIT]->setText("EXIT");
        mEsOpcionVisible[OpcionesMenu::EXIT] = true;

        mOpcionSeleccionadaMenuPausa = OpcionesMenu ::NEW_GAME;

        mpTextureFlechaOpcionSeleccionada= new LTexture();
        mpTextureFlechaOpcionSeleccionada->loadFromFile("resources/flecha_opcion_seleccionada.png",gRenderer,false);

        mpTextureCuadroAzulFondo = new LTexture();
        mpTextureCuadroAzulFondo->loadFromFile("resources/cuadro_opcion_seleccionada.png",gRenderer,false);

        mMusicaFondo = cargar_musica("resources/music/8_bit_electro_house_remix.wav");
        mSfxChangeSelect = cargar_sonido((char *) "resources/music/SFX_PieceLockdown.ogg");
    }

    void start() override {
        InterfazUI::start();
        mGameManagerInterfaz->playSound(mMusicaFondo,MIX_MAX_VOLUME);
    }

    void resume() override {
        InterfazUI::resume();
        mGameManagerInterfaz->playSound(mMusicaFondo,MIX_MAX_VOLUME);
    }

    void procesarEvento(SDL_Event *event) override {
        InterfazUI::procesarEvento(event);
        if(event->type==SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    mGameManagerInterfaz->goBack();
                    //mGameManagerInterfaz->showPopUp()
                    break;
                case SDLK_DOWN:
                {
                    int avance = 1;
                    while(mOpcionSeleccionadaMenuPausa + avance < OpcionesMenu::N_OPCIONES){
                        if(mEsOpcionVisible[mOpcionSeleccionadaMenuPausa + avance]){
                            mpBitFntRendOpsMenuPausa[mOpcionSeleccionadaMenuPausa]->setBitmapFont(mpBitmapFont[NORMAL]);
                            mOpcionSeleccionadaMenuPausa = (Menu::OpcionesMenu)(mOpcionSeleccionadaMenuPausa + avance);
                            mGameManagerInterfaz->play(mSfxChangeSelect);
                            mpBitFntRendOpsMenuPausa[mOpcionSeleccionadaMenuPausa]->setBitmapFont(mpBitmapFont[RESALTADO]);
                            break;
                        }else{
                            avance++;
                        }
                    }

                }

                    break;
                case SDLK_UP:
                {
                    int avance = 1;
                    while(mOpcionSeleccionadaMenuPausa - avance >= 0){
                        if(mEsOpcionVisible[mOpcionSeleccionadaMenuPausa - avance]){
                            mpBitFntRendOpsMenuPausa[mOpcionSeleccionadaMenuPausa]->setBitmapFont(mpBitmapFont[NORMAL]);
                            mOpcionSeleccionadaMenuPausa = (Menu::OpcionesMenu)(mOpcionSeleccionadaMenuPausa - avance);
                            mpBitFntRendOpsMenuPausa[mOpcionSeleccionadaMenuPausa]->setBitmapFont(mpBitmapFont[RESALTADO]);
                            mGameManagerInterfaz->play(mSfxChangeSelect);
                            break;
                        }else{
                            avance++;
                        }
                    }
                    //mGameManagerInterfaz->goBack();
                    //mGameManagerInterfaz->showPopUp(new PopUpMostrarMensajeText())

                }

                    break;
                case SDLK_RETURN:
                    switch(mOpcionSeleccionadaMenuPausa){
                        case CONTINUE:break;
                        case NEW_GAME:
                            mGameManagerInterfaz->cambiarInterfaz(new TetrisInterfaz(mGameManagerInterfaz));
                            break;
                        case SCORES:break;
                        case EXIT:
                            mGameManagerInterfaz->goBack();
                            break;
                        case N_OPCIONES:break;
                    }
                    //mGameManagerInterfaz->goBack();
                    //mGameManagerInterfaz->showPopUp(new PopUpMostrarMensajeText())
                    break;
                default:
                    break;
            }
        }
    }

    void update() override {
        InterfazUI::update();
    }

    void draw(SDL_Renderer *gRenderer) override {

        mTextureFondo->render(gRenderer,0,0);

        int yDibujo = yIni;
        for(int i = 0 ; i < OpcionesMenu::N_OPCIONES;i++){
            if(mEsOpcionVisible[i]){

                if(mOpcionSeleccionadaMenuPausa == i){
                    mpTextureFlechaOpcionSeleccionada->render(gRenderer,xIni - mpTextureFlechaOpcionSeleccionada->getWidth() - 5,yDibujo);
                    mpTextureCuadroAzulFondo->render(gRenderer,xIni - 3,yDibujo);
                }

                mpBitFntRendOpsMenuPausa[i]->draw(gRenderer,xIni,yDibujo);

                yDibujo +=  mpBitFntRendOpsMenuPausa[i]->getHeight() + 10;

            }
        }


    }

    ~Menu(){
        delete mTextureFondo;
        for(int i = 0; i < N_OPCIONES;i++){
            delete mpBitFntRendOpsMenuPausa[i];
        }
        delete mpTextureFlechaOpcionSeleccionada;
        delete mpTextureCuadroAzulFondo;
        Mix_FreeMusic(mMusicaFondo);
        Mix_FreeChunk(mSfxChangeSelect);
    }
private:

    int xIni,yIni;

    LTexture * mTextureFondo = nullptr;

    enum EstadoOpcionMenu{
        NORMAL,
        RESALTADO
    };

    enum OpcionesMenu{
        CONTINUE,
        NEW_GAME,
        SCORES,
        EXIT,
        N_OPCIONES
    };

    bool mEsOpcionVisible[4] {false};

    BitmapFont * mpBitmapFont[2]  {nullptr};

    BitmapFontRenderer * mpBitFntRendOpsMenuPausa[N_OPCIONES] {nullptr};

    LTexture * mpTextureFlechaOpcionSeleccionada = nullptr;


    OpcionesMenu mOpcionSeleccionadaMenuPausa;
    Mix_Music * mMusicaFondo;

    Mix_Chunk * mSfxChangeSelect;
    LTexture * mpTextureCuadroAzulFondo;
};

#endif //TETRIS_MENU_HPP
