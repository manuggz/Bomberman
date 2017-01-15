//
// Created by manuggz on 14/01/17.
//

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

class Cliente{

};

class InterfazEsperarLlenarServidor: public InterfazGrafica, public UpdateGroupContainerInterfaz, public BotonInterfaz {
public:
    static const int MAX_SOCKETS = 5;


    InterfazEsperarLlenarServidor(GameManagerInterfazUI *gameManagerInterfaz) : InterfazGrafica(gameManagerInterfaz),
                                                                                mMapaTerrenoSeleccionado(0,32){}

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
        SpriteSheet * spriteSheetTmp = new SpriteSheet();
        spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_1.bmp",1,12,true);
        mAnimacionPlayer[0]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");

        spriteSheetTmp = new SpriteSheet();
        spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_2.bmp",1,12,true);
        mAnimacionPlayer[1]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");

        spriteSheetTmp = new SpriteSheet();
        spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_3.bmp",1,12,true);
        mAnimacionPlayer[2]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");

        spriteSheetTmp = new SpriteSheet();
        spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_4.bmp",1,12,true);
        mAnimacionPlayer[3]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");

        spriteSheetTmp = new SpriteSheet();
        spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/personajes/player_5.bmp",1,12,true);
        mAnimacionPlayer[4]=new Animacion(spriteSheetTmp,"6,6,7,7,8,8");


        for(int i=0;i<Player::N_PLAYERS;i++){
            // Animacion para cuando aun no se ha seleccionado el personaje(Hace que parpadee "presiona")

            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/textos/txt_presiona.png",2,1);
            //mAnimacionMensajePresiona[i]=new Animacion(spriteSheetTmp,"0,0,1,1");
            // Animacion para cuando se selecciono el personaje(Hace que parpadee "activado")
            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer,"data/imagenes/textos/txt_activado.png",2,1);
            mAnimacionMensajeActivado[i]=new Animacion(spriteSheetTmp,"0,0,0,1,1,1");

            // Hace que las animaciones se repitan indefinidamente(Hasta que se eliminen desde el codigo)
            mAnimacionPlayer[i]->setRepeticiones(-1);
            mAnimacionMensajeActivado[i]->setRepeticiones(-1);
            //mAnimacionMensajePresiona[i]->setRepeticiones(-1);

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
        establecerTerrenoBatalla(gRenderer,mMapaEscogido);

