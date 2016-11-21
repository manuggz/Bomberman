//
// Created by manuggz on 20/11/16.
//

#ifndef BOMBERMAN_MENUMODOMULTIJUGADOR_HPP
#define BOMBERMAN_MENUMODOMULTIJUGADOR_HPP

#include <SDL_render.h>
#include <SDL_events.h>
#include "../engine/interfaces/interfaz.hpp"
#include "../engine/sprites/CGroup.hpp"
#include "../menu.hpp"
#include "../engine/layout/LayoutManager/LayoutVertical.hpp"
#include "../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../engine/layout/Componentes/ImageComponent.hpp"
#include "../engine/layout/Componentes/TextLabelComponent.hpp"

class MenuModoMultijugador: public Interfaz{

public:
    MenuModoMultijugador(GameManager * gameManager){
        //cout << "MenuModoMultijugador::MenuModoMultijugador"<<endl;
        mGameManager = gameManager;
        previewTerreno = nullptr;
        mSprites= nullptr;
        mMapaTerrenoSeleccionado = nullptr;
        //dataNivel = nullptr;

        mBtnSubirTiempo = nullptr;
        mBtnSubirVictorias = nullptr;
        mBtnCambiarMapa = nullptr;
        mBtnJugar = nullptr;

        for(int i = 0; i < 5 ;i++){
            mAnimacionPlayer[i] = nullptr;
            mAnimaPresiona[i] = nullptr;
            mAnimaActivado[i] = nullptr;
            mIsPlayerActivado[i] = false;
        }
        terrenoActual = -1;
        minutosEscogidos = -1;
        victoriasEscogidas = -1;
        mBotonClicked = -1;
        mMaxTerrenoBatalla = -1;

        mIsPaused = false;
        mLayoutParent = nullptr;
        mTextLabelMinutos = nullptr;
        mTextLabelVictorias = nullptr;
    }

    void prepare() override {
        cout << "MenuModoMultijugador::prepare"<<endl;

        // Buscamos el Maximo numero de terrenos disponibles para usar en el juego
        mMaxTerrenoBatalla = std::stoi(buscar_dato(RUTA_CONFIG_BASE, NAME_MAX_TERRENO_BATALLA));

        //Creamos el Controlador que se encarga de dibujar el Mapa
        mMapaTerrenoSeleccionado = new Mapa(this);

        // Establecemos las imagenes para los tiles del mapa
        mMapaTerrenoSeleccionado->setImgTiles(mGameManager->getImagen(IMG_TILES));

        minutosEscogidos = 1;
        victoriasEscogidas = 1;

        establecerTerrenoBatalla(0);
    }

