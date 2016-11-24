#include "juego.hpp"
#include "../engine/util/LTimer.hpp"

#define MAPA_EJE_X 0
#define MAPA_EJE_Y 32

Juego::Juego (GameManager * gameManager, int x, int y, int idTerrenoBatalla, int victorias, int minutos, bool isPlayerActivo[_PLAYERS])
:InterfazUI(x,y),mGrpSprites(this){
    cout << "Constructor de Juego:"<<this<<endl;

    mGameManager = gameManager;

    for(int i = 0; i < _PLAYERS;i++) {
        mIsPlayerActivado[i] = isPlayerActivo[i];
    }

    mIDTerrenoMapa = idTerrenoBatalla;
    mMinutos       = minutos*60;
    mNVictorias    = victorias;
}

void Juego::prepare() {
    InterfazUI::prepare();

    //mMapa           = new Mapa(this,getX(),getY());
    mMapa           = new NivelMapa();
    mGameTimer      = new LTimer();

    //crearReferencias();

    //this->idTerrenoActual=idTerrenoBatalla;
    crearPlayersActivos();
    //cargarMapa();
    //muertosPorTiempo=false;

    //repro_war=false;
    //iniciado=false;

    //patinesLanzados=false;
    //bombasMaxLanzado=false;
    //alcanceMaxLanzado=false;

    //animandoEntradaMapaVertical=true;
    //desplazamiento=0;


    //displayMensage("�Qu� gane el mejor!");//se presenta el mensage con el nivel actual
//    estado_siguiente=PLAY;
    //id_lider_ganadas=PLAYER_NONE;
    //min=minutos*60;
    //vic=victorias;
}

void Juego::createUI(SDL_Renderer *gRenderer) {
    SDL_ShowCursor(SDL_DISABLE);
    mMapa->cargar(gRenderer,"data/niveles/batalla/mapa_batalla_" + std::to_string(mIDTerrenoMapa + 1) + ".tmx");
    mGameRenderer = gRenderer;
}

void Juego::start() {
    InterfazUI::start();
    establecerValoresPlayersDeMapa();
    agregarPlayersActivos();
    mGameTimer->start();
    //playSonido((CodeMusicSonido)(4 + rand()%1));
}


/**
 * Una vez cargado el mapa se deben iniciar los players con los valores iniciales que se establecieron que
 * el mapa especifica
 */
void Juego::establecerValoresPlayersDeMapa() {

    for(int i = 0; i < _PLAYERS;i++) {
        if(mIsPlayerActivado[i] && mPlayerSprite[i]) {
            mPlayerSprite[i]->move(mMapa->getPosXPlayer((IdPlayer)(PLAYER_1 + i))
                    ,mMapa->getPosYPlayer((IdPlayer)(PLAYER_1 + i)));
            mPlayerSprite[i]->setVidas(std::stoi(mMapa->getMapProperty(MAPA_PROPERTY_X_N_VIDAS_PLAYER)));
            mPlayerSprite[i]->setNBombas(std::stoi(mMapa->getMapProperty(MAPA_PROPERTY_N_BOMBAS)));
            mPlayerSprite[i]->setAlcanceBombas(std::stoi(mMapa->getMapProperty(MAPA_PROPERTY_ALCANCE_BOMBAS)));
        }
    }
}

/**
 * Crea las clases que controlan los players en memoria
 */
void Juego::crearPlayersActivos() {

    for (int i = 0; i < _PLAYERS; i++) {
        if (mIsPlayerActivado[i]) {
            mPlayerSprite[i] = new Player(this, (IdPlayer) i);
        }
    }
}

/**
 * Agrega los players que fueron activados a los grupos del juego
 * Lo cual hace que se actualizen y dibujen
 */
void Juego::agregarPlayersActivos() {
    for (int i = 0; i < _PLAYERS; i++) {
        if (mIsPlayerActivado[i]) {
            mGrpSprites.add(mPlayerSprite[i]);
            mGrpPlayers.add(mPlayerSprite[i]);
        }
    }
}


/*mGameTimer->setTicksPerdidos(4);

    if(comprobar_players){
        for(int i=0;i<_PLAYERS;i++){
            if(refeSprites[PLAYER][i]){//si fue elegido para que batalle
                if(!isActivo(PLAYER,i)){//si no esta en pantalla
                    mGrpSprites->add(refeSprites[PLAYER][i]);
                    spriteActivos[PLAYER]++;
                }else{//si sobrevivio a la batalla
                    static_cast<Player *>(refeSprites[PLAYER][i])->posicionInicial();
                }*
                static_cast<Player *>(refeSprites[PLAYER][i])->setVidas(data->getVidas());
                static_cast<Player *>(refeSprites[PLAYER][i])->reiniciar();
            }
        }
    }

    clearSprites();
}
*/

