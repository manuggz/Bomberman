#include "juego_batalla.hpp"


JuegoBatalla::JuegoBatalla (GameManager * game,int idTerrenoBatalla,bool playerEnBatalla[_PLAYERS],int minutos,int victorias):Juego(game){
    #ifdef DEBUG
    cout << "Constructor de JuegoBatalla:"<<this<<endl;
    #endif

    EjeX=27;
    EjeY=54;
    mapa=new Mapa(this,EjeX,EjeY);

    totalSprite[GLOBO]=0;
    crearReferencias();
    
    this->idTerrenoActual=idTerrenoBatalla;
    setMapaPlay(idTerrenoBatalla,false);
    
    Player * player_;
    for(int i=0;i<_PLAYERS;i++){
        batallasGanadas[i]=0;
        if(playerEnBatalla[i]){
             spriteActivos[PLAYER]++;
             player_=new Player(this,(IdPlayer)i,\
                                      data->getX(i),\
                                      data->getY(i),\
                                      data->getVidas(),\
                                      data->getBombas(),\
                                      data->getAlcanceBombas());
            refeSprites[PLAYER][i]=player_;
            sprites->add(player_);
        }
    }
    
    displayMensage("�Qu� gane el mejor!");//se presenta el mensage con el nivel actual
//    estado_siguiente=PLAY;
    id_lider_ganadas=PLAYER_NONE;
    SDL_ShowCursor(SDL_DISABLE);
    min=minutos*60;
    vic=victorias;
    mapa->setImgTiles(game->getImagen(IMG_TILES));
}

void JuegoBatalla::crearReferencias(){
    for(int i=0;i<_REFERENCIADOS;i++){
        if(totalSprite[i]){
            refeSprites[i]=new Sprite* [totalSprite[i]];
            spriteActivos[i]=0;
            for(int j=0;j<totalSprite[i];j++){
                refeSprites[i][j]=NULL;
            }
        }
    }
}

void JuegoBatalla::setMapaPlay(int idTerreno,bool comprobar_players){
    char ruta[30],ruta2[50];
    sprintf(ruta,"data/niveles/batalla/%d.txt",idTerreno + 1);    
    sprintf(ruta2,"data/niveles/batalla/%d.map",idTerreno + 1);
    if(data)delete data;
    data=new DatNivel(ruta);
    if(clockTick)delete clockTick;
    clockTick=new TimeController();
    clockTick->setTicksPerdidos(4);
    
    if(comprobar_players){
        for(int i=0;i<_PLAYERS;i++){
            if(refeSprites[PLAYER][i]){//si fue elegido para que batalle
                if(!isActivo(PLAYER,i)){//si no esta en pantalla
                    sprites->add(refeSprites[PLAYER][i]);
                    spriteActivos[PLAYER]++;
                }/*else{//si sobrevivio a la batalla
                    static_cast<Player *>(refeSprites[PLAYER][i])->posicionInicial();
                }*/
                static_cast<Player *>(refeSprites[PLAYER][i])->setVidas(data->getVidas());
                static_cast<Player *>(refeSprites[PLAYER][i])->reiniciar();
            }
        }
    }

    clearSprites();
    mapa->cargarDeArchivoBin(ruta2,ruta);
    mapa->setEjeVisualizacion(mapa->getEjeX(),H_SCREEN);
    mapa->setItems();

    playSonido((CodeMusicSonido)(4 + rand()%1));
    muertosPorTiempo=false;
    repro_war=false;
    iniciado=false;
    patinesLanzados=false;
    bombasMaxLanzado=false;
    alcanceMaxLanzado=false;
    animandoEntradaMapaVertical=true;
    desplazamiento=0;
}

