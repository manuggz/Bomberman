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
 * CLIENTE <--- Reconocer      {tiempo_por_ronda:uint8_t,num_victorias:uint_8_t,id_cliente:uint16_t,
 *                              is_activo:uint8_t,is_activo:uint8_t,is_activo:uint8_t,is_activo:uint8_t,is_activo:uint8_t}:3                         -----  SERVIDOR
 * CLIENTE <--- PuertoUdp      {n_puerto:uint16_t}:2                                            <-----  SERVIDOR
 * CLIENTE ---> PuertoUdp      {n_puerto:uint16_t}:2                                            ----->  SERVIDOR
 * CLIENTE ---> Desconectar    {} -----  SERVIDOR

 * Parte 2: UDP
 *
 * CLIENTES <- UPDATE_ESTADO__ROOM {flair:uint8_t ,id_update:uint_32_t, *
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
#include "ConstantesNetwork.hpp"
#include "../../engine/util/BitmapFont.hpp"
#include "Servidor.hpp"
#include "Cliente.hpp"

class InterfazEsperarLlenarServidor: public InterfazGrafica, public UpdateGroupContainerInterfaz{
public:
    static const int ID_POP_UP_INSERTAR_NICK_SERVIDOR = 12;
    InterfazEsperarLlenarServidor(
            GameManagerInterfazUI *gameManagerInterfaz,
            ClienteDatosNameSpace::DatosThreadConectarServidor * datosThreadConectarServidor
    ) : InterfazGrafica(gameManagerInterfaz),
                                                                                mMapaTerrenoSeleccionado(0,32){

        InterfazEsperarLlenarServidor::datosThreadConectarServidor = datosThreadConectarServidor;
        //InterfazEsperarLlenarServidor::datosConfiguracionServidor = datosConfiguracionServidor;
        

        for(int i = 0; i < MAX_CLIENTES;i++){
            clients[i] = new ServidorNameSpace::ClienteConectado();
            clients[i]->activo = false;
        }

        mUDPPacketEnviar = SDLNet_AllocPacket(MAX_TAM_UPDATE_ROOM);
        if(!mUDPPacketEnviar) {
            printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
            return;
        }

        mUDPPacketRecibir = SDLNet_AllocPacket(10);
        if(!mUDPPacketRecibir) {
            return;
        }

    }

    void update_gui_room(){
        char nombre[MAX_NICK + 1];
        for(int i=0;i < MAX_CLIENTES;i++){

            actualizarPlayerSprite(i);

            if(!datosThreadConectarServidor->resp.isPlayerActivado[i]){
                mSprites->erase(mAnimacionPlayer[i]);
                //mpComponentTextoNickPlayer[i]->setText("Esperando...");
            }
        }
        
    }
    /**
     *  Cambia el estado de un player lo establece activo/desactivado
     * @param idPlayer
     */
    void actualizarPlayerSprite(int indice){
        static char nombre[MAX_NICK + 1];

        if(clients[indice]->activo) {
            memcpy(nombre, clients[indice]->nick_name, MAX_NICK);
            nombre[MAX_NICK] = '\0';

            //mpComponentTextoNickPlayer[clients[indice]->id_player]->setText(nombre);
            if (!mSprites->contain(mAnimacionPlayer[clients[indice]->id_player])) {
                mSprites->add(mAnimacionPlayer[clients[indice]->id_player]);
            }

            // Si hay mas de dos botones players activados se muestra el boton de jugar
            mpSfxTogglePlayerEstado->play();
        }
    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazGrafica::createUI(gRenderer);
        //mLayoutParent = new LayoutAbsolute();

        // BotonComponent para controlar cuanto tiempo para acabar una ronda
//        mBtnSubirTiempo=new BotonComponent(
        //              mGameManager->getTexture(Galeria::CodeImagen::IMG_BOTON_FLECHA_PEQUE_DERECHA),this);
        // Controla las animaciones de los personajes cuando se seleccionan para jugar
        mSprites=new DrawGroup(this);

        //Animaciones para los personajes (Hace que parezcan que caminan) cuando se seleccionan
        SpriteSheet * spriteSheetTmp;

        for(int i=0;i<Player::N_PLAYERS;i++){
            // Animacion para cuando aun no se ha seleccionado el personaje(Hace que parpadee "presiona")

            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_" + std::to_string(i+1)+".bmp",1,12,true);
            mAnimacionPlayer[i]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");


            //mAnimacionMensajePresiona[i]=new Animacion(spriteSheetTmp,"0,0,1,1");
            // Animacion para cuando se selecciono el personaje(Hace que parpadee "activado")
            //mAnimacionMensajeActivado[i]=new Animacion(spriteSheetTmp,"0,0,0,1,1,1");

            // Hace que las animaciones se repitan indefinidamente(Hasta que se eliminen desde el codigo)
            mAnimacionPlayer[i]->setRepeticiones(-1);

        }

        mpSfxPressJugar  = new EfectoSonido("data/sonidos/ping_5.wav",100);
        mpSfxTogglePlayerEstado = new EfectoSonido("data/sonidos/ping_3.wav",100);

        musicaFondoMenu = new MusicaFondo("data/sonidos/musica_1.mid");


        for(int i = 0; i < Player::N_PLAYERS; i++) {
            mpSpriteSheetPlayer[i] = new SpriteSheet(gRenderer, "data/imagenes/personajes/player_" + std::to_string(i + 1) + ".bmp", 1, 12,true);
            mpSpriteSheetPlayer[i]->setAlpha(150);
            mpSpriteSheetPlayer[i]->setCurrentCuadro(6);
        }

        mBitmapFont[FUENTE_NORMAL] = new BitmapFont(gRenderer,   "data/fuentes/fuente2_16_normal.png");
        mBitmapFont[FUENTE_RESALTADA] = new BitmapFont(gRenderer,"data/fuentes/fuente2_16_resaltado.png");

        // HUD
        mpTextureHUD = new LTexture();
        mpTextureHUD->cargarDesdeArchivo("data/imagenes/objetos/tablero.bmp",gRenderer,true);

        mpSpriteSheetCarasBomberman = new SpriteSheet(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);

        SpriteSheet *spriteSheet;
        for(int i = 0; i < Player::N_PLAYERS;i++){
            if(datosThreadConectarServidor->resp.isPlayerActivado[i]) {
                spriteSheet = new SpriteSheet(gRenderer, "data/imagenes/objetos/trofeo.bmp", 1, 13, true);
                pAnimaTrofeos[i] = new Animacion(spriteSheet, "7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",
                                                 19 + i * 60, 15);
                pAnimaTrofeos[i]->setRepeticiones(-1);

                mpBitmapValorCopasGanadas[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 42 + i * 60, 20);
                mpBitmapValorCopasGanadas[i]->setText("0");

                mSprites->add(pAnimaTrofeos[i]);
            }

        }
        spriteSheet = new SpriteSheet(gRenderer,"data/imagenes/objetos/trofeo.bmp",1,13,true);
        mpAnimacionCopaMaxVictorias=new Animacion(spriteSheet,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",139,-2);
        mpAnimacionCopaMaxVictorias->setRepeticiones(-1);
        mpBitmapValorCopasMax = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 139 + 23,3);

        mpBitmapMaxTimeRonda = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 139 + 23,3);

        if(datosThreadConectarServidor->resp.minutos){
            char tiempo[6];
            sprintf(tiempo,"0%d:00",datosThreadConectarServidor->resp.minutos);
            mpBitmapMaxTimeRonda->setText(tiempo);
        }
        if(!datosThreadConectarServidor->resp.num_victorias){
            rectPlaceHolderTime.x =128;
        }else {
            rectPlaceHolderTime.x = 90;
            mpBitmapValorCopasMax->setText(std::to_string(datosThreadConectarServidor->resp.num_victorias));
            mSprites->add(mpAnimacionCopaMaxVictorias);
        }

        establecerTerrenoBatalla(gRenderer);

        mGRenderer = gRenderer;

    }

    void start() override {
        InterfazGrafica::start();
    }


    virtual void eliminarSprite(Sprite *sprite) override {

    }

    /**
     * Establece/Cambia el terreno en el que se jugara
     * @param nuevoTerreno
     * @return
     */
    bool establecerTerrenoBatalla(SDL_Renderer * gRenderer) {
        
        char tmp[255];
        sprintf(tmp,"data/niveles/batalla/%s",datosThreadConectarServidor->resp.nombreMapa);
        if(!mMapaTerrenoSeleccionado.cargar(gRenderer,tmp)){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Error cambiando al mapa %s.",tmp);
            return false;
        }

        for(int i=0;i<Player::N_PLAYERS;i++){

            mAnimacionPlayer[i]->setX(mMapaTerrenoSeleccionado.getPosXPlayer((IdPlayer)(PLAYER_1 + i)));
            mAnimacionPlayer[i]->setY(mMapaTerrenoSeleccionado.getPosYPlayer((IdPlayer)(PLAYER_1 + i)));

            //mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_X,std::to_string(mAnimacionPlayer[i]->getX()-9));
            //mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_Y,std::to_string(mAnimacionPlayer[i]->getY()+20));

        }
        //indiceTerrenoActual = nuevoTerreno;
        return true;

    }

    /**
     * Ejecuta la opcion enlazada a un boton
     */
    void procesarEvento(SDL_Event *event) override {
        if(event->type==SDL_KEYDOWN){
            switch(event->key.keysym.sym){
                case SDLK_ESCAPE:
                    mGameManagerInterfaz->goBack();
                    break;
                case SDLK_RETURN:
                    //mBotonClicked=MENU_BOTON_JUGAR;
                    //ejecutarAccionBotonClicked();
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

        //mLayoutParent->procesarEvento(event);
    }
    /**
     *  Cambia el estado de un player lo establece activo/desactivado
     * @param idPlayer
     */
    void cambiarEstadoPlayer(int idPlayer){
        mIsPlayerAsignadoCliente[idPlayer]=!mIsPlayerAsignadoCliente[idPlayer];

        if(mIsPlayerAsignadoCliente[idPlayer]){ // Si debe agregarse al juego
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
        //mBtnJugar->setVisible(datosConfiguracionServidor->isPlayerActivado[PLAYER_1]+ datosConfiguracionServidor->isPlayerActivado[PLAYER_2]+ datosConfiguracionServidor->isPlayerActivado[PLAYER_3] + datosConfiguracionServidor->isPlayerActivado[PLAYER_4] + datosConfiguracionServidor->isPlayerActivado[PLAYER_5]>1);
        mpSfxTogglePlayerEstado->play();
    }

    void update() override {
        InterfazGrafica::update();

        mSprites->update(nullptr);
        mMapaTerrenoSeleccionado.update();

        if(SDLNet_UDP_Recv(datosThreadConectarServidor->misocket,mUDPPacketRecibir)){
            switch(mUDPPacketRecibir->data[OFFSET_PACKET_FLAG]){
                case FLAG_UPDATE_ESTADO_ROOM: {
                    mControlTimer.start();
                    // Si hemos recibido una update de mayor versión a la que poseemos
                    // Recordar que clients[0]
                    uint32_t id_actualizacion_recibida_actual = (*(uint32_t *) &mUDPPacketRecibir->data[OFFSET_PACKET_ID_UPDATE]);
                    if (id_ultima_actualizacion_recibida < id_actualizacion_recibida_actual) {
                        update_estado_room(mUDPPacketRecibir->data);
                        update_gui_room();
                        id_ultima_actualizacion_recibida = id_actualizacion_recibida_actual;
                    }

                }
                    break;
                default:break;
            }

        }

        if(mControlTimer.getTicks() >= TIMEOUT_DISCONECT_CLIENT/3){

            Uint8 * data = new Uint8[TAM_PAQUETE_KEEP_ALIVE];
            data[OFFSET_PACKET_FLAG] = FLAG_KEEP_ALIVE;

            *(uint16_t *)&data[1] = datosThreadConectarServidor->resp.id_cliente;
            *(uint32_t *)&data[3] = id_ultima_actualizacion_recibida;

            mUDPPacketEnviar->data = data;
            mUDPPacketEnviar->len = TAM_PAQUETE_KEEP_ALIVE;

            mUDPPacketEnviar->address.port = datosThreadConectarServidor->resp.adressudp.port;
            mUDPPacketEnviar->address.host = datosThreadConectarServidor->resp.adressudp.host;

            if(!SDLNet_UDP_Send(datosThreadConectarServidor->misocket, -1, mUDPPacketEnviar)){
                printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
            }
            delete data;
            mControlTimer.start();
        }

    }

/**
 * Dibuja los datos que se muestran arriba del Mapa
 * @param gRenderer
 */
    void drawHUD(SDL_Renderer *gRenderer){

//    // Dibuja un cuadro anaranjado donde van a estar los datos
        mpTextureHUD->draw(gRenderer, 0, 0);

        for(int i=0;i<MAX_CLIENTES;i++){
            if(datosThreadConectarServidor->resp.isPlayerActivado[i]){
                if(!mIsPlayerAsignadoCliente[i]){
                    mpSpriteSheetPlayer[i]->draw(gRenderer,mAnimacionPlayer[i]->getX(),mAnimacionPlayer[i]->getY());
                }
                mpSpriteSheetCarasBomberman->setCurrentCuadro(i*2 + !mIsPlayerAsignadoCliente[i]);
                mpSpriteSheetCarasBomberman->draw(gRenderer,6+ i*60,20);
                mpBitmapValorCopasGanadas[i]->draw(gRenderer);
            }
        }

        if(datosThreadConectarServidor->resp.num_victorias > 0){
            mpBitmapValorCopasMax->draw(gRenderer, mpAnimacionCopaMaxVictorias->getX() + 23,3);
        }

        if(datosThreadConectarServidor->resp.minutos > 0){
            SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
            SDL_RenderFillRect(gRenderer,&rectPlaceHolderTime);
            mpBitmapMaxTimeRonda->draw(gRenderer,rectPlaceHolderTime.x + 5,rectPlaceHolderTime.y + 1);
        }

    }
    void stop() override {
        InterfazGrafica::stop();

        Uint8 *data = new Uint8[2];
        data[OFFSET_PACKET_FLAG] = FLAG_DISCONNECT;

        *(uint16_t *) &data[1] = datosThreadConectarServidor->resp.id_cliente;
        //*(uint32_t *)&data[3] = id_ultima_actualizacion_recibida;

        mUDPPacketEnviar->data = data;
        mUDPPacketEnviar->len = 2;

        mUDPPacketEnviar->address.port = datosThreadConectarServidor->resp.adressudp.port;
        mUDPPacketEnviar->address.host = datosThreadConectarServidor->resp.adressudp.host;

        if (!SDLNet_UDP_Send(datosThreadConectarServidor->misocket, -1, mUDPPacketEnviar)) {
            printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
        }
        delete data;
    }

    void update_estado_room(Uint8 * data){

        std::memset(mIsPlayerAsignadoCliente,false,Player::N_PLAYERS);

        int offset = OFFSET_PACKET_PRIMER_CLIENTE;
        for(int i = 0; i < MAX_CLIENTES;i++){
            clients[i]->activo = data[offset];
            if(clients[i]->activo){
                clients[i]->id_cliente = (*(uint16_t*)&data[offset + OFFSET_PACKET_ID_CLIENTE]);
                clients[i]->id_player  = (IdPlayer) data[offset + OFFSET_PACKET_ID_PLAYER];
                mIsPlayerAsignadoCliente[clients[i]->id_player] = true;
                memcpy(clients[i]->nick_name,&data[offset + OFFSET_PACKET_NICK_NAME],MAX_NICK);

                if(clients[i]->id_cliente == datosThreadConectarServidor->resp.id_cliente){
                    mi_indice = (uint8_t) i;
                }
            }
            offset += TAM_PACKET_BYTES_CLIENTE;
        }

    }
    void draw(SDL_Renderer *gRenderer) override {

        mMapaTerrenoSeleccionado.draw(gRenderer);//imprimimos el nivel
        drawHUD(gRenderer);//imprimimos la barra mensage
        mSprites->draw(gRenderer);

    }

    void resume() override {
        InterfazGrafica::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }
    }


    ~InterfazEsperarLlenarServidor() override {
        //if(SDLNet_TCP_DelSocket(socket_set, mTCPServerSocket) == -1) {
        //    fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        //    exit(-1);
        // }

        SDLNet_UDP_Close(datosThreadConectarServidor->misocket);

        //SDLNet_FreeSocketSet(socket_set);
        for(int i=0;i<Player::N_PLAYERS;i++){
            delete mAnimacionPlayer[i];
            //delete mAnimacionMensajePresiona[i];
            //delete mAnimacionMensajeActivado[i];
            delete mpSpriteSheetPlayer[i];
            delete pAnimaTrofeos[i];
            delete mpBitmapValorCopasGanadas[i];
        }
        //delete mpSfxCambiarMapa;
        delete mpSfxPressJugar;
        delete mpSfxTogglePlayerEstado;

        delete mpTextureHUD;

        delete mpSpriteSheetCarasBomberman;

        //SDL_FreeSurface(previewTerreno);
        //delete dataNivel;
        delete musicaFondoMenu;
        delete mpBitmapMaxTimeRonda;

        SDLNet_FreePacket(mUDPPacketEnviar);
        SDLNet_FreePacket(mUDPPacketRecibir);

        delete mpBitmapValorCopasMax;
        delete mpAnimacionCopaMaxVictorias;
        delete mBitmapFont[0];
        delete mBitmapFont[1];

    }

private:


    ServidorNameSpace::ClienteConectado * clients[MAX_CLIENTES];

    SDL_Renderer * mGRenderer = nullptr;
    // Contiene las animaciones(los players que se mueven)
    DrawGroup * mSprites = nullptr;

    // Usado para dibujar el mapa seleccionado actualmente
    LectorMapa mMapaTerrenoSeleccionado;

    // Dice cuales fueron seleccionados para la partida
    bool mIsPlayerAsignadoCliente[Player::N_PLAYERS] {false};

    // Dice cuales se han asignado a un cliente

    // ID del terreno actual escogido por el usuario / EL ID del terreno dibujado en pantalla
    // Maximo ID(Numero) asignado a un mapa de batalla
    //int mMaxTerrenoBatalla = 1;


    // Animacion del personaje
    Animacion * mAnimacionPlayer[Player::N_PLAYERS] {nullptr};

    EfectoSonido * mpSfxPressJugar;
    EfectoSonido * mpSfxTogglePlayerEstado;

    MusicaFondo *musicaFondoMenu;

    // PAra mostrar un cuadro de este SS cuando el player aun no se ha conectado
    SpriteSheet * mpSpriteSheetPlayer[Player::N_PLAYERS];

    SpriteSheet * mpSpriteSheetCarasBomberman;
    // Dice cual boton fué clickeado / Tambien se usa para ejecutar una funcion asociada al click de un boton
    //int mBotonClicked = -1;
    /**
     * Ids asignados a los botones de la interfaz, son usados en un swith cuando se llama a la funcion
     * enlazada a los botones para saber cual boton fué presionado.
     */
    string mMiNick;

    enum{
        FUENTE_NORMAL,
        FUENTE_RESALTADA
    };
    //LayoutAbsolute *mLayoutParent = nullptr;

    BitmapFont *mBitmapFont[2];
    // HUD
    Animacion * pAnimaTrofeos[Player::N_PLAYERS] {nullptr};

    SDL_Rect rectPlaceHolderTime {0,2,52,18};
    BitmapFontRenderer *mpBitmapMaxTimeRonda;

    BitmapFontRenderer *mpBitmapValorCopasGanadas[Player::N_PLAYERS] {nullptr};
    BitmapFontRenderer *mpBitmapValorCopasMax;
    LTexture * mpTextureHUD;

    Animacion *mpAnimacionCopaMaxVictorias;
    uint32_t id_ultima_actualizacion_recibida = 0;

    LTimer mControlTimer;

    UDPpacket *mUDPPacketRecibir = nullptr;
    UDPpacket *mUDPPacketEnviar = nullptr;
    
    uint8_t mi_indice ;

    ClienteDatosNameSpace::DatosThreadConectarServidor *datosThreadConectarServidor;
    //ServidorNameSpace::DatosConfiguracionServidor *datosConfiguracionServidor;
};
#endif //BOMBERMAN_INTERFAZESPERARLLENARSERVIDOR_HPP
