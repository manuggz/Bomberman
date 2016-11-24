#include "item.hpp"

Item::Item(SDL_Renderer * gRenderer,string frames,TipoItem tipo,int x,int  y):
    Animacion(new SpriteSheet(gRenderer,"data/imagenes/objetos/items.bmp",6,8),frames,x,y){
    //this->juego=juego;
    mRepeticiones=-1;
    mTipo = tipo;
//    if(!juego->getPuertaAbierta()&&juego->getTipoJuego()==TIPO_NORMAL&&y==juego->getYPuerta()&&x==juego->getXPuerta()){
//        this->tipo=ITEM_PUERTA;
//        juego->setPuertaAbierta(true);
//        }
//    else
//        this->tipo=tipo;

}
/*
void Item::draw(SDL_Renderer * gRenderer){
    mSprSCuadros->setCurrentCuadro(mTipo/8*8 + mTipo + 8*getCuadro());
    Animacion::draw(gRenderer);
    //if(x+16>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)return;
    	//imprimir_desde_grilla(juego->getImagen(IMG_ITEM), , gRenderer, x,y,6,8,0);
}
*/