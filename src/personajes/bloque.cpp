#include "bloque.hpp"

Bloque::Bloque(Juego * juego,int x,int y,int id):
    Animacion(nullptr,"0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,4,4,5",x,y,id){
    this->juego=juego;
    //idTileBloque=juego->getIdTile();
}

void Bloque::disable(){
    /*
    if(juego->isBloqueItem(x,y)){
        juego->addSprite(ITEM,x,y,juego->getTipoNuevoItem(true));
    }
    juego->romperBloque(x,y);
    kill();*/
}

void Bloque::draw(SDL_Renderer * gRenderer){
    if(x+16>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)
        imprimir_desde_grilla (juego->getImagen(IMG_BLOQUES_FIRE),getCuadro()+idTileBloque*6, gRenderer, x,y,4,6,0);
}
