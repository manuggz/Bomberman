#include "ModoJuegoMultiPlayer.hpp"
#include "../../engine/util/MusicaFondo.hpp"

/**
 * Inicializa la clase Juego
 * @param gameManager
 * @param rutaMapa  Ruta al mapa .tmx
 * @param nVictorias Numero de victorias totales que debe tener un jugador para acabar el juego
 * @param nMinutos Numero de minutos que debe durar como máximo el juego
 * @param isPlayerActivo Array con los players que jugaran
 *
 */
ModoJuegoMultiPlayer::ModoJuegoMultiPlayer (GameManagerInterfazUI * gameManager,std::string rutaMapa, int nVictorias, int nMinutos, bool isPlayerActivo[_PLAYERS])
:InterfazGrafica(gameManager),mGrpSprites(this),mMapa(0,32){

    SDL_Log("ModoJuegoMultiPlayer::ModoJuegoMultiPlayer");

    // Establecemos como activos los players seleccionados a que jueguen
    // Notar que el uso de esta variable recae en que tenemos un array de punteros a clases Players
    // queremos crear en los player en memoria que sean seleccionados en el juego
    // por lo que el uso de esta variable es:
    // si mIsPlayerActivado[i] entonces crear el puntero en la posicion i
    // si mIsPlayerActivado[i] entonces el puntero en la posicion i != NULL
    //
    for(int i = 0; i < _PLAYERS;i++) {
        mIsPlayerActivado[i] = isPlayerActivo[i];
        if(mIsPlayerActivado[i]){
            mPlayerSprite[i] = new Player(this, (IdPlayer) i);

        }
    }

    mRutaTerrenoMapa = rutaMapa;
    mMinutos         = nMinutos;
    mNVictorias      = nVictorias;
}

/**
 * Crea el Mapa los players y el timer
 */
void ModoJuegoMultiPlayer::prepare() {
    InterfazGrafica::prepare();

    //mMapa = new NivelMapa();
    //crearPlayersActivos();

    //displayMensage("�Qu� gane el mejor!");//se presenta el mensage con el nivel actual
}

/**
 * Crea El layout que se encargara de dibujar los componentes necesarios para la interfaz
 * Tales son los componentes que dibujan el texto en pantalla
 * @param gRenderer
 */
