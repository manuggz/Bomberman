#include "juego_mostrar_gan.hpp"

JuegoMostrarGanadas::JuegoMostrarGanadas(GameManager * game,JuegoBatalla * parent,int batallasGanadas[_PLAYERS]){

    this->game=game;
    juegoEnCurso=parent;
    for(int i=0;i<_PLAYERS;i++)
        this->batallasGanadas[i]=batallasGanadas[i];
    conteo=0;
    animacion=1;


  	animaCuadro=new Animacion(game->getImagen(IMG_CUADRO_SCOREBOARD),3,1,"0,0,1,1,2,2",80,H_SCREEN);
  	animaTexto=new Animacion(game->getImagen(IMG_TXT_SCOREBOARD),4,1,"0,0,1,1,2,2,3,3",90,38);

  	int tmp=0;
    for(int i=0;i<_PLAYERS;i++){
        for(int j=0;j<batallasGanadas[i];j++){
            tmp++;
        }
    }
    animaTrofeos=new Animacion*[tmp];
    totalTrofeosCreados=tmp;
    tmp=0;
    for(int i=0;i<_PLAYERS;i++){
        for(int j=0;j<batallasGanadas[i];j++){
            if(tmp+1!=totalTrofeosCreados){
                animaTrofeos[tmp]=new Animacion(game->getImagen(IMG_TROFEO),1,13,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",86+22*j,H_SCREEN+33*i+8,i);
            }else{
                animaTrofeos[tmp]=new Animacion(game->getImagen(IMG_TROFEO),1,13,"0,0,1,1,2,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",86+22*j,H_SCREEN+35*PLAYER_3+1,i);
                animaTrofeos[tmp]->setCuadroDespues(17);            
            }
            if(i==PLAYER_3)
                animaTrofeos[tmp]->setY(H_SCREEN+35*i+1);
            else if(i==PLAYER_4)
                animaTrofeos[tmp]->setY(H_SCREEN+35*i-4);
            else if(i==PLAYER_5)
                animaTrofeos[tmp]->setY(H_SCREEN+35*i-7);
            else
                animaTrofeos[tmp]->setY(H_SCREEN+35*i+6);
            animaTrofeos[tmp]->setLoop(-1);            
            tmp++;
        }
    }
}


void JuegoMostrarGanadas::crearTexturas(SDL_Renderer * gRenderer) {

    SDL_Surface * tmp;
    tmp = SDL_CreateRGBSurface(SDL_SWSURFACE,W_SCREEN, H_SCREEN, 16,0,0, 0, 255);
    fondoNegro = SDL_CreateTextureFromSurface(gRenderer,tmp);
    SDL_SetRenderTarget(gRenderer,fondoNegro);
    SDL_RenderPresent(gRenderer);
    SDL_SetRenderTarget(gRenderer,NULL);

    tmp=SDL_CreateRGBSurface(SDL_SWSURFACE,W_SCREEN, H_SCREEN, 16,0,0, 0, 255);
    SDL_FillRect(tmp,0,0);
    SDL_SetSurfaceAlphaMod(tmp, (Uint8) conteo);
    fondoNegro = SDL_CreateTextureFromSurface(gRenderer,tmp);
    SDL_FreeSurface(tmp);

}

void JuegoMostrarGanadas::procesarEvento(SDL_Event * evento){
    if(animacion==3)
        switch(evento->type){
            case SDL_JOYBUTTONDOWN:if(evento->jbutton.type != SDL_JOYBUTTONDOWN)break;
            case SDL_KEYDOWN:
                salir();
            break;
            
        }

}
void JuegoMostrarGanadas::update(){
    if(animacion==1){
        if((conteo+=3)>=255){
            animacion=2;
            conteo=0;
    	   SDL_SetTextureAlphaMod(fondoNegro,255);
        }else
            SDL_SetTextureAlphaMod(fondoNegro,conteo);
    	
    }else if(animacion==2){
        if(animaCuadro->getY()<=70){
            animacion=3;
            conteo=0;
        }
        animaCuadro->setY(animaCuadro->getY()-9);
        for(int i=0;i<totalTrofeosCreados;i++){
            animaTrofeos[i]->setY(animaTrofeos[i]->getY()-9);
        }
        
    }else if(animacion==3){
        if(++conteo>20){
            animaTrofeos[totalTrofeosCreados-1]->update();
            conteo=20;
        }
    }
    animaCuadro->update();
    animaTexto->update();
    for(int i=0;i<totalTrofeosCreados-1;i++){
        animaTrofeos[i]->update();
    }
}

void JuegoMostrarGanadas::draw(SDL_Renderer * gr){
    //dibujar_objeto(fondoJuego,0,0,gr);
    //dibujar_objeto(fondoNegro,0,0,gr);
    if(animacion!=1)
        animaTexto->draw(gr);
    animaCuadro->draw(gr);
    for(int i=0;i<totalTrofeosCreados-1;i++){
        animaTrofeos[i]->draw(gr);
    }
    if(animacion==3&&conteo>=20)animaTrofeos[totalTrofeosCreados-1]->draw(gr);
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),PLAYER_1*2,gr,64,animaCuadro->getY()+PLAYER_1*35+8,1,10,0);
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),PLAYER_2*2,gr,64,animaCuadro->getY()+PLAYER_2*35+8,1,10,0);
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),PLAYER_3*2,gr,64,animaCuadro->getY()+PLAYER_3*35+6,1,10,0);
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),PLAYER_4*2,gr,64,animaCuadro->getY()+PLAYER_4*35+2,1,10,0);
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),PLAYER_5*2,gr,64,animaCuadro->getY()+PLAYER_5*35,1,10,0);
}

void JuegoMostrarGanadas::salir(){
    game->cambiarInterfaz(juegoEnCurso);
}
JuegoMostrarGanadas::~JuegoMostrarGanadas(){
    #ifdef DEBUG
        cout << "Destructor de JuegoMostrarGanadas"<<endl;
    #endif
    SDL_DestroyTexture(fondoJuego);
    SDL_DestroyTexture(fondoNegro);
    delete animaCuadro;
    delete animaTexto;
    for(int i=0;i<totalTrofeosCreados;i++){
        delete animaTrofeos[i];
    }
}

bool JuegoMostrarGanadas::isPaused() {
    return false;
}

void JuegoMostrarGanadas::pause() {

}

void JuegoMostrarGanadas::resume() {

}


