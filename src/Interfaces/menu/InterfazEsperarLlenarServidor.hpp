//
// Created by manuggz on 14/01/17.
//

/**
 *
 * Parte 1: TCP
 * CLIENTE ---> Conectar        {}                                                              -----> SERVIDOR
 * CLIENTE <--- TieneMapa     {Nombre:uint8_t[100]}                                            <----- SERVIDOR
 * CLIENTE ---> RespuestaTieneMapa     {tiene_mapa:uint8_t}                                            -----> SERVIDOR

 * CLIENTE [NO TIENE MAPA]<--- DatosMapa  {linea:uint8_t[255]}xtodas                                            -----> SERVIDOR

 * CLIENTE ---> Indentificarse  {NickName:uint8_t[8]}:8                                         -----> SERVIDOR
 * CLIENTE <--- Reconocer      {id_cliente:uint16_t}:3                         -----  SERVIDOR
 * CLIENTE <--- PuertoUdp      {n_puerto:uint16_t}:2                                            <-----  SERVIDOR
 * CLIENTE ---> PuertoUdp      {n_puerto:uint16_t}:2                                            ----->  SERVIDOR
 * CLIENTE ---> Desconectar    {} -----  SERVIDOR

 * Parte 2: UDP
 *
 * CLIENTES <- UPDATE_ESTADO__ROOM {flair:uint8_t ,id_update:uint_32_t,
 *                          tiempo_por_ronda:uint8_t,num_victorias:uint_8_t,
 *                          is_activo:uint8_t,id_cliente:uint16_t ,id_player:uint8_t, nick_name:uint8_t[8],
 *                          is_acti vo:uint8_t,id_cliente:uint16_t ,id_player:uint8_t, nick_name:uint8_t[8],
 *                          is_activo:uint8_t,id_cliente:uint16_t ,id_player:uint8_t, nick_name:uint8_t[8],
 *                          is_activo:uint8_t,id_cliente:uint16_t ,id_player:uint8_t, nick_name:uint8_t[8],
 *                          is_activo:uint8_t,id_cliente:uint16_t ,id_player:uint8_t, nick_name:uint8_t[8],
 *                          }:[67] <--- SERVIDOR

 * CLIENTE --->  KEEP_ALIVE {flair:uint8_t,id_cliente:uint16_t,id_last_update:uint_32_t}: -----> SERVIDOR
 * CLIENTE <--- ACK_KEEP_ALIVE  {flair:uint8_t} <----- SERVIDOR
 *
 * CLIENTES <--- START_GAME  {flair:uint8_t,idPlayer:uint8_t}: <----- SERVIDOR
 * CLIENTE ---> ACK_START_GAME  {flair:uint8_t} -----> SERVIDOR
 *
 */

#ifndef BOMBERMAN_INTERFAZESPERARLLENARSERVIDOR_HPP
#define BOMBERMAN_INTERFAZESPERARLLENARSERVIDOR_HPP


#include <SDL_net.h>
#include "../../engine/interfaces/InterfazGrafica.hpp"
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/layout/Componentes/BotonComponent.hpp"
#include "../../personajes/player.hpp"
#include "../../engine/layout/Componentes/LabelComponent.hpp"
#include "../../engine/util/EfectoSonido.hpp"
#include "../../engine/util/MusicaFondo.hpp"
#include "../../engine/sprites/CDrawGroup.hpp"
#include "../../niveles/LectorMapa.hpp"
#include "PopUpInsertarTexto.hpp"
#include "ConstantesServidor.hpp"

