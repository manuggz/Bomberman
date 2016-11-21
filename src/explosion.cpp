#include "explosion.hpp"


Explosion::Explosion(Juego * juego,int x,int y,int alcance_llamas,int lanzador,int id):
    Animacion(NULL,0,0,"0,1,2,3,4,4,3,2,1,1,0",x,y,id){
    this->juego=juego;
    
    this->lanzador=lanzador;
    this->alcance_llamas=alcance_llamas;
    detectarAlcance(DERECHA,16,0);
    detectarAlcance(IZQUIERDA,-16,0);
    detectarAlcance(ABAJO,0,16);
    detectarAlcance(ARRIBA,0,-16);

    //reproducimos un sonido
    juego->play(SFX_EXPLOSION);
    this->type=EXPLOSION;
}

void Explosion::detectarAlcance(int dir,int aum_x,int aum_y){

    int es_bloque_rompible,colision_con_bomba,colision_con_item;
    int globo_anyadido;
    SDL_Rect coli={0,0,16,16};
    for(int i=1;i<alcance_llamas+1;i++){
        coli.x=x+aum_x*i;
        coli.y=y+aum_y*i;
        alcances[dir]=i;
        if(coli.x<juego->getEjeXVisual()||\
           coli.x+coli.w>juego->getEjeXVisual()+juego->getAnchoMapa()||\
           coli.y<juego->getEjeYVisual()||\
           coli.y+coli.h>juego->getEjeYVisual()+juego->getAltoMapa()){
            --alcances[dir];
            return;
        }
        es_bloque_rompible=juego->isBloqueRompible(coli.x,coli.y);
        colision_con_bomba=juego->colision(BOMBA,coli);
        colision_con_item=juego->colision(ITEM,coli);

        if(colision_con_bomba!=-1){
            juego->setRepeticionBomba(colision_con_bomba,0);//se acelera el 'explote'
            --alcances[dir];
            return;
        }

        if(juego->isBloqueDuro(coli.x,coli.y)||es_bloque_rompible||colision_con_item!=-1){


            if(es_bloque_rompible&&juego->colision(BLOQUE,coli)==-1){
                juego->addSprite(BLOQUE,coli.x,coli.y);
            }else if(colision_con_item!=-1){
                if(juego->getTipoItem(colision_con_item)!=Item::ITEM_PUERTA){
                    juego->addSprite(new Animacion(juego->getImagen(IMG_ITEM_FIRE),1,7,"0,0,0,1,1,2,2,2,3,3,4,4,5,5,6,6",coli.x,coli.y));
                    juego->killSprite(ITEM,colision_con_item);
                }else{
                     int x,y;
                     juego->getPosicion(ITEM,colision_con_item,x,y);
//                     globo_anyadido=juego->addSprite(GLOBO,new Globox,y);
//                     if(globo_anyadido!=-1)
//                        juego->setProteccion(GLOBO,globo_anyadido,true);
                }
            }

            --alcances[dir];
            return;
        }

    }

}
void Explosion::dibujarFlama(int dir,int aum_x,int aum_y,int cuadro_normal,int cuadro_final,SDL_Renderer * gRenderer)
{
    int i;
	int x,y;

    for(i=1;i<alcances[dir];i++)
    {
        x=this->x+aum_x*i;
        y=this->y+aum_y*i;
        if(x+16>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)
        imprimir_desde_grilla (juego->getImagen(IMG_EXPLOSION),cuadro_normal+COLUMNAS_EXPLO*getCuadro(),gRenderer, x,y,FILAS_EXPLO,COLUMNAS_EXPLO,0);
    }
    x=this->x+aum_x*i;
    y=this->y+aum_y*i;
    if(x+10>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0){
        if(alcances[dir]==alcance_llamas)
        	imprimir_desde_grilla (juego->getImagen(IMG_EXPLOSION),cuadro_final+COLUMNAS_EXPLO*getCuadro(), gRenderer,  x,y,FILAS_EXPLO,COLUMNAS_EXPLO,0);
        else if(alcances[dir])
        	imprimir_desde_grilla (juego->getImagen(IMG_EXPLOSION),cuadro_normal+COLUMNAS_EXPLO*getCuadro(),gRenderer,  x,y,FILAS_EXPLO,COLUMNAS_EXPLO,0);
    }
}


void Explosion::draw(SDL_Renderer * gRenderer){

    //DIBUJAMOS EL CENTRO
    if(x+10>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)
	     imprimir_desde_grilla (juego->getImagen(IMG_EXPLOSION),2+COLUMNAS_EXPLO*getCuadro(), gRenderer, x,y,FILAS_EXPLO,COLUMNAS_EXPLO,0);

    dibujarFlama(DERECHA,16,0,3,4,gRenderer);
    dibujarFlama(IZQUIERDA,-16,0,1,0,gRenderer);
    dibujarFlama(ABAJO,0,16,6,7,gRenderer);
    dibujarFlama(ARRIBA,0,-16,6,5,gRenderer);


}

bool Explosion::colision(SDL_Rect & rect_coli){
    //COLISION CON EL EJE X de la bomba

    rect.x=x - alcances[IZQUIERDA]*16;
    rect.y=y;
    rect.w=alcances[IZQUIERDA]*16+16 + alcances[DERECHA]*16;
    rect.h=16;
    if(rects_colisionan(rect,rect_coli))
        return true;

    //COLISION CON EL EJE Y de la bomba
    rect.w=16;
    rect.x=x;
    rect.y=y - alcances[ARRIBA]*16;
    rect.h=alcances[ARRIBA]*16+16 + alcances[ABAJO]*16;
    if(rects_colisionan(rect,rect_coli))
        return true;

    return false;
     
}
