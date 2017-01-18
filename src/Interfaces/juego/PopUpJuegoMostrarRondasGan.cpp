#include "PopUpJuegoMostrarRondasGan.hpp"
#include "../menu/MenuEscogerMapa.hpp"

PopUpJuegoMostrarGanadas::PopUpJuegoMostrarGanadas(GameManagerPopUpInterfaz *gameManager,
                                         int rondasGanadas[5]) : PopUpInterfaz(gameManager) {

    SDL_Log("PopUpJuegoMostrarGanadas::PopUpJuegoMostrarGanadas");
    for(int i=0;i<Player::N_PLAYERS;i++)
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
    int indice_player_mayor_copas = 0;
    int valor_mayor = 0;

    //int test[5] = {2,3,5,6,5};
    //std::memcpy(mRondasGanadas,test,4*5);

    for(int i=0;i<Player::N_PLAYERS;i++){

        if(mRondasGanadas[i] > valor_mayor) {
            indice_player_mayor_copas = i;
            valor_mayor = mRondasGanadas[i];
        }

        mRondasGanadas[i] = min(mRondasGanadas[i],MAX_VICTORIAS - 1);

        tmp += mRondasGanadas[i];
    }

    animaTrofeos        = new Animacion*[tmp];
    totalTrofeosCreados = tmp;

    tmp=0;

    for(int i=0;i<Player::N_PLAYERS;i++){
        for(int j=0;j<mRondasGanadas[i];j++){
            spriteSheet = new SpriteSheet(gRenderer,"data/imagenes/objetos/trofeo.bmp",1,13);

            if(i != indice_player_mayor_copas || j != mRondasGanadas[i] - 1){
                animaTrofeos[tmp]=new Animacion(spriteSheet,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",86+22*j, mGameManager->getRectScreen().h +33*i+8);
            }else{
                animaTrofeos[tmp]=new Animacion(spriteSheet,"0,0,1,1,2,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",86+22*j, mGameManager->getRectScreen().h + 33*i+8);
                animaTrofeos[tmp]->setCuadroDespues(17);
                id_trofeo_agregado = tmp ;
            }

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
            animaTrofeos[id_trofeo_agregado]->update();
            conteo=20;
        }
    }
    animaCuadro->update();
    animaTexto->update();
    for(int i=0;i<totalTrofeosCreados;i++){
        if(i != id_trofeo_agregado)
        animaTrofeos[i]->update();
    }
}

void PopUpJuegoMostrarGanadas::draw(SDL_Renderer * gr){
    PopUpInterfaz::draw(gr);

    if(animacion!=1)
        animaTexto->draw(gr);

    animaCuadro->draw(gr);

    for(int i=0;i<totalTrofeosCreados;i++){
        if(i != id_trofeo_agregado)
            animaTrofeos[i]->draw(gr);
    }
    if(animacion==3&&conteo>=20)animaTrofeos[id_trofeo_agregado]->draw(gr);

    for(int i = 0; i < Player::N_PLAYERS;i++) {
        mSpriteSheetCarasBomberman->setCurrentCuadro(i * 2);
        mSpriteSheetCarasBomberman->draw(gr, 64, animaCuadro->getY() + i * 33 + 8);
    }

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