    void createUI(SDL_Renderer * gRenderer) override {
        cout << "MenuModoMultijugador::createUI"<<endl;

        mLayoutParent = new LayoutAbsolute();

        // BotonComponent para controlar cuanto tiempo para acabar una ronda
        mBtnSubirTiempo=new BotonComponent<MenuModoMultijugador>(mGameManager->getImagen(IMG_BOTON_FLECHA_PEQUE_DERECHA),this);
        mBtnSubirTiempo->setId(MENU_BOTON_SUBIR_TIEMPO);
        mBtnSubirTiempo->bindAccion(&MenuModoMultijugador::clickControl);
        mLayoutParent->addComponent(mBtnSubirTiempo);
        mBtnSubirTiempo->setLayoutParam(LAYOUT_PARAM_X,"194");
        mBtnSubirTiempo->setLayoutParam(LAYOUT_PARAM_Y,"10");

        // BotonComponent para controlar cuantas victorias son necesarias para terminar el juego
        mBtnSubirVictorias=new BotonComponent<MenuModoMultijugador>(mGameManager->getImagen(IMG_BOTON_FLECHA_PEQUE_DERECHA),this);
        mBtnSubirVictorias->setId(MENU_BOTON_SUBIR_VICTORIAS);
        mBtnSubirVictorias->bindAccion(&MenuModoMultijugador::clickControl);
        mLayoutParent->addComponent(mBtnSubirVictorias);
        mBtnSubirVictorias->setLayoutParam(LAYOUT_PARAM_X,"295");
        mBtnSubirVictorias->setLayoutParam(LAYOUT_PARAM_Y,"10");

        // BotonComponent para cambiar el mapa a usar
        mBtnCambiarMapa=new BotonComponent<MenuModoMultijugador>(mGameManager->getImagen(IMG_BOTON_CAMBIAR_MAPA),this);
        mBtnCambiarMapa->setId(MENU_BOTON_CAMBIAR_MAPA);
        mBtnCambiarMapa->bindAccion(&MenuModoMultijugador::clickControl);
        mLayoutParent->addComponent(mBtnCambiarMapa);
        mBtnCambiarMapa->setLayoutParam(LAYOUT_PARAM_X,"160");
        mBtnCambiarMapa->setLayoutParam(LAYOUT_PARAM_Y,"225");

        // BotonComponent para comenzar a jugar
        mBtnJugar=new BotonComponent<MenuModoMultijugador>(mGameManager->getImagen(IMG_BOTON_JUGAR_2),this);
        mBtnJugar->setId(MENU_BOTON_JUGAR);
        mBtnJugar->bindAccion(&MenuModoMultijugador::clickControl);
        mBtnJugar->setVisible(false); // Lo ocultamos hasta que se seleccionen dos jugadores
        mLayoutParent->addComponent(mBtnJugar);
        mBtnJugar->setLayoutParam(LAYOUT_PARAM_X,"240");
        mBtnJugar->setLayoutParam(LAYOUT_PARAM_Y,"225");

        // Controla las animaciones de los personajes cuando se seleccionan para jugar
        mSprites=new Group(this);
        cout << "mSprites : " << mSprites << endl;

        //Animaciones para los personajes (Hace que parezcan que caminan) cuando se seleccionan
        mAnimacionPlayer[0]=new Animacion(mGameManager->getImagen(IMG_PLAYER_1),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_1,Y_INIT_PLAYER_1,0);
        mAnimacionPlayer[1]=new Animacion(mGameManager->getImagen(IMG_PLAYER_2),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_2,Y_INIT_PLAYER_2,1);
        mAnimacionPlayer[2]=new Animacion(mGameManager->getImagen(IMG_PLAYER_3),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_3,Y_INIT_PLAYER_3,2);
        mAnimacionPlayer[3]=new Animacion(mGameManager->getImagen(IMG_PLAYER_4),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_4,Y_INIT_PLAYER_4-20,3);
        mAnimacionPlayer[4]=new Animacion(mGameManager->getImagen(IMG_PLAYER_5),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_5,Y_INIT_PLAYER_5,4);

        for(int i=0;i<_PLAYERS;i++){

            // Animacion para cuando aun no se ha seleccionado el personaje(Hace que parpadee "presiona")
            mAnimaPresiona[i]=new Animacion(mGameManager->getImagen(IMG_TXT_PRESIONA),2,1,"0,0,1,1",mAnimacionPlayer[i]->getX()-9,mAnimacionPlayer[i]->getY()+20,i);
            // Animacion para cuando se selecciono el personaje(Hace que parpadee "activado")
            mAnimaActivado[i]=new Animacion(mGameManager->getImagen(IMG_TXT_ACTIVADO),2,1,"0,0,0,1,1,1",mAnimacionPlayer[i]->getX()-9,mAnimacionPlayer[i]->getY()+20,i);

            // Hace que las animaciones se repitan indefinidamente(Hasta que se eliminen desde el codigo)
            mAnimacionPlayer[i]->setLoop(-1);
            mAnimaActivado[i]->setLoop(-1);
            mAnimaPresiona[i]->setLoop(-1);

            // Las agrega al controlador que hace que se actualizen y se muestren
            mSprites->add(mAnimaPresiona[i]);
        }

        SDL_Color color = {255,0,0,255};
        mTextLabelMinutos = new TextLabelComponent();
        mTextLabelMinutos->setText(std::to_string(minutosEscogidos));
        mTextLabelMinutos->setFont("data/fuentes/OpenSans-Bold.ttf",15);
        mTextLabelMinutos->setTextColor(color);
        mTextLabelMinutos->setLayoutParam(LAYOUT_PARAM_X,"180");
        mTextLabelMinutos->setLayoutParam(LAYOUT_PARAM_Y,std::to_string(5 + mMapaTerrenoSeleccionado->getYPanel()));
        mLayoutParent->addComponent(mTextLabelMinutos);

        mTextLabelVictorias = new TextLabelComponent();
        mTextLabelVictorias->setText(std::to_string(victoriasEscogidas));
        mTextLabelVictorias->setFont("data/fuentes/OpenSans-Bold.ttf",15);
        mTextLabelVictorias->setTextColor(color);
        mTextLabelVictorias->setLayoutParam(LAYOUT_PARAM_X,"283");
        mTextLabelVictorias->setLayoutParam(LAYOUT_PARAM_Y,std::to_string(5 + mMapaTerrenoSeleccionado->getYPanel()));
        mLayoutParent->addComponent(mTextLabelVictorias);

        //static char tmp[50];
        //sprintf(tmp,"%d",i+1);
        //imprimir_palabra(gRenderer,mGameManager->getImagen(IMG_FUENTE_6),mAnimacionPlayer[i]->getX()-9+41,mAnimacionPlayer[i]->getY()+19,tmp,STR_MAX_ESTENDIDA);

        //mGameManager->playSonido(SND_MENU);

        SDL_ShowCursor(SDL_ENABLE);
    }

