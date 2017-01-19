//
// Created by manuggz on 17/01/17.
//

#ifndef BOMBERMAN_MENUESCOGERMAPANETWORKBATTLE_HPP
#define BOMBERMAN_MENUESCOGERMAPANETWORKBATTLE_HPP
#include "MenuEscogerMapa.hpp"
#include "InterfazEsperarLlenarServidor.hpp"
#include "Cliente.hpp"
#include "../../util/MensajeUsuarioToast.hpp"

class MenuEscogerMapaNetworkBattle: public MenuEscogerMapa {
public:
    MenuEscogerMapaNetworkBattle(GameManagerInterfazUI *gameManagerInterfaz) : MenuEscogerMapa(gameManagerInterfaz) {
        datosThreadConectarServidor.estado  = ClienteDatosNameSpace::IDLE;
        datosConfiguracionServidor.estado   = ServidorNameSpace::IDLE;
    }

    bool configuracionAceptada() override {
        int total_players = mIsPlayerActivado[PLAYER_1] + mIsPlayerActivado[PLAYER_2] + mIsPlayerActivado[PLAYER_3] +
                            mIsPlayerActivado[PLAYER_4] + mIsPlayerActivado[PLAYER_5];
        if (total_players >= 2) {
            if(!motradaToastCreandoservidor) {
                datosConfiguracionServidor.minutos = minutosEscogidos;
                datosConfiguracionServidor.victorias = victoriasEscogidas;

                memcpy(datosConfiguracionServidor.isPlayerActivado,mIsPlayerActivado,Player::N_PLAYERS);
                sprintf((char *)datosConfiguracionServidor.mapa_escogido,"%s",mNombreMapas[indiceTerrenoActual].c_str());
                datosConfiguracionServidor.cerrar = false;
                threadCrearServidor = SDL_CreateThread(servidorEsperarConecciones, "servidorEsperarConecciones",
                                                          (void *) &datosConfiguracionServidor);

                if (nullptr == threadCrearServidor) {
                    printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                } else {
                    SDL_DetachThread(threadCrearServidor);
                    //SDL_WaitThread(threadConectarServidor, &threadReturnValue);
                    //printf("\nThread returned value: %d", threadReturnValue);
                }

                MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(
                        mGameManagerInterfaz,
                        "Creating Server...",
                        Toast::TOAST_DURACION_LARGA
                );
                mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);
                motradaToastCreandoservidor = true;
            }

            setVisibilidadMenu(false);


            return true;
        }
        return false;
    }

    void update() override {
        MenuEscogerMapa::update();
        switch(datosConfiguracionServidor.estado){
            case ServidorNameSpace::IDLE:break;
            case ServidorNameSpace::CREANDO:break;
            case ServidorNameSpace::ERROR_CREACION:
                errorCreandoGameServer();
                break;
            case ServidorNameSpace::ESPERANDO_CLIENTES:{
                if(!estaEstableciendoSelfConeccionAlServidor){
                    MetaData * metaData = new MetaData(mGameManagerInterfaz->obtenerPrefPath() + "/player.inf",":");
                    SDL_Log("ESPERANDO_CLIENTES!");
                    sprintf(datosThreadConectarServidor.nombreServidor,"localhost");
                    sprintf(datosThreadConectarServidor.nick_usuario,"%s",metaData->getMetaData("NICK_NAME").c_str());
                    delete metaData;
                    threadConectarServidor = SDL_CreateThread(conectarServidor, "conectarServidor", (void *)&datosThreadConectarServidor);
                    if (nullptr == threadConectarServidor) {
                        errorCreandoGameServer();
                        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                    } else {
                        SDL_DetachThread(threadConectarServidor);
                        //SDL_WaitThread(threadConectarServidor, &threadReturnValue);
                        //printf("\nThread returned value: %d", threadReturnValue);

                    }
                    estaEstableciendoSelfConeccionAlServidor = true;
                }

            }

                break;
            case ServidorNameSpace::CERRADO:
                SDL_Log("Cerrado Servidor!");
                MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(
                        mGameManagerInterfaz,
                        "Closed Game Server!...",
                        Toast::TOAST_DURACION_MEDIA
                );
                mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);
                datosConfiguracionServidor.estado = ServidorNameSpace::IDLE;
                break;
        }

        switch(datosThreadConectarServidor.estado){

            case ClienteDatosNameSpace::IDLE:break;
            case ClienteDatosNameSpace::CONECTANDO:break;
            case ClienteDatosNameSpace::ERROR_CONECCION:
                errorCreandoGameServer();
                SDL_Log("ERROR_CONECCION!");
                break;
            case ClienteDatosNameSpace::CONECTADO: {
                SDL_Log("CONECTADO!");
                MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(
                        mGameManagerInterfaz,
                        "Game Server Created!...",
                        Toast::TOAST_DURACION_MEDIA
                );
                mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);
                InterfazEsperarLlenarServidor *nuevoJuego = new InterfazEsperarLlenarServidor(
                        mGameManagerInterfaz,
                        &datosThreadConectarServidor
                );
                mGameManagerInterfaz->cambiarInterfaz(nuevoJuego); //iniciamos en modo batalla, le pasamos el array con los players seleccionados por el usuario
                motradaToastCreandoservidor = true;
                datosThreadConectarServidor.estado = ClienteDatosNameSpace::IDLE;
                motradaToastCreandoservidor = false;
                estaEstableciendoSelfConeccionAlServidor = false;
            }
                break;
        }
    }

    void resume() override {
        MenuEscogerMapa::resume();
        setVisibilidadMenu(true);
        if(datosConfiguracionServidor.estado == ServidorNameSpace::ESPERANDO_CLIENTES){
            datosConfiguracionServidor.cerrar = true;
        }
    }

    void errorCreandoGameServer(){
        MensajeUsuarioToast *mensajeUsuarioToast = new MensajeUsuarioToast(
                mGameManagerInterfaz,
                "Error creating game server...",
                Toast::TOAST_DURACION_MEDIA
        );
        mGameManagerInterfaz->mostrarToast(mensajeUsuarioToast);
        setVisibilidadMenu(true);
        datosThreadConectarServidor.estado = ClienteDatosNameSpace::IDLE;
        datosConfiguracionServidor.estado = ServidorNameSpace::IDLE;
        datosConfiguracionServidor.cerrar = true;
        motradaToastCreandoservidor = false;
        estaEstableciendoSelfConeccionAlServidor = false;
    }
private:
    ClienteDatosNameSpace::DatosThreadConectarServidor datosThreadConectarServidor;
    ServidorNameSpace::DatosConfiguracionServidor datosConfiguracionServidor;
    bool motradaToastCreandoservidor = false;
    SDL_Thread *threadConectarServidor = nullptr;
    SDL_Thread *threadCrearServidor;
    bool estaEstableciendoSelfConeccionAlServidor;
};

#endif //BOMBERMAN_MENUESCOGERMAPANETWORKBATTLE_HPP