class InterfazEsperarLlenarServidor: public InterfazGrafica, public UpdateGroupContainerInterfaz, public BotonInterfaz {
public:
    static const int ID_POP_UP_INSERTAR_NICK_SERVIDOR = 12;
    InterfazEsperarLlenarServidor(GameManagerInterfazUI *gameManagerInterfaz) : InterfazGrafica(gameManagerInterfaz),
                                                                                mMapaTerrenoSeleccionado(0,32){
        for(int i = 0; i < MAX_CLIENTES;i++){
            clients[i] = new Cliente();
            clients[i]->activo = false;
        }
        
        mUltimoIdUtilizado = 0;
        clients[0]->activo = true;
        clients[0]->id_cliente = mUltimoIdUtilizado++;
        clients[0]->id_player = PLAYER_1;
        mNumClientes = 1;
    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazGrafica::createUI(gRenderer);
        mLayoutParent = new LayoutAbsolute();

        // BotonComponent para controlar cuanto tiempo para acabar una ronda
//        mBtnSubirTiempo=new BotonComponent(
        //              mGameManager->getTexture(Galeria::CodeImagen::IMG_BOTON_FLECHA_PEQUE_DERECHA),this);
        LTexture * textureBotonSubirTiempo = new LTexture();
        textureBotonSubirTiempo->cargarDesdeArchivo("data/imagenes/botones/boton_flecha.png", gRenderer, false);
        mBtnSubirTiempo=new BotonComponent(textureBotonSubirTiempo, this, MENU_BOTON_SUBIR_TIEMPO);
        mLayoutParent->addComponent(mBtnSubirTiempo);
        mBtnSubirTiempo->setLayoutParam(LAYOUT_PARAM_X,"197");
        mBtnSubirTiempo->setLayoutParam(LAYOUT_PARAM_Y,"2");

        // BotonComponent para controlar cuantas victorias son necesarias para terminar el juego
        LTexture * textureBotonSubirVictorias = new LTexture();
        textureBotonSubirVictorias->cargarDesdeArchivo("data/imagenes/botones/boton_flecha.png", gRenderer, false);
        mBtnSubirVictorias=new BotonComponent(textureBotonSubirVictorias,this,MENU_BOTON_SUBIR_VICTORIAS);
        mLayoutParent->addComponent(mBtnSubirVictorias);
        mBtnSubirVictorias->setLayoutParam(LAYOUT_PARAM_X,"297");
        mBtnSubirVictorias->setLayoutParam(LAYOUT_PARAM_Y,"2");


        // BotonComponent para comenzar a jugar
        LTexture * textureBotonJugar = new LTexture();
        textureBotonJugar->cargarDesdeArchivo("data/imagenes/botones/boton_jugar_2.png", gRenderer, false);
        mBtnJugar=new BotonComponent(textureBotonJugar,this,MENU_BOTON_JUGAR);
        mBtnJugar->setVisible(false); // Lo ocultamos hasta que se seleccionen dos jugadores
        mLayoutParent->addComponent(mBtnJugar);
        mBtnJugar->setLayoutParam(LAYOUT_PARAM_X,"240");
        mBtnJugar->setLayoutParam(LAYOUT_PARAM_Y,"225");

        // Controla las animaciones de los personajes cuando se seleccionan para jugar
        mSprites=new DrawGroup(this);

        //Animaciones para los personajes (Hace que parezcan que caminan) cuando se seleccionan
        SpriteSheet * spriteSheetTmp;

        for(int i=0;i<Player::N_PLAYERS;i++){
            // Animacion para cuando aun no se ha seleccionado el personaje(Hace que parpadee "presiona")

            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_" + std::to_string(i+1)+".bmp",1,12,true);
            mAnimacionPlayer[i]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");


            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/textos/txt_presiona.png",2,1);
            //mAnimacionMensajePresiona[i]=new Animacion(spriteSheetTmp,"0,0,1,1");
            // Animacion para cuando se selecciono el personaje(Hace que parpadee "activado")
            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/textos/txt_activado.png",2,1);
            //mAnimacionMensajeActivado[i]=new Animacion(spriteSheetTmp,"0,0,0,1,1,1");

            // Hace que las animaciones se repitan indefinidamente(Hasta que se eliminen desde el codigo)
            mAnimacionPlayer[i]->setRepeticiones(-1);

            mpComponentTextoNickPlayer[i] = new LabelComponent();
            mpComponentTextoNickPlayer[i]->setText("Esperando...");
            mpComponentTextoNickPlayer[i]->setFont("data/fuentes/OpenSans-Bold.ttf",10);
            mpComponentTextoNickPlayer[i]->setTextColor(SDL_Color {0,255,0,255});
            mLayoutParent->addComponent(mpComponentTextoNickPlayer[i]);
        }

        SDL_Color color = {255,0,0,255};
        mTextLabelMinutos = new LabelComponent();
        mTextLabelMinutos->setText(std::to_string(minutosEscogidos));
        mTextLabelMinutos->setFont("data/fuentes/OpenSans-Bold.ttf",15);
        mTextLabelMinutos->setTextColor(color);
        mTextLabelMinutos->setLayoutParam(LAYOUT_PARAM_X,"180");
        mTextLabelMinutos->setLayoutParam(LAYOUT_PARAM_Y,"0");
        mLayoutParent->addComponent(mTextLabelMinutos);

        mTextLabelVictorias = new LabelComponent();
        mTextLabelVictorias->setText(std::to_string(victoriasEscogidas));
        mTextLabelVictorias->setFont("data/fuentes/OpenSans-Bold.ttf",15);
        mTextLabelVictorias->setTextColor(color);
        mTextLabelVictorias->setLayoutParam(LAYOUT_PARAM_X,"283");
        mTextLabelVictorias->setLayoutParam(LAYOUT_PARAM_Y,"0");
        mLayoutParent->addComponent(mTextLabelVictorias);

        //static char tmp[50];
        //sprintf(tmp,"%d",i+1);
        //imprimir_palabra(gRenderer,mGameManager->getTexture(IMG_FUENTE_6),mAnimacionPlayer[i]->getX()-9+41,mAnimacionPlayer[i]->getY()+19,tmp,STR_MAX_ESTENDIDA);

        //mGameManager->playSound(SND_MENU);

        //mpSfxCambiarMapa = new EfectoSonido("data/sonidos/ping_2.wav",100);
        mpSfxPressJugar  = new EfectoSonido("data/sonidos/ping_5.wav",100);
        mpSfxTogglePlayerEstado = new EfectoSonido("data/sonidos/ping_3.wav",100);

        musicaFondoMenu = new MusicaFondo("data/sonidos/musica_1.mid");

        mpTextureTablero = new LTexture();
        mpTextureTablero->cargarDesdeArchivo("data/imagenes/objetos/tablero.bmp",gRenderer,true);

        mpTextureCuadroPeque = new LTexture();
        mpTextureCuadroPeque->cargarDesdeArchivo("data/imagenes/objetos/cuadro_1.png",gRenderer,false);

        mpTextureMensPlayersEnBatalla = new LTexture();
        mpTextureMensPlayersEnBatalla->cargarDesdeArchivo("data/imagenes/textos/txt_players_en_batalla.png",gRenderer,false);

        mpTextureMensTiempoPorRonda = new LTexture();
        mpTextureMensTiempoPorRonda->cargarDesdeArchivo("data/imagenes/textos/txt_tiempo_por_ronda.png",gRenderer,false);

        mpTextureMensVictorias = new LTexture();
        mpTextureMensVictorias->cargarDesdeArchivo("data/imagenes/textos/txt_victorias.png",gRenderer,false);

        for(int i = 0; i < Player::N_PLAYERS; i++) {
            mpSpriteSheetPlayer[i] = new SpriteSheet(gRenderer, "data/imagenes/personajes/player_" + std::to_string(i + 1) + ".bmp", 1, 12,true);
            mpSpriteSheetPlayer[i]->setAlpha(150);
            mpSpriteSheetPlayer[i]->setCurrentCuadro(6);
        }

        mpSpriteSheetCarasBomberman = new SpriteSheet(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);
        establecerTerrenoBatalla(gRenderer,mMapaEscogido);

        SDL_ShowCursor(SDL_ENABLE);
        mGRenderer = gRenderer;

    }