/*void Juego::crearReferencias(){
    /*Inicia y crea las estructuras para administrar los personajes
    
    for(int i=0;i<_REFERENCIADOS;i++){
        refeSprites[i]=new Sprite* [totalSprite[i]];
        spriteActivos[i]=0;
        for(int j=0;j<totalSprite[i];j++)
            refeSprites[i][j]=NULL;
    }
    
}*/
void Juego::procesarEvento(SDL_Event * evento){
    switch(evento->type){
        case SDL_KEYDOWN:
             switch(evento->key.keysym.sym){
                case SDLK_ESCAPE:
                    mGameManager->goBack();
                    break;
                case SDLK_TAB:
                     /*if(estado!=DISPLAY_MSG&&!pausado){
                         mostrar_kills=!mostrar_kills;
                         if(mostrar_kills)
                             juego_preparar_kills(juego);
                     }*/
                     break;
             }
        break;
        
    }
    
}

/*
void Juego::displayMensage(const char *  mensage){
  //realiza operaciones para presentar un mensage al usuario

  estado=DISPLAY_MSG;
  y_msg=x_msg=0;
  vel_y=0.0;
  strncpy(msg_mostrar,mensage,50);
  estado_siguiente=PLAY;
}

void Juego::estadoDisplayMensage(){
//efecto sobre texto (autor: Hugo Ruscitii -http://www.loosersjuegos.com.ar- ) 
    static int dir=1;

    x_msg += dir;
	vel_y += 0.1;
	if (y_msg >= H_SCREEN/2&&vel_y>0)
	{
		vel_y -=1.2; // pierde fuerza al tocar el suelo
		vel_y *= -1;
        if((int)vel_y==0)
        {
            vel_y=0;
           estado=estado_siguiente;
//           retraso=50;
           if(_quit){
                salir();
            }
        }
	}
	else{
		y_msg += (int) vel_y;
	}
	if(x_msg > W_SCREEN-200)
	   dir=-1;
	else if(x_msg < 80)
	   dir=1;
}
*/
void Juego::playSfx(CodeMusicEfecto code) {
     mGameManager->play(code);
}
void Juego::playSonido(CodeMusicSonido code){
     mGameManager->playSonido(code);
}

/*
void Juego::clearSprites(bool elimina_players){
    /*Elimina todas las referencias de refeSprites si especifica "all_clear" sino no se borrara los players ni los cuadros en memoria*
    #ifdef DEBUG
        cout << "Llamado a clearSprites"<<endl;
    #endif
     int count=0;
     for(int i=0;i<_REFERENCIADOS;i++){
        if(!elimina_players&&i==PLAYER)continue;

        if(spriteActivos[i]>0){
             for(int j=0;j<totalSprite[i];j++){
                 if(refeSprites[i][j]!=NULL){
                     mGrpSprites->erase(refeSprites[i][j]);
                    #ifdef DEBUG
                        cout << "Eliminando Sprite:"<<refeSprites[i][j]<<endl;
                    #endif
                     delete refeSprites[i][j];
                     refeSprites[i][j]=NULL;
                     if(++count==spriteActivos[i]){
                         spriteActivos[i]=0;
                         count=0;
                         break;
                     }
                }
             }
        }
     }

}
*
int Juego::getLanzador(TipoSprite type,int id_spri){
    if(type==BOMBA||type==EXPLOSION)
        return static_cast<Bomba *>((refeSprites[type][id_spri]))->getLanzador();
}
*
int Juego::getTipoItem(int id_item){
         return static_cast<Item *>(refeSprites[ITEM][id_item])->getTipoItem();
}*

bool Juego::isActivo(TipoSprite type,int id){
     if(type==PLAYER)
         return refeSprites[type][id]!=NULL&&static_cast<Player *>(refeSprites[type][id])->isActivo();
     else
         return refeSprites[type][id]!=NULL;
}
*
void Juego::setPuntaje(IdPlayer id,int nuevo){
    mPuntajePlayer[id]  = nuevo;
     //static_cast<Player *>((refeSprites[PLAYER][id]))->setPuntaje(nuevo);
}

int Juego::getPuntaje(IdPlayer id){
    return mPuntajePlayer[id];
     //return static_cast<Player *>((refeSprites[PLAYER][id]))->getPuntaje();
}
/*
void Juego::setEstadoPlayer(IdPlayer id,EstadoSprite nuevo){
     static_cast<Player *>((refeSprites[PLAYER][id]))->cambiarEstado(nuevo);
}*/