    void packLayout(SDL_Renderer * gRenderer){
        cout << "MenuModoMultijugador::packLayout"<<endl;
        SDL_Rect rect = {0,0,mGameManager->getWidth(),mGameManager->getHeight()};
        mLayoutParent->pack(gRenderer);
        mLayoutParent->setRectDibujo(rect);
    }
    /**
     * Establece/Cambia el terreno en el que se jugara
     * @param nuevoTerreno
     * @return
     */
    bool establecerTerrenoBatalla(int nuevoTerreno) {
        cout << "MenuModoMultijugador::establecerTerrenoBatalla"<<endl;

        if(nuevoTerreno>=0 && nuevoTerreno < mMaxTerrenoBatalla && nuevoTerreno != terrenoActual){
            static char ruta1[50],ruta2[50];
            sprintf(ruta1,"data/niveles/batalla/%d.map",nuevoTerreno+1);
            sprintf(ruta2,"data/niveles/batalla/%d.txt",nuevoTerreno+1);
            if(!mMapaTerrenoSeleccionado->cargarDeArchivoBin(ruta1,ruta2)){
                cout << "ASDASD" << endl;
            }
            mMapaTerrenoSeleccionado->setEjeVisualizacion(mMapaTerrenoSeleccionado->getEjeX(),mMapaTerrenoSeleccionado->getEjeY());
            terrenoActual = nuevoTerreno;
            return true;
        }

        return false;

    }

    /**
     * Funcion llamada por los botones de la interfaz cuando son presionados
     * @param control_click
     */
    void clickControl(BotonComponent<MenuModoMultijugador> * control_click) {
        cout << "MenuModoMultijugador::clickControl"<<endl;
        mBotonClicked = control_click->getId();
        ejecutarAccionBotonClicked();
    }

    /**
     * Ejecuta la opcion enlazada a un boton
     */
    void ejecutarAccionBotonClicked(){
        cout << "MenuModoMultijugador::ejecutarAccionBotonClicked"<<endl;
        switch(mBotonClicked){
            case MENU_BOTON_SUBIR_TIEMPO:
                if(++minutosEscogidos>5)minutosEscogidos=1;
                mTextLabelMinutos->setText(std::to_string(minutosEscogidos));
                break;
            case MENU_BOTON_SUBIR_VICTORIAS:
                if(++victoriasEscogidas>8)victoriasEscogidas=1;
                mTextLabelVictorias->setText(std::to_string(victoriasEscogidas));
                break;
            case MENU_BOTON_CAMBIAR_MAPA:
                if(establecerTerrenoBatalla((terrenoActual + 1 == mMaxTerrenoBatalla)?0:terrenoActual + 1)){
                    mGameManager->play(SFX_TONO_ACUATICO);
                }
                break;
            case MENU_BOTON_JUGAR:
                int total_players=mIsPlayerActivado[PLAYER_1]+ mIsPlayerActivado[PLAYER_2]+ mIsPlayerActivado[PLAYER_3] + mIsPlayerActivado[PLAYER_4] + mIsPlayerActivado[PLAYER_5];
                if(total_players>=2){

                    Juego * nuevoJuego = new Juego(mGameManager,27,54,terrenoActual,victoriasEscogidas,minutosEscogidos,mIsPlayerActivado);
                    mGameManager->cambiarInterfaz(nuevoJuego); //iniciamos en modo batalla, le pasamos el array con los players seleccionados por el usuario
                    mGameManager->play(SFX_EXPLOSION);
                }
                break;
        }
    }

