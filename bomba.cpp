#include "bomba.hpp"

Bomba::Bomba(SDL_Surface *imgBomba,int x,int y,int alcance,int lanzador,int id):
    Animacion(imgBomba,1,3,"0,0,0,1,1,1,2,2,2,2,2,2,1,1,1,0,0,0",x,y,id){
    this->lanzador=lanzador;
    this->alcance=alcance;
    type=BOMBA;
    loop=2;
}


