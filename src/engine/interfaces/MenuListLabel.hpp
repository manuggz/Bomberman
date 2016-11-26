//
// Created by manuggz on 20/11/16.
//

#ifndef BOMBERMAN_MENULISTLABEL_HPP
#define BOMBERMAN_MENULISTLABEL_HPP

#include <SDL2/SDL.h>
#include "InterfazUI.hpp"
#include "../layout/LayoutManager/LayoutVertical.hpp"
#include "../layout/Componentes/TextLabelComponent.hpp"
#include "../layout/LayoutManager/LayoutParent.hpp"


const char * rutaFont = "data/fuentes/OpenSans-BoldItalic.ttf";
const Uint8 sizeFont = 20;

class MenuListLabel : public InterfazUI{
public:

public:

    MenuListLabel(GameManagerInterfazUI *gameManagerInterfaz)
            : InterfazUI(gameManagerInterfaz) {

        mColorLabelNormal.r = 255;
        mColorLabelNormal.g = 0;
        mColorLabelNormal.b = 0;
        mColorLabelNormal.a = 255;

        mColorLabelResaltado.r = 255;
        mColorLabelResaltado.g = 255;
        mColorLabelResaltado.b = 0;
        mColorLabelResaltado.a = 255;
        
        mLayoutBackGround = new LayoutVertical();
        mLayout = new LayoutVertical();
        mLayoutParent = new LayoutParent(mLayoutBackGround);
        mOpcionMenuResaltadaActual = -1;
    }

    virtual void createUI(SDL_Renderer *renderer)  override{

        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_HEIGHT,LAYOUT_PARAM_TRUE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_WIDTH,LAYOUT_PARAM_TRUE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_WIDTH,LAYOUT_PARAM_FALSE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_HEIGHT,LAYOUT_PARAM_FALSE);
        LTexture * lTexture = new LTexture();
        lTexture->loadFromFile("data/imagenes/fondos/fondo_menu.bmp",renderer,false);
        mLayoutBackGround->setBackgroundTexture(lTexture);


        TextLabelComponent * nuevoTextLabel;
        for(int i = 0 ; i < mMenuOpcionesText.size() ; i++){
            nuevoTextLabel = new TextLabelComponent();
            nuevoTextLabel->setFont(rutaFont,sizeFont);
            nuevoTextLabel->setTextColor(mColorLabelNormal);
            nuevoTextLabel->setText(mMenuOpcionesText[i]);
            menuTextOptions.push_back(nuevoTextLabel);
            mLayout->addComponent(nuevoTextLabel);
            nuevoTextLabel->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);
        }

        menuTextOptions[0]->setTextColor(mColorLabelResaltado);

        mLayoutBackGround->addComponent(mLayout);
        mLayout->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_HORIZONTAL,LAYOUT_PARAM_TRUE);
        mLayout->setLayoutParam(LAYOUT_PARAM_CENTER_PARENT_VERTICAL,LAYOUT_PARAM_TRUE);

        //packLayout(renderer);

        if(menuTextOptions.size()){
            mOpcionMenuResaltadaActual = 0;
        }
        SDL_ShowCursor(SDL_DISABLE);//ocultamos el cursor
        //mLayout->pack(renderer);
    }


    virtual void resume() override {
        InterfazUI::resume();
        mLayoutBackGround->setDisabled(true);
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
            mLayoutBackGround->setDisabled(true); // Para que se dibuje de nuevo
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
                    //cout << "Tecla Escape Presionada " << endl;
                    mGameManagerInterfaz->goBack();
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
    void draw(SDL_Renderer *renderer) override {
        if(mLayoutBackGround->isDisabled()){
            SDL_Rect rect = mGameManagerInterfaz->getRectScreen();
            mLayoutBackGround->pack(renderer);
            mLayoutBackGround->setRectDibujo(rect);
            mLayoutBackGround->draw(renderer);
        }
    }

    virtual ~MenuListLabel() override {
        delete mLayoutBackGround; // Al liberar el layout parent se liberan todos sus mComponentes

        for(int i = 0 ; i < menuTextOptions.size();i++){
            delete menuTextOptions[i];
        }
    }

protected:

    deque<TextLabelComponent  *> menuTextOptions;
    LayoutVertical * mLayout;
    LayoutVertical *mLayoutBackGround;

    deque<string> mMenuOpcionesText;

    SDL_Color mColorLabelNormal,mColorLabelResaltado;
    int mOpcionMenuResaltadaActual;

    LayoutParent *mLayoutParent;
};

#endif //BOMBERMAN_MENULISTLABEL_HPP