    void start() override {
        InterfazGrafica::start();
        IPaddress ip;
        mTCPPuerto = TCP_DEFAULT_PUERTO;

        if(SDLNet_ResolveHost(&ip, NULL, mTCPPuerto) == -1) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDLNet_ResolveHost.%s",SDLNet_GetError());
            mHaOcurridoError = true;
            return;
        }

        mTCPServerSocket = SDLNet_TCP_Open(&ip);
        if(mTCPServerSocket == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDLNet_TCP_Open.%s",SDLNet_GetError());
            mHaOcurridoError = true;
            return;
        }

        //socket_set = SDLNet_AllocSocketSet(MAX_CLIENTES);

        //if(socket_set == NULL) {
        //    fprintf(stderr, "ER: SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
         //   exit(-1);
        //}

        // create a UDPsocket on any available port (client)
        //UDPsocket udpsock;

        mUDPServerSocket=SDLNet_UDP_Open(0);
        if(!mUDPServerSocket) {
            printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
            mHaOcurridoError = true;
            return;
        }else{
            IPaddress *address;

            address=SDLNet_UDP_GetPeerAddress(mUDPServerSocket,-1);
            if(!address) {
                printf("SDLNet_UDP_GetPeerAddress: %s\n", SDLNet_GetError());
                // do something because we failed to get the address
                mHaOcurridoError = true;
                return;
            }
            else {
                // perhaps print out address->host and address->port
                mUDPPuerto = address->port;
                SDL_Log("Puerto asignado al udp servidor:%d.",mUDPPuerto);
            }
        }

        mUDPPacketEnviar=SDLNet_AllocPacket(MAX_TAM_UPDATE_ROOM);
        if(!mUDPPacketEnviar) {
            printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
            mHaOcurridoError = true;
        }

        mUDPPacketRecibir=SDLNet_AllocPacket(10);
        if(!mUDPPacketRecibir) {
            printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
            mHaOcurridoError = true;
        }