int Juego::getSegundosInicioNivel(){
    return mGameTimer->getTicks()/1000;
}

/*int Juego::getActivos(TipoSprite type,int & id){
    for(int i=0;i<totalSprite[type],spriteActivos[type];i++)
        if((refeSprites[type][i]!=NULL&&type!=PLAYER)||
        (type==PLAYER&&isActivo(PLAYER,i))){
             id=i;
             return spriteActivos[type];
        }
    return 0;
}*/
/*
void Juego::setActivos(TipoSprite type,int nuevo){
    spriteActivos[type]=nuevo;
}

int Juego::getActivosId(TipoSprite type,IdPlayer  id){
    /*Obtiene todos los personajes activos cuyo lanzador fue el id*
    int count=0;
    if(spriteActivos[type]){
        for(int i=0;i<totalSprite[type];i++){
            if(refeSprites[type][i]!=NULL&&(type==BOMBA||type==EXPLOSION)&&static_cast<Bomba *>(refeSprites[type][i])->getLanzador()==id){
                 count++;
            }
        }
    }
    return count;
}
*/
/*void Juego::killSprite(int type,int id_sprite){
     if(refeSprites[type][id_sprite]!=NULL){
         refeSprites[type][id_sprite]->kill();
         spriteActivos[type]--;
         Sprite * spri=refeSprites[type][id_sprite]; // por si se necesitan saber datos delsprite que se eliminra antes de hacerlo
         refeSprites[type][id_sprite]=NULL; /*Notese que el grupo "mGrpSprites" sige referenciandolo, por lo que �l
         se encargara de eliminarlo de memoria*

         if(type==BOMBA){
             /*se agrega una explosion en la posicion de la bomba con el alcance que ella tenia*
             addSprite(EXPLOSION,
                 spri->getX(),spri->getY(),
                 static_cast<Bomba *>(spri)->getLanzador(),static_cast<Bomba *>(spri)->getAlcance());
             
         }
         else if(type==BOMBA){
             /*se agrega una explosion en la posicion de la bomba con el alcance que ella tenia
             addSprite(EXPLOSION,
                 refeSprites[type][id_sprite]->getX(),refeSprites[type][id_sprite]->getY(),
                 refeSprites[type][id_sprite]->getLanzador(),refeSprites[type][id_sprite]->getAlcance());
             
         }*
     }
     
}*

void Juego::soloKill(int type,int id_sprite){
     if(refeSprites[type][id_sprite]!=NULL){
         refeSprites[type][id_sprite]->kill();
         spriteActivos[type]--;
         refeSprites[type][id_sprite]=NULL; /*Notese que el grupo "mGrpSprites" sige referenciandolo, por lo que �l
         se encargara de eliminarlo de memoria*
     }
     
}
void Juego::erase(int type,int id_sprite){
    //Elimina parcialmente a un sprite ya que no lo muestra pero sigue en memoria
     if(refeSprites[type][id_sprite]!=NULL){
         spriteActivos[type]--;
         mGrpSprites->erase(refeSprites[type][id_sprite]);
    }
}

void Juego::addSprite(Sprite * spri){
    int regresar;
    if(spriteActivos[spri->getTipo()]==totalSprite[spri->getTipo()]){
        delete spri;
        spri=NULL;
    }

    for(int i=0;i<totalSprite[spri->getTipo()];i++){
            if(refeSprites[spri->getTipo()][i]==NULL){
                refeSprites[spri->getTipo()][i]=spri;
                spriteActivos[spri->getTipo()]++;
                mGrpSprites->add(refeSprites[spri->getTipo()][i]);
                refeSprites[spri->getTipo()][i]->setId(i);
                return;
            }
    }
    return ;
}

int Juego::addSprite(int type,int x,int y,int lanzador,int otra_var){
    if(spriteActivos[type]==totalSprite[type]) return -1;//No hay espacio

    for(int i=0;i<totalSprite[type];i++){
            if(refeSprites[type][i]==NULL){
                if(type==BOMBA)
                    refeSprites[type][i]=new Bomba(getImagen(IMG_BOMBA),x,y,static_cast<Player *>(refeSprites[PLAYER][lanzador])->getAlcanceBombas(),(IdPlayer)lanzador,i);
                else if(type==EXPLOSION)
                    refeSprites[type][i]=new Explosion(this,x,y,otra_var,(IdPlayer)lanzador,i);/*otra_var=alcance*
                else if(type==ITEM)
                    refeSprites[type][i]=new Item(this,x,y,lanzador,i);/*lanzador=TipoItem*
                else if(type==BLOQUE)
                    refeSprites[type][i]=new Bloque(this,x,y,i);/*lanzador=TipoItem*
                else if(type==GLOBO)
//                    refeSprites[type][i]=new Explosion(this,x,y,otra_var,lanzador)/*otra_var=alcance*
                    cout << "Not implemented yet"<<endl;  

                spriteActivos[type]++;
                mGrpSprites->add(refeSprites[type][i]);
                return i;
            }
    }
    return -1;
                
}
void Juego::getPosicion(TipoSprite type, int id,int & x,int & y){
     x=refeSprites[type][id]->getX();
     y=refeSprites[type][id]->getY();
}


int Juego::colision(SDL_Rect & rect_coli,int * lado_colision,bool solo_bloques_duros){
    /*Comprueba si un rect colisiona con el nivel*
    return mMapa->colision(&rect_coli,lado_colision,solo_bloques_duros);
}

int Juego::colision(TipoSprite  type[],int tamanyo,SDL_Rect & rect_coli){
    /*Detecta colisiones por conjuntos de colision*
    int id_coli;
    for(int i=0;i<tamanyo;i++){
        id_coli=colision(type[i],rect_coli);
        if(id_coli!=-1)return id_coli;
    }
    return -1;
}

 int Juego::colision(TipoSprite type,SDL_Rect & rect_coli,int id_ignorar){
    /*regresa True si "rect_coli" colisiona con un Sprite de refeSprites[TYPE]*
    if(type==NIVEL){
       int err=colision(rect_coli,&err,false);
       return (err)?1:-1;
    }else if(spriteActivos[type]>0){
        int cont=0;
	    for(int i=0;i<totalSprite[type];i++){
	       if(refeSprites[type][i]!=NULL&&i!=id_ignorar){
                    if(refeSprites[type][i]->colision(rect_coli)){
                            return i;//regresa el indice de con quien colisiona 
                    }
                if(++cont==spriteActivos[type])return -1;
            }
        }
    }
    return -1;
}
*/

