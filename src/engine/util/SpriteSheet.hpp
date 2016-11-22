//
// Created by manuggz on 22/11/16.
//

#ifndef BOMBERMAN_SPRITESHEET_HPP
#define BOMBERMAN_SPRITESHEET_HPP

#include "LTexture.hpp"

class SpriteSheet{
public:

    SpriteSheet()= default;

    SpriteSheet(LTexture * texture, int nFilas, int nColumnas){
        mRectSource.x = 0;
        mRectSource.y = 0;
        mRectSource.w = texture->getWidth()/nColumnas;
        mRectSource.h = texture->getHeight()/nFilas;
        mFilas = nFilas;
        mColumnas =nColumnas;
        mTexture = texture;
    }

    bool cargarDesdeArchivo(SDL_Renderer * gRenderer,std::string ruta,int nFilas,int nColumnas,bool colorClave = false){

        if(mTexture != nullptr){
            delete mTexture;
            mTexture = new LTexture();
        }
        mTexture->loadFromFile(ruta,gRenderer,colorClave);
        mRectSource.x = 0;
        mRectSource.y = 0;
        mRectSource.w = mTexture->getWidth()/nColumnas;
        mRectSource.h = mTexture->getHeight()/nFilas;
        mFilas = nFilas;
        mColumnas =nColumnas;
        mTexture = mTexture;
        cargada_desde_archivo = true;
    }

    int getWidthCuadro() {
        return mRectSource.w;
    }

    void setCurrentCuadro(int nCuadro){
        mRectSource.x = (nCuadro % mColumnas) * mRectSource.w;
        mRectSource.y = (nCuadro / mColumnas) * mRectSource.h;
    }

    void setAlpha(Uint8 nuevoValor){
        //mAlpha = nuevoValor;
        mTexture->setAlpha(nuevoValor);
    }
    int getHeightCuadro() {
        return mRectSource.h;
    }

    void draw(SDL_Renderer * gRenderer,int x,int y){
        mTexture->render(gRenderer,x,y,&mRectSource);
    }

    int getNColumnas() {
        return mColumnas;
    }

    ~SpriteSheet(){
        if(cargada_desde_archivo)
            delete mTexture;
    }

private:
    LTexture * mTexture = nullptr;
    SDL_Rect mRectSource {0,0,0,0};
    int mFilas = 0;
    int mColumnas = 0;

    bool cargada_desde_archivo = false;
    //int mAlpha = -1;
};
#endif //BOMBERMAN_SPRITESHEET_HPP
