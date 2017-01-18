//
// Created by manuggz on 14/01/17.
//

#ifndef BOMBERMAN_INTERFAZESPERARLLENARCLIENTE_HPP
#define BOMBERMAN_INTERFAZESPERARLLENARCLIENTE_HPP

//
//#include <SDL_net.h>
//#include <netdb.h>
//#include <ifaddrs.h>
//#include <arpa/inet.h>
//#include "../../engine/interfaces/InterfazGrafica.hpp"
//#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
//#include "../../engine/layout/Componentes/BotonComponent.hpp"
//#include "../../engine/layout/Componentes/LabelComponent.hpp"
//#include "../../engine/util/EfectoSonido.hpp"
//#include "../../engine/util/MusicaFondo.hpp"
//#include "../../engine/sprites/CDrawGroup.hpp"
//#include "../../niveles/LectorMapa.hpp"
//#include "../../personajes/player.hpp"
//#include "PopUpInsertarTexto.hpp"
//#include "MenuEscogerMapa.hpp"


static const int TAM_PAQUETE_KEEP_ALIVE = 7;

#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <SDL_net.h>

class InterfazEsperarLlenarCliente: public InterfazGrafica, public UpdateGroupContainerInterfaz, public BotonInterfaz {
public:
    static const int ID_POP_UP_INSERTAR_NICK_CLIENTE = 12;

    InterfazEsperarLlenarCliente(GameManagerInterfazUI *gameManagerInterfaz) : InterfazGrafica(gameManagerInterfaz),
                                                                                mMapaTerrenoSeleccionado(0,32){
        for(int i = 0; i < MAX_CLIENTES;i++){
            clients[i] = new Cliente();
            clients[i]->activo = false;
        }
    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazGrafica::createUI(gRenderer);
        mLayoutParent = new LayoutAbsolute();

        // Controla las animaciones de los personajes cuando se seleccionan para jugar
        mSprites=new DrawGroup(this);

        //Animaciones para los personajes (Hace que parezcan que caminan) cuando se seleccionan
        SpriteSheet *spriteSheetTmp;

        for(int i=0;i<Player::N_PLAYERS;i++){

            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer, "data/imagenes/personajes/player_" + std::to_string(i+1)+".bmp", 1, 12, true);
            mAnimacionPlayer[i] = new Animacion(spriteSheetTmp, "6,6,7,7,8,8");
            // Hace que las animaciones se repitan indefinidamente(Hasta que se eliminen desde el codigo)
            mAnimacionPlayer[i]->setRepeticiones(-1);

            mpComponentTextoNickPlayer[i] = new LabelComponent();
            mpComponentTextoNickPlayer[i]->setText("Esperando...");
            mpComponentTextoNickPlayer[i]->setFont("data/fuentes/OpenSans-Bold.ttf",10);
            mpComponentTextoNickPlayer[i]->setTextColor(SDL_Color {0,255,0,255});
            //mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_X,"180");
            //mpComponentTextoNickPlayer[i]->setLayoutParam(LAYOUT_PARAM_Y,"0");
            mLayoutParent->addComponent(mpComponentTextoNickPlayer[i]);

            // Las agrega al controlador que hace que se actualizen y se muestren
            //mSprites->add(mAnimacionMensajePresiona[i]);
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
        //establecerTerrenoBatalla(gRenderer,mMapaEscogido);

        SDL_ShowCursor(SDL_ENABLE);
        mGRenderer = gRenderer;

    }

    void start() override {
        InterfazGrafica::start();

        PopUpInsertarTexto *popUpInsertarTexto = new PopUpInsertarTexto(mGameManagerInterfaz,
                                                                        "Inserte su Nick:",
                                                                        8
        );
        mGameManagerInterfaz->showPopUp(popUpInsertarTexto, ID_POP_UP_INSERTAR_NICK_CLIENTE);
    }

