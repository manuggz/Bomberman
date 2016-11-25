//
// Created by manuggz on 25/11/16.
//

#ifndef BOMBERMAN_MOSTRARMENSAJETEXTO_HPP
#define BOMBERMAN_MOSTRARMENSAJETEXTO_HPP

#include <iostream>
#include "../../engine/interfaces/PopUpInterfaz.hpp"
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/layout/Componentes/TextLabelComponent.hpp"
#include "../../engine/util/LTimer.hpp"
#include "../../engine/util/game_manager.hpp"

/**
 * PopUp que Muestra un Texto Centrado en la pantalla al usuario por cierto tiempo
 */
class PopUpMostrarMensajeTexto : public PopUpInterfaz{

public:

    /**
     * Inicia la clase
     * @param mensaje MEnsaje a mostrar
     * @param tiempoDeMuestraSegundos  segundos que durará el mensaje
     */
    PopUpMostrarMensajeTexto(GameManager * gameManager,std::string mensaje,Uint8 tiempoDeMuestraSegundos){
        mMensajeMostrar          = mensaje;
        mTiempoDeMuestraSegundos = tiempoDeMuestraSegundos;
        mGameManager             = gameManager;
    }

    void setText(std::string nuevoTexto){
        mMensajeMostrar = nuevoTexto;
        if(mpMensajeTexto != nullptr){
            mpMensajeTexto->setText(mMensajeMostrar);
        }
    }

    void setColorText(SDL_Color nuevoColor){
        mColorTexto = nuevoColor;
        if(mpMensajeTexto != nullptr){
            mpMensajeTexto->setTextColor(mColorTexto);
        }
    }

    void setSizeText(int nuevaSize) {
        mSizeText = nuevaSize;
        if(mpMensajeTexto != nullptr){
            mpMensajeTexto->setTextSize(mSizeText);
        }
    }
    void createUI(SDL_Renderer *gRenderer) override {
        InterfazUI::createUI(gRenderer);

        mLayoutParent   = new LayoutAbsolute();

        mpMensajeTexto = new TextLabelComponent();

        mpMensajeTexto->setText(mMensajeMostrar);
        mpMensajeTexto->setFont("data/fuentes/OpenSans-Bold.ttf",mSizeText);
        mpMensajeTexto->setTextColor(mColorTexto);
        mpMensajeTexto->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);
        mpMensajeTexto->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_VERTICAL,LAYOUT_PARAM_TRUE);

        mLayoutParent->addComponent(mpMensajeTexto);

        mpGameRenderer = gRenderer;
    }

    void packLayout(){
        SDL_Rect rect = mGameManager->getRectScreen();
        mLayoutParent->pack(mpGameRenderer);
        mLayoutParent->setRectDibujo(rect);
    }
    void start() override {
        InterfazUI::start();
        mControlTimer.start();
    }

    void update() override {
        InterfazUI::update();

        if(mControlTimer.getTicks()/1000 >= mTiempoDeMuestraSegundos){
            mGameManager->closePopUp(nullptr);
        }
    }

    void draw(SDL_Renderer *gRenderer) override {

        PopUpInterfaz::draw(gRenderer);

        if(mLayoutParent->isDisabled()){
            packLayout();
        }
        mLayoutParent->draw(gRenderer);
    }


protected:
    std::string     mMensajeMostrar;
    LayoutAbsolute *mLayoutParent;
    LTimer mControlTimer;
    Uint8 mTiempoDeMuestraSegundos = 0;
    GameManager *mGameManager;
    TextLabelComponent *mpMensajeTexto = nullptr;
    SDL_Color mColorTexto {255,255,0,255};
    int mSizeText = 15;
    SDL_Renderer *mpGameRenderer;
};
#endif //BOMBERMAN_MOSTRARMENSAJETEXTO_HPP
