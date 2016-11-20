//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_LAYOUTCOMPONENT_HPP
#define BOMBERMAN_LAYOUTCOMPONENT_HPP


#include <SDL_render.h>
#include <iostream>
#include "../util/LTexture.hpp"

using namespace std;
class LayoutComponent{
public:

    /**
     * Inicializa el componente
     * @return
     */
    LayoutComponent(){

        mFillParentHeight = false;
        mFillParentWidth  = false;

        mCenterParentVertical = false;
        mCenterParentHorizontal = false;

        mWrapWidth = true;
        mWrapHeight = true;

        mTextureBackground = nullptr;

        mDisabled = true;

        mMarginTop = 0;

        mInternalRect.x = mInternalRect.y = mInternalRect.w = mInternalRect.h = 0;
        mDrawRect.x = mDrawRect.y = mDrawRect.w = mDrawRect.h = 0;

        mBackgroundColor.r = mBackgroundColor.g =mBackgroundColor.b = mBackgroundColor.a = 0;
        mEstablecidoColorFondo = false;
    }

    /**
     * Establece si se quiere que el componente ocupe toda la altura disponible en el parent
     * @param fillParentHeight booleando indicando el nuevo valor
     */
    void setFillParentHeight(bool fillParentHeight){
        mFillParentHeight = fillParentHeight;
        mWrapHeight = false; // No queremos que la altura se establezca de acuerdo al contenido
    }
    /**
     * Establece si se quiere que la anchura del componente ocupe/se expanda para ocupar tod el espacio disponible en parent
     * @param fillParentWidth
     */
    void setFillParentWidth(bool fillParentWidth){
        mFillParentWidth = fillParentWidth;
        mWrapWidth = false; // No queremos que el ancho se establezca de acuerdo al contenido
    }

    /**
     * Establece si queremos que el ancho sea determinado por el contenido de este componente
     * @param wrapWidth
     */
    void setWrapWidth(bool wrapWidth){
        mWrapWidth = wrapWidth;
        mFillParentWidth = false; // No queremos que el ancho sea determinado por el parent
    }

    /**
     * Establece si se quiere que la altura sea determinada por el contenido
     * @param wrapHeight
     */
    void setWrapHeight(bool wrapHeight){
        mWrapHeight = wrapHeight;
        mFillParentHeight = false; // No queremos que la altura sea determinada por el parent
    }

    /**
     * Establece si queremos que el componente se centre verticalmente en el parent
     * @param centerParentVertical
     */
    void setCenterParentVertical(bool centerParentVertical){
        mCenterParentVertical = centerParentVertical;
        setWrapHeight(true); // Que la altura sea del contenido
    }

    /**
     * Establece si queremos que el componente se centre horizontalmente en el parent
     * @param centerParentHorizontal
     */
    void setCenterParentHorizontal(bool centerParentHorizontal){
        mCenterParentHorizontal = centerParentHorizontal;
        setWrapWidth(true); // Que la anchura sea del contenido
    }

    /**
     * Establece la textura a dibujar en el fondo del componente
     * @param lTexture
     */
    void setBackgroundTexture(LTexture * lTexture){
        if(mTextureBackground != nullptr){
            mTextureBackground->free();
            delete lTexture;
            mTextureBackground = nullptr;
        }
        mTextureBackground = lTexture;
    }

    /**
     * Establece un estado que hace que redibuje este componente al mismo tiempo
     * que se recalculen los estados del layout que contiene este componente.
     *
     * Después de modificar un/varios estado de este componente se debe llamar a esta funcion para que
     * se puedan ver en la pantalla.
     */
    void setDisabled(bool nuevo){
        mDisabled = nuevo;
    }

    /**
     * Retorna el estado de la variable mDisabled.
     * @return
     */
    virtual bool isDisabled(){
        return mDisabled;
    }

    /**
     * Obtiene el ancho de dibujo
     * @return
     */
    int getWidth(){
        return mDrawRect.w;
    }

    /**
     * Obtiene el alto de dibujo
     * @return
     */
    int getHeight(){
        return mDrawRect.h;
    }

    /**
     * Se encarga de crear las texturas del componente asi como otras acciones asociadas con el renderer
     * Notar que despues de esta funcion se debe llamar a calculateRect, es decir, realizar una nueva
     * calculacion del rectangulo de dibujo del componente
     * @param gRenderer Render de la pantalla
     */
    virtual void pack(SDL_Renderer * gRenderer) = 0;

    /**
     * Calcula el Rectangulo de dibujo para el componente
     * @param disponible
     */
    virtual void calculateSize(int widthDisponible,int heightDisponible){

        mDrawRect.w = mInternalRect.w;
        mDrawRect.h = mInternalRect.h;

        // Si se va a abarcar tod el espacio disponible
        if(mFillParentWidth){
            mDrawRect.w = widthDisponible;
        }

        if(mDrawRect.w > widthDisponible){
            mDrawRect.w = widthDisponible;
        }

        // Si se va a abarcar tod el espacio disponible
        if(mFillParentHeight){
            mDrawRect.h = heightDisponible;
        }
        if(mDrawRect.h > heightDisponible){
            mDrawRect.h = heightDisponible;
        }

    }

    virtual void calcularPosicion(SDL_Rect & dest){

        mDrawRect.x = dest.x;
        mDrawRect.y = dest.y;

        if(mCenterParentHorizontal){
            mDrawRect.x = dest.x +  dest.w/2  - mDrawRect.w/2;
        }

        if(mCenterParentVertical){
            mDrawRect.y = dest.y + dest.h/2  - mDrawRect.h/2;
        }
    }
    /**
     * Establece un color de fondo para el componente
     * @param color
     */
    void setBackgroundColor(SDL_Color color){
        mBackgroundColor = color;
        mEstablecidoColorFondo = true;
    }

    /**
     * Dibuja el componente
     * @param gRenderer
     */
    virtual void draw(SDL_Renderer * gRenderer){


        // Dibuja el color de fondo
        if(mEstablecidoColorFondo){
            Uint8 r,g,b,a;
            SDL_GetRenderDrawColor(gRenderer,&r,&g,&b,&a);
            SDL_SetRenderDrawColor(gRenderer,mBackgroundColor.r,mBackgroundColor.g,mBackgroundColor.b,mBackgroundColor.a);
            SDL_RenderFillRect(gRenderer,&mDrawRect);
            SDL_SetRenderDrawColor(gRenderer,r,g,b,a);
        }

        // Dibuja la imagen de background
        if(mTextureBackground != nullptr){
            SDL_Rect clip = {0,0,mDrawRect.w,mDrawRect.h};
            mTextureBackground->render(gRenderer,mDrawRect.x,mDrawRect.y,&clip);
        }



    };

    void setMarginTop(int margenTop) {
        mMarginTop = margenTop;
    }


protected:

    bool mFillParentWidth;
    bool mFillParentHeight;

    bool mWrapWidth;
    bool mWrapHeight;

    bool mCenterParentHorizontal;
    bool mCenterParentVertical;

    LTexture * mTextureBackground;

    bool mDisabled;

    // Este es el rectangulo que representa el contenido real del componente
    // Se distingue del de dibujo porque puede ser mas grande
    SDL_Rect mInternalRect;

    // Este es el rectangulo de dibujo limitado por el espacio en el layout
    SDL_Rect mDrawRect;

    SDL_Color mBackgroundColor;
    bool mEstablecidoColorFondo; // Controla si se debe dibujar el color de fondo

    int mMarginTop;
};
#endif //BOMBERMAN_LAYOUTCOMPONENT_HPP