void ModoJuegoMultiPlayer::createUI(SDL_Renderer *gRenderer) {


    mLayoutParent = new LayoutAbsolute();

    SDL_Color color = {255,0,0,255}; // Red

    // Componente para el tiempo restante de la ronda
    mpTxtTiempoRestante = new LabelComponent();
    mpTxtTiempoRestante->setText("0");
    mpTxtTiempoRestante->setFont("data/fuentes/OpenSans-Bold.ttf",15);
    mpTxtTiempoRestante->setTextColor(color);
    mpTxtTiempoRestante->setLayoutParam(LAYOUT_PARAM_X,"152");
    mpTxtTiempoRestante->setLayoutParam(LAYOUT_PARAM_Y,"1");

    mLayoutParent->addComponent(mpTxtTiempoRestante);

    // Componente para las vidas restantes del player 1
    for(int i = 0; i < _PLAYERS ; i++){
        mpVidasRestantesPlayer[i] = new LabelComponent();
        mpVidasRestantesPlayer[i]->setText("0");
        mpVidasRestantesPlayer[i]->setFont("data/fuentes/OpenSans-Bold.ttf",15);
        mpVidasRestantesPlayer[i]->setTextColor(color);
        mLayoutParent->addComponent(mpVidasRestantesPlayer[i]);

        if(mIsPlayerActivado[i]){
            mPlayerSprite[i]->cargarRecursos(gRenderer);

        }
    }
    mpVidasRestantesPlayer[PLAYER_1]->setLayoutParam(LAYOUT_PARAM_X,"18");
    mpVidasRestantesPlayer[PLAYER_1]->setLayoutParam(LAYOUT_PARAM_X,"18");
    mpVidasRestantesPlayer[PLAYER_1]->setLayoutParam(LAYOUT_PARAM_Y,"1");

    // Componente para las vidas restantes del player 2
    mpVidasRestantesPlayer[PLAYER_2]->setLayoutParam(LAYOUT_PARAM_X,"51");
    mpVidasRestantesPlayer[PLAYER_2]->setLayoutParam(LAYOUT_PARAM_Y,"1");

    mpVidasRestantesPlayer[PLAYER_3]->setLayoutParam(LAYOUT_PARAM_X,"83");
    mpVidasRestantesPlayer[PLAYER_3]->setLayoutParam(LAYOUT_PARAM_Y,"1");

    mpVidasRestantesPlayer[PLAYER_4]->setLayoutParam(LAYOUT_PARAM_X,"273");
    mpVidasRestantesPlayer[PLAYER_4]->setLayoutParam(LAYOUT_PARAM_Y,"1");

    mpVidasRestantesPlayer[PLAYER_5]->setLayoutParam(LAYOUT_PARAM_X,"307");
    mpVidasRestantesPlayer[PLAYER_5]->setLayoutParam(LAYOUT_PARAM_Y,"1");

    mpTextureTablero = new LTexture();
    mpTextureTablero->cargarDesdeArchivo("data/imagenes/objetos/tablero.bmp",gRenderer,true);

    mpSpriteSheetCarasBomberman = new SpriteSheet(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);

    mpTextureCuadroPeque  = new LTexture();
    mpTextureCuadroPeque->cargarDesdeArchivo("data/imagenes/objetos/cuadro_1.png",gRenderer,false);

    mpTextureCuadroGrande = new LTexture();
    mpTextureCuadroGrande->cargarDesdeArchivo("data/imagenes/objetos/cuadro_3.png",gRenderer,false);


    mpSfxCreadaExplosion = new EfectoSonido("data/sonidos/ping_5.wav",100);
    mpSfxPlayerRecogioItem = new EfectoSonido("data/sonidos/ping_1.wav",100);
    mpSfxPlayerPerdioVida = new EfectoSonido("data/sonidos/ping_7.wav",100);

    mpMusicasFondo[0] = new MusicaFondo("data/sonidos/musica_5.mid");
    mpMusicasFondo[1] = new MusicaFondo("data/sonidos/musica_6.mid");
    mpMusicaAdvertenciaTiempo = new MusicaFondo("data/sonidos/musica_4.mid");

    mGameRenderer = gRenderer;


    SDL_ShowCursor(SDL_DISABLE);
}
/**
 * Inicia el estado del juego
 */
void ModoJuegoMultiPlayer::start() {
    InterfazGrafica::start();
    reiniciarEstado();
    PopUpCountDown *  mostrarMensajeTexto = new PopUpCountDown(mGameManagerInterfaz,"El juego comienza en ",3);
    mostrarMensajeTexto->setSizeText(20);
    mGameManagerInterfaz->showPopUp(mostrarMensajeTexto,ID_POPUP_JUEGO_COMIENZA);
    mpMusicasFondo[rand()%1]->play();
}


void ModoJuegoMultiPlayer::pause() {
    InterfazGrafica::pause();
    mGameTimer.pause();
}

void ModoJuegoMultiPlayer::resume() {
    InterfazGrafica::resume();
    mGameTimer.resume();
}

void ModoJuegoMultiPlayer::resultPopUp(void *result, int popUpCode) {
    InterfazGrafica::resultPopUp(result, popUpCode);

    switch(popUpCode){
        case ID_POPUP_JUEGO_NADIE_GANA_RONDA:
            mGrpSprites.kill();
            reiniciarEstado();
            break;
        case ID_POPUP_JUEGO_MOSTRAR_GAN_CONTINUAR:
            mGrpSprites.kill();
            reiniciarEstado();
            break;
        case ID_POPUP_JUEGO_MOSTRAR_GAN_TERMINAR:{

            IdPlayer idPlayerActivo = PLAYER_NONE;
            for(int j = 0 ; j < _PLAYERS;j++){
                if(estaPlayerActivo((IdPlayer) j)){
                    idPlayerActivo = (IdPlayer) j;
                }
            }

            PopUpMostrarMensajeTexto *  mostrarMensajeTexto = new PopUpMostrarMensajeTexto(mGameManagerInterfaz,
                                                                                           "Player " + std::to_string(
                                                                                                   idPlayerActivo + 1) +
                                                                                           " ha ganado el juego!",3);
            mGameManagerInterfaz->showPopUp(mostrarMensajeTexto,ID_POPUP_JUEGO_GANADOR);

            }
            break;
        case ID_POPUP_JUEGO_GANADOR:
            mGameManagerInterfaz->goBack();
            break;
        case ID_POPUP_JUEGO_COMIENZA:
            break;
        default:break;
    }

    if(result)delete result;
}
/**
 * Una vez cargado el mapa se deben iniciar los players con los valores iniciales que se establecieron que
 * el mapa especifica
 */
