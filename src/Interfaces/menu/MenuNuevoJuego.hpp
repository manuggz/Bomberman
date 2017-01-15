//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_MENUNUEVOJUEGO_HPP
#define BOMBERMAN_MENUNUEVOJUEGO_HPP

static const int ID_INTERFAZ_ESCOGER_MAPA = 123;

#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include "../../engine/interfaces/MenuListLabel.hpp"
#include "MenuModoMultijugador.hpp"
#include "MenuEscogerMapa.hpp"
#include "InterfazEsperarLlenarServidor.hpp"

class MenuNuevoJuego : public MenuListLabel{

public:

    MenuNuevoJuego(GameManagerInterfazUI *game) : MenuListLabel(game) {
        SDL_Log("MenuNuevoJuego::MenuNuevoJuego");
        //mMenuOpcionesText.push_back("Historia");
        mMenuOpcionesText.push_back("Multiplayer");
        mMenuOpcionesText.push_back("Conexion Local Crear");
        mMenuOpcionesText.push_back("Conexion Local Unirse");
    }

    void createUI(SDL_Renderer *renderer) override {
        MenuListLabel::createUI(renderer);
        mLayoutBackGround->setBackgroundTexture(renderer,"data/imagenes/fondos/fondo_menu.bmp",false);
        mpSfxCambiarOpcionResaltada = new EfectoSonido("data/sonidos/ping_2.wav",100);
    }

    void start() override {
        InterfazGrafica::start();

    }

    virtual bool setOpcionResaltada(int nuevaOpcion) override {
        if(MenuListLabel::setOpcionResaltada(nuevaOpcion)){
            mpSfxCambiarOpcionResaltada->play();
            return true;
        }
        return false;
    }


    void ejecutarAccionOpcionResaltada() {
        switch(mOpcionMenuResaltadaActual){
            //case MENU_OPCION_HISTORIA:
                //mGameManager->cambiarInterfaz(new JuegoHistoria(mGameManager));
            //    break;
            case MENU_OPCION_MULTIPLAYER:
                mGameManagerInterfaz->cambiarInterfaz(new MenuModoMultijugador(mGameManagerInterfaz));
                break;
            case MENU_OPCION_CONEXION_CREAR:
                mGameManagerInterfaz->cambiarInterfaz(new MenuEscogerMapa(mGameManagerInterfaz),
                                                      ID_INTERFAZ_ESCOGER_MAPA);
                //cout << "MENU_OPCION_CONEXION"<< endl;
                break;
            case MENU_OPCION_CONEXION_UNIRSE: {
                struct ifaddrs *ifAddrStruct = NULL;
                struct ifaddrs *ifa = NULL;
                void *tmpAddrPtr = NULL;

                getifaddrs(&ifAddrStruct);

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

                        if(SDLNet_ResolveHost(&ip,addressBuffer,8099)==-1) {
                            printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
                            exit(1);
                        }

                        tcpsock=SDLNet_TCP_Open(&ip);
                        if(!tcpsock) {
                            printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
                            continue;
                        }
                        SDL_Delay(5000);
                        SDLNet_TCP_Close(tcpsock);

                    } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
                        // is a valid IP6 Address
                        tmpAddrPtr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
                        char addressBuffer[INET6_ADDRSTRLEN];
                        inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                        printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
                    }
                }
                if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
            }
                break;
            default:break;
        }

    }

    void resultInterfazAnterior(int id, InterfazEstandarBackResult *pResult) override {
        InterfazGrafica::resultInterfazAnterior(id, pResult);
        SDL_Log("Resultado: %s.", pResult->texto.c_str());
        InterfazEsperarLlenarServidor * interfazEsperarLlenarServidor = new InterfazEsperarLlenarServidor(mGameManagerInterfaz);
        interfazEsperarLlenarServidor->establecerMapa(pResult->texto);
        interfazEsperarLlenarServidor->puedeCambiarMapa(false);
        mGameManagerInterfaz->cambiarInterfaz(interfazEsperarLlenarServidor);
    }

    ~MenuNuevoJuego() override {
        SDL_Log("MenuNuevoJuego::~MenuNuevoJuego");
        delete mpSfxCambiarOpcionResaltada;
    }

private:


    typedef enum{
        //MENU_OPCION_HISTORIA,
        MENU_OPCION_MULTIPLAYER,
        MENU_OPCION_CONEXION_CREAR,
        MENU_OPCION_CONEXION_UNIRSE,
    }MenuOption;
    EfectoSonido * mpSfxCambiarOpcionResaltada;

};
#endif //BOMBERMAN_MENUPRINCIPAL_HPP
