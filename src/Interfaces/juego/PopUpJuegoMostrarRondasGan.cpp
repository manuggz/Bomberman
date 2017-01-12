#include "PopUpJuegoMostrarRondasGan.hpp"

PopUpJuegoMostrarGanadas::PopUpJuegoMostrarGanadas(GameManagerPopUpInterfaz *gameManager,
                                         int rondasGanadas[5]) : PopUpInterfaz(gameManager) {

    SDL_Log("PopUpJuegoMostrarGanadas::PopUpJuegoMostrarGanadas");
    for(int i=0;i<_PLAYERS;i++)
        mRondasGanadas[i] = rondasGanadas[i];

    conteo = 0;
    animacion = 1;

}

void PopUpJuegoMostrarGanadas::createUI(SDL_Renderer *gRenderer) {
    PopUpInterfaz::createUI(gRenderer);

    mSpriteSheetCarasBomberman = new SpriteSheet();
    mSpriteSheetCarasBomberman->cargarDesdeArchivo(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);

    SpriteSheet  * spriteSheet = new SpriteSheet();
    spriteSheet->cargarDesdeArchivo(gRenderer,"data/imagenes/objetos/cuadro_scoreboard.png",3,1);
    animaCuadro= new Animacion(spriteSheet,"0,0,1,1,2,2",80, mGameManager->getRectScreen().h);

    spriteSheet = new SpriteSheet();
    spriteSheet->cargarDesdeArchivo(gRenderer,"data/imagenes/textos/txt_scoreboard.png",4,1);
    animaTexto = new Animacion(spriteSheet,"0,0,1,1,2,2,3,3",90,38);

    int tmp=0;
    for(int i=0;i<_PLAYERS;i++){
        for(int j=0;j<mRondasGanadas[i];j++){
            tmp++;
        }
    }

    animaTrofeos        = new Animacion*[tmp];
    totalTrofeosCreados = tmp;

    tmp=0;

    for(int i=0;i<_PLAYERS;i++){
        for(int j=0;j<mRondasGanadas[i];j++){
            spriteSheet = new SpriteSheet();
            spriteSheet->cargarDesdeArchivo(gRenderer,"data/imagenes/objetos/trofeo.bmp",1,13);

            if(tmp+1!=totalTrofeosCreados){
                animaTrofeos[tmp]=new Animacion(spriteSheet,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",86+22*j, mGameManager->getRectScreen().h +33*i+8,i);
            }else{
                animaTrofeos[tmp]=new Animacion(spriteSheet,"0,0,1,1,2,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",86+22*j, mGameManager->getRectScreen().h +35*PLAYER_3+1,i);
                animaTrofeos[tmp]->setCuadroDespues(17);
            }
            if(i==PLAYER_3)
                animaTrofeos[tmp]->setY(mGameManager->getRectScreen().h +35*i+1);
            else if(i==PLAYER_4)
                animaTrofeos[tmp]->setY(mGameManager->getRectScreen().h +35*i-4);
            else if(i==PLAYER_5)
                animaTrofeos[tmp]->setY(mGameManager->getRectScreen().h +35*i-7);
            else
                animaTrofeos[tmp]->setY(mGameManager->getRectScreen().h +35*i+6);
            animaTrofeos[tmp]->setRepeticiones(-1);
            tmp++;
        }
    }
}

void PopUpJuegoMostrarGanadas::procesarEvento(SDL_Event * evento){
    PopUpInterfaz::procesarEvento(evento);
    if(animacion==3)
        switch(evento->type){
            case SDL_JOYBUTTONDOWN:if(evento->jbutton.type != SDL_JOYBUTTONDOWN)break;
            case SDL_KEYDOWN:
                mGameManager->closePopUp();
            break;
            
        }

}


void PopUpJuegoMostrarGanadas::update(){
    PopUpInterfaz::update();
    if(animacion==1){
        if((conteo+=3)>=255){
            animacion=2;
            conteo=0;
            mpColorOscurecer.a = 255;
        }else
            mpColorOscurecer.a = (Uint8) conteo;

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

void PopUpJuegoMostrarGanadas::draw(SDL_Renderer * gr){
    PopUpInterfaz::draw(gr);

    if(animacion!=1)
        animaTexto->draw(gr);
    animaCuadro->draw(gr);
    for(int i=0;i<totalTrofeosCreados-1;i++){
        animaTrofeos[i]->draw(gr);
    }
    if(animacion==3&&conteo>=20)animaTrofeos[totalTrofeosCreados-1]->draw(gr);

    mSpriteSheetCarasBomberman->setCurrentCuadro(PLAYER_1*2);
    mSpriteSheetCarasBomberman->draw(gr,64,animaCuadro->getY()+PLAYER_1*35+8);

    mSpriteSheetCarasBomberman->setCurrentCuadro(PLAYER_2*2);
    mSpriteSheetCarasBomberman->draw(gr,64,animaCuadro->getY()+PLAYER_2*35+8);

    mSpriteSheetCarasBomberman->setCurrentCuadro(PLAYER_3*2);
    mSpriteSheetCarasBomberman->draw(gr,64,animaCuadro->getY()+PLAYER_3*35+6);

    mSpriteSheetCarasBomberman->setCurrentCuadro(PLAYER_4*2);
    mSpriteSheetCarasBomberman->draw(gr,64,animaCuadro->getY()+PLAYER_4*35+2);

    mSpriteSheetCarasBomberman->setCurrentCuadro(PLAYER_5*2);
    mSpriteSheetCarasBomberman->draw(gr,64,animaCuadro->getY()+PLAYER_5*35+1);
}

PopUpJuegoMostrarGanadas::~PopUpJuegoMostrarGanadas(){
    SDL_Log("PopUpJuegoMostrarGanadas::PopUpJuegoMostrarGanadas");
    delete animaCuadro;
    delete animaTexto;
    for(int i=0;i<totalTrofeosCreados;i++){
        delete animaTrofeos[i];
    }
    delete mSpriteSheetCarasBomberman;
}
