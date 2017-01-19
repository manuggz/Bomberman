//
// Created by manuggz on 17/01/17.
//

#ifndef BOMBERMAN_MENSAJEUSUARIOTOAST_HPP
#define BOMBERMAN_MENSAJEUSUARIOTOAST_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include "../engine/util/LTexture.hpp"
#include "../engine/util/BitmapFont.hpp"
#include "../engine/util/Toast.hpp"

class MensajeUsuarioToast:public Toast{
public:


    MensajeUsuarioToast(GameManagerInterfazUI *pGameManagerInterfazUI, std::string mensaje,int duracion) :
            Toast(pGameManagerInterfazUI, mensaje,duracion) {

    }

    void createUI(SDL_Renderer * gRenderer) override {
        fondo = new LTexture();
        fondo->cargarDesdeArchivo("data/imagenes/objetos/rectangulo_redondeado.png",gRenderer,false);

        pBitmapFont = new BitmapFont(gRenderer,"data/fuentes/fuente2_16_normal.png");

        mPosRect.w = fondo->getWidth();
        mPosRect.h = fondo->getHeight();

        mPosRect.x = mpGameManagerInterfaz->getNativeWidth()/2 -  mPosRect.w/2;
        mPosRect.y = mpGameManagerInterfaz->getNativeHeight() -  mPosRect.h - mMarginBottom;

        int widthMensaje = pBitmapFont->calculateWidth(mensaje);
        int heightMensaje = pBitmapFont->getHeight();
        pBitmapFontRenderer= new BitmapFontRenderer(
                pBitmapFont,
                mpGameManagerInterfaz->getNativeWidth()/2 -  widthMensaje/2,
                mPosRect.y + mPosRect.h/2 - heightMensaje/2
        );
        pBitmapFontRenderer->setText(mensaje);
    }

    void draw(SDL_Renderer * gRenderer)override {
        fondo->draw(gRenderer,mPosRect.x,mPosRect.y);
        pBitmapFontRenderer->draw(gRenderer);
    }

    ~MensajeUsuarioToast(){
        delete fondo;
        delete pBitmapFont;
        delete pBitmapFontRenderer;
    }

private:
    LTexture * fondo;
    SDL_Rect   mPosRect {0,0,0,0};
    int mMarginBottom = 10;

    BitmapFont * pBitmapFont;
    BitmapFontRenderer * pBitmapFontRenderer;
};
#endif //BOMBERMAN_MENSAJEUSUARIOTOAST_HPP