/**
 * Actualiza la lógica del juego
 */
void Juego::update(){
    const Uint8 *teclas= SDL_GetKeyboardState(NULL);//se obtiene el estado actual del teclado

    mGrpSprites.update(teclas);
    //mPlayers->update(teclas);
    //mGameTimer->update();

    /*SI SE ACABO EL TIEMPO*/
    if(getSegundosInicioNivel()>=mMinutos){
        /*
        for(int i=0;i<_PLAYERS;i++){
            if(refeSprites[PLAYER][i]&&isActivo(PLAYER,i)){
                static_cast<Player *>(refeSprites[PLAYER][i])->cambiarEstado(MURIENDO);
                static_cast<Player *>(refeSprites[PLAYER][i])->setVidas(0);
            }
        }
        muertosPorTiempo=true;*/
        std::cout << "SE ACABO EL TIEMPO" << std::endl;
    }

        /*SI SE ACERCA EL TIEMPO PARA ACABAR*
        if(mGameTimer->getMiliSegundos()>min/3&&!repro_war){
            playSonido(SND_WARNING_TIME);
            repro_war=true;
        }

        int id_activo=-1;
        int total_activos=0;

        total_activos=getActivos(PLAYER,id_activo);

        if(total_activos==1){
            static char msg_ganador[20];
            batallasGanadas[id_activo]++;
            if((id_lider_ganadas==PLAYER_NONE)||(id_lider_ganadas!=PLAYER_NONE&&batallasGanadas[id_activo] > batallasGanadas[id_lider_ganadas]))
                    id_lider_ganadas=(IdPlayer)id_activo;
            else if(id_lider_ganadas!=PLAYER_NONE&&id_lider_ganadas!=id_activo&&batallasGanadas[id_activo] == batallasGanadas[id_lider_ganadas])
                    id_lider_ganadas=PLAYER_NONE;
            game->cambiarInterfaz(new JuegoMostrarGanadas(game,this,batallasGanadas));

            if(batallasGanadas[id_activo]>=vic){
                sprintf(msg_ganador,"�PLAYER %d GAN�!",id_activo+1);
                displayMensage(msg_ganador);
                _quit=true;
            }else{
                setMapaPlay(idTerrenoActual);
            }
        }else if(total_activos==0){
            char msg_ganador[20];
            sprintf(msg_ganador,"empate");
            displayMensage(msg_ganador);
            setMapaPlay(idTerrenoActual);
        }


}//fin if(!pausado)

controlaPausa(teclas);


/*    switch(estado){
    case PLAY:
         if(!animandoEntradaMapaVertical)estadoPlay();
         break;
    case DISPLAY_MSG:
         estadoDisplayMensage();
         break;
    }
if(animandoEntradaMapaVertical){
    desplazamiento+=2;
    mMapa->setEjeVisualizacion(mMapa->getEjeX(),H_SCREEN-desplazamiento);
    if(H_SCREEN-desplazamiento<=mMapa->getEjeY()){
        animandoEntradaMapaVertical=false;
    }
}*/
}

