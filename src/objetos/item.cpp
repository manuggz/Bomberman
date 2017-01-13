#include "item.hpp"

Item::Item(SDL_Renderer * gRenderer,string frames,TipoItem tipo,int x,int  y):
    Animacion(new SpriteSheet(gRenderer,"data/imagenes/objetos/items.bmp",6,8),frames,x,y){
    mRepeticiones=-1;
    mTipo = tipo;

}