void ModoJuegoMultiPlayer::establecerValoresDeMapaPlayers() {
    for(int i = 0; i < _PLAYERS;i++) {
        establecerValoresDeMapaPlayer((IdPlayer)(PLAYER_1 + i));
    }
}

/**
 * Establece los valores iniciales de un player establecidos por el Mapa
 * @param idPlayer
 */
void ModoJuegoMultiPlayer::establecerValoresDeMapaPlayer(IdPlayer idPlayer){
    if(mIsPlayerActivado[idPlayer] && mPlayerSprite[idPlayer]) {
        mPlayerSprite[idPlayer]->move(mMapa.getPosXPlayer(idPlayer),mMapa.getPosYPlayer(idPlayer));
        mPlayerSprite[idPlayer]->setVidas(std::stoi(mMapa.getMapProperty(MAPA_PROPERTY_N_VIDAS_PLAYER)));
        mPlayerSprite[idPlayer]->setNBombas(std::stoi(mMapa.getMapProperty(MAPA_PROPERTY_N_BOMBAS)));
        mPlayerSprite[idPlayer]->setAlcanceBombas(std::stoi(mMapa.getMapProperty(MAPA_PROPERTY_ALCANCE_BOMBAS)));
        mPlayerSprite[idPlayer]->setNCorazones(0);
        mPlayerSprite[idPlayer]->setMPuedeAtravesarBloques(false);
        mPlayerSprite[idPlayer]->setMPuedeAtravesarBombas(false);
        mPlayerSprite[idPlayer]->setMEstaEnfermo(false);
        mpVidasRestantesPlayer[idPlayer]->setText(std::to_string(mPlayerSprite[idPlayer]->getVidas()));
    }
}


/**
 * Agrega los players que fueron activados a los grupos del juego
 * Lo cual hace que se actualizen y dibujen
 */
void ModoJuegoMultiPlayer::agregarPlayersActivos() {
    for (int i = 0; i < _PLAYERS; i++) {
        if(mIsPlayerActivado[i]){

            mPlayerSprite[i]->cambiarEstado(EstadoSprite::ABAJO);
            mPlayerSprite[i]->cambiarEstado(EstadoSprite::PARADO);
            mPlayerSprite[i]->setProteccion(10);

            if(!mPlayerSprite[i]->isActivo()){
                mPlayerSprite[i]->setEnPantalla(true);
                mGrpSprites.add(mPlayerSprite[i]);
                mGrpPlayers.add(mPlayerSprite[i]);
            }
        }
    }
}

void ModoJuegoMultiPlayer::procesarEvento(SDL_Event * evento){
    switch(evento->type){
        case SDL_KEYDOWN:
             switch(evento->key.keysym.sym){
                case SDLK_ESCAPE:
                    mGameManagerInterfaz->goBack();
                    break;
                case SDLK_TAB:
                     /*if(estado_actual!=DISPLAY_MSG&&!pausado){
                         mostrar_kills=!mostrar_kills;
                             if(mostrar_kills)
                             juego_preparar_kills(juego);
                     }*/
                     break;
             }
        break;
        
    }
    
}

int ModoJuegoMultiPlayer::getSegundosInicioNivel(){
    return mGameTimer.getTicks()/1000;
}


/**
 * Actualiza la lógica del juego
 */
