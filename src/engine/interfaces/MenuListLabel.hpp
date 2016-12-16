//
// Created by manuggz on 20/11/16.
//

#ifndef BOMBERMAN_MENULISTLABEL_HPP
#define BOMBERMAN_MENULISTLABEL_HPP

#include <SDL2/SDL.h>
#include "InterfazUI.hpp"
#include "../layout/LayoutManager/LayoutVertical.hpp"
#include "../layout/Componentes/LabelComponent.hpp"


const char * rutaFont = "data/fuentes/OpenSans-BoldItalic.ttf";
const Uint8 sizeFont = 20;
/**
 * Representa un menu de opciones simple en el que el usuario se puede desplazar usando las teclas UP y DOWN
 *
 * Heredar esta clase y en el constructor agregar las opciones del menu en orden.
 * menuTextOptions.push_back("opcion i")
 *
 * Luego se ejecutara ejecutarAccionOpcionResaltada() cuando el usuario presione [ENTER].
 *
 * chequear la variable mOpcionMenuResaltadaActual para saber cual es la opcion resaltada actual.
 *
 * @example
 *
 * class MenuNuevoJuego : public MenuListLabel{
 * public:
 *    MenuNuevoJuego(GameManagerInterfazUI *game) : MenuListLabel(game) {
 *        mMenuOpcionesText.push_back("Historia");
 *        mMenuOpcionesText.push_back("Multiplayer");
 *        mMenuOpcionesText.push_back("Conexion");
 *    }
 *    void ejecutarAccionOpcionResaltada() {
 *        switch(mOpcionMenuResaltadaActual){
 *            case MENU_OPCION_HISTORIA:
 *                break;
 *            case MENU_OPCION_MULTIPLAYER:
 *                break;
 *            case MENU_OPCION_CONEXION:
 *                break;
 *            default:break;
 *        }
 *    }
 * private:
 *    typedef enum{
 *        MENU_OPCION_HISTORIA,
 *        MENU_OPCION_MULTIPLAYER,
 *        MENU_OPCION_CONEXION,
 *    }MenuOption;
 *
 *};
 *
 *
 */
class MenuListLabel : public InterfazUI{
public:

    MenuListLabel(GameManagerInterfazUI *gameManagerInterfaz)
            : InterfazUI(gameManagerInterfaz) {

    }

    void prepare() override {
        InterfazUI::prepare();
        mLayoutBackGround          = new LayoutVertical();
        mLayout                    = new LayoutVertical();
    }

    virtual void createUI(SDL_Renderer *renderer)  override{

        // Establecemos el fondo con los parametros adecados para que ocupe toda la pantalla
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_HEIGHT,LAYOUT_PARAM_TRUE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_WIDTH,LAYOUT_PARAM_TRUE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_WIDTH,LAYOUT_PARAM_FALSE);
        mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_HEIGHT,LAYOUT_PARAM_FALSE);
        mLayoutBackGround->setBackgroundColor(SDL_Color {0,0,0,255});

        //mLayoutBackGround->setBackgroundTexture(renderer,"data/imagenes/fondos/fondo_menu.bmp",false);

        LabelComponent * nuevoTextLabel;
        for(int i = 0 ; i < mMenuOpcionesText.size() ; i++){
            nuevoTextLabel = new LabelComponent();
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
        SDL_ShowCursor(SDL_DISABLE);//ocultamos el cursor
    }

     /**
     * Establece la nueva opcion del menu resaltada al usuario
     * @param nuevaOpcion Nueva seleccion
     * @return True en caso que se haya resaltado con exito, false en caso contrario
     */
     virtual bool setOpcionResaltada(int nuevaOpcion){
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

    deque<LabelComponent  *> menuTextOptions;
    LayoutVertical * mLayout    = nullptr;
    LayoutVertical *mLayoutBackGround = nullptr;

    deque<string> mMenuOpcionesText;

    SDL_Color mColorLabelNormal    {255,0,0,255};
    SDL_Color mColorLabelResaltado {255,255,0,255};
    int mOpcionMenuResaltadaActual = -1;
};

#endif //BOMBERMAN_MENULISTLABEL_HPP