    void resultPopUp(InterfazEstandarBackResult *result, int i) override {
        InterfazGrafica::resultPopUp(result, i);
        switch(i){
            case ID_POP_UP_INSERTAR_NICK_CLIENTE:
                if(result) {
                    struct ifaddrs *ifAddrStruct = NULL;
                    struct ifaddrs *ifa = NULL;
                    void *tmpAddrPtr = NULL;
                    //int result;
                    uint8_t pdata[MAX_TAM_TCP_PAQUETE];
                    int num_recv;

                    getifaddrs(&ifAddrStruct);

                    mHaOcurridoError = true;
                    
                    mi_nick = result->texto;

                    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
                        if (!ifa->ifa_addr) {
                            continue;
                        }
                        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
                            // is a valid IP4 Address
                            tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
                            char addressBuffer[INET_ADDRSTRLEN];
                            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);

                            IPaddress ip;
                            TCPsocket tcpsock;

                            if(SDLNet_ResolveHost(&ip,addressBuffer,TCP_DEFAULT_PUERTO)==-1) {
                                printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
                                continue;
                            }

                            tcpsock=SDLNet_TCP_Open(&ip);
                            if(!tcpsock) {
                                printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
                                continue;
                            }

                            // TieneMapa
                            bool tiene_mapa = false;
                            num_recv = recibirDatos(tcpsock, pdata, MAX_TAM_TCP_PAQUETE);
                            if(num_recv <= 0){
                                SDLNet_TCP_Close(tcpsock);
                                break;
                            }else{
                                for(std::string & nombre:MenuEscogerMapa::getNombresMapas()){
                                    if(!strcmp(nombre.c_str(), (const char *) pdata)){
                                        tiene_mapa = true;
                                        mMapaEscogido = nombre;
                                        break;
                                    }
                                }
                            }

                            int nresultsend;
                            // Informamos al servidor si tenemos o no el mapa
                            nresultsend = SDLNet_TCP_Send(tcpsock, pdata, 1);
                            if(nresultsend<1) {
                                printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                                // It may be good to disconnect sock because it is likely invalid now.
                                SDLNet_TCP_Close(tcpsock);
                                continue;
                            }

                            if(!tiene_mapa){
                                SDLNet_TCP_Close(tcpsock);
                                SDL_Log("No tiene el Mapa :(. %s.",pdata);
                                break;
                            }

                            // Identificarse
                            memcpy(pdata,mi_nick.c_str(),MAX_NICK);

                            nresultsend = SDLNet_TCP_Send(tcpsock, pdata, MAX_NICK);
                            if(nresultsend < MAX_NICK) {
                                printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                                // It may be good to disconnect sock because it is likely invalid now.
                                SDLNet_TCP_Close(tcpsock);
                                continue;
                            }

                            // Reconocer
                            num_recv = recibirDatos(tcpsock, pdata, 3);
                            if(num_recv <= 0){
                                SDLNet_TCP_Close(tcpsock);
                                break;
                            }else{
                                mi_id = *((uint16_t *)&pdata);
                                //clients[0]->id_player = (IdPlayer) pdata[2];
                                //memcpy(clients[0]->nick_name,pdata,8);
                                //clients[0]->nick_name[8] = '\0';
                            }

                            // Obtengo la IP address del socket tcp
                            IPaddress * ipAdress=SDLNet_TCP_GetPeerAddress(tcpsock);
                            iPaddressServidorUDP.host = ipAdress->host;
                            // Obtengo el Puerto UDP del socket udp del servidor
                            num_recv = recibirDatos(tcpsock, pdata, 2);
                            if(num_recv <= 0){
                                for(int k=1;k < MAX_CLIENTES;k++){
                                    clients[k]->activo = false;
                                }
                                SDLNet_TCP_Close(tcpsock);
                                break;
                            }else{
                                // Asigno el puerto del socket udp del servidor a la estructura ipddress
                                iPaddressServidorUDP.port = *((uint16_t *) &pdata);
                            }

                            // Creo mi socket udp
                            mUDPSocket=SDLNet_UDP_Open(0);
                            if(!mUDPSocket) {
                                printf("SDLNet_UDP_Open socket udp cliente: %s\n", SDLNet_GetError());
                                SDLNet_TCP_Close(tcpsock);
                                mHaOcurridoError = true;
                                break;
                            }

                            // Obtengo el puerto asignado al socket udp
                            miipaddress=SDLNet_UDP_GetPeerAddress(mUDPSocket,-1);
                            if(!miipaddress) {
                                printf("SDLNet_UDP_GetPeerAddress cliente: %s\n", SDLNet_GetError());
                                mHaOcurridoError = true;
                                break;
                            }
                            else {
                                // perhaps print out address->host and address->port
                                SDL_Log("Puerto asignado al udp cliente:%d.",miipaddress->port);
                            }

                            // Envio mi puerto del mi socket udp al servidor
                            // Notar que intento simular una conexion-orientada conversacion con el servidor usando el
                            // socket udp

                            nresultsend = SDLNet_TCP_Send(tcpsock, &miipaddress->port,2);
                            if(nresultsend < 2) {
                                printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                                mHaOcurridoError = true;
                                SDLNet_TCP_Close(tcpsock);
                                break;
                            }


                            SDLNet_TCP_Close(tcpsock);
                            mUDPPacket=SDLNet_AllocPacket(MAX_TAM_UPDATE_ROOM);
                            if(!mUDPPacket) {
                                printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
                                mHaOcurridoError = true;
                            }

                            mUDPPacketEnviar=SDLNet_AllocPacket(10);
                            if(!mUDPPacketEnviar) {
                                printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
                                mHaOcurridoError = true;
                            }

                            //update_gui_room();
                            mHaOcurridoError = false;
                            establecerTerrenoBatalla(mGRenderer,mMapaEscogido);
                            mControlTimer.start();

                            break;
                        }
                    }