void ModoJuegoMultiPlayer::update(){
    const Uint8 *teclas= SDL_GetKeyboardState(NULL);//se obtiene el estado_actual actual del teclado

    mGrpSprites.update(teclas);
    mMapa.update();

    /*SI SE ACABO EL TIEMPO*/
    if(getSegundosInicioNivel() > mMinutos*60){

        for(int i = PLAYER_1 ; i < _PLAYERS;i++){
            if(estaPlayerActivo((IdPlayer) i)){
                //if(mPlayerSprite[i]->getVidas())
                mPlayerSprite[i]->setVidas(0);
                if(mPlayerSprite[i]->getEstado() != EstadoSprite::MURIENDO)
                    mPlayerSprite[i]->cambiarEstado(EstadoSprite::MURIENDO);
            }
        }
        mGameTimer.stop();

    }

    // Si solo quedan 20 segundos o menos
    if((mMinutos*60 - getSegundosInicioNivel()) <= 20 && !mIsPlayingWarningSound){
        mpMusicaAdvertenciaTiempo->playFadeIn();
        mIsPlayingWarningSound = true;
    }

    int totalPlayersActivos = (int) mGrpPlayers.size();

    if(totalPlayersActivos == 1){

        IdPlayer idPlayerActivo = PLAYER_NONE;
        for(int j = 0 ; j < _PLAYERS,idPlayerActivo == PLAYER_NONE;j++){
            if(estaPlayerActivo((IdPlayer) j)){
                idPlayerActivo = (IdPlayer) j;
            }
        }

        if(idPlayerActivo != PLAYER_NONE){
            mRondasGanadas[idPlayerActivo]++;
            if((mIdLiderRondasGanadas==PLAYER_NONE)
               ||(mRondasGanadas[idPlayerActivo] > mRondasGanadas[mIdLiderRondasGanadas]))
                mIdLiderRondasGanadas = idPlayerActivo;
            else if(mIdLiderRondasGanadas != idPlayerActivo
                    &&mRondasGanadas[idPlayerActivo] == mRondasGanadas[mIdLiderRondasGanadas])
                mIdLiderRondasGanadas = PLAYER_NONE;


            if(mRondasGanadas[idPlayerActivo] >= mNVictorias){
                // Notar que dependiendo si se terminó el juego una vez que se muestre quien lleva la mayoria de copas
                // se establece el codigo del POP UP, esto es para que una vez que se ha mostrado el pop up realizar
                // una acción distinta y no tener que agregar una variable de más
                // tal como: terminoJuego = true
                mGameManagerInterfaz->showPopUp(new PopUpJuegoMostrarGanadas(mGameManagerInterfaz, mRondasGanadas), ID_POPUP_JUEGO_MOSTRAR_GAN_TERMINAR);
            }else{
                mGameManagerInterfaz->showPopUp(new PopUpJuegoMostrarGanadas(mGameManagerInterfaz, mRondasGanadas), ID_POPUP_JUEGO_MOSTRAR_GAN_CONTINUAR);
            }
        }
    }else if(totalPlayersActivos==0){
        PopUpMostrarMensajeTexto *  mostrarMensajeTexto = new PopUpMostrarMensajeTexto(mGameManagerInterfaz,
                                                                                       "Nadie gana en esta ronda! :( ",3);
        mGameManagerInterfaz->showPopUp(mostrarMensajeTexto,ID_POPUP_JUEGO_NADIE_GANA_RONDA);
    }

    /**



}//fin if(!pausado)

controlaPausa(teclas);


/*    switch(estado_actual){
case PLAY:
     if(!animandoEntradaMapaVertical)estadoPlay();
     break;
case DISPLAY_MSG:
     estadoDisplayMensage();
     break;
}
if(animandoEntradaMapaVertical){
desplazamiento+=2;
mMapa.setEjeVisualizacion(mMapa.getEjeX(),H_SCREEN-desplazamiento);
if(H_SCREEN-desplazamiento<=mMapa.getEjeY()){
    animandoEntradaMapaVertical=false;
}
}*/
}

bool ModoJuegoMultiPlayer::estaPlayerActivo(IdPlayer playerId){
    return mIsPlayerActivado[playerId]&&mPlayerSprite[playerId]->isActivo();
}

/**
 * Dibuja los datos que se muestran arriba del Mapa
 * @param gRenderer
 */
