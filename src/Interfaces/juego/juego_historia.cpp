#include "juego_historia.hpp"
///*
//JuegoHistoria::JuegoHistoria (GameManager * game):Juego(game){
//    /*Inicializa las referencias y pone todo para que se inicialize el juego*/
//    #ifdef DEBUG
//    cout << "Constructor de JuegoHistoria:"<<this<<endl;
//    #endif
//
//    EjeX=0;
//    EjeY=0;
//    mapa=new Mapa(this);
//    mapa->setImgTiles(game->getImagen(IMG_TILES ));
//
//    totalSprite[PLAYER]=2;
//    crearReferencias();
//    refeSprites[PLAYER][PLAYER_1]=new Player(this,PLAYER_1,X_INIT_PLAYER_1,Y_INIT_PLAYER_1,3,3);
//    if(!refeSprites[PLAYER][PLAYER_1])
//        cout << "Warning--No se pudo crear el Player 1"<<endl;
//    refeSprites[PLAYER][PLAYER_2]=new Player(this,PLAYER_2,X_INIT_PLAYER_2,Y_INIT_PLAYER_2);
//    if(!refeSprites[PLAYER][PLAYER_2])
//        cout << "Warning--No se pudo crear el Player 2"<<endl;
//    static_cast<Player *>(refeSprites[PLAYER][PLAYER_2])->setEnPantalla(false); /*Desactivamos el player2*/
//    spriteActivos[PLAYER]=1; /*Solo estar� activo el player 1*/
//    mSprites->add(refeSprites[PLAYER][PLAYER_1]); /*Lo agregamos al Grupo*/
//    mayor_puntaje=0;
//    setMapaPlay(1,false); /*Se empezara a jugar desde el Nivel 1*/
//    static_cast<Player *>(refeSprites[PLAYER][PLAYER_2])->disable(); /*Desactivamos el player2*/
//
//}
//
//void JuegoHistoria::setMapaPlay(int id_nivel,bool reiniciar_jugadores){
//    char ruta1[50],ruta2[50],ruta3[50];
//
//    if(id_nivel<1)id_nivel=1;
//
//    if(id_nivel<MAX_NIVEL){
//        if(mGameTimer)delete mGameTimer;
//        mGameTimer=new TimeController();
//        mGameTimer->setTicksPerdidos(4);
//
//        clearSprites();
//        for(int i=PLAYER_1;i<=PLAYER_2;i++){
//            if(isActivo(PLAYER,i)){
//                if(reiniciar_jugadores){
//                    static_cast<Player *>(refeSprites[PLAYER][i])->reiniciar();
//                }else{
//                    static_cast<Player *>(refeSprites[PLAYER][i])->posicionInicial();
//                    static_cast<Player *>(refeSprites[PLAYER][i])->setProteccion(10);
//                }
//            }
//        }
//
//        sprintf(ruta1,"data/niveles/historia/nivel_%d.map",id_nivel);
//        sprintf(ruta2,"data/niveles/historia/%d.txt",id_nivel);
//        mapa->cargarDeArchivoBin(ruta1,ruta2);
//        mapa->setEjeVisualizacion(mapa->getEjeX(),mapa->getEjeY());
//        mapa->setItems();
//        mapa->setEnemigos();
//        char mens[50];
//        sprintf(mens,"NIVEL %d",id_nivel);
//        displayMensage(mens);//se presenta el mensage con el nivel actual
//        repro_war=false;
//        playSonido((CodeMusicSonido)(4 + rand() % 1));
//        n_actual=id_nivel;
//        p_abierta=false;
//        patinesLanzados=false;
//        bombasMaxLanzado=false;
//        alcanceMaxLanzado=false;
//    }else{
//        displayMensage("Te terminaste el juego :P, �FELICIDADES!");//se presenta el mensage con el nivel actual
//        _quit=true;
//    }
//}
//
//void JuegoHistoria::aumentarNivel(){
//    int bonus=time(0)-getSegundosInicioNivel();
//
//    for(int i=0;i<=PLAYER_2;i++){
//        if(isActivo(PLAYER,i)){
//            static_cast<Player *>(refeSprites[PLAYER][i])->setPuntaje(static_cast<Player *>(refeSprites[PLAYER][i])->getPuntaje()+bonus);
//            static_cast<Player *>(refeSprites[PLAYER][i])->setEntroPuerta(false);
//            static_cast<Player *>(refeSprites[PLAYER][i])->setProteccion(10);
//            static_cast<Player *>(refeSprites[PLAYER][i])->cambiarEstado(PARADO);
//        }
//    }
//    setMapaPlay(n_actual + 1,false);
//}
//
//
//
//void JuegoHistoria::estadoPlay(){
//    const Uint8 * teclas=SDL_GetKeyboardState (NULL);//se obtiene el estado actual del teclado
//    if(!pausado){
//        mSprites->update(teclas);
//
//        /*SI NO HAY PLAYERS ACTIVOS*/
//        if(!isActivo(PLAYER,PLAYER_1) && !isActivo(PLAYER,PLAYER_2)){
//            displayMensage("game over");
//           _quit=true;
//        }
//
//         mGameTimer->update();
//        /*SI SE ACABO EL TIEMPO*/
//        if(mGameTimer->getMiliSegundos()>=_TIME_POR_NIVEL)
//            setMapaPlay(n_actual,true);
//
//        /*SI SE ACERCA EL TIEMPO PARA ACABAR*/
//        if(mGameTimer->getMiliSegundos()==_TIME_POR_NIVEL-50&&!repro_war){
//            playSonido(SND_WARNING_TIME);
//            repro_war=true;
//        }
//
//        /*SI ALGUN PLAYER PRESIONO START Y ESTABA MUERTO*/
//        for(int i=0;i<=PLAYER_2;i++)
//            if(!isActivo(PLAYER,i)&&static_cast<Player *>(refeSprites[PLAYER][i])->isPressed(TECLA_START,teclas)){
//                if(static_cast<Player *>(refeSprites[PLAYER][!i])->getVidas()>0){
//                    static_cast<Player *>(refeSprites[PLAYER][!i])->setVidas(static_cast<Player *>(refeSprites[PLAYER][!i])->getVidas()-1);
//                    static_cast<Player *>(refeSprites[PLAYER][i])->reiniciar();
//                    static_cast<Player *>(refeSprites[PLAYER][i])->setVidas(0);
//                    hold_start=true;//controlamos que no mantenga la tecla presionada
//                    mSprites->add(refeSprites[PLAYER][i]);
//                    break;
//                }
//            }
//    }
//    controlaPausa(teclas);
//
//}
//
//inline void JuegoHistoria::salir(){
//    _quit=true;
//    game->cambiarInterfaz(new Menu(game));
//}
//
//
//void JuegoHistoria::drawBarra(SDL_Renderer * gRenderer){
//    char tmp[50];
//
//    game->getImagen(IMG_TABLERO)->render(gRenderer,0,mapa->getYPanel());
//
//
//    //Dibujamos el tiempo
//    game->getImagen(IMG_CUADRO_GRANDE)->render(gRenderer,129,3+mapa->getYPanel());
//    if(mGameTimer){
//        static char min[3],seg[3],tiempo[6];
//
//        sprintf(min,"%2d",(_TIME_POR_NIVEL-mGameTimer->getMiliSegundos())/60);
//        if(min[0]==' ')min[0]='0';
//        sprintf(seg,"%2d",_TIME_POR_NIVEL-mGameTimer->getMiliSegundos()-(_TIME_POR_NIVEL-mGameTimer->getMiliSegundos())/60*60);
//        if(seg[0]==' ')seg[0]='0';
//        sprintf(tiempo,"%s:%s",min,seg);
//
//    	/*imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_6),\
//    						136,6+mapa->getYPanel(),tiempo,STR_MAX_ESTENDIDA);*/
//    }
//
//    if(isActivo(PLAYER,PLAYER_1)){
//
//        //DIBUJAMOS LAS VIDAS
//        game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,59,5+mapa->getYPanel());
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_1])->getVidas());
//    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_1),59,8+mapa->getYPanel(),tmp,STR_NORMAL);
//
//        //Dibujamos la cara
//        imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN_GRANDES),PLAYER_1,gRenderer,28,-8+mapa->getYPanel(),1,5,0);
//
//        //DIBUJAMOS EL PUNTAJE
//        game->getImagen(IMG_CUADRO_MEDIANO)->render(gRenderer,4,23+mapa->getYPanel());
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_1])->getPuntaje());
//        //imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_2),40,24+mapa->getYPanel(),tmp,STR_NORMAL);
//    }else{
//        //Dibujamos la cara
//        imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN_GRANDES),PLAYER_1,gRenderer,28,-8+mapa->getYPanel(),1,5,0);
//
//        game->getImagen(IMG_TXT_PRESIONA_START)->render(gRenderer,5,27+mapa->getYPanel());
//    }
//
//    if(isActivo(PLAYER,PLAYER_2)){
//
//        //DIBUJAMOS LAS VIDAS
//        game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,292,5+mapa->getYPanel());
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_2])->getVidas());
//    	//imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_1),293,8+mapa->getYPanel(),tmp,STR_NORMAL);
//
//        //Dibujamos la cara
//        imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN_GRANDES),PLAYER_2,gRenderer,262,-8+mapa->getYPanel(),1,5,0);
//
//        //DIBUJAMOS EL PUNTAJE
//        game->getImagen(IMG_CUADRO_MEDIANO)->render(gRenderer,232,23+mapa->getYPanel());
//        sprintf(tmp,"%d",static_cast<Player *>(refeSprites[PLAYER][PLAYER_2])->getPuntaje());
//        //imprimir_palabra (gRenderer,game->getImagen(IMG_FUENTE_2),273,24+mapa->getYPanel(),tmp,STR_NORMAL);
//
//    }else{
//        //Dibujamos la cara
//        imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN_GRANDES),PLAYER_2,gRenderer,262,-8+mapa->getYPanel(),1,5,0);
//
//        game->getImagen(IMG_TXT_PRESIONA_START)->render(gRenderer,225,21+mapa->getYPanel());
//    }
//}
//
//JuegoHistoria::~JuegoHistoria(){
//    #ifdef DEBUG
//        cout << "Destructor de JuegoHistoria:"<<this<<endl;
//    #endif
//}
//
//bool JuegoHistoria::isPaused() {
//    return false;
//}
//
//void JuegoHistoria::pause() {
//
//}
//
//void JuegoHistoria::resume() {
//
//}
//
//*/