bool Juego::estaPlayerActivo(IdPlayer playerId){
    return mIsPlayerActivado[playerId]&&mPlayerSprite[playerId]->isActivo();
}
void Juego::drawBarra(SDL_Renderer * gRenderer){
    char tmp[50];
    mGameManager->getImagen(IMG_TABLERO)->render(gRenderer,0,0);

    //PLAYER_1
    imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),
                          !(estaPlayerActivo(PLAYER_1)) + PLAYER_1*2 ,gRenderer,1,6,1,10,0);

    mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,15,3);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(estaPlayerActivo(PLAYER_1)){
        //sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_1])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),15,24,tmp,STR_ESTENDIDA);
    }
//
    //PLAYER_2
    imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),
                          !(estaPlayerActivo(PLAYER_2)) + PLAYER_2*2 ,gRenderer,32,6,1,10,0);

    mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,48,3);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(estaPlayerActivo(PLAYER_2)){
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_2])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),48,24,tmp,STR_ESTENDIDA);
    }
//
    //PLAYER_3
    imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),
                          !(estaPlayerActivo(PLAYER_3)) + PLAYER_3*2 ,gRenderer,65,6,1,10,0);

    mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,80,3);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(estaPlayerActivo(PLAYER_3)){
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_3])->getVidas());
//    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),80,24,tmp,STR_ESTENDIDA);
    }
//
//    //PLAYER_4
    imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),
                          !(estaPlayerActivo(PLAYER_4)) + PLAYER_4*2 ,gRenderer,253,6,1,10,0);

    mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,270,3);
//
    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(estaPlayerActivo(PLAYER_4)){
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_4])->getVidas());
//    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),271,23,tmp,STR_ESTENDIDA);
    }
//
    //PLAYER_5
    imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),
                          !(estaPlayerActivo(PLAYER_5)) + PLAYER_5*2 ,gRenderer,288,6,1,10,0);

    mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,304,3);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(estaPlayerActivo(PLAYER_5)){
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_5])->getVidas());
//    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),305,23,tmp,STR_ESTENDIDA);
    }

    if(mIdLiderRondasGanadas!=PLAYER_NONE)
        imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN_GRANDES),mIdLiderRondasGanadas,gRenderer,154,-10,1,5,0);

    mGameManager->getImagen(IMG_CUADRO_GRANDE)->render(gRenderer,137,3);

    if(mGameTimer){
//        static char min_[3],seg[3],tiempo[6];
//
//        sprintf(min_,"%2d",(min-mGameTimer->getMiliSegundos())/60);
//        if(min_[0]==' ')min_[0]='0';
//        sprintf(seg,"%2d",min-mGameTimer->getMiliSegundos()-(min-mGameTimer->getMiliSegundos())/60*60);
//        if(seg[0]==' ')seg[0]='0';
//        sprintf(tiempo,"%s:%s",min_,seg);
//
//    	imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_6),142,24,tiempo,STR_MAX_ESTENDIDA);
    }
}
int Juego::getJoysActivos(){
    return mGameManager->getJoysActivos();
}
SDL_Joystick * Juego::getJoy(int id){
    return mGameManager->getJoy(id);
}