        PopUpInsertarTexto *popUpInsertarTexto = new PopUpInsertarTexto(mGameManagerInterfaz,
                                                                        "Inserte su Nick:",
                                                                        8
        );
        mGameManagerInterfaz->showPopUp(popUpInsertarTexto, ID_POP_UP_INSERTAR_NICK_SERVIDOR);
    }

    void resultPopUp(InterfazEstandarBackResult *result, int i) override {
        InterfazGrafica::resultPopUp(result, i);
        switch(i){
            case ID_POP_UP_INSERTAR_NICK_SERVIDOR:
                if(result) {
                    mMiNick = result->texto;;
                    memcpy(clients[0]->nick_name,mMiNick.c_str(),8);
                    cambiarEstadoPlayer(PLAYER_1);
                    mpComponentTextoNickPlayer[PLAYER_1]->setText(mMiNick);
                }
                break;
        }
        delete result;
    }

    /**
     * Funcion llamada por los botones de la interfaz cuando son presionados
     * @param control_click
     */
    void onClickButton(int id) override {
        mBotonClicked = id;
        ejecutarAccionBotonClicked();
    }

    virtual void eliminarSprite(Sprite *sprite) override {

    }

    void packLayout(SDL_Renderer * gRenderer){
        SDL_Rect rect = mGameManagerInterfaz->getRectScreen();
        mLayoutParent->pack(gRenderer);
        mLayoutParent->setRectDibujo(rect);
    }

    float getScaleRatioW() override {
        return mGameManagerInterfaz->getScaleRatioW();
    }

    float getScaleRatioH() override {
        return mGameManagerInterfaz->getScaleRatioH();
    }
    /**
     * Establece/Cambia el terreno en el que se jugara
     * @param nuevoTerreno
     * @return
     */
    bool establecerTerrenoBatalla(SDL_Renderer * gRenderer,std::string nuevoTerreno) {

        if(!mMapaTerrenoSeleccionado.cargar(gRenderer,"data/niveles/batalla/" + nuevoTerreno)){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Error cambiando al mapa %s.",nuevoTerreno.c_str());
            return false;
        }

        for(int i=0;i<Player::N_PLAYERS;i++){

            mAnimacionPlayer[i]->setX(mMapaTerrenoSeleccionado.getPosXPlayer((IdPlayer)(PLAYER_1 + i)));
            mAnimacionPlayer[i]->setY(mMapaTerrenoSeleccionado.getPosYPlayer((IdPlayer)(PLAYER_1 + i)));

            // Animacion para cuando aun no se ha seleccionado el personaje(Hace que parpadee "presiona")

            //mAnimacionMensajePresiona[i]->setX(mAnimacionPlayer[i]->getX()-9);
            //mAnimacionMensajePresiona[i]->setY(mAnimacionPlayer[i]->getY()+20);

            //mAnimacionMensajeActivado[i]->setX(mAnimacionPlayer[i]->getX()-9);
            //mAnimacionMensajeActivado[i]->setY(mAnimacionPlayer[i]->getY()+20);

            //mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_X,"180");
            //mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_Y,"0");
            mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_X,std::to_string(mAnimacionPlayer[i]->getX()-9));
            mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_Y,std::to_string(mAnimacionPlayer[i]->getY()+20));

        }
        //indiceTerrenoActual = nuevoTerreno;
        return true;

    }

    /**
     * Ejecuta la opcion enlazada a un boton
     */
    void ejecutarAccionBotonClicked(){
        switch(mBotonClicked){
            case MENU_BOTON_SUBIR_TIEMPO:
                if(++minutosEscogidos>5)minutosEscogidos=1;
                mTextLabelMinutos->setText(std::to_string(minutosEscogidos));
                enviar_estado_room_clientes();
                break;
            case MENU_BOTON_SUBIR_VICTORIAS:
                if(++victoriasEscogidas>8)victoriasEscogidas=1;
                mTextLabelVictorias->setText(std::to_string(victoriasEscogidas));
                enviar_estado_room_clientes();
                break;
            case MENU_BOTON_JUGAR:
                int total_players=mIsPlayerActivado[PLAYER_1]+ mIsPlayerActivado[PLAYER_2]+ mIsPlayerActivado[PLAYER_3] + mIsPlayerActivado[PLAYER_4] + mIsPlayerActivado[PLAYER_5];
                if(total_players>=2){
//                    ModoJuegoMultiPlayer * nuevoJuego = new ModoJuegoMultiPlayer(
//                            mGameManagerInterfaz,
//                            "data/niveles/batalla/" +mNombresMapas[indiceTerrenoActual],
//                            victoriasEscogidas,
//                            minutosEscogidos,
//                            mIsPlayerActivado
//                    );
//                    mGameManagerInterfaz->cambiarInterfaz(nuevoJuego); //iniciamos en modo batalla, le pasamos el array con los players seleccionados por el usuario
                    mpSfxPressJugar->play();
                }
                break;
        }
    }

    void procesarEvento(SDL_Event *event) override {
        if(event->type==SDL_KEYDOWN){
            switch(event->key.keysym.sym){
                case SDLK_ESCAPE:
                    mGameManagerInterfaz->goBack();
                    break;
                case SDLK_RETURN:
                    mBotonClicked=MENU_BOTON_JUGAR;
                    ejecutarAccionBotonClicked();
                    break;
                case SDLK_KP_1:case SDLK_KP_2:case SDLK_KP_3:case SDLK_KP_4:case SDLK_KP_5:
                    //actualizarPlayerSprite(event->key.keysym.sym-SDLK_KP_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
                    break;
                case SDLK_1:case SDLK_2:case SDLK_3:case SDLK_4:case SDLK_5:
                    //actualizarPlayerSprite(event->key.keysym.sym-SDLK_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
                    break;
                default:
                    break;
            }
        }

        mLayoutParent->procesarEvento(event);
    }
    /**
     *  Cambia el estado de un player lo establece activo/desactivado
     * @param idPlayer
     */
    void cambiarEstadoPlayer(int idPlayer){
        mIsPlayerActivado[idPlayer]=!mIsPlayerActivado[idPlayer];

        if(mIsPlayerActivado[idPlayer]){ // Si debe agregarse al juego
            // Se activan/desactivan las animaciones
            mSprites->add(mAnimacionPlayer[idPlayer]);
            //mSprites->add(mAnimacionMensajeActivado[idPlayer]);
            //mSprites->erase(mAnimacionMensajePresiona[idPlayer]);
        }else{ // Si debe eliminarse del juego
            // Se activan/desactivan las animaciones
            mSprites->erase(mAnimacionPlayer[idPlayer]);
            //mSprites->erase(mAnimacionMensajeActivado[idPlayer]);
            //mSprites->add(mAnimacionMensajePresiona[idPlayer]);
        }

        // Si hay mas de dos botones players activados se muestra el boton de jugar
        mBtnJugar->setVisible(mIsPlayerActivado[PLAYER_1]+ mIsPlayerActivado[PLAYER_2]+ mIsPlayerActivado[PLAYER_3] + mIsPlayerActivado[PLAYER_4] + mIsPlayerActivado[PLAYER_5]>1);
        mpSfxTogglePlayerEstado->play();
    }

    void update() override {
        InterfazGrafica::update();

        mSprites->update(nullptr);
        mMapaTerrenoSeleccionado.update();

        int index_nuevo_cliente;
        if((index_nuevo_cliente = aceptarNuevoCliente()) > 0){

            enviar_estado_room_clientes();
        }

        if(SDLNet_UDP_Recv(mUDPServerSocket,mUDPPacketRecibir)) {
            switch (mUDPPacketRecibir->data[OFFSET_PACKET_FLAG]) {
                case FLAG_KEEP_ALIVE: {
                    uint16_t id_cliente = mUDPPacketRecibir->data[1];
                    for(int i = 1; i < MAX_CLIENTES;i++){
                        if(clients[i]->activo && clients[i]->id_cliente == id_cliente){
                            mControlTimer[i-1].start();
                            id_updates_clientes[i - 1] = mUDPPacketRecibir->data[3];
                            SDL_Log("FLAG_KEEP_ALIVE %d",id_cliente);
                        }
                    }

                    }
                    break;
                case FLAG_DISCONNECT:
                    for(int i = 1; i < MAX_CLIENTES;i++){
                        if(clients[i]->activo && clients[i]->id_cliente == mUDPPacketRecibir->data[1]){
                            desconectar_cliente(i);
                            cambiarEstadoPlayer(clients[i]->id_player);
                            SDL_Log("FLAG_DISCONNECT %d",mUDPPacketRecibir->data[1]);
                        }
                    }
                    break;
            }
        }

        for(int i = 1; i < MAX_CLIENTES;i++){
            if(clients[i]->activo){
                if(mControlTimer[i-1].getTicks() >= TIMEOUT_DISCONECT_CLIENT) {
                    SDL_Log("Timeout %d",clients[i]->id_cliente);
                    desconectar_cliente(i);
                    cambiarEstadoPlayer(clients[i]->id_player);
                }
            }
        }

    }

    void desconectar_cliente(int indice){
        clients[indice]->activo = false;
        mpComponentTextoNickPlayer[clients[indice]->id_player]->setText("Esperando...");
    }

    void enviar_estado_room_clientes(){
        mUDPPacketEnviar->len = MAX_TAM_UPDATE_ROOM;

        Uint8 * data = new Uint8[MAX_TAM_UPDATE_ROOM];
        construir_estado_room(data);
        mUDPPacketEnviar->data = data;
        for(int i = 1 ; i < MAX_CLIENTES;i++){
            if(clients[i]->activo){
                mUDPPacketEnviar->address.port = clients[i]->updsocketipadress.port;
                mUDPPacketEnviar->address.host = clients[i]->updsocketipadress.host;
                if(!SDLNet_UDP_Send(mUDPServerSocket, -1, mUDPPacketEnviar)){
                    printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
                }
            }
        }
        delete data;
    }
    void construir_estado_room(uint8_t *data){
        data[OFFSET_PACKET_FLAG]                     = FLAG_UPDATE_ESTADO_ROOM;
        (*(uint32_t*)&data[OFFSET_PACKET_ID_UPDATE]) = next_id_update++;
        data[OFFSET_PACKET_MINUTOS_ESCOGIDOS]        = minutosEscogidos;
        data[OFFSET_PACKET_VICTORIAS_ESCOGIDAS]      = victoriasEscogidas;

        int offset_player = OFFSET_PACKET_PRIMER_CLIENTE;

        for(int i = 0; i < MAX_CLIENTES;i++){
            data[offset_player] = (Uint8) clients[i]->activo;
            if(clients[i]->activo){
                (*(uint16_t*)&data[offset_player + OFFSET_PACKET_ID_CLIENTE])  = clients[i]->id_cliente;
                data[offset_player + OFFSET_PACKET_ID_PLAYER] = clients[i]->id_player;
                memcpy(&data[offset_player + OFFSET_PACKET_NICK_NAME] , clients[i]->nick_name,MAX_NICK);
            }
            offset_player+=TAM_PACKET_BYTES_CLIENTE;

        }
    }
    int aceptarNuevoCliente() {

        if(mNumClientes >= MAX_CLIENTES) return -1;

        int index = 0;
        for(index = 0;  index <MAX_CLIENTES; index++){
            if(!clients[index]->activo) break;
        }

        TCPsocket psocket= SDLNet_TCP_Accept(mTCPServerSocket);
        if(psocket == nullptr) return -1;

        int id_player_no_activado = 0;
        while(mIsPlayerActivado[id_player_no_activado]&&id_player_no_activado<Player::N_PLAYERS){
            id_player_no_activado++;
        };

        uint8_t pdata[MAX_TAM_TCP_PAQUETE];
        int num_recv;
        int result;

        // Tiene Mapa
        memcpy(pdata,mMapaEscogido.c_str(),MAX_NOMBRE_MAPA);

        result = SDLNet_TCP_Send(psocket, pdata, MAX_NOMBRE_MAPA);
        if(result<MAX_NOMBRE_MAPA) {
            printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            // It may be good to disconnect sock because it is likely invalid now.
            SDLNet_TCP_Close(psocket);
            return -1;
        }

        // Respuesta Tiene Mapa
        num_recv = recibirDatos(psocket, pdata, 1);
        if(num_recv <= 0){
            SDLNet_TCP_Close(psocket);
            return -1;
        }else{
            if(!pdata[0]){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"No tiene el mapa descargado! Sorry :(");
                SDLNet_TCP_Close(psocket);
                return -1;
            }
        }

        // Identificarse
        num_recv = recibirDatos(psocket, pdata, 8);
        if(num_recv <= 0){
            SDLNet_TCP_Close(psocket);
            return -1;
        }else{
            memcpy(clients[index]->nick_name,pdata,MAX_NICK);
        }

        clients[index]->id_cliente = mUltimoIdUtilizado++;
        clients[index]->id_player = (IdPlayer) id_player_no_activado;


        // Reconocer
        // Insertamos el id del cliente
        *((uint16_t *) &pdata) = clients[index]->id_cliente;
        // Insertamos el id del player
        pdata[2] = clients[index]->id_player;
        result = SDLNet_TCP_Send(psocket, pdata, 3);
        if(result<3) {
            printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            // It may be good to disconnect sock because it is likely invalid now.
            SDLNet_TCP_Close(psocket);
            return -1;
        }

        // Puerto UDP
        *((uint16_t *) &pdata) = mUDPPuerto;

        result = SDLNet_TCP_Send(psocket, pdata, 2);
        if(result<2) {
            printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            // It may be good to disconnect sock because it is likely invalid now.
            SDLNet_TCP_Close(psocket);
            return -1;

        }

        // Obtengo la IP address del socket tcp
        IPaddress * ipadress = SDLNet_TCP_GetPeerAddress(psocket);
        clients[index]->updsocketipadress.host = ipadress->host;
        // Obtengo el Puerto UDP del socket udp del servidor
        num_recv = recibirDatos(psocket, pdata, 2);
        if(num_recv <= 0){
            SDLNet_TCP_Close(psocket);
            return -1;
        }else{
            // Asigno el puerto del socket udp del servidor a la estructura ipddress
            clients[index]->updsocketipadress.port = *((uint16_t *) &pdata);
        }

        // Intenta enlazar la direccion del socket udp del cliente al channel usado en nuestro socket udp servidor
        // Que es donde se van a hacer las actualizaciones del estado del room

        SDLNet_TCP_Close(psocket);

        clients[index]->activo = true;
        cambiarEstadoPlayer(id_player_no_activado); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53

        char nombre[MAX_NICK + 1];
        memcpy(nombre,clients[index]->nick_name,MAX_NICK);
        nombre[MAX_NICK] = '\0';
        mpComponentTextoNickPlayer[index]->setText(nombre);

        mControlTimer[index - 1].start();
        mNumClientes++;

        return index;
    }


    int recibirDatos(TCPsocket psocket,uint8_t * pBuffer,uint8_t length) {

        //uint8_t temp_data[MAX_PACKET];
        //uint8_t * pdata = new uint8_t[length];
        int num_recv = SDLNet_TCP_Recv(psocket, pBuffer, length);

        if(num_recv <= 0) {
            const char* err = SDLNet_GetError();
            if(strlen(err) == 0) {
                printf("DB: client disconnected\n");
            } else {
                fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
            }
        } else {

            //memcpy(pBuffer, &temp_data[offset], (num_recv-offset));
        }

        return num_recv;
    }

    void cerrarConeccionCliente(int index) {
        //if(clients[index] == NULL) {
        //    fprintf(stderr, "ER: Attempted to delete a NULL socket.\n");
        //    return;
        //}

        //if(SDLNet_TCP_DelSocket(socket_set, clients[index]->socket) == -1) {
        //    fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        //    exit(-1);
        //}
        //delete clients[index];
        //clients[index] = nullptr;

        //SDLNet_TCP_Close(clients[index]->socket);
        //sockets[index] = nullptr;
    }

    ~InterfazEsperarLlenarServidor() override {
        //if(SDLNet_TCP_DelSocket(socket_set, mTCPServerSocket) == -1) {
        //    fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        //    exit(-1);
       // }

        SDLNet_TCP_Close(mTCPServerSocket);
        SDLNet_UDP_Close(mUDPServerSocket);
        SDLNet_FreePacket(mUDPPacketEnviar);
        SDLNet_FreePacket(mUDPPacketRecibir);

        for(int i=0; i<MAX_CLIENTES; ++i) {
            delete clients[i];
        }

        //SDLNet_FreeSocketSet(socket_set);
        for(int i=0;i<Player::N_PLAYERS;i++){
            delete mAnimacionPlayer[i];
            //delete mAnimacionMensajePresiona[i];
            //delete mAnimacionMensajeActivado[i];
            delete mpSpriteSheetPlayer[i];
        }
        //delete mpSfxCambiarMapa;
        delete mpSfxPressJugar;
        delete mpSfxTogglePlayerEstado;

        delete mpTextureTablero;
        delete mpTextureCuadroPeque;
        delete mpTextureMensPlayersEnBatalla;
        delete mpTextureMensTiempoPorRonda;
        delete mpTextureMensVictorias;

        delete mpSpriteSheetCarasBomberman;

        //SDL_FreeSurface(previewTerreno);
        //delete dataNivel;
        delete mLayoutParent;
        delete musicaFondoMenu;

    }

    void draw(SDL_Renderer *gRenderer) override {
        mpTextureTablero->draw(gRenderer, 0, 0);//imprimimos la barra mensage
        mpTextureCuadroPeque->draw(gRenderer, 177, 0);//imprimimos la barra mensage
        mpTextureCuadroPeque->draw(gRenderer, 280, 0);//imprimimos la barra mensage
        mpTextureMensPlayersEnBatalla->draw(gRenderer, 15, 0);//imprimimos la barra mensage
        mpTextureMensTiempoPorRonda->draw(gRenderer, 140, 18);//imprimimos la barra mensage
        mpTextureMensVictorias->draw(gRenderer, 261, 18);//imprimimos la barra mensage

        mMapaTerrenoSeleccionado.draw(gRenderer);//imprimimos el nivel

        mSprites->draw(gRenderer);
        for(int i=0;i<Player::N_PLAYERS;i++){
            if(!mIsPlayerActivado[i]){
                mpSpriteSheetPlayer[i]->draw(gRenderer,mAnimacionPlayer[i]->getX(),mAnimacionPlayer[i]->getY());
            }else{
                mpSpriteSheetCarasBomberman->setCurrentCuadro(i*2);
                mpSpriteSheetCarasBomberman->draw(gRenderer,i*16+20,15);
            }
        }

        if(mLayoutParent->isDisabled()){
            packLayout(gRenderer);
        }

        mLayoutParent->draw(gRenderer);

    }

    void resume() override {
        InterfazGrafica::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }

        if(mHaOcurridoError){
            mGameManagerInterfaz->goBack();
        }


        SDL_ShowCursor(SDL_ENABLE);
    }

    void establecerMapa(string nombre) {
        mMapaEscogido = nombre;
    }

