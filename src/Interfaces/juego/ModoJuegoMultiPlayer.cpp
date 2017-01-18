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
ModoJuegoMultiPlayer::ModoJuegoMultiPlayer (GameManagerInterfazUI * gameManager,std::string rutaMapa, int nVictorias, int nMinutos, bool isPlayerActivo[Player::N_PLAYERS])
:InterfazGrafica(gameManager),mGrpSprites(this),mMapa(0,32){

    SDL_Log("ModoJuegoMultiPlayer::ModoJuegoMultiPlayer");

    // Establecemos como activos los players seleccionados a que jueguen
    // Notar que el uso de esta variable recae en que tenemos un array de punteros a clases Players
    // queremos crear en los player en memoria que sean seleccionados en el juego
    // por lo que el uso de esta variable es:
    // si mIsPlayerActivado[i] entonces crear el puntero en la posicion i
    // si mIsPlayerActivado[i] entonces el puntero en la posicion i != NULL
    //
    for(int i = 0; i < Player::N_PLAYERS;i++) {
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

    //mMapa = new LectorMapa();
    //crearPlayersActivos();

    //displayMensage("�Qu� gane el mejor!");//se presenta el mensage con el nivel actual
}

/**
 * Crea El layout que se encargara de dibujar los componentes necesarios para la interfaz
 * Tales son los componentes que dibujan el texto en pantalla
 * @param gRenderer
 */
void ModoJuegoMultiPlayer::createUI(SDL_Renderer *gRenderer) {



    // Componente para las vidas restantes del player 1
    for(int i = 0; i < Player::N_PLAYERS ; i++){

        if(mIsPlayerActivado[i]){
            mPlayerSprite[i]->cargarRecursos(gRenderer);

        }
    }

    mpTextureHUD = new LTexture();
    mpTextureHUD->cargarDesdeArchivo("data/imagenes/objetos/tablero.bmp",gRenderer,true);

    mpSpriteSheetCarasBomberman = new SpriteSheet(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);

    mBitmapFont[FUENTE_NORMAL] = new BitmapFont(gRenderer,   "data/fuentes/fuente2_16_normal.png");
    mBitmapFont[FUENTE_RESALTADA] = new BitmapFont(gRenderer,"data/fuentes/fuente2_16_resaltado.png");

    SpriteSheet *spriteSheet;
    for(int i = 0; i < Player::N_PLAYERS;i++){
        if(mIsPlayerActivado[i]) {
            spriteSheet = new SpriteSheet(gRenderer, "data/imagenes/objetos/trofeo.bmp", 1, 13, true);
            pAnimaTrofeos[i] = new Animacion(spriteSheet, "7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",
                                             19 + i * 60, 15);
            pAnimaTrofeos[i]->setRepeticiones(-1);

            mpBitmapValorCopasGanadas[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 42 + i * 60, 20);
            mpBitmapValorCopasGanadas[i]->setText("0");

            mGrpSprites.add(pAnimaTrofeos[i]);
        }

    }

    spriteSheet = new SpriteSheet(gRenderer,"data/imagenes/objetos/trofeo.bmp",1,13,true);
    mpAnimacionCopaMaxVictorias=new Animacion(spriteSheet,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",139,-2);
    mpAnimacionCopaMaxVictorias->setRepeticiones(-1);
    mpBitmapValorCopasMax = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 139 + 23,3);

    mpBitmapMaxTimeRonda = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 139 + 23,3);


    mpSfxCreadaExplosion = new EfectoSonido("data/sonidos/ping_5.wav",100);
    mpSfxPlayerRecogioItem = new EfectoSonido("data/sonidos/ping_1.wav",100);
    mpSfxPlayerPerdioVida = new EfectoSonido("data/sonidos/ping_7.wav",100);

    mpMusicasFondo[0] = new MusicaFondo("data/sonidos/musica_5.mid");
    mpMusicasFondo[1] = new MusicaFondo("data/sonidos/musica_6.mid");
    mpMusicaAdvertenciaTiempo = new MusicaFondo("data/sonidos/musica_4.mid");

    if(!mNVictorias){
        rectPlaceHolderTime.x =128;
    }else {
        rectPlaceHolderTime.x = 90;
        mpBitmapValorCopasMax->setText(std::to_string(mNVictorias));
        mGrpSprites.add(mpAnimacionCopaMaxVictorias);
    }
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
    mpMusicasFondo[rand()%2]->play();
}


void ModoJuegoMultiPlayer::pause() {
    InterfazGrafica::pause();
    if(mMinutos)mGameTimer.pause();
}

