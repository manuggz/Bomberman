//
// Created by manuggz on 20/11/16.
//

#ifndef BOMBERMAN_MENULISTLABEL_HPP
#define BOMBERMAN_MENULISTLABEL_HPP

#include <SDL2/SDL.h>
#include "interfaz.hpp"
#include "../util/game_manager.hpp"
#include "../layout/LayoutVertical.hpp"
#include "../layout/TextLabel.hpp"


const char * rutaFont = "data/fuentes/OpenSans-BoldItalic.ttf";
const Uint8 sizeFont = 20;

class MenuListLabel : public Interfaz{
public:

public:

    MenuListLabel(GameManager * gameManager) {

        mGameManager = gameManager;
        mColorLabelNormal.r = 255;
        mColorLabelNormal.g = 0;
        mColorLabelNormal.b = 0;
        mColorLabelNormal.a = 255;

        mColorLabelResaltado.r = 255;
        mColorLabelResaltado.g = 255;
        mColorLabelResaltado.b = 0;
        mColorLabelResaltado.a = 255;

        mLayoutParent = new LayoutVertical();
        mLayout = new LayoutVertical();
        mOpcionMenuResaltadaActual = -1;
    }

    virtual void start(SDL_Renderer *renderer)  override {

        mLayoutParent->setFillParentHeight(true);
        mLayoutParent->setFillParentWidth(true);
        mLayoutParent->setBackgroundTexture(mGameManager->getImagen(IMG_FONDO_MENU));

        mLayout->setCenterParentVertical(true);
        mLayout->setCenterParentHorizontal(true);

        TextLabel * nuevoTextLabel;
        for(int i = 0 ; i < mMenuOpcionesText.size() ; i++){
            nuevoTextLabel = new TextLabel();
            nuevoTextLabel->setFont(rutaFont,sizeFont);
            nuevoTextLabel->setTextColor(mColorLabelNormal);
            nuevoTextLabel->setText(mMenuOpcionesText[i]);
            nuevoTextLabel->setCenterParentHorizontal(true);
            menuTextOptions.push_back(nuevoTextLabel);
            mLayout->addComponent(nuevoTextLabel);
        }

        menuTextOptions[0]->setTextColor(mColorLabelResaltado);

        mLayoutParent->addComponent(mLayout);

        //packLayout(renderer);

        if(menuTextOptions.size()){
            mOpcionMenuResaltadaActual = 0;
        }
        SDL_ShowCursor(SDL_DISABLE);//ocultamos el cursor
        //mLayout->pack(renderer);
    }

    void packLayout(SDL_Renderer *renderer){
        SDL_Rect rect = {0,0,mGameManager->getWidth(),mGameManager->getHeight()};
        mLayoutParent->pack(renderer);
        mLayoutParent->calculateSize(rect.w,rect.h);
        mLayoutParent->calcularPosicion(rect);

    }

    virtual bool isPaused() override {
        return mIsPaused;
    }

    virtual void pause() override {
        mIsPaused = true;
    }

    virtual void resume() override {
        mIsPaused = false;
        mLayoutParent->setDisabled(true);

    }

    virtual /**
     * Establece la nueva opcion del menu resaltada al usuario
     * @param nuevaOpcion Nueva seleccion
     * @return True en caso que se haya resaltado con exito, false en caso contrario
     */
    bool setOpcionResaltada(int nuevaOpcion){
        if(nuevaOpcion >= 0 && nuevaOpcion < menuTextOptions.size()){
            menuTextOptions[mOpcionMenuResaltadaActual]->setTextColor(mColorLabelNormal); // Cambiamos el color de la opcion
            menuTextOptions[nuevaOpcion]->setTextColor(mColorLabelResaltado); // Cambiamos el color de la opcion
            mLayoutParent->setDisabled(true); // Para que se dibuje de nuevo
            mOpcionMenuResaltadaActual =  nuevaOpcion;
            return true;
        }

        return false;
    }

    virtual void ejecutarAccionOpcionResaltada() = 0;

/**
         * Procesa el evento del usuario
         * Se encarga de mover la opcion resaltada al usuario o en caso de que sea ENTER llamar a la funcion enlazada a
         * la opcion.
         * @param evento  Evento producido por SDL
         */
    void procesarEvento(SDL_Event *evento) override {
        if(evento->type==SDL_KEYDOWN){
            switch(evento->key.keysym.sym){
                case SDLK_ESCAPE:
                    cout << "Tecla Escape Presionada " << endl;
                    mGameManager->popInterface();
                    break;
                case SDLK_UP:
                    setOpcionResaltada(mOpcionMenuResaltadaActual - 1);
                    break;
                case SDLK_DOWN:
                    setOpcionResaltada(mOpcionMenuResaltadaActual + 1);
                    break;
                case SDLK_RETURN:
                    ejecutarAccionOpcionResaltada();
                    break;
                default:
                    break;
            }
        }else if(evento->type == SDL_JOYAXISMOTION&&evento->jaxis.type == SDL_JOYAXISMOTION){
            if(evento->jaxis.axis != 0){
                if(evento->jaxis.value > 10){
                    setOpcionResaltada(mOpcionMenuResaltadaActual + 1);
                }else if(evento->jaxis.value < -10){
                    setOpcionResaltada(mOpcionMenuResaltadaActual - 1);
                }
            }
        }else if(evento->type == SDL_JOYBUTTONDOWN){
            if(evento->jbutton.type == SDL_JOYBUTTONDOWN)
                if(evento->jbutton.button + 1==3)
                    ejecutarAccionOpcionResaltada();

        }
    }

    void update(void) override {

    }

    void draw(SDL_Renderer *renderer) override {
        if(mLayoutParent->isDisabled()){
            packLayout(renderer);
            mLayoutParent->draw(renderer);
        }
    }

    virtual ~MenuListLabel() override {
        delete mLayoutParent; // Al liberar el layout parent se liberan todos sus mComponentes

        for(int i = 0 ; i < menuTextOptions.size();i++){
            delete menuTextOptions[i];
        }
    }

protected:

    deque<TextLabel  *> menuTextOptions;
    LayoutVertical * mLayout;
    LayoutVertical *mLayoutParent;

    deque<string> mMenuOpcionesText;

    GameManager *mGameManager;
    SDL_Color mColorLabelNormal,mColorLabelResaltado;
    int mOpcionMenuResaltadaActual;

    bool mIsPaused = false;
};

#endif //BOMBERMAN_MENULISTLABEL_HPP