private:
    //int next_ind = 0;
    TCPsocket mTCPServerSocket;

    Cliente * clients[MAX_CLIENTES];
    int mNumClientes = 0;

    //SDLNet_SocketSet socket_set;

    //TCPsocket sockets[MAX_CLIENTES] {nullptr};

    bool mHaOcurridoError;

    UDPsocket mUDPServerSocket;

    Uint16 mTCPPuerto;
    //bool estaRoomCompleto = false;

    Uint8 minutosEscogidos   = 1;
    Uint8 victoriasEscogidas = 1;

    SDL_Renderer * mGRenderer = nullptr;
    // Contiene las animaciones(los players que se mueven)
    DrawGroup * mSprites = nullptr;

    // Usado para dibujar el mapa seleccionado actualmente
    LectorMapa mMapaTerrenoSeleccionado;

    // Botones de la interfaz
    BotonComponent *mBtnSubirTiempo = nullptr;
    BotonComponent *mBtnSubirVictorias = nullptr;
    BotonComponent *mBtnJugar = nullptr;

    // Dice cuales estan activados
    bool mIsPlayerActivado[Player::N_PLAYERS] {false};

    IdPlayer idPlayerUsuario;
    
    string mMapaEscogido;

    // ID del terreno actual escogido por el usuario / EL ID del terreno dibujado en pantalla
    // Maximo ID(Numero) asignado a un mapa de batalla
    //int mMaxTerrenoBatalla = 1;


    // Animacion del personaje
    Animacion * mAnimacionPlayer[Player::N_PLAYERS] {nullptr};
    // Animacion del texto "presiona"
    //Animacion * mAnimacionMensajePresiona[Player::N_PLAYERS] {nullptr};
    // Animacion del texto "activado"
    //Animacion * mAnimacionMensajeActivado[Player::N_PLAYERS] {nullptr};

    // Controla los botones en un layout
    LayoutAbsolute *mLayoutParent = nullptr;

    // Muestra en la UI el numero de minutos escogidos
    LabelComponent *mTextLabelMinutos = nullptr;
    // Muestra en la UI el numero de victorias escogidas
    LabelComponent *mTextLabelVictorias = nullptr;

    LabelComponent * mpComponentTextoNickPlayer[Player::N_PLAYERS];

    EfectoSonido * mpSfxPressJugar;
    EfectoSonido * mpSfxTogglePlayerEstado;

    LTexture * mpTextureTablero;
    LTexture * mpTextureCuadroPeque;
    LTexture * mpTextureMensPlayersEnBatalla;
    LTexture * mpTextureMensTiempoPorRonda;
    LTexture * mpTextureMensVictorias;

    SpriteSheet * mpSpriteSheetPlayer[Player::N_PLAYERS];
    SpriteSheet * mpSpriteSheetCarasBomberman;
    MusicaFondo *musicaFondoMenu;
    // Dice cual boton fué clickeado / Tambien se usa para ejecutar una funcion asociada al click de un boton
    int mBotonClicked = -1;
    /**
     * Ids asignados a los botones de la interfaz, son usados en un swith cuando se llama a la funcion
     * enlazada a los botones para saber cual boton fué presionado.
     */
    enum{
        MENU_BOTON_SUBIR_TIEMPO,
        MENU_BOTON_SUBIR_VICTORIAS,
        MENU_BOTON_JUGAR,
    };
    string mMiNick;
    uint16_t mUltimoIdUtilizado = 0;
    uint16_t mUDPPuerto;
    //int mChannel = -1;
    UDPpacket *mUDPPacketEnviar = nullptr;

    // Comenzamos las actualizaciones en 1 para que los clientes utilizen 0 como si fuera la actualizacion que
    // reciben al conectarse al servidor
    uint32_t next_id_update = 1;

    uint32_t id_updates_clientes[MAX_CLIENTES  - 1] {0};
    UDPpacket *mUDPPacketRecibir;
    LTimer mControlTimer[MAX_CLIENTES -1];
};
#endif //BOMBERMAN_INTERFAZESPERARLLENARSERVIDOR_HPP
