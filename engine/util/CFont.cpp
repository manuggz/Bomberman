//
// Created by manuggz on 19/11/16.
//

#include "CFont.hpp"

/**
 * Inicia las variables
 * */
CFont::CFont() {

    mFont= nullptr;
    //mTexture = new LTexture();
    mPathFont = "";
    mSize = -1;
    mColor.r = mColor.g = mColor.b = 0;
    mColor.a = 255;
}


bool CFont::loadFont(string pathFont,int size){

    mFont =  TTF_OpenFont(pathFont.c_str(), size );

    if(!mFont){
        cerr << "No se logró cargar la fuente : "<< pathFont << " SDL Error: " << TTF_GetError() << endl;
        return false;
    }

    mPathFont = pathFont;
    mSize = size;

    return true;
};

LTexture * CFont::createTextureFromText(SDL_Renderer *gRenderer, string texto) {

    LTexture * nuevaTextura = new LTexture();
    nuevaTextura->loadFromRenderedText(gRenderer,mFont,texto,mColor);
    return nuevaTextura;
}

CFont::~CFont() {

    TTF_CloseFont( mFont );
    mFont = NULL;

}

void CFont::setTextColor(SDL_Color color) {
    mColor = color;
}