                    if(mHaOcurridoError){
                        mGameManagerInterfaz->goBack();
                    }
                    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
                }
                break;
        }
        delete result;
    }

    void update_gui_room(){
        char nombre[MAX_NICK + 1];
        for(int i=0;i < MAX_CLIENTES;i++){

            actualizarPlayerSprite(i);

            if(!mIsPlayerActivado[i]){
                mSprites->erase(mAnimacionPlayer[i]);
                mpComponentTextoNickPlayer[i]->setText("Esperando...");
            }
        }
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
                break;
            case MENU_BOTON_SUBIR_VICTORIAS:
                if(++victoriasEscogidas>8)victoriasEscogidas=1;
                mTextLabelVictorias->setText(std::to_string(victoriasEscogidas));
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
                    //actualizarPlayerSprite(event->key.keysym.sym - SDLK_KP_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
                    break;
                case SDLK_1:case SDLK_2:case SDLK_3:case SDLK_4:case SDLK_5:
                    //actualizarPlayerSprite(event->key.keysym.sym - SDLK_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
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
    void actualizarPlayerSprite(int indice){
        static char nombre[MAX_NICK + 1];

        if(clients[indice]->activo) {
            memcpy(nombre, clients[indice]->nick_name, MAX_NICK);
            nombre[MAX_NICK] = '\0';

            mpComponentTextoNickPlayer[clients[indice]->id_player]->setText(nombre);
            if (!mSprites->contain(mAnimacionPlayer[clients[indice]->id_player])) {
                mSprites->add(mAnimacionPlayer[clients[indice]->id_player]);
            }

            // Si hay mas de dos botones players activados se muestra el boton de jugar
            mpSfxTogglePlayerEstado->play();
        }
    }

    void update() override {
        InterfazGrafica::update();

        mSprites->update(nullptr);
        mMapaTerrenoSeleccionado.update();

        if(SDLNet_UDP_Recv(mUDPSocket,mUDPPacket)){
            switch(mUDPPacket->data[OFFSET_PACKET_FLAG]){
                case FLAG_UPDATE_ESTADO_ROOM: {
                    mControlTimer.start();
                    // Si hemos recibido una update de mayor versión a la que poseemos
                    // Recordar que clients[0]
                    uint32_t id_actualizacion_recibida_actual = (*(uint32_t *) &mUDPPacket->data[OFFSET_PACKET_ID_UPDATE]);
                    if (id_ultima_actualizacion_recibida < id_actualizacion_recibida_actual) {
                        update_estado_room(mUDPPacket->data);
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

            *(uint16_t *)&data[1] = mi_id;
            *(uint32_t *)&data[3] = id_ultima_actualizacion_recibida;

            mUDPPacketEnviar->data = data;
            mUDPPacketEnviar->len = TAM_PAQUETE_KEEP_ALIVE;

            mUDPPacketEnviar->address.port = iPaddressServidorUDP.port;
            mUDPPacketEnviar->address.host = iPaddressServidorUDP.host;

            if(!SDLNet_UDP_Send(mUDPSocket, -1, mUDPPacketEnviar)){
                printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
            }
            delete data;
            mControlTimer.start();
        }

    }

    void stop() override {
        InterfazGrafica::stop();

        if(!mHaOcurridoError) {
            Uint8 *data = new Uint8[2];
            data[OFFSET_PACKET_FLAG] = FLAG_DISCONNECT;

            *(uint16_t *) &data[1] = mi_id;
            //*(uint32_t *)&data[3] = id_ultima_actualizacion_recibida;

            mUDPPacketEnviar->data = data;
            mUDPPacketEnviar->len = 2;

            mUDPPacketEnviar->address.port = iPaddressServidorUDP.port;
            mUDPPacketEnviar->address.host = iPaddressServidorUDP.host;

            if (!SDLNet_UDP_Send(mUDPSocket, -1, mUDPPacketEnviar)) {
                printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
            }
            delete data;
        }
    }

    void update_estado_room(Uint8 * data){

        Uint8 datosprueba[MAX_TAM_UPDATE_ROOM];
        memcpy(datosprueba,data,MAX_TAM_UPDATE_ROOM);
        if(minutosEscogidos   != data[OFFSET_PACKET_MINUTOS_ESCOGIDOS]){
            minutosEscogidos   = data[OFFSET_PACKET_MINUTOS_ESCOGIDOS];
            mTextLabelMinutos->setText(std::to_string(minutosEscogidos));
        }

        if(victoriasEscogidas   != data[OFFSET_PACKET_VICTORIAS_ESCOGIDAS]){
            victoriasEscogidas   = data[OFFSET_PACKET_VICTORIAS_ESCOGIDAS];
            mTextLabelVictorias->setText(std::to_string(victoriasEscogidas));
        }

        std::memset(mIsPlayerActivado,false,Player::N_PLAYERS);

        int offset = OFFSET_PACKET_PRIMER_CLIENTE;
        for(int i = 0; i < MAX_CLIENTES;i++){
            clients[i]->activo = data[offset];
            if(clients[i]->activo){
                clients[i]->id_cliente = (*(uint16_t*)&data[offset + OFFSET_PACKET_ID_CLIENTE]);
                clients[i]->id_player  = (IdPlayer) data[offset + OFFSET_PACKET_ID_PLAYER];
                mIsPlayerActivado[clients[i]->id_player] = true;
                memcpy(clients[i]->nick_name,&data[offset + OFFSET_PACKET_NICK_NAME],MAX_NICK);

                if(clients[i]->id_cliente == mi_id){
                    mi_indice = (uint8_t) i;
                }
            }
            offset += TAM_PACKET_BYTES_CLIENTE;
        }

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



    void draw(SDL_Renderer *gRenderer) override {
        mpTextureTablero->draw(gRenderer, 0, 0);//imprimimos la barra mensage

        if(mMapaTerrenoSeleccionado.esMapaCargado()) {
            mpTextureCuadroPeque->draw(gRenderer, 177, 0);//imprimimos la barra mensage
            mpTextureCuadroPeque->draw(gRenderer, 280, 0);//imprimimos la barra mensage
            mpTextureMensPlayersEnBatalla->draw(gRenderer, 15, 0);//imprimimos la barra mensage
            mpTextureMensTiempoPorRonda->draw(gRenderer, 140, 18);//imprimimos la barra mensage
            mpTextureMensVictorias->draw(gRenderer, 261, 18);//imprimimos la barra mensage

            mMapaTerrenoSeleccionado.draw(gRenderer);//imprimimos el nivel

            mSprites->draw(gRenderer);
            for (int i = 0; i < Player::N_PLAYERS; i++) {
                if (!mIsPlayerActivado[i]) {
                    mpSpriteSheetPlayer[i]->draw(gRenderer, mAnimacionPlayer[i]->getX(), mAnimacionPlayer[i]->getY());
                } else {
                    mpSpriteSheetCarasBomberman->setCurrentCuadro(i * 2);
                    mpSpriteSheetCarasBomberman->draw(gRenderer, i * 16 + 20, 15);
                }
            }

            if (mLayoutParent->isDisabled()) {
                packLayout(gRenderer);
            }
        mLayoutParent->draw(gRenderer);
        }

    }

    void resume() override {
        InterfazGrafica::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }


        SDL_ShowCursor(SDL_ENABLE);
    }

    void establecerMapa(string nombre) {
        mMapaEscogido = nombre;
    }

    ~InterfazEsperarLlenarCliente(){
        //if(SDLNet_TCP_DelSocket(socket_set, mTCPServerSocket) == -1) {
        //    fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        //    exit(-1);
        // }

        SDLNet_UDP_Close(mUDPSocket);
        mUDPSocket = nullptr;
        SDLNet_FreePacket(mUDPPacket);
        mUDPPacket = nullptr;

        for(int i=0; i<MAX_CLIENTES; ++i) {
            delete clients[i];
        }

        //SDLNet_FreeSocketSet(socket_set);
        for(int i=0;i<Player::N_PLAYERS;i++){
            delete mAnimacionPlayer[i];
            //delete mAnimacionMensajePresiona[i];
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

private:
    //int next_ind = 0;
    //TCPsocket mTCPServerSocket;

    Cliente * clients[MAX_CLIENTES];
    //int mNumClientes = 0;

    //SDLNet_SocketSet socket_set;

    //TCPsocket sockets[MAX_CLIENTES] {nullptr};

    bool mHaOcurridoError;

    UDPsocket mUDPSocket = nullptr;

    Uint16 mTCPPuerto;
    //bool estaRoomCompleto = false;

    int minutosEscogidos   = 1;
    int victoriasEscogidas = 1;

    SDL_Renderer * mGRenderer = nullptr;
    // Contiene las animaciones(los players que se mueven)
    DrawGroup * mSprites = nullptr;

    // Usado para dibujar el mapa seleccionado actualmente
    LectorMapa mMapaTerrenoSeleccionado;

    // Botones de la interfaz
    //BotonComponent *mBtnSubirTiempo = nullptr;
    //BotonComponent *mBtnSubirVictorias = nullptr;
    //BotonComponent *mBtnJugar = nullptr;

    // Dice cuales estan activados
    bool mIsPlayerActivado[Player::N_PLAYERS] {false};

    //IdPlayer idPlayerUsuario;
    
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
    //uint16_t mUDPPuertoServidor;
    IPaddress *miipaddress = nullptr;
    IPaddress iPaddressServidorUDP;

    UDPpacket *mUDPPacket = nullptr;
    uint32_t id_ultima_actualizacion_recibida = 0;

    uint16_t mi_id = 0;
    uint8_t  mi_indice;
    string   mi_nick;
    LTimer mControlTimer;
    Uint32 mMaxTiempoMandarKeepAlive = 1000;
    UDPpacket *mUDPPacketEnviar = nullptr;
};
#endif //BOMBERMAN_INTERFAZESPERARLLENARCLIENTE_HPP