int JuegoBatalla::getTipoNuevoItem(bool hacerComprobaciones){
    int tmp,indice=-1;
    bool aprobado=false;
    do{
        tmp=rand()%1200;
        if(tmp<10&&tmp>=0&&!bombasMaxLanzado){//0.8% probabilidades de aparecer
            indice=Item::ITEM_BOMBA_MAX; 
            bombasMaxLanzado=true;
        }
        else if(tmp<20&&tmp>=10&&!alcanceMaxLanzado){//0.8%
            indice=Item::ITEM_ALCANCE_MAX; 
            alcanceMaxLanzado=true;
        }
        else if(tmp<120&&tmp>=20)indice=Item::ITEM_ALCANCE; //8% 
        else if(tmp<180&&tmp>=120)indice=Item::ITEM_BOMBA; //4% 
        else if(tmp<280&&tmp>=180)indice=Item::ITEM_ATRAVIESA_PAREDES;//8% 
        else if(tmp<330&&tmp>=280)indice=Item::ITEM_PROTECCION;//4% 
        else if(tmp<430&&tmp>=330)indice=Item::ITEM_ALEATORIO;//8%
        else if(tmp<480&&tmp>=430)indice=Item::ITEM_CORAZON;//4%
        else if(tmp<530&&tmp>=480)indice=Item::ITEM_ATRAVIESA_BOMBAS;//4%
        else if(tmp<580&&tmp>=530&&!patinesLanzados){//4% 
            indice=Item::ITEM_PATINETA; 
            patinesLanzados=true;
        }
        if(tmp>=0&&tmp<580&&indice!=-1)aprobado=true;
        
    }while(!aprobado);

    if(hacerComprobaciones&&mapa->getNumItems()>=1){
            mapa->setNumItems(mapa->getNumItems()-1); 
    }
    return indice;
}

void JuegoBatalla::estadoPlay(){
    const Uint8 *teclas= SDL_GetKeyboardState(NULL);//se obtiene el estado actual del teclado

    if(!pausado){
            sprites->update(teclas);
            clockTick->update();            
            /*SI SE ACABO EL TIEMPO*/
            if(!muertosPorTiempo&&clockTick->getMiliSegundos()>=min){ 
                for(int i=0;i<_PLAYERS;i++){
                    if(refeSprites[PLAYER][i]&&isActivo(PLAYER,i)){
                        static_cast<Player *>(refeSprites[PLAYER][i])->cambiarEstado(MURIENDO);
                        static_cast<Player *>(refeSprites[PLAYER][i])->setVidas(0);
                    }
                }
                muertosPorTiempo=true;
            }
                
            /*SI SE ACERCA EL TIEMPO PARA ACABAR*/
            if(clockTick->getMiliSegundos()>min/3&&!repro_war){
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
}
void JuegoBatalla::salir(){
    _quit=true;
    game->cambiarInterfaz(new Menu(game));

}

void JuegoBatalla::drawBarra(SDL_Renderer * gRenderer){
    char tmp[50];

    game->getImagen(IMG_TABLERO)->render(gRenderer,0,mapa->getYPanel());

    //PLAYER_1
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN), !(refeSprites[PLAYER][PLAYER_1]&&isActivo(PLAYER,PLAYER_1)) + PLAYER_1*2 ,gRenderer,1,24,1,10,0);

    game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,15,21);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(refeSprites[PLAYER][PLAYER_1]&&isActivo(PLAYER,PLAYER_1)){
        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_1])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),15,24,tmp,STR_ESTENDIDA);
    }

    //PLAYER_2
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN), !(refeSprites[PLAYER][PLAYER_2]&&isActivo(PLAYER,PLAYER_2)) + PLAYER_2*2 ,gRenderer,32,24,1,10,0);

    game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,48,21);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(refeSprites[PLAYER][PLAYER_2]&&isActivo(PLAYER,PLAYER_2)){
        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_2])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),48,24,tmp,STR_ESTENDIDA);
    }

    //PLAYER_3
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN), !(refeSprites[PLAYER][PLAYER_3]&&isActivo(PLAYER,PLAYER_3)) + PLAYER_3*2 ,gRenderer,65,24,1,10,0);

    game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,80,21);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(refeSprites[PLAYER][PLAYER_3]&&isActivo(PLAYER,PLAYER_3)){
        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_3])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),80,24,tmp,STR_ESTENDIDA);
    }

    //PLAYER_4
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN), !(refeSprites[PLAYER][PLAYER_4]&&isActivo(PLAYER,PLAYER_4)) + PLAYER_4*2 ,gRenderer,253,24,1,10,0);

    game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,270,21);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(refeSprites[PLAYER][PLAYER_4]&&isActivo(PLAYER,PLAYER_4)){
        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_4])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),271,23,tmp,STR_ESTENDIDA);
    }

    //PLAYER_5
    imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN), !(refeSprites[PLAYER][PLAYER_5]&&isActivo(PLAYER,PLAYER_5)) + PLAYER_5*2 ,gRenderer,288,24,1,10,0);

    game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,304,21);

    /*DIBUJAMOS LAS VIDAS RESTANTES*/
    if(refeSprites[PLAYER][PLAYER_5]&&isActivo(PLAYER,PLAYER_5)){
        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_5])->getVidas());
    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_3),305,23,tmp,STR_ESTENDIDA);
    }

    if(id_lider_ganadas!=PLAYER_NONE)
        imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN_GRANDES),id_lider_ganadas,gRenderer,154,-10,1,5,0);
    
    game->getImagen(IMG_CUADRO_GRANDE)->render(gRenderer,137,21);
    
    if(clockTick){
        static char min_[3],seg[3],tiempo[6];
    
        sprintf(min_,"%2d",(min-clockTick->getMiliSegundos())/60);
        if(min_[0]==' ')min_[0]='0';
        sprintf(seg,"%2d",min-clockTick->getMiliSegundos()-(min-clockTick->getMiliSegundos())/60*60);
        if(seg[0]==' ')seg[0]='0';
        sprintf(tiempo,"%s:%s",min_,seg);
    
    	/*imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_6),\
    						142,24,tiempo,STR_MAX_ESTENDIDA);*/
    }
}
JuegoBatalla::~JuegoBatalla(){
    #ifdef DEBUG
        cout << "Destructor de JuegoBatalla:"<<this<<endl;
    #endif
}

