//
// Created by manuggz on 18/01/17.
//

#ifndef BOMBERMAN_SERVIDOR_HPP
#define BOMBERMAN_SERVIDOR_HPP

#include <SDL2/SDL_net.h>
#include "ConstantesNetwork.hpp"
#include "../../personajes/player.hpp"

namespace ServidorNameSpace {
    class ClienteConectado {
    public:
        bool activo = 0;
        IdPlayer id_player;
        uint16_t id_cliente;
        uint8_t nick_name[MAX_NICK];

        IPaddress updsocketipadress;
    };

    typedef enum {
        IDLE,
        CREANDO,
        ERROR_CREACION,
        ESPERANDO_CLIENTES,
        CERRADO
    } EstadoServidor;


    struct DatosConfiguracionServidor {
        bool isPlayerActivado[Player::N_PLAYERS];
        uint8_t mapa_escogido[MAX_NOMBRE_MAPA];
        uint8_t minutos;
        uint8_t victorias;

        EstadoServidor estado;

        bool cerrar;
    };
}

void enviar_estado_room_clientes(ServidorNameSpace::ClienteConectado * clientes[MAX_CLIENTES], uint32_t * next_id_update, uint8_t minutos, uint8_t victorias,UDPsocket serversock,UDPpacket * mUDPPacketEnviar) ;
void construir_estado_room(ServidorNameSpace::ClienteConectado * clientes[MAX_CLIENTES], uint32_t * next_id_update, uint8_t minutos, uint8_t victorias, uint8_t *data);
int aceptarNuevoCliente(
        ServidorNameSpace::ClienteConectado * clientes[MAX_CLIENTES],
        TCPsocket server,
        bool mIsPlayerActivado[Player::N_PLAYERS],
        bool mIsPlayerAsignadoCliente[Player::N_PLAYERS],
        uint8_t mapaEscogido[MAX_NOMBRE_MAPA],
        uint16_t mUltimoIdUtilizado,
        Uint16 mUDPPuerto,
        uint8_t minutos,
        uint8_t victorias
) ;
int recibirDatos(TCPsocket psocket,uint8_t * pBuffer,uint8_t length);
void desconectar_cliente(ServidorNameSpace::ClienteConectado  * cliente);
int servidorEsperarConecciones(void *ptr);
#endif //BOMBERMAN_SERVIDOR_HPP