void ModoJuegoMultiPlayer::drawBarra(SDL_Renderer * gRenderer){

//    // Dibuja un cuadro anaranjado donde van a estar los datos
    mpTextureTablero->render(gRenderer,0,0);

    //PLAYER_1
    // Dibuja la cara del player
    mpSpriteSheetCarasBomberman->setCurrentCuadro(!(estaPlayerActivo(PLAYER_1)) + PLAYER_1*2);
    mpSpriteSheetCarasBomberman->draw(gRenderer,1,6);

    // Dibuja el cuadro que estara por debajo del texto con las vidas restantes
    mpTextureCuadroPeque->render(gRenderer,15,3);

    //PLAYER_2
    // Dibuja la cara del player
    mpSpriteSheetCarasBomberman->setCurrentCuadro(!(estaPlayerActivo(PLAYER_2)) + PLAYER_2*2);
    mpSpriteSheetCarasBomberman->draw(gRenderer,32,6);

    // Dibuja el cuadro que estara por debajo del texto con las vidas restantes
    mpTextureCuadroPeque->render(gRenderer,48,3);

    //PLAYER_3
    // Dibuja la cara del player
    mpSpriteSheetCarasBomberman->setCurrentCuadro(!(estaPlayerActivo(PLAYER_3)) + PLAYER_3*2);
    mpSpriteSheetCarasBomberman->draw(gRenderer,65,6);

    mpTextureCuadroPeque->render(gRenderer,80,3);

//    //PLAYER_4
    // Dibuja la cara del player
    mpSpriteSheetCarasBomberman->setCurrentCuadro(!(estaPlayerActivo(PLAYER_4)) + PLAYER_4*2);
    mpSpriteSheetCarasBomberman->draw(gRenderer,253,6);

    // Dibuja el cuadro que estara por debajo del texto con las vidas restantes
    mpTextureCuadroPeque->render(gRenderer,270,3);

    //PLAYER_5
    // Dibuja la cara del player
    mpSpriteSheetCarasBomberman->setCurrentCuadro(!(estaPlayerActivo(PLAYER_5)) + PLAYER_5*2);
    mpSpriteSheetCarasBomberman->draw(gRenderer,288,6);

    // Dibuja el cuadro que estara por debajo del texto con las vidas restantes
    mpTextureCuadroPeque->render(gRenderer,304,3);

    // Dibujamos el cuadro donde se dibujara el tiempo restante
    mpTextureCuadroGrande->render(gRenderer,137,3);

    // Calculamos y dibujamos el tiempo restante
    if(mGameTimer.isStarted()){
        static char min_[3],seg[3],tiempo[6];

        sprintf(min_,"%2d",(mMinutos*60 - getSegundosInicioNivel()) / 60);
        if(min_[0]==' ')min_[0]='0';

        sprintf(seg,"%2d",(mMinutos*60 - getSegundosInicioNivel()) % 60);
        if(seg[0]==' ')seg[0]='0';

        sprintf(tiempo,"%s:%s",min_,seg);
        mpTxtTiempoRestante->setText(tiempo);
    }

}
int ModoJuegoMultiPlayer::getJoysActivos(){
    return mGameManagerInterfaz->getActiveJoys();
}
SDL_Joystick * ModoJuegoMultiPlayer::getJoy(int id){
    return mGameManagerInterfaz->getJoy(id);
}

void ModoJuegoMultiPlayer::draw(SDL_Renderer * gRenderer){

    drawBarra(gRenderer);//imprimimos la barra mensage
    mMapa.draw(gRenderer);//imprimimos el nivel
    mGrpSprites.draw(gRenderer);

    if(mLayoutParent->isDisabled()){
        packLayout(gRenderer);
    }

    mLayoutParent->draw(gRenderer);

/*    if(pausado){
        //imprimir_palabra(gRenderer, game->getTexture(IMG_FUENTE_5),80,100,"pausa",STR_NORMAL);
        imprimir_desde_grilla(mGameManagerInterfaz->getTexture(IMG_CARAS_BOMBERMAN),id_quien_pauso*2 ,gRenderer,130,90,1,10,0);
    }*/
    //if(estado_actual==DISPLAY_MSG)imprimir_palabra (gRenderer,game->getTexture(IMG_FUENTE_6),x_msg,y_msg,msg_mostrar,STR_MAX_ESTENDIDA);
}