void Juego::draw(SDL_Renderer * gRenderer){
    //mGameManager->getImagen((CodeImagen)std::stoi(mMapa->getMapProperty(MAPA_PROPERTY_ID_FONDO)))->render(gRenderer);
    drawBarra(gRenderer);//imprimimos la barra mensage
    mMapa->draw(gRenderer,
                MAPA_EJE_X,
                MAPA_EJE_Y);//imprimimos el nivel
    mGrpSprites.draw(gRenderer);

/*    if(pausado){
        //imprimir_palabra(gRenderer, game->getImagen(IMG_FUENTE_5),80,100,"pausa",STR_NORMAL);
        imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),id_quien_pauso*2 ,gRenderer,130,90,1,10,0);
    }*/
    //if(estado==DISPLAY_MSG)imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_6),x_msg,y_msg,msg_mostrar,STR_MAX_ESTENDIDA);
}

/*void Juego::setProteccion(TipoSprite type, int id,int nuevo){
     if(type==GLOBO||type==PLAYER){
         static_cast<Player *>(refeSprites[type][id])->setProteccion(nuevo);
     }
}

void Juego::setRepeticionBomba(int id,int nuevo){
     if(refeSprites[BOMBA][id]!=NULL)
         static_cast<Bomba *>(refeSprites[BOMBA][id])->setRepeticion(nuevo);
}
bool Juego::isBloqueRompible(int x,int y){
     return mMapa->isBloqueRompible(x,y);
}
bool Juego::isBloqueDuro(int x,int y){
    return mMapa->getTipoBloque(x,y)==Mapa::BLOQUE_METAL;
}
bool Juego::getPuertaAbierta(){
     return p_abierta;
}

bool Juego::isBloqueItem(int x,int y){
     return mMapa->getTipoBloque(x,y)==Mapa::BLOQUE_ITEM;
}

void Juego::setPuertaAbierta(bool nuevo){
     p_abierta=nuevo;
}

void Juego::romperBloque(int x,int y){
    mMapa->romperBloque(x,y);
}


void Juego::controlaPausa(const Uint8 * teclas){
    /*SI ALGUN PLAYER PRESIONO START SE PAUSA EL JUEGO*
    if(!hold_start){
        for(int i=0;i<totalSprite[PLAYER];i++){
            if(isActivo(PLAYER,i)&&\
                static_cast<Player *>(refeSprites[PLAYER][i])->isPressed(TECLA_START,teclas)){
                if(!pausado){
                    pausado=true;
                    inicio_pausa=time(0);
                    id_quien_pauso=(IdPlayer)i;
                    playSfx(SFX_CAMPANADA);
                }else if(id_quien_pauso==(IdPlayer)i){
					pausado=false;
					mGameTimer->setTicksPerdidos(mGameTimer->getTickPerdidos()+time(0)-inicio_pausa);
					id_quien_pauso_anterior=id_quien_pauso; //se guarda el player que habia puesto pausa, para que no mantenga START presionada
					id_quien_pauso=PLAYER_NONE;
                    playSfx(SFX_TONO_ACUATICO);
                    
                }
                break;
            }
        }
    }

	if(id_quien_pauso!=PLAYER_NONE)
		hold_start=static_cast<Player *>(refeSprites[PLAYER][id_quien_pauso])->isPressed(TECLA_START,teclas);
	else if(id_quien_pauso_anterior!=PLAYER_NONE)
		hold_start=static_cast<Player *>(refeSprites[PLAYER][id_quien_pauso_anterior])->isPressed(TECLA_START,teclas);
}

int Juego::getTipoNuevoItem(bool disminuir_de_mapa){

    static int tipos[5]={Item::ITEM_BOLA_ARROZ,
                         Item::ITEM_PASTEL,
                         Item::ITEM_PALETA,
                         Item::ITEM_BARQUILLA,
                         Item::ITEM_MANZANA};

    int tmp=rand()%1200,indice;
    if(tmp<10&&tmp>=0)indice=Item::ITEM_BOMBA_MAX; //0.8% probabilidades de aparecer
    else if(tmp<20&&tmp>=10)indice=Item::ITEM_ALCANCE_MAX;//0.8%
    else if(tmp<120&&tmp>=20)indice=Item::ITEM_ALCANCE; //8% 
    else if(tmp<180&&tmp>=120)indice=Item::ITEM_VIDA; //4% 
    else if(tmp<280&&tmp>=180)indice=Item::ITEM_BOMBA;//8% 
    else if(tmp<330&&tmp>=280)indice=Item::ITEM_ATRAVIESA_PAREDES;//4% 
    else if(tmp<430&&tmp>=330)indice=Item::ITEM_PROTECCION;//8%
    else if(tmp<530&&tmp>=430)indice=Item::ITEM_ALEATORIO;//8%
    else if(tmp<580&&tmp>=530)indice=Item::ITEM_PATINETA; //4%
    else if(tmp<630&&tmp>=580)indice=Item::ITEM_CORAZON; //4% 
    else if(tmp<680&&tmp>=630)indice=Item::ITEM_ATRAVIESA_BOMBAS;//4%
    else indice=tipos[rand() % 5 ];//54%
    
    if(disminuir_de_mapa&&mMapa->getNumItems()>=1)
            mMapa->setNumItems(mMapa->getNumItems()-1);
    
    return indice;
}

void Juego::moveAllSprites(int aumX,int aumY){
     int count=0;
     for(int i=0;i<_REFERENCIADOS;i++){
        if(spriteActivos[i]>0){
             for(int j=0;j<totalSprite[i];j++){
                 if(refeSprites[i][j]!=NULL){
                     refeSprites[i][j]->setX(refeSprites[i][j]->getX()+aumX);
                     refeSprites[i][j]->setY(refeSprites[i][j]->getY()+aumY);
                     if(++count==spriteActivos[i]){
                         count=0;
                         break;
                     }
                }
             }
        }
     }
}
*/

