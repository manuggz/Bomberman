//
// Created by manuggz on 14/01/17.
//

#ifndef BOMBERMAN_POPUPINSERTARTEXTO_HPP
#define BOMBERMAN_POPUPINSERTARTEXTO_HPP

#include <iostream>
#include "../../engine/interfaces/PopUpInterfaz.hpp"
#include "../../engine/layout/LayoutManager/LayoutVertical.hpp"
#include "../../engine/layout/Componentes/LabelComponent.hpp"
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/GameManager/GameManager.hpp"

class PopUpInsertarTexto: public PopUpInterfaz{
public:

    /**
     * Inicia la clase
     * @param mensaje MEnsaje a mostrar
     * @param tiempoDeMuestraSegundos  segundos que durará el mensaje
     */
    PopUpInsertarTexto(GameManagerPopUpInterfaz *gameManager1, std::string promptText,int n) :
            PopUpInterfaz(gameManager1) {
        mMensajePrompt          = promptText;
        mMaxCaracteres = n;
    }


    void setColorText(SDL_Color nuevoColor){
        mColorTexto = nuevoColor;
        if(mpComponenteMensajePrompt != nullptr){
            mpComponenteMensajePrompt->setTextColor(mColorTexto);
        }
    }

    void setSizeText(int nuevaSize) {
        mSizeText = nuevaSize;
        if(mpComponenteMensajePrompt != nullptr){
            mpComponenteMensajePrompt->setTextSize(mSizeText);
        }
    }
    void createUI(SDL_Renderer *gRenderer) override {
        PopUpInterfaz::createUI(gRenderer);

        mLayoutBackGround          = new LayoutAbsolute();
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_HEIGHT,LAYOUT_PARAM_TRUE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_WIDTH,LAYOUT_PARAM_TRUE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_WIDTH,LAYOUT_PARAM_FALSE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_HEIGHT,LAYOUT_PARAM_FALSE);

        mLayoutParent   = new LayoutVertical();

        mpComponenteMensajePrompt = new LabelComponent();

        mpComponenteMensajePrompt->setText(mMensajePrompt);
        mpComponenteMensajePrompt->setFont("data/fuentes/OpenSans-Bold.ttf",mSizeText);
        mpComponenteMensajePrompt->setTextColor(mColorTexto);
        //mpComponenteMensajePrompt->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);
        //mpComponenteMensajePrompt->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_VERTICAL,LAYOUT_PARAM_TRUE);

        mLayoutParent->addComponent(mpComponenteMensajePrompt);
        mpComponenteMensajePrompt->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);

        mpComponenteTextoIntroducido = new LabelComponent();

        //mpComponenteTextoIntroducido->setText("");
        mpComponenteTextoIntroducido->setFont("data/fuentes/OpenSans-Bold.ttf",mSizeText);
        mpComponenteTextoIntroducido->setTextColor(SDL_Color {0,0,0,255});
        mpComponenteTextoIntroducido->setBackgroundColor(SDL_Color {255,255,255,255});
        mpComponenteTextoIntroducido->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);
        mpComponenteTextoIntroducido->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_VERTICAL,LAYOUT_PARAM_TRUE);

        mLayoutParent->addComponent(mpComponenteTextoIntroducido);
        mpComponenteTextoIntroducido->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);

        mLayoutBackGround->addComponent(mLayoutParent);
        mLayoutParent->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);
        mLayoutParent->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_VERTICAL,LAYOUT_PARAM_TRUE);

        mpGameRenderer = gRenderer;
    }

    void procesarEvento(SDL_Event *event) override {
        if(event->type == SDL_KEYDOWN){
            char keyName[10];
            if(((event->key.keysym.scancode>= SDL_SCANCODE_A &&
                event->key.keysym.scancode<= SDL_SCANCODE_Z)||
                    (event->key.keysym.scancode>= SDL_SCANCODE_1 &&
                     event->key.keysym.scancode<= SDL_SCANCODE_0))&&textoActualIntroducido.size()<mMaxCaracteres){
                sprintf(keyName,"%s",SDL_GetKeyName(event->key.keysym.sym));
                textoActualIntroducido += keyName[0];
                mpComponenteTextoIntroducido->setText(textoActualIntroducido);
            }else{
                switch(event->key.keysym.sym){
                    case SDLK_BACKSPACE:
                        if(!textoActualIntroducido.empty()) {
                            textoActualIntroducido.pop_back();
                            mpComponenteTextoIntroducido->setText(textoActualIntroducido);
                        }
                        break;
                    case SDLK_RETURN:
                        InterfazEstandarBackResult * resultado = new InterfazEstandarBackResult();
                        resultado->texto = textoActualIntroducido;
                        mGameManager->closePopUp(resultado);
                        break;
                }
            }

            //SDL_Log("",event->key.keysym.scancode);
        }
    }

    void packLayout(){
        SDL_Rect rect = mGameManager->getRectScreen();
        mLayoutBackGround->pack(mpGameRenderer);
        mLayoutBackGround->setRectDibujo(rect);
    }
    void start() override {
        PopUpInterfaz::start();
    }

    void update() override {
        PopUpInterfaz::update();

    }

    void draw(SDL_Renderer *gRenderer) override {
        PopUpInterfaz::draw(gRenderer);

        if(mLayoutBackGround->isDisabled()){
            packLayout();
        }
        mLayoutBackGround->draw(gRenderer);
    }

    ~PopUpInsertarTexto() override {
        delete mLayoutBackGround;
    }

protected:
    std::string     mMensajePrompt;
    LayoutVertical *mLayoutParent;
    Uint8 mTiempoDeMuestraSegundos = 0;
    LabelComponent *mpComponenteTextoIntroducido = nullptr;
    LabelComponent * mpComponenteMensajePrompt = nullptr;

    SDL_Color mColorTexto {255,255,0,255};
    int mSizeText = 15;
    SDL_Renderer *mpGameRenderer;

    LayoutAbsolute *mLayoutBackGround;
    std::string textoActualIntroducido;
    int mMaxCaracteres;
};
#endif //BOMBERMAN_POPUPINSERTARTEXTO_HPP