/**
 * Elimina un Sprite del juego
 * Dependiendo del tipo de sprite a eliminar se hace una accion correspondiente
 * Esta funcion es llamada cuando un Sprite Del juego es eliminado.
 * Tal como cuando una bomba termina su animación y esta llama a su funcion "kill" que hace que sea eliminada de todos
 * los grupos asociados y que uno de ellos el UpdateGroup(Solo debería haber un UpdateGroup que lo contenga) llame a
 * este metodo pasandole la referencia a la bomba.
 * @param sprite
 */
void ModoJuegoMultiPlayer::eliminarSprite(Sprite *sprite) {


    // En caso de que el sprite a eliminar sea una bomba
    // Agregamos la explosion
    Bomba * pBombaEliminada   = nullptr;

    if((pBombaEliminada = dynamic_cast<Bomba * >(sprite)) != nullptr){

        // Obtenemos el player que ha lanzado la bomba
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
        mpSfxCreadaExplosion->play();

        delete sprite;
        return;
    }

    TileEnLlamas * pBloqueEliminado = nullptr;
    // En caso que el sprite a eliminar sea un TileEnLlamas En Llamas
    // eliminamos el bloque del mapa
    if((pBloqueEliminado = dynamic_cast<TileEnLlamas * >(sprite)) != nullptr){

        // Eliminamos/Rompemos el tile/bloque del mapa
        // Aun no se habia roto
        mMapa.romperBloque(pBloqueEliminado->getX() - mMapa.getX(),pBloqueEliminado->getY() - mMapa.getY());

        // Obtenemos un posible item a Colocar
        Item::TipoItem tipoNuevoItem = getTipoNuevoItem();

        // Si se ha obtenido uno
        if(tipoNuevoItem != Item::NINGUNO){

            // Creamos los frames de su animacion
            std::string frames = std::to_string(tipoNuevoItem/8*8 + tipoNuevoItem) + "," +
                    std::to_string(tipoNuevoItem/8*8 + 8 + tipoNuevoItem);

            // Creamos el objeto ITem
            Item * nuevoItem = new Item(mGameRenderer,frames,tipoNuevoItem);

            // Lo posicionamos en donde estaba el bloque
            nuevoItem->move(pBloqueEliminado->getX(),pBloqueEliminado->getY());

            // Lo Agregamos a los grupos del juego para que se actualizen/dibujen
            // y para que se detecten las colisones
            mGrpItems.add(nuevoItem);
            mGrpSprites.add(nuevoItem);
        }

        delete sprite;
        return;
    }

    Item * pItemEliminado     = nullptr;
    /**
     * Si un item es eliminado puede ser :
     * Que una explosion lo ha alcanzado y la explosion le aplico kill lo cual lo mando aquí indirectamente
     * Que un player ha colisionado con él y le ha dicho "hey yo te he activado!" y le ha hecho kill()
     * lo cual tambien lo ha mandado aqui.
     * Por lo que al inicio solo obtenemos el player que ha activado el item
     * el cual si ha ocurrido el primer caso debería ser null y por consiguiente se agrega un item en llamas ahí
     * sino entonces se le dice al player "bien hecho toma tu recompensa!"
     */
    if((pItemEliminado = dynamic_cast<Item *>(sprite))){

        Player * pPlayerActivadorItem = pItemEliminado->getPlayerActivador();

        if(!pPlayerActivadorItem){
            Animacion * nuevaAnimacion = new Animacion(new SpriteSheet(mGameRenderer,"data/imagenes/objetos/item_fire.png",1,7),
                                                       "0,0,0,1,1,2,2,2,3,3,4,4,5,5,6,6");
            nuevaAnimacion->move(pItemEliminado->getX(),pItemEliminado->getY());
            mGrpSprites.add(nuevaAnimacion);
        }else{
            Item::TipoItem tipo_item= pItemEliminado->getTipo();
            pPlayerActivadorItem->activarPoderItem(tipo_item);
            mpSfxPlayerRecogioItem->play();

        }
        delete sprite;
        return;
    }

    if(dynamic_cast<Explosion *>(sprite)){
        delete sprite;
    }
    return;
}
/**
 * Este metodo es llamado por los players para decir "hey estoy muerto! y este tipo me ha matado! dime que hago"
 * o simplemente "hey estoy muerto dime que hago"
 * @param pPlayer
 * @param pPlayerCausante
 */