        SDL_ShowCursor(SDL_ENABLE);
        mGRenderer = gRenderer;

    }

    void start() override {
        InterfazGrafica::start();
        IPaddress ip;
        mTCPPuerto = 8099;

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

        socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS);

        if(socket_set == NULL) {
            fprintf(stderr, "ER: SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
            exit(-1);
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

            // Animacion para cuando aun no se ha seleccionado el personaje(Hace que parpadee "presiona")

            //mAnimacionMensajePresiona[i]->setX(mAnimacionPlayer[i]->getX()-9);
            //mAnimacionMensajePresiona[i]->setY(mAnimacionPlayer[i]->getY()+20);

            mAnimacionMensajeActivado[i]->setX(mAnimacionPlayer[i]->getX()-9);
            mAnimacionMensajeActivado[i]->setY(mAnimacionPlayer[i]->getY()+20);

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
                    //cambiarEstadoPlayer(event->key.keysym.sym-SDLK_KP_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
                    break;
                case SDLK_1:case SDLK_2:case SDLK_3:case SDLK_4:case SDLK_5:
                    //cambiarEstadoPlayer(event->key.keysym.sym-SDLK_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
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
            mSprites->add(mAnimacionMensajeActivado[idPlayer]);
            //mSprites->erase(mAnimacionMensajePresiona[idPlayer]);
        }else{ // Si debe eliminarse del juego
            // Se activan/desactivan las animaciones
            mSprites->erase(mAnimacionPlayer[idPlayer]);
            mSprites->erase(mAnimacionMensajeActivado[idPlayer]);
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

        if(aceptarNuevoCliente()){

        }
        if(mNumClientes >= MAX_SOCKETS){

        }

    }

    bool aceptarNuevoCliente() {
        if(mNumClientes >= MAX_SOCKETS) return false;

        int index = 0;
        for(index = 0;  index <MAX_SOCKETS; index++){
            if(sockets[index] == nullptr) break;
        }

        //if(sockets[index]) {
        //    fprintf(stderr, "ER: Overriding socket at index %d.\n", index);
        //    cerrarConeccionCliente(index);
        //}

        sockets[index] = SDLNet_TCP_Accept(mTCPServerSocket);
        if(sockets[index] == nullptr) return false;

        clients[index] = new Cliente();
        cambiarEstadoPlayer(index); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53

        mNumClientes++;

        return true;
    }

    void cerrarConeccionCliente(int index) {
        if(sockets[index] == NULL) {
            fprintf(stderr, "ER: Attempted to delete a NULL socket.\n");
            return;
        }

        if(SDLNet_TCP_DelSocket(socket_set, sockets[index]) == -1) {
            fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
            exit(-1);
        }
        delete clients[index];
        clients[index] = nullptr;
        SDLNet_TCP_Close(sockets[index]);
        sockets[index] = nullptr;
    }

    ~InterfazEsperarLlenarServidor() override {
        //if(SDLNet_TCP_DelSocket(socket_set, mTCPServerSocket) == -1) {
        //    fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        //    exit(-1);
       // }

        SDLNet_TCP_Close(mTCPServerSocket);

        int i;
        for(i=0; i<MAX_SOCKETS; ++i) {
            if(sockets[i] == nullptr) continue;
            cerrarConeccionCliente(i);
        }

        SDLNet_FreeSocketSet(socket_set);
        for(int i=0;i<Player::N_PLAYERS;i++){
            delete mAnimacionPlayer[i];
            //delete mAnimacionMensajePresiona[i];
            delete mAnimacionMensajeActivado[i];
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
        InterfazGrafica::draw(gRenderer);
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
        SDL_ShowCursor(SDL_ENABLE);
    }

private:
    //int next_ind = 0;
    TCPsocket mTCPServerSocket;

    Cliente * clients[MAX_SOCKETS];
    int mNumClientes = 0;

    SDLNet_SocketSet socket_set;

    TCPsocket sockets[MAX_SOCKETS] {nullptr};

    bool mHaOcurridoError;

    //UDPsocket mUDPServerSocket;

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
    BotonComponent *mBtnSubirTiempo = nullptr;
    BotonComponent *mBtnSubirVictorias = nullptr;
    BotonComponent *mBtnJugar = nullptr;

    // Dice cuales estan activados
    bool mIsPlayerActivado[Player::N_PLAYERS] {false};
    
    string mMapaEscogido;

    // ID del terreno actual escogido por el usuario / EL ID del terreno dibujado en pantalla
    // Maximo ID(Numero) asignado a un mapa de batalla
    //int mMaxTerrenoBatalla = 1;


    // Animacion del personaje
    Animacion * mAnimacionPlayer[Player::N_PLAYERS] {nullptr};
    // Animacion del texto "presiona"
    //Animacion * mAnimacionMensajePresiona[Player::N_PLAYERS] {nullptr};
    // Animacion del texto "activado"
    Animacion * mAnimacionMensajeActivado[Player::N_PLAYERS] {nullptr};

    // Controla los botones en un layout
    LayoutAbsolute *mLayoutParent = nullptr;

    // Muestra en la UI el numero de minutos escogidos
    LabelComponent *mTextLabelMinutos = nullptr;
    // Muestra en la UI el numero de victorias escogidas
    LabelComponent *mTextLabelVictorias = nullptr;

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
};
#endif //BOMBERMAN_INTERFAZESPERARLLENARSERVIDOR_HPP
