//
// Created by manuggz on 17/01/17.
//

#ifndef BOMBERMAN_MENUNETWORKBATTLE_HPP
#define BOMBERMAN_MENUNETWORKBATTLE_HPP
//
// Created by manuggz on 19/11/16.
//


#include "../../engine/util/EfectoSonido.hpp"
#include "../../engine/util/MusicaFondo.hpp"
#include "../../engine/util/BitmapFont.hpp"
#include "../InterfazConfiguracion.hpp"
#include "SpriteFlecha.hpp"
#include "MenuEscogerMapaBattle.hpp"
#include "PopUpInsertarTexto.hpp"
#include "MenuEscogerMapaNetworkBattle.hpp"
#include "../../util/MensajeUsuarioToast.hpp"
#include "Cliente.hpp"

class MenuNetworkBattle : public InterfazGrafica{

public:

    static const int Y_OPCIONES_MENU_INICIAL = 105;
    static const int ID_POP_UP_INSERTAR_NICK_CLIENTE = 0;
    static const int ID_POP_UP_INSERTAR_SERVER_NAME = 1;
    static const int X_OPCIONES_MENU = 81;
    

    MenuNetworkBattle(GameManagerInterfazUI *gameManager) : InterfazGrafica(gameManager) {
        SDL_Log("MenuNetworkBattle::MenuNetworkBattle");

    }

    void resultPopUp(InterfazEstandarBackResult *result, int idPopUp) override {
        switch (idPopUp) {
            case ID_POP_UP_INSERTAR_NICK_CLIENTE:
                if (result) {
                    mNick = result->texto;
                    mpBitmapTexto[MENU_OPCION_NICK]->setText("Your Nick:" + mNick);
                    metaData->setMetaData("NICK_NAME",mNick);
                    metaData->guardar(mGameManagerInterfaz->obtenerPrefPath() + "/player.inf",":");
                }
                break;
            case ID_POP_UP_INSERTAR_SERVER_NAME:
                if (result) {
                    mostradoToastConectando = false;
                    sprintf(datosThreadConectarServidor.nombreServidor,"%s",result->texto.c_str());
                    threadConectarServidor = SDL_CreateThread(conectarServidor, "conectarServidor", (void *)&datosThreadConectarServidor);
                    if (nullptr == threadConectarServidor) {
                        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                    } else {
                        SDL_DetachThread(threadConectarServidor);
                        //SDL_WaitThread(threadConectarServidor, &threadReturnValue);
                        //printf("\nThread returned value: %d", threadReturnValue);
                    }

                    //mNick = result->texto;
                    //mpBitmapTexto[MENU_OPCION_NICK]->setText("Your Nick:" + mNick);
                    //metaData->setMetaData("NICK_NAME",mNick);
                    //metaData->guardar(mGameManagerInterfaz->obtenerPrefPath() + "/player.inf",":");
                }
                break;
        }
        delete result;
    }