void ModoJuegoMultiPlayer::resume() {
    InterfazGrafica::resume();
    if(mMinutos)mGameTimer.resume();
}

void ModoJuegoMultiPlayer::resultPopUp(InterfazEstandarBackResult *result, int popUpCode) {
    InterfazGrafica::resultPopUp(result, popUpCode);

    switch(popUpCode){
        case ID_POPUP_JUEGO_NADIE_GANA_RONDA:
        case ID_POPUP_JUEGO_MOSTRAR_GAN_CONTINUAR:
            mGrpSprites.kill();
            reiniciarEstado();
            for(int i = 0; i < Player::N_PLAYERS;i++) {
                if(mIsPlayerActivado[i]) {
                    mGrpSprites.add(pAnimaTrofeos[i]);
                    mpBitmapValorCopasGanadas[i]->setText(std::to_string(mRondasGanadas[i]));
                }
            }
            if(mNVictorias > 0){
                mGrpSprites.add(mpAnimacionCopaMaxVictorias);
            }
            break;
        case ID_POPUP_JUEGO_MOSTRAR_GAN_TERMINAR:{

            IdPlayer idPlayerActivo = PLAYER_NONE;
            for(int j = 0 ; j < Player::N_PLAYERS;j++){
                if(estaPlayerActivo((IdPlayer) j)){
                    idPlayerActivo = (IdPlayer) j;
                }
            }

            PopUpMostrarMensajeTextoTimer *  mostrarMensajeTexto = new PopUpMostrarMensajeTextoTimer(mGameManagerInterfaz,
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
    for(int i = 0; i < Player::N_PLAYERS;i++) {
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
        mPlayerSprite[idPlayer]->setVelocidad(1);
    }
}


/**
 * Agrega los players que fueron activados a los grupos del juego
 * Lo cual hace que se actualizen y dibujen
 */
void ModoJuegoMultiPlayer::agregarPlayersActivos() {
    for (int i = 0; i < Player::N_PLAYERS; i++) {
        if(mIsPlayerActivado[i]){

            mPlayerSprite[i]->cambiarEstado(EstadoSprite::ABAJO);
            mPlayerSprite[i]->cambiarEstado(EstadoSprite::PARADO);
            mPlayerSprite[i]->setProteccion(10);

            if(! mGrpPlayers.contain(mPlayerSprite[i])){
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

    // Calculamos y dibujamos el tiempo restante
    if(mGameTimer.isStarted()){
        static char min_[3],seg[3],tiempo[6];

        sprintf(min_,"%2d",(mMinutos*60 - getSegundosInicioNivel()) / 60);
        if(min_[0]==' ')min_[0]='0';

        sprintf(seg,"%2d",(mMinutos*60 - getSegundosInicioNivel()) % 60);
        if(seg[0]==' ')seg[0]='0';

        sprintf(tiempo,"%s:%s",min_,seg);
        if(!(min_ < 0 || seg < 0))mpBitmapMaxTimeRonda->setText(tiempo);
    }
    mGrpSprites.update(teclas);
    mMapa.update();

    /*SI SE ACABO EL TIEMPO*/
    if(getSegundosInicioNivel() > mMinutos*60){

        for(int i = PLAYER_1 ; i < Player::N_PLAYERS;i++){
            if(estaPlayerActivo((IdPlayer) i)){
                //if(mPlayerSprite[i]->getVidas())
                mPlayerSprite[i]->setVidas(0);
                if(mPlayerSprite[i]->getEstado() != EstadoSprite::MURIENDO)
                    mPlayerSprite[i]->cambiarEstado(EstadoSprite::MURIENDO);
            }
        }
        if(mMinutos)mGameTimer.stop();

    }

    // Si solo quedan 20 segundos o menos
    if((mMinutos*60 - getSegundosInicioNivel()) <= 20 && !mIsPlayingWarningSound){
        mpMusicaAdvertenciaTiempo->playFadeIn();
        mIsPlayingWarningSound = true;
    }

    int totalPlayersActivos = (int) mGrpPlayers.size();

    if(totalPlayersActivos == 1){

        IdPlayer idPlayerActivo = PLAYER_NONE;
        for(int j = 0 ; j < Player::N_PLAYERS,idPlayerActivo == PLAYER_NONE;j++){
            if(estaPlayerActivo((IdPlayer) j)){
                idPlayerActivo = (IdPlayer) j;
            }
        }

        if(idPlayerActivo != PLAYER_NONE){
            mRondasGanadas[idPlayerActivo]++;
            mpBitmapValorCopasGanadas[idPlayerActivo]->setText(std::to_string(mRondasGanadas[idPlayerActivo]));
            if((mIdLiderRondasGanadas==PLAYER_NONE)
               ||(mRondasGanadas[idPlayerActivo] > mRondasGanadas[mIdLiderRondasGanadas]))
                mIdLiderRondasGanadas = idPlayerActivo;
            else if(mIdLiderRondasGanadas != idPlayerActivo
                    &&mRondasGanadas[idPlayerActivo] == mRondasGanadas[mIdLiderRondasGanadas])
                mIdLiderRondasGanadas = PLAYER_NONE;


            if(mRondasGanadas[idPlayerActivo] >= mNVictorias && mNVictorias > 0){
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
        PopUpMostrarMensajeTextoTimer *  mostrarMensajeTexto = new PopUpMostrarMensajeTextoTimer(mGameManagerInterfaz,
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
void ModoJuegoMultiPlayer::drawHUD(SDL_Renderer *gRenderer){

//    // Dibuja un cuadro anaranjado donde van a estar los datos
    mpTextureHUD->draw(gRenderer, 0, 0);

    for(int i=0;i<Player::N_PLAYERS;i++){
        if(mIsPlayerActivado[i]){
            mpSpriteSheetCarasBomberman->setCurrentCuadro(i*2 + !mPlayerSprite[i]->isActivo());
            mpSpriteSheetCarasBomberman->draw(gRenderer,6+ i*60,20);
            mpBitmapValorCopasGanadas[i]->draw(gRenderer);
        }
    }

    if(mNVictorias > 0){
        mpBitmapValorCopasMax->draw(gRenderer, mpAnimacionCopaMaxVictorias->getX() + 23,3);
    }

    if(mMinutos > 0){
        SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
        SDL_RenderFillRect(gRenderer,&rectPlaceHolderTime);
        mpBitmapMaxTimeRonda->draw(gRenderer,rectPlaceHolderTime.x + 5,rectPlaceHolderTime.y + 1);
    }

}
int ModoJuegoMultiPlayer::getJoysActivos(){
    return mGameManagerInterfaz->getActiveJoys();
}
SDL_Joystick * ModoJuegoMultiPlayer::getJoy(int id){
    return mGameManagerInterfaz->getJoy(id);
}

void ModoJuegoMultiPlayer::draw(SDL_Renderer * gRenderer){

    mMapa.draw(gRenderer);//imprimimos el nivel
    drawHUD(gRenderer);//imprimimos la barra mensage
    mGrpSprites.draw(gRenderer);
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
            int vidas_actuales = pPlayer->getVidas();
            establecerValoresDeMapaPlayer(pPlayer->getId());
            pPlayer->cambiarEstado(EstadoSprite::PARADO);
            pPlayer->setProteccion(5);
            pPlayer->setVidas(vidas_actuales - 1);
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

LectorMapa::ExtremoColision ModoJuegoMultiPlayer::colisionConMapa(SDL_Rect rect_coli, int *lado_colision, bool soloBloquesNoTraspasables){
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


void ModoJuegoMultiPlayer::reiniciarEstado() {
    mMapa.cargar(mGameRenderer,mRutaTerrenoMapa);
    establecerValoresDeMapaPlayers();
    agregarPlayersActivos();
    if(mIsPlayingWarningSound){
        mpMusicasFondo[rand()%2]->play();
    }
    mIsPlayingWarningSound = false;
    if(mMinutos > 0) {
        mGameTimer.start();
    }
}

ModoJuegoMultiPlayer::~ModoJuegoMultiPlayer(){
    SDL_Log("ModoJuegoMultiPlayer::~ModoJuegoMultiPlayer");
    for(int i= 0;i<Player::N_PLAYERS;i++){
        delete mPlayerSprite[i];
        delete pAnimaTrofeos[i];
        delete mpBitmapValorCopasGanadas[i];

    }
    delete mBitmapFont[0];
    delete mBitmapFont[1];

    delete mpTextureHUD;
    delete mpSpriteSheetCarasBomberman;

    delete mpSfxCreadaExplosion;
    delete mpSfxPlayerRecogioItem;
    delete mpSfxPlayerPerdioVida;

    delete mpMusicasFondo[0];
    delete mpMusicasFondo[1];
    delete mpMusicaAdvertenciaTiempo;

    delete mpBitmapMaxTimeRonda;

    delete mpBitmapValorCopasMax;
    delete mpAnimacionCopaMaxVictorias;

}

void ModoJuegoMultiPlayer::updateWhenPopUp() {
    mGrpSprites.update(nullptr);
    mMapa.update();
}