void Juego::killedSprite(Sprite * sprite) {

    Bomba * pBombaEliminada   = nullptr;
    Bloque * pBloqueEliminado = nullptr;

    if((pBombaEliminada = dynamic_cast<Bomba * >(sprite)) != nullptr){

        // Obtenemos el player que ha lanzado la pBombaEliminada
        Player * playerLanzador = pBombaEliminada->getPlayerPropietario();

        // Le restamos uno a las bombas colocadas por el player que la hanzado
        playerLanzador->setBombasColocadas(playerLanzador->getBombasColocadas() - 1);

        // Creamos una nueva Explosion
        Explosion * explosion = new Explosion(this,mGameRenderer,playerLanzador);

        // Establecemos la posicion de inicio donde estaba la pBombaEliminada
        explosion->move(pBombaEliminada->getX(),pBombaEliminada->getY());
        explosion->detectarAlcances();

        mGrpExplosiones.add(explosion);
        mGrpSprites.add(explosion);

        //reproducimos un sonido
        mGameManager->play(SFX_EXPLOSION);
    }else if((pBloqueEliminado = dynamic_cast<Bloque * >(sprite)) != nullptr){
        
        Item * nuevoItem = new Item();
        // Obtenemos el player que ha lanzado la pBombaEliminada
        Player * playerLanzador = pBombaEliminada->getPlayerPropietario();

        // Le restamos uno a las bombas colocadas por el player que la hanzado
        playerLanzador->setBombasColocadas(playerLanzador->getBombasColocadas() - 1);

        // Creamos una nueva Explosion
        Explosion * explosion = new Explosion(this,mGameRenderer,playerLanzador);

        // Establecemos la posicion de inicio donde estaba la pBombaEliminada
        explosion->move(pBombaEliminada->getX(),pBombaEliminada->getY());
        explosion->detectarAlcances();

        mGrpExplosiones.add(explosion);
        mGrpSprites.add(explosion);

        //reproducimos un sonido
        mGameManager->play(SFX_EXPLOSION);
    }

    delete sprite;
}

deque<Sprite *> Juego::colisionBloqueEnLlamas(SDL_Rect rect) {
    return mGrpBloques.collide(rect);
}

deque<Sprite *> Juego::colisionConItems(SDL_Rect rect) {
    return mGrpItems.collide(rect);
}