    void prepare() override {

        metaData = new MetaData(mGameManagerInterfaz->obtenerPrefPath() + "/player.inf",":");
        mNick = metaData->getMetaData("NICK_NAME");
        if(mNick.empty()){
            mNick = "Bomber";
            metaData->setMetaData("NICK_NAME",mNick);
            metaData->guardar(mGameManagerInterfaz->obtenerPrefPath() + "/player.inf",":");
        }
    }
    void createUI(SDL_Renderer *renderer) override {
        InterfazGrafica::createUI(renderer);

        textureFondo = new LTexture();
        textureFondo->cargarDesdeArchivo("data/imagenes/fondos/fondo_menu.png",renderer,false);

        LTexture *pTextureFlechaDerecha = new LTexture();
        pTextureFlechaDerecha->cargarDesdeArchivo("data/imagenes/objetos/flecha_menu_apunta_hacia_izquierda.png",renderer,false);

        LTexture * pTextureFlechaIzquierda = new LTexture();
        pTextureFlechaIzquierda->cargarDesdeArchivo("data/imagenes/objetos/flecha_menu_apunta_hacia_derecha.png",renderer,false);

        flechaIzquierda = new FlechaDinamica(pTextureFlechaIzquierda);
        flechaIzquierda->move(X_OPCIONES_MENU - pTextureFlechaDerecha->getWidth(),Y_OPCIONES_MENU_INICIAL);
        flechaIzquierda->setYDestino(Y_OPCIONES_MENU_INICIAL);

        flechaDerecha = new FlechaDinamica(pTextureFlechaDerecha);
        flechaDerecha->move(X_OPCIONES_MENU + 173,Y_OPCIONES_MENU_INICIAL);
        flechaDerecha->setYDestino(Y_OPCIONES_MENU_INICIAL);

        mBitmapFont[FUENTE_NORMAL] = new BitmapFont(renderer,   "data/fuentes/fuente2_16_normal.png");
        mBitmapFont[FUENTE_RESALTADA] = new BitmapFont(renderer,"data/fuentes/fuente2_16_resaltado.png");

        for(int i = 0; i < _N_OPCIONES_MENU;i++) {
            mpBitmapTexto[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], X_OPCIONES_MENU, Y_OPCIONES_MENU_INICIAL + 20*i);
        }
        mpBitmapTexto[0]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);

        mpSfxCambiarOpcionResaltada = new EfectoSonido("data/sonidos/ping_3.wav",100);

        musicaFondoMenu = new MusicaFondo("data/sonidos/musica_1.mid");


        mpBitmapTexto[MENU_OPCION_JOIN_BATTLE]->setText("Join Battle");
        mpBitmapTexto[MENU_OPCION_CREATE_NEW_BATTLE]->setText("Create New Battle");


        mpBitmapTexto[MENU_OPCION_NICK]->setText("Your Nick:" + mNick);


    }

    virtual bool setOpcionResaltada(Uint8 nuevaOpcion) {
        if(nuevaOpcion < _N_OPCIONES_MENU && nuevaOpcion != mOpcionMenuResaltadaActual){
            mpBitmapTexto[mOpcionMenuResaltadaActual]->setBitmapFont(mBitmapFont[FUENTE_NORMAL]);
            mpBitmapTexto[nuevaOpcion]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);
            mOpcionMenuResaltadaActual =  nuevaOpcion;
            flechaIzquierda->setYDestino(108 + 20*nuevaOpcion);
            flechaDerecha->setYDestino(108 + 20*nuevaOpcion);
            mpSfxCambiarOpcionResaltada->play();
            return true;
        }

        return false;
    }

    void resume() override {
        InterfazGrafica::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }
    }

    void start() override {
        InterfazGrafica::start();
        datosThreadConectarServidor.estado=ClienteDatosNameSpace::IDLE;
    }

    void ejecutarAccionOpcionMenu(Uint8 opcion) {
        switch(opcion){
            case MENU_OPCION_JOIN_BATTLE: {
                //mGameManagerInterfaz->cambiarInterfaz(new MenuEscogerMapaBattle(mGameManagerInterfaz));
                PopUpInsertarTexto *popUpInsertarTexto = new PopUpInsertarTexto(mGameManagerInterfaz,
                                                                                "Insert Server Name:",
                                                                                3,
                                                                                19,
                                                                                "localhost"
                );
                mGameManagerInterfaz->showPopUp(popUpInsertarTexto, ID_POP_UP_INSERTAR_SERVER_NAME);
            }
                break;
            case MENU_OPCION_CREATE_NEW_BATTLE:
                mGameManagerInterfaz->cambiarInterfaz(new MenuEscogerMapaNetworkBattle(mGameManagerInterfaz));
                break;
            case MENU_OPCION_NICK: {
                PopUpInsertarTexto *popUpInsertarTexto = new PopUpInsertarTexto(mGameManagerInterfaz,
                                                                                "Insert Your New Nick:",
                                                                                4,
                                                                                8,
                                                                                mNick
                );
                mGameManagerInterfaz->showPopUp(popUpInsertarTexto, ID_POP_UP_INSERTAR_NICK_CLIENTE);
                //mGameManagerInterfaz->cambiarInterfaz(new InterfazConfiguracion(mGameManagerInterfaz));
            }
                break;
            default:break;
        }

    }

    void procesarEvento(SDL_Event *pEvento) override {
        InterfazGrafica::procesarEvento(pEvento);
        if(pEvento->type==SDL_KEYDOWN){
            switch(pEvento->key.keysym.sym){
                case SDLK_UP:
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual > 0 ? mOpcionMenuResaltadaActual - 1 : 0));
                    break;
                case SDLK_DOWN:
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual + 1));
                    break;
                case SDLK_RETURN:
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual);
                    break;
                default:
                    break;
            }
        }else if(pEvento->type == SDL_JOYAXISMOTION&&pEvento->jaxis.type == SDL_JOYAXISMOTION){
            if(pEvento->jaxis.axis != 0){
                if(pEvento->jaxis.value > 10){
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual + 1));
                }else if(pEvento->jaxis.value < -10){
                    setOpcionResaltada((Uint8) (mOpcionMenuResaltadaActual > 0 ? mOpcionMenuResaltadaActual - 1 : 0));
                }
            }
        }else if(pEvento->type == SDL_JOYBUTTONDOWN){
            if(pEvento->jbutton.type == SDL_JOYBUTTONDOWN)
                if(pEvento->jbutton.button + 1==3) {
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual);
                }

        }
    }

    void update() override {
        InterfazGrafica::update();
        flechaIzquierda->update(nullptr);
        flechaDerecha->update(nullptr);

        switch(datosThreadConectarServidor.estado){

            case ClienteDatosNameSpace::IDLE:break;
            case ClienteDatosNameSpace::CONECTANDO: {
                if(!mostradoToastConectando) {
                    MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(mGameManagerInterfaz, "Connecting...",
                                                                                       Toast::TOAST_DURACION_MEDIA);
                    mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);
                    mostradoToastConectando = true;
                }
                }
                break;
            case ClienteDatosNameSpace::ERROR_CONECCION: {
                MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(mGameManagerInterfaz,
                                                                                   "Something went wrong!.",
                                                                                   Toast::TOAST_DURACION_CORTA);
                mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);
                datosThreadConectarServidor.estado = ClienteDatosNameSpace::IDLE;
                }
                break;
            case ClienteDatosNameSpace::CONECTADO: {
                MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(mGameManagerInterfaz,
                                                                                   "Conected!.",
                                                                                   Toast::TOAST_DURACION_CORTA);
                mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);

                InterfazEsperarLlenarServidor *nuevoJuego = new InterfazEsperarLlenarServidor(
                        mGameManagerInterfaz,
                        &datosThreadConectarServidor
                );
                mGameManagerInterfaz->cambiarInterfaz(nuevoJuego); //iniciamos en modo batalla, le pasamos el array con los players seleccionados por el usuario

            }
                datosThreadConectarServidor.estado = ClienteDatosNameSpace::IDLE;
                break;
        }
    }

    void draw(SDL_Renderer *gRenderer) override {
        textureFondo->draw(gRenderer);
        for(int i = 0; i < _N_OPCIONES_MENU;i++){
            mpBitmapTexto[i]->draw(gRenderer);
        }
        flechaIzquierda->draw(gRenderer);
        flechaDerecha->draw(gRenderer);
    }

    ~MenuNetworkBattle() override {
        SDL_Log("MenuNetworkBattle::~MenuNetworkBattle");
        delete mpSfxCambiarOpcionResaltada;
        delete musicaFondoMenu;
        delete mBitmapFont[0];
        delete mBitmapFont[1];

        for(int i = 0; i < _N_OPCIONES_MENU;i++) {
            delete mpBitmapTexto[i];
        }
        delete textureFondo;
        delete metaData;


        delete flechaDerecha;
        delete flechaIzquierda;
    }

private:
    typedef enum{
        MENU_OPCION_JOIN_BATTLE,
        MENU_OPCION_CREATE_NEW_BATTLE,
        MENU_OPCION_NICK,
        _N_OPCIONES_MENU,
    }MenuOption;

    enum{
        FUENTE_NORMAL,
        FUENTE_RESALTADA,
    };
    EfectoSonido * mpSfxCambiarOpcionResaltada;
    MusicaFondo *musicaFondoMenu;

    BitmapFont *mBitmapFont[2];
    BitmapFontRenderer *mpBitmapTexto[_N_OPCIONES_MENU] {nullptr};

    //LayoutAbsolute *  mLayoutBackGround;
    LTexture * textureFondo = nullptr;
    Uint8 mOpcionMenuResaltadaActual = 0;

    FlechaDinamica * flechaIzquierda;
    FlechaDinamica * flechaDerecha;
    std::string mNick;
    MetaData *metaData;
    SDL_Thread *threadConectarServidor = nullptr;
    std::string mServerNameIntroducidoUsuario;


    ClienteDatosNameSpace::DatosThreadConectarServidor datosThreadConectarServidor;
    bool mostradoToastConectando = false;
};

#endif //BOMBERMAN_MENUNETWORKBATTLE_HPP