    /**
     *  Cambia el estado de un player lo establece activo/desactivado
     * @param idPlayer
     */
    void cambiarEstadoPlayer(int idPlayer){
        cout << "MenuModoMultijugador::cambiarEstadoPlayer"<<endl;
        mIsPlayerActivado[idPlayer]=!mIsPlayerActivado[idPlayer];

        if(mIsPlayerActivado[idPlayer]){ // Si debe agregarse al juego
            // Se activan/desactivan las animaciones
            mSprites->add(mAnimacionPlayer[idPlayer]);
            mSprites->add(mAnimaActivado[idPlayer]);
            mSprites->erase(mAnimaPresiona[idPlayer]);
        }else{ // Si debe eliminarse del juego
            // Se activan/desactivan las animaciones
            mSprites->erase(mAnimacionPlayer[idPlayer]);
            mSprites->erase(mAnimaActivado[idPlayer]);
            mSprites->add(mAnimaPresiona[idPlayer]);
        }

        // Si hay mas de dos botones players activados se muestra el boton de jugar
        mBtnJugar->setVisible(mIsPlayerActivado[PLAYER_1]+ mIsPlayerActivado[PLAYER_2]+ mIsPlayerActivado[PLAYER_3] + mIsPlayerActivado[PLAYER_4] + mIsPlayerActivado[PLAYER_5]>1);
        mGameManager->play(SFX_TONO_SECO);
    }

    virtual bool isPaused() override {
        cout << "MenuModoMultijugador::isPaused"<<endl;
        return mIsPaused;
    }

    virtual void pause() override {
        cout << "MenuModoMultijugador::pause"<<endl;
        mIsPaused = true;
    }

    virtual void resume() override {
        cout << "MenuModoMultijugador::resume"<<endl;
        mIsPaused = false;
    }

    virtual void procesarEvento(SDL_Event *event) override {
        cout << "MenuModoMultijugador::procesarEvento"<<endl;
        if(event->type==SDL_KEYDOWN){
            switch(event->key.keysym.sym){
                case SDLK_ESCAPE:
                    mGameManager->popInterface();
                    break;
                case SDLK_RETURN:
                    mBotonClicked=MENU_BOTON_JUGAR;
                    ejecutarAccionBotonClicked();
                    break;
                case SDLK_KP_1:case SDLK_KP_2:case SDLK_KP_3:case SDLK_KP_4:case SDLK_KP_5:
                    cambiarEstadoPlayer(event->key.keysym.sym-SDLK_KP_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
                    break;
                case SDLK_1:case SDLK_2:case SDLK_3:case SDLK_4:case SDLK_5:
                    cambiarEstadoPlayer(event->key.keysym.sym-SDLK_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
                    break;
                case SDLK_LEFT:case SDLK_RIGHT:
                    mBotonClicked=MENU_BOTON_CAMBIAR_MAPA;
                    ejecutarAccionBotonClicked();
                    break;
                default:
                    break;
            }
        }

        mBtnSubirTiempo->procesarEvento(event);
        mBtnSubirVictorias->procesarEvento(event);
        mBtnCambiarMapa->procesarEvento(event);
        mBtnJugar->procesarEvento(event);
    }

    virtual void update() override {
        cout << "MenuModoMultijugador::update"<<endl;
        mSprites->update();
    }

    virtual void draw(SDL_Renderer *gRenderer) override {
        //cout << "MenuModoMultijugador::draw"<<endl;

        mGameManager->getImagen((CodeImagen)mMapaTerrenoSeleccionado->getIdFondo())->render(gRenderer,0,0);
        mGameManager->getImagen(IMG_TABLERO)->render(gRenderer,0,mMapaTerrenoSeleccionado->getYPanel());//imprimimos la barra mensage
        mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,177,7+mMapaTerrenoSeleccionado->getYPanel());//imprimimos la barra mensage
        mGameManager->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,280,7+mMapaTerrenoSeleccionado->getYPanel());//imprimimos la barra mensage
        mGameManager->getImagen(IMG_TXT_PLAYERS_EN_BATALLA)->render(gRenderer,15,24+mMapaTerrenoSeleccionado->getYPanel());//imprimimos la barra mensage
        mGameManager->getImagen(IMG_TXT_TIEMPO_POR_RONDA)->render(gRenderer,140,24+mMapaTerrenoSeleccionado->getYPanel());//imprimimos la barra mensage
        mGameManager->getImagen(IMG_TXT_VICTORIAS)->render(gRenderer,261,24+mMapaTerrenoSeleccionado->getYPanel());//imprimimos la barra mensage


        mMapaTerrenoSeleccionado->draw(gRenderer);//imprimimos el nivel

        mSprites->draw(gRenderer);
        for(int i=0;i<_PLAYERS;i++){
            if(!mIsPlayerActivado[i]){
                imprimir_desde_grilla(mGameManager->getImagen((CodeImagen)(IMG_PLAYER_1 + i)), 6,gRenderer, mAnimacionPlayer[i]->getX(),mAnimacionPlayer[i]->getY(),1, 12,true);
            }else{
                imprimir_desde_grilla(mGameManager->getImagen(IMG_CARAS_BOMBERMAN),i*2,gRenderer,i*16+20,mMapaTerrenoSeleccionado->getYPanel()+2,1,10,0);
            }
        }

        if(mLayoutParent->isDisabled()){
            packLayout(gRenderer);
        }
        mLayoutParent->draw(gRenderer);

    }

