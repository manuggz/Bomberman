//
// Created by manuggz on 15/01/17.
//

#ifndef BOMBERMAN_CONSTANTESSERVIDOR_HPP
#define BOMBERMAN_CONSTANTESSERVIDOR_HPP

#include <cstdint>
#include "../../util/constantes.hpp"

static const int MAX_NOMBRE_MAPA = 100;
static const int MAX_TAM_TCP_PAQUETE = 100;
static const int MAX_NICK = 8;
static const int TCP_DEFAULT_PUERTO = 8099;
static const int MAX_CLIENTES = 5;
static const int MAX_TAM_UPDATE_ROOM = 67;

static const int OFFSET_PACKET_FLAG = 0;
static const int OFFSET_PACKET_ID_UPDATE = 1;
static const int OFFSET_PACKET_MINUTOS_ESCOGIDOS = 5;
static const int OFFSET_PACKET_VICTORIAS_ESCOGIDAS = 6;
static const int OFFSET_PACKET_PRIMER_CLIENTE = 7;

// OFFSETS respecto OFFSET_PACKET_PRIMER_CLIENTE
static const int OFFSET_PACKET_ID_CLIENTE = 1;
static const int OFFSET_PACKET_ID_PLAYER  = 3;
static const int OFFSET_PACKET_NICK_NAME  = 4;

static const int TAM_PACKET_BYTES_CLIENTE = 12;


static const int FLAG_CLIENTE_CONECTADO = 1;
static const int FLAG_UPDATE_ESTADO_ROOM = 2;
static const int FLAG_KEEP_ALIVE = 3;
static const int FLAG_DISCONNECT = 4;

static const int TIMEOUT_DISCONECT_CLIENT = 5000;

class Cliente{
public:
    bool activo = 0;
    IdPlayer  id_player;
    uint16_t  id_cliente;
    uint8_t   nick_name[MAX_NICK];

    IPaddress updsocketipadress;
};

#endif //BOMBERMAN_CONSTANTESSERVIDOR_HPP