void JuegoBatalla::start(SDL_Renderer *renderer) {

}

bool JuegoBatalla::isPaused() {
    return false;
}

void JuegoBatalla::pause() {

}

void JuegoBatalla::resume() {

}

/*
    cout << "1.1.1"<<endl;
void juego_dibujar_kills(Juego * juego,SDL_Surface * gRenderer){
     char tmp[50];
    render_texture(game->galeria->tabs_kills,0,0,gRenderer);
    int i;
    
    for(i=0;i<_PLAYERS;i++){
        dibujamos el primer player
        imprimir_desde_grilla(game->galeria->grilla_caras_bomberman,!(i==0) + sort_kills[i]*2 ,gRenderer,39,67 + 29*i,1,10,0);
        dibujamos el player
        sprintf(tmp,"player %d",sort_kills[i]+1);
       	imprimir_palabra (gRenderer, game->galeria->grilla_fuente_1,58,69 + 28*i,tmp,STR_NORMAL);
       	
        numero de matadas
        sprintf(tmp,"%d",matadas[sort_kills[i]]);
       	imprimir_palabra (gRenderer, game->galeria->grilla_fuente_3,174,69 + 28*i,tmp,STR_ESTENDIDA);
     	
        numero de kills
        sprintf(tmp,"%d",kills[sort_kills[i]]);
       	imprimir_palabra (gRenderer, game->galeria->grilla_fuente_3,248,68 + 28*i,tmp,STR_ESTENDIDA);
    }

}




void juego_preparar_kills(Juego * juego){
     mostrar_kills=1;
     sort_array(matadas,sort_kills);
}
*/