    ~MenuModoMultijugador(){
        cout << "MenuModoMultijugador::~MenuModoMultijugador"<<endl;
        for(int i=0;i<_PLAYERS;i++){
            delete mAnimacionPlayer[i];
            delete mAnimaPresiona[i];
            delete mAnimaActivado[i];
        }
        //SDL_FreeSurface(previewTerreno);
        //delete dataNivel;
        delete mMapaTerrenoSeleccionado;
        delete mLayoutParent;
    }
private:


    GameManager *  mGameManager;

    // Contiene las animaciones(los players que se mueven)
    Group *        mSprites;

    // Usado para dibujar el mapa seleccionado actualmente
    Mapa *         mMapaTerrenoSeleccionado;

    //DatNivel *     dataNivel;
    //SDL_Surface *  previewTerreno;

    // Botones de la interfaz
    BotonComponent<MenuModoMultijugador> *mBtnSubirTiempo,*mBtnSubirVictorias,*mBtnCambiarMapa,*mBtnJugar;

    /**
     * Ids asignados a los botones de la interfaz, son usados en un swith cuando se llama a la funcion
     * enlazada a los botones para saber cual boton fué presionado.
     */
    enum{
        MENU_BOTON_SUBIR_TIEMPO,
        MENU_BOTON_SUBIR_VICTORIAS,
        MENU_BOTON_CAMBIAR_MAPA,
        MENU_BOTON_JUGAR,
    };

    // Dice cual boton fué clickeado / Tambien se usa para ejecutar una funcion asociada al click de un boton
    int mBotonClicked;

    // Animacion del personaje
    Animacion * mAnimacionPlayer[_PLAYERS];
    // Animacion del texto "presiona"
    Animacion * mAnimaPresiona[_PLAYERS];
    // Animacion del texto "activado"
    Animacion * mAnimaActivado[_PLAYERS];

    // Dice cuales estan activados
    bool mIsPlayerActivado[_PLAYERS];

    // ID del terreno actual escogido por el usuario / EL ID del terreno dibujado en pantalla
    int terrenoActual;

    // Minutos Escogidos de duracion de cada ronda
    int minutosEscogidos;

    // Victorias escogidas para acabar el juego
    int victoriasEscogidas;

    // Maximo ID(Numero) asignado a un mapa de batalla
    int mMaxTerrenoBatalla;

    // Controla los botones en un layout
    LayoutAbsolute *mLayoutParent;

    // Muestra en la UI el numero de minutos escogidos
    TextLabelComponent *mTextLabelMinutos;
    // Muestra en la UI el numero de victorias escogidas
    TextLabelComponent *mTextLabelVictorias;
};
#endif //BOMBERMAN_MENUMODOMULTIJUGADOR_HPP