Bloque *Juego::agregarBloqueEnLlamas(int x, int y) {

    // Buscamos la animacion del mapa para los bloques en llamas
    vector<string> *aniBloqueLlamas = mMapa->getAnimacionFrames(
            mMapa->getMapProperty(MAPA_PROPERTY_ID_TILE_LLAMAS)
    );

    // Creamos los frames de la animacion
    // notar que se ignora la duracion de los frames
    // Eso es porque aun no esta implementado
    std::string frames = "";
    auto itAnimacion = aniBloqueLlamas->begin();
    while(itAnimacion != aniBloqueLlamas->end()){
        frames += (*itAnimacion);
        itAnimacion++;
        if(itAnimacion != aniBloqueLlamas->end()){
            frames+=",";
        }
    }


    // Se crea el bloque CON UNA COPIA DEL TILESET DEL MAPA
    Bloque * nuevoBloque = new Bloque(new SpriteSheet(mGameRenderer,
                                                      mMapa->getRutaTileSet(),
                                                      mMapa->getNFilasTileSet(),
                                                      mMapa->getNColumnasTileSet()),frames,x,y,1);
    //nuevoBloque->setAnimacion(mMapa->getSpriteSheetTiles(),aniBloqueLlamas);
    mGrpBloques.add(nuevoBloque);
    mGrpSprites.add(nuevoBloque);
    return nuevoBloque;
}

bool Juego::esBloqueSolido(int x, int y) {
    x -= MAPA_EJE_X;
    y -= MAPA_EJE_Y;
    return mMapa->esBloqueSolido(x,y);
}

bool Juego::esBloqueRompible(int x, int y) {
    x -= MAPA_EJE_X;
    y -= MAPA_EJE_Y;
    return mMapa->esBloqueRompible(x,y);
}

Juego::~Juego(){
    for(int i= 0;i<_PLAYERS;i++){
        delete mPlayerSprite[i];
    }
    delete mGameTimer;
    delete mMapa;
}

std::deque<Sprite *> Juego::colisionConBombas(SDL_Rect  rect) {
    return mGrpBombas.collide(rect);
}

int Juego::colisionConMapa(SDL_Rect rect_coli, int *lado_colision, bool solo_bloques_duros){
    /*Comprueba si un rect colisiona con el nivel*/
    rect_coli.x -= MAPA_EJE_X;
    rect_coli.y -= MAPA_EJE_Y;
    return mMapa->colision(rect_coli,lado_colision,solo_bloques_duros);
}

bool Juego::isOutOfMapBounds(SDL_Rect rect) {
    rect.x -= MAPA_EJE_X;
    rect.y -= MAPA_EJE_Y;
    return !mMapa->contain(rect);
}

Bomba *Juego::agregarBomba(Player * player) {

    //int id_bomba_colocada=juego->addSprite(BOMBA,(x+7-juego->getEjeXVisual())/16*16+juego->getEjeXVisual(),(y+11-juego->getEjeYVisual())/16*16+juego->getEjeYVisual(),(int)id);
    //SpriteSheet * nuevaSpriteSheet = new SpriteSheet();

    // Pasamos la posicion X a la coordenada del Mapa
    int nuevaPosicionX = player->getX() + 7 - MAPA_EJE_X;
    // Formateamos la posicion X a que sea proporcional al ancho de los tiles
    nuevaPosicionX = nuevaPosicionX/mMapa->getTileWidth()*mMapa->getTileWidth();
    // Pasamos la posicion X a la coordenada de la pantalla
    nuevaPosicionX = nuevaPosicionX + MAPA_EJE_X;

    // Pasamos la posicion Y a la coordenada del Mapa
    int nuevaPosicionY = player->getY() + 11 - MAPA_EJE_Y;
    // Formateamos la posicion Y a que sea proporcional al alto de los tiles
    nuevaPosicionY = nuevaPosicionY/mMapa->getTileHeight()*mMapa->getTileHeight();
    // Pasamos la posicion Y a la coordenada de la pantalla
    nuevaPosicionY = nuevaPosicionY + MAPA_EJE_Y;


    Bomba * nuevaBomba = new Bomba(mGameRenderer,player);
    nuevaBomba->move(nuevaPosicionX,nuevaPosicionY);

    if(   mGrpEnemigos.collide(nuevaBomba).size() == 0
       && mGrpItems.collide(nuevaBomba).size()    == 0
       && mGrpPlayers.collide(nuevaBomba).size()  == 1){
        mGrpBombas.add(nuevaBomba);
        mGrpSprites.add(nuevaBomba);
        return nuevaBomba;
    }

    delete nuevaBomba;
//                (mJuego->getNumBombasLanzadas(mPlayerId) < numBombas)&&!mJuego->colisionConBombas(rect)
//                &&!mJuego->colisionConEnemigos(rect)
//                &&!mJuego->colisionConMapa(rect)
//                &&!mJuego->colisionConItems(rect)){
    /*anyadimos la bomba inocentemente*/

    //mUltimaBomba = mJuego->agregarBomba(mPlayerId,x+7,y+11);
    return nullptr;
}