void ModoJuegoMultiPlayer::playerMuerto(Player * pPlayer,Sprite * pPlayerCausante){

    if(pPlayer->getEstado() != EstadoSprite::MURIENDO){
        if(!pPlayer->getNCorazones()){

            pPlayer->cambiarEstado(EstadoSprite::MURIENDO);

            /*if(juego->explosiones[id_explo-1]->lanzador!=id)
                juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]++;
            else
                juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]--;
            juego->kills[id]++;*/
            //if(juego->getLanzador(EXPLOSION,id_explo)!=this->id);
            //                        juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]++;
            //else;
            //                        juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]--;
            //                    juego->kills[id]++;
        }else{
            pPlayer->setProteccion(10);
            pPlayer->setNCorazones(pPlayer->getNCorazones() - 1);
        }

    }else {

        if (pPlayer->getVidas() > 0) {
            establecerValoresDeMapaPlayer(pPlayer->getId());
            pPlayer->cambiarEstado(EstadoSprite::PARADO);
            pPlayer->setProteccion(5);
            pPlayer->setVidas(pPlayer->getVidas() - 1);
            mpVidasRestantesPlayer[pPlayer->getId()]->setText(std::to_string(pPlayer->getVidas()));
            mpSfxPlayerPerdioVida->play();
        } else {
            pPlayer->setEnPantalla(false);
            pPlayer->kill();

        }
    }
}
Item::TipoItem ModoJuegoMultiPlayer::getTipoNuevoItem(){


    std::vector<Item::TipoItem > disponibles = {
            Item::ITEM_BOMBA_MAX,
            Item::ITEM_ALCANCE_MAX,
            Item::ITEM_ALCANCE,
            Item::ITEM_BOMBA,
            Item::ITEM_ATRAVIESA_PAREDES,
            Item::ITEM_PROTECCION,
            Item::ITEM_ALEATORIO,
            Item::ITEM_PATINETA,
            Item::ITEM_CORAZON,
            Item::ITEM_ATRAVIESA_BOMBAS,
            Item::ITEM_PATINETA
    };

    if(rand() % 100 >= 70){
        return disponibles[rand() % disponibles.size()];
    }else{
        return  Item::NINGUNO;
    }
}

deque<Sprite *> ModoJuegoMultiPlayer::colisionBloqueEnLlamas(SDL_Rect rect) {
    return mGrpBloques.collide(rect);
}

deque<Sprite *> ModoJuegoMultiPlayer::colisionConItems(SDL_Rect rect) {
    return mGrpItems.collide(rect);
}

