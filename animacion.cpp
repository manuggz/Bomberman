#include "animacion.hpp"

Animacion::Animacion(SDL_Surface * img_grilla,int filas,int columnas,string frames,int x,int y,int id):
    control_fra(frames){

    this->imgGrilla=img_grilla;
    this->x=rect.x=x;
    this->y=rect.y=y;
    rect.w=rect.h=16;
    self_kill=false;
    type=ANIMACION;
    this->id=id; 
    f=filas;
    c=columnas;  
    delay=0;
    loop=0;
    indexInicioAniEnd=0;
}

void Animacion::update(Uint8 * teclas){

	if (++delay > DELAY_CAMBIO){
        if(control_fra.avanzar()){
            if(loop!=-1&&--loop<0)
                disable();
            else if(indexInicioAniEnd!=0){
                control_fra.setInicioAnimacion(indexInicioAniEnd);
                indexInicioAniEnd=0;
                control_fra.reiniciar();
            }
        }
        delay=0;
	}
}
void Animacion::disable(){
    kill();
}

void Animacion::setCuadrosFrames(char * frames){
    control_fra.setCuadros(frames);
}

void Animacion::draw(SDL_Surface * screen){
    if(x+16>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)
        imprimir_desde_grilla (imgGrilla,control_fra.cuadro(), screen, x,y,f,c,0);
}
