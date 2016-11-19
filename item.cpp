#include "item.hpp"

Item::Item(Juego * juego,int x,int  y, int tipo,int id):
    Animacion(NULL,0,0,"0,1",x,y,id){
    this->juego=juego;
    type=ITEM;
    loop=-1;
    
    if(!juego->getPuertaAbierta()&&juego->getTipoJuego()==TIPO_NORMAL&&y==juego->getYPuerta()&&x==juego->getXPuerta()){
        this->tipo=ITEM_PUERTA;
        juego->setPuertaAbierta(true);
        }
    else
        this->tipo=tipo;

}

void Item::draw(SDL_Renderer * gRenderer){
    if(x+16>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)
    	imprimir_desde_grilla(juego->getImagen(IMG_ITEM), tipo/8*8 + tipo + 8*getCuadro(), gRenderer, x,y,6,8,0);
}