TileEnLlamas *ModoJuegoMultiPlayer::agregarBloqueEnLlamas(int x, int y) {

    // Buscamos la animacion del mapa para los bloques en llamas
    vector<string> *aniBloqueLlamas = mMapa.getAnimacionFrames(
            mMapa.getMapProperty(MAPA_PROPERTY_ID_TILE_LLAMAS)
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
    TileEnLlamas * nuevoBloque = new TileEnLlamas(new SpriteSheet(mGameRenderer,
                                                      mMapa.getRutaTileSet(),
                                                      mMapa.getNFilasTileSet(),
                                                      mMapa.getNColumnasTileSet()),frames,x,y,1);
    //nuevoBloque->setAnimacion(mMapa.getSpriteSheetTiles(),aniBloqueLlamas);
    mGrpBloques.add(nuevoBloque);
    mGrpSprites.add(nuevoBloque);
    return nuevoBloque;
}

bool ModoJuegoMultiPlayer::esBloqueSolido(int x, int y) {
    x -= mMapa.getX();
    y -= mMapa.getY();
    return mMapa.esBloqueSolido(x,y);
}

bool ModoJuegoMultiPlayer::esBloqueRompible(int x, int y) {
    x -= mMapa.getX();
    y -= mMapa.getY();
    return mMapa.esBloqueRompible(x,y);
}


deque<Sprite *> ModoJuegoMultiPlayer::colisionConExplosiones(SDL_Rect rect) {
    return mGrpExplosiones.collide(rect);
}

std::deque<Sprite *> ModoJuegoMultiPlayer::colisionConBombas(SDL_Rect  rect) {
    return mGrpBombas.collide(rect);
}

NivelMapa::ExtremoColision ModoJuegoMultiPlayer::colisionConMapa(SDL_Rect rect_coli, int *lado_colision, bool soloBloquesNoTraspasables){
    /*Comprueba si un rect colisiona con el nivel*/
    rect_coli.x -= mMapa.getX();
    rect_coli.y -= mMapa.getY();
    return mMapa.colision(rect_coli,lado_colision,soloBloquesNoTraspasables);
}

bool ModoJuegoMultiPlayer::isOutOfMapBounds(SDL_Rect rect) {
    rect.x -= mMapa.getX();
    rect.y -= mMapa.getY();
    return !mMapa.contain(rect);
}

Bomba *ModoJuegoMultiPlayer::agregarBomba(Player * player) {

    // Pasamos la posicion X a la coordenada del Mapa
    int nuevaPosicionX = player->getX() + 7 - mMapa.getX();
    // Formateamos la posicion X a que sea proporcional al ancho de los tiles
    nuevaPosicionX = nuevaPosicionX/mMapa.getTileWidth()*mMapa.getTileWidth();
    // Pasamos la posicion X a la coordenada de la pantalla
    nuevaPosicionX = nuevaPosicionX + mMapa.getX();

    // Pasamos la posicion Y a la coordenada del Mapa
    int nuevaPosicionY = player->getY() + 11 - mMapa.getY();
    // Formateamos la posicion Y a que sea proporcional al alto de los tiles
    nuevaPosicionY = nuevaPosicionY/mMapa.getTileHeight()*mMapa.getTileHeight();
    // Pasamos la posicion Y a la coordenada de la pantalla
    nuevaPosicionY = nuevaPosicionY + mMapa.getY();

    // Si en esa posición hay un bloque solido no se coloca una bomba ahí
    if(mMapa.esBloqueSolido(nuevaPosicionX - mMapa.getX(),nuevaPosicionY - mMapa.getY())){
        return nullptr;
    }

    Bomba * nuevaBomba = new Bomba(mGameRenderer,player);
    nuevaBomba->move(nuevaPosicionX,nuevaPosicionY);

    if(   mGrpEnemigos.collide(nuevaBomba).size() == 0
       && mGrpItems.collide(nuevaBomba).size()    == 0
       && mGrpPlayers.collide(nuevaBomba).size()  == 1
        && mGrpBombas.collide(nuevaBomba).size() == 0){
        mGrpBombas.add(nuevaBomba);
        mGrpSprites.add(nuevaBomba);
        return nuevaBomba;
    }

    delete nuevaBomba;

    return nullptr;
}


void ModoJuegoMultiPlayer::packLayout(SDL_Renderer *pRenderer) {
    SDL_Rect rect = mGameManagerInterfaz->getRectScreen();
    mLayoutParent->pack(pRenderer);
    mLayoutParent->setRectDibujo(rect);
}

void ModoJuegoMultiPlayer::reiniciarEstado() {
    mMapa.cargar(mGameRenderer,mRutaTerrenoMapa);
    establecerValoresDeMapaPlayers();
    agregarPlayersActivos();
    mGameTimer.start();
}

ModoJuegoMultiPlayer::~ModoJuegoMultiPlayer(){
    SDL_Log("ModoJuegoMultiPlayer::~ModoJuegoMultiPlayer");
    for(int i= 0;i<_PLAYERS;i++){
        delete mPlayerSprite[i];
        delete mpVidasRestantesPlayer[i];
    }

    delete mpTxtTiempoRestante;
    delete mLayoutParent;
    delete mpTextureTablero;
    delete mpSpriteSheetCarasBomberman;
    delete mpTextureCuadroPeque;
    delete mpTextureCuadroGrande;

    delete mpSfxCreadaExplosion;
    delete mpSfxPlayerRecogioItem;
    delete mpSfxPlayerPerdioVida;

    delete mpMusicasFondo[0];
    delete mpMusicasFondo[1];
    delete mpMusicaAdvertenciaTiempo;

}

void ModoJuegoMultiPlayer::updateWhenPopUp() {
    mGrpSprites.update(nullptr);
    mMapa.update();
}
