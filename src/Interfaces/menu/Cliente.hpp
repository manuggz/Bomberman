//
// Created by manuggz on 18/01/17.
//

#ifndef BOMBERMAN_CLIENTE_HPP
#define BOMBERMAN_CLIENTE_HPP

#include <SDL_net.h>
#include "ConstantesNetwork.hpp"
#include "MenuEscogerMapa.hpp"

namespace ClienteDatosNameSpace {
    typedef enum {
        IDLE,
        CONECTANDO,
        ERROR_CONECCION,
        CONECTADO
    } EstadoConeccion;

    struct DatosRespuestaServidorConeccion {
        IPaddress adressudp;
        char nombreMapa[MAX_NOMBRE_MAPA + 1];//
        uint16_t id_cliente;
        bool isPlayerActivado[Player::N_PLAYERS];
        uint8_t minutos;
        uint8_t num_victorias;

    };

    struct DatosThreadConectarServidor {

        EstadoConeccion estado; // Estado de la coneccion al servidor

        char nombreServidor[MAX_SERVER_NAME + 1];
        char nick_usuario[MAX_NICK + 1];

        UDPsocket misocket;
        DatosRespuestaServidorConeccion resp;

    };
}

static int conectarServidor(void *ptr){

    ClienteDatosNameSpace::DatosThreadConectarServidor* datos = (ClienteDatosNameSpace::DatosThreadConectarServidor *) ptr;

    datos->estado = ClienteDatosNameSpace::CONECTANDO;
    IPaddress ip;

    if(SDLNet_ResolveHost(&ip,datos->nombreServidor,TCP_DEFAULT_PUERTO)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }

    TCPsocket tcpsocket = SDLNet_TCP_Open(&ip);
    if(!tcpsocket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }

    int num_brecv;
    int num_bsend;
    uint8_t pdata[MAX_TAM_TCP_PAQUETE] {0};

    // TieneMapa
    bool tiene_mapa = false;

    num_brecv = SDLNet_TCP_Recv(tcpsocket, pdata, MAX_TAM_TCP_PAQUETE);

    if(num_brecv <= 0) {
        const char* err = SDLNet_GetError();
        if(strlen(err) == 0) {
            printf("DB: client disconnected\n");
        } else {
            fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
        }
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    } else {

        for(std::string & nombre:MenuEscogerMapa::getNombresMapas()){
            if(!strcmp(nombre.c_str(), (const char *) pdata)){
                tiene_mapa = true;
                sprintf(datos->resp.nombreMapa,"%s",nombre.c_str());
                break;
            }
        }
    }

    // Informamos al servidor si tenemos o no el mapa
    num_bsend = SDLNet_TCP_Send(tcpsocket, pdata, 1);
    if(num_bsend<1) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        // It may be good to disconnect sock because it is likely invalid now.
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }

    if(!tiene_mapa){
        SDL_Log("No tiene el Mapa :(. %s.",pdata);
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }

    // Identificarse
    memcpy(pdata,datos->nick_usuario,MAX_NICK);

    num_bsend = SDLNet_TCP_Send(tcpsocket, pdata, MAX_NICK);
    if(num_bsend < MAX_NICK) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        // It may be good to disconnect sock because it is likely invalid now.
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }

    // Reconocer
    num_brecv = SDLNet_TCP_Recv(tcpsocket, pdata, 2);

    if(num_brecv <= 0) {
        const char* err = SDLNet_GetError();
        if(strlen(err) == 0) {
            printf("DB: client disconnected\n");
        } else {
            fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
        }
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    } else {
        datos->resp.minutos = *((uint8_t *)&pdata[0]);
        datos->resp.num_victorias = *((uint8_t *)&pdata[1]);
        datos->resp.id_cliente = *((uint16_t *)&pdata[2]);

        for(int i = 0; i < Player::N_PLAYERS;i++) {
            datos->resp.isPlayerActivado[i] = pdata[4 + i];
        }
    }

    // Obtengo la IP address del socket tcp
    IPaddress * ipAdress=SDLNet_TCP_GetPeerAddress(tcpsocket);
    datos->resp.adressudp.host = ipAdress->host;
    // Obtengo el Puerto UDP del socket udp del servidor
    num_brecv = SDLNet_TCP_Recv(tcpsocket, pdata, 2);
    if(num_brecv <= 0){
        const char* err = SDLNet_GetError();
        if(strlen(err) == 0) {
            printf("DB: client disconnected\n");
        } else {
            fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
        }
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }else{
        // Asigno el puerto del socket udp del servidor a la estructura ipddress
        datos->resp.adressudp.port = *((uint16_t *) &pdata);
    }

    // Creo mi socket udp
    datos->misocket =SDLNet_UDP_Open(0);
    if(!datos->misocket ) {
        printf("SDLNet_UDP_Open socket udp cliente: %s\n", SDLNet_GetError());
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }

    // Obtengo el puerto asignado al socket udp
    IPaddress *miipaddress = SDLNet_UDP_GetPeerAddress(datos->misocket , -1);
    if(!miipaddress) {
        printf("SDLNet_UDP_GetPeerAddress cliente: %s\n", SDLNet_GetError());
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }
    else {
        // perhaps print out address->host and address->port
        SDL_Log("Puerto asignado al udp cliente:%d.",miipaddress->port);
    }

    // Envio mi puerto del mi socket udp al servidor
    // Notar que intento simular una conexion-orientada conversacion con el servidor usando el
    // socket udp

    num_bsend = SDLNet_TCP_Send(tcpsocket, &miipaddress->port,2);
    if(num_bsend < 2) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        SDLNet_TCP_Close(tcpsocket);
        datos->estado = ClienteDatosNameSpace::ERROR_CONECCION;
        return 0;
    }


    SDLNet_TCP_Close(tcpsocket);
    datos->estado = ClienteDatosNameSpace::CONECTADO;
    return 1;
}


#endif //BOMBERMAN_CLIENTE_HPP
