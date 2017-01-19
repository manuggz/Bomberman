//
// Created by manuggz on 18/01/17.
//

#include "Servidor.hpp"


void enviar_estado_room_clientes(ServidorNameSpace::ClienteConectado * clientes[MAX_CLIENTES], uint32_t * next_id_update, uint8_t minutos, uint8_t victorias,UDPsocket serversock,UDPpacket * mUDPPacketEnviar) {
    mUDPPacketEnviar->len = MAX_TAM_UPDATE_ROOM;

    Uint8 * data = new Uint8[MAX_TAM_UPDATE_ROOM];
    construir_estado_room(clientes,next_id_update,minutos,victorias,data);
    mUDPPacketEnviar->data = data;
    for(int i = 1 ; i < MAX_CLIENTES;i++){
        if(clientes[i]->activo){
            mUDPPacketEnviar->address.port = clientes[i]->updsocketipadress.port;
            mUDPPacketEnviar->address.host = clientes[i]->updsocketipadress.host;
            if(!SDLNet_UDP_Send(serversock, -1, mUDPPacketEnviar)){
                printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
            }
        }
    }
    delete data;
}
void construir_estado_room(ServidorNameSpace::ClienteConectado * clientes[MAX_CLIENTES], uint32_t * next_id_update, uint8_t minutos, uint8_t victorias, uint8_t *data){
    data[OFFSET_PACKET_FLAG]                     = FLAG_UPDATE_ESTADO_ROOM;
    (*(uint32_t*)&data[OFFSET_PACKET_ID_UPDATE]) = (*next_id_update)++;

    int offset_player = OFFSET_PACKET_PRIMER_CLIENTE;

    for(int i = 0; i < MAX_CLIENTES;i++){
        data[offset_player] = (Uint8) clientes[i]->activo;
        if(clientes[i]->activo){
            (*(uint16_t*)&data[offset_player + OFFSET_PACKET_ID_CLIENTE])  = clientes[i]->id_cliente;
            data[offset_player + OFFSET_PACKET_ID_PLAYER] = clientes[i]->id_player;
            memcpy(&data[offset_player + OFFSET_PACKET_NICK_NAME] , clientes[i]->nick_name,MAX_NICK);
        }
        offset_player+=TAM_PACKET_BYTES_CLIENTE;

    }
}

int aceptarNuevoCliente(
        ServidorNameSpace::ClienteConectado * clientes[MAX_CLIENTES],
        TCPsocket server,
        bool mIsPlayerActivado[Player::N_PLAYERS],
        bool mIsPlayerAsignadoCliente[Player::N_PLAYERS],
        uint8_t mapaEscogido[MAX_NOMBRE_MAPA],
        uint16_t * next_id_cliente,
        Uint16 mUDPPuerto,
        uint8_t minutos,
        uint8_t victorias
) {
    
    int index = 0;
    for(index = 0;  index <MAX_CLIENTES; index++){
        if(!clientes[index]->activo) break;
    }
    
    if(index == MAX_CLIENTES) return -1;
    
    TCPsocket psocket= SDLNet_TCP_Accept(server);
    if(psocket == nullptr) return -1;

    int id_player_no_asignado = 0;
    while(mIsPlayerActivado[id_player_no_asignado]&&
          !mIsPlayerAsignadoCliente[id_player_no_asignado] &&
          id_player_no_asignado<Player::N_PLAYERS){
        id_player_no_asignado++;
    };

    uint8_t pdata[MAX_TAM_TCP_PAQUETE];
    int num_recv;
    int result;

    // Tiene Mapa

    memcpy(pdata,mapaEscogido,MAX_NOMBRE_MAPA);
    result = SDLNet_TCP_Send(psocket, pdata, MAX_NOMBRE_MAPA);
    if(result < MAX_NOMBRE_MAPA) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        // It may be good to disconnect sock because it is likely invalid now.
        SDLNet_TCP_Close(psocket);
        return -1;
    }

    // Respuesta Tiene Mapa
    num_recv = recibirDatos(psocket, pdata, 1);
    if(num_recv <= 0){
        SDLNet_TCP_Close(psocket);
        return -1;
    }else{
        if(!pdata[0]){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"No tiene el mapa descargado! Sorry :(");
            SDLNet_TCP_Close(psocket);
            return -1;
        }
    }

    // Identificarse
    num_recv = recibirDatos(psocket, pdata, 8);
    if(num_recv <= 0){
        SDLNet_TCP_Close(psocket);
        return -1;
    }else{
        memcpy(clientes[index]->nick_name,pdata,MAX_NICK);
    }

    clientes[index]->id_cliente = (*next_id_cliente)++;
    clientes[index]->id_player = (IdPlayer) id_player_no_asignado;


    // Reconocer
    // Insertamos el id del cliente
    pdata[0] = minutos;
    pdata[1] = victorias;
    // Insertamos el id del player
    *((uint16_t *) &pdata[2]) = clientes[index]->id_cliente;

    for(int i = 0; i < Player::N_PLAYERS;i++){
        pdata[4+i]= (uint8_t) mIsPlayerActivado[i];
    }
    result = SDLNet_TCP_Send(psocket, pdata, 8);
    if(result<8) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        // It may be good to disconnect sock because it is likely invalid now.
        SDLNet_TCP_Close(psocket);
        return -1;
    }

    // Puerto UDP
    *((uint16_t *) &pdata) = mUDPPuerto;

    result = SDLNet_TCP_Send(psocket, pdata, 2);
    if(result<2) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        // It may be good to disconnect sock because it is likely invalid now.
        SDLNet_TCP_Close(psocket);
        return -1;

    }

    // Obtengo la IP address del socket tcp
    IPaddress * ipadress = SDLNet_TCP_GetPeerAddress(psocket);
    clientes[index]->updsocketipadress.host = ipadress->host;
    // Obtengo el Puerto UDP del socket udp del servidor
    num_recv = recibirDatos(psocket, pdata, 2);
    if(num_recv <= 0){
        SDLNet_TCP_Close(psocket);
        return -1;
    }else{
        // Asigno el puerto del socket udp del servidor a la estructura ipddress
        clientes[index]->updsocketipadress.port = *((uint16_t *) &pdata);
    }

    // Intenta enlazar la direccion del socket udp del cliente al channel usado en nuestro socket udp servidor
    // Que es donde se van a hacer las actualizaciones del estado del room

    SDLNet_TCP_Close(psocket);

    clientes[index]->activo = true;
    mIsPlayerAsignadoCliente[id_player_no_asignado] = true;
    char nombre[MAX_NICK + 1];
    memcpy(nombre,clientes[index]->nick_name,MAX_NICK);
    nombre[MAX_NICK] = '\0';
    //mpComponentTextoNickPlayer[index]->setText(nombre);


    return index;
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

void desconectar_cliente(ServidorNameSpace::ClienteConectado  * cliente){
    cliente->activo = false;
    //mpComponentTextoNickPlayer[clients[indice]->id_player]->setText("Esperando...");
}

int servidorEsperarConecciones(void *ptr){

    ServidorNameSpace::DatosConfiguracionServidor * datosConfiguracionServidor = (ServidorNameSpace::DatosConfiguracionServidor *) ptr;
    ServidorNameSpace::ClienteConectado * clients[MAX_CLIENTES];
    bool mIsPlayerActivado[Player::N_PLAYERS] {false};
    bool mIsPlayerAsignado[Player::N_PLAYERS] {false};

    int num_clientes = 0;
    int max_clientes = 0;

    uint16_t next_id_cliente = 0;
    uint32_t next_id_update  = 1;

    uint32_t id_updates_clientes[MAX_CLIENTES  - 1] {0};
    UDPpacket *mUDPPacketRecibir;
    LTimer mControlTimer[MAX_CLIENTES -1];

    for(int i = 0; i < MAX_CLIENTES;i++){
        clients[i] = new ServidorNameSpace::ClienteConectado();
        clients[i]->activo = false;
        mIsPlayerActivado[i] = datosConfiguracionServidor->isPlayerActivado[i];
        max_clientes += (mIsPlayerActivado[i])?1:0; //Yes, Boolean es un subconjunto de INT en c++ LO sé
    }

    datosConfiguracionServidor->estado =ServidorNameSpace::CREANDO;

    IPaddress ip;

    Uint16 mUDPPuerto;

    if(SDLNet_ResolveHost(&ip, NULL, TCP_DEFAULT_PUERTO) == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDLNet_ResolveHost.%s",SDLNet_GetError());
        datosConfiguracionServidor->estado = ServidorNameSpace::ERROR_CREACION;
        return 0;
    }

    TCPsocket mTCPServerSocket = SDLNet_TCP_Open(&ip);
    if(mTCPServerSocket == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDLNet_TCP_Open.%s",SDLNet_GetError());
        datosConfiguracionServidor->estado = ServidorNameSpace::ERROR_CREACION;
        return 0;
    }

    UDPsocket mUDPServerSocket = SDLNet_UDP_Open(0);
    if(!mUDPServerSocket) {
        printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        datosConfiguracionServidor->estado = ServidorNameSpace::ERROR_CREACION;
        return 0;
    }else{

        IPaddress *address;

        address=SDLNet_UDP_GetPeerAddress(mUDPServerSocket,-1);
        if(!address) {
            printf("SDLNet_UDP_GetPeerAddress: %s\n", SDLNet_GetError());
            // do something because we failed to get the address
            datosConfiguracionServidor->estado = ServidorNameSpace::ERROR_CREACION;
            return 0;
        }
        else {
            // perhaps print out address->host and address->port
            mUDPPuerto = address->port;
            SDL_Log("Puerto asignado al udp servidor:%d.",mUDPPuerto);
        }
    }


    UDPpacket *mUDPPacketEnviar = SDLNet_AllocPacket(MAX_TAM_UPDATE_ROOM);
    if(!mUDPPacketEnviar) {
        printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        datosConfiguracionServidor->estado = ServidorNameSpace::ERROR_CREACION;
        SDLNet_TCP_Close(mTCPServerSocket);
        SDLNet_UDP_Close(mUDPServerSocket);
        return 0;
    }

    mUDPPacketRecibir = SDLNet_AllocPacket(10);
    if(!mUDPPacketRecibir) {
        printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        datosConfiguracionServidor->estado = ServidorNameSpace::ERROR_CREACION;
        SDLNet_TCP_Close(mTCPServerSocket);
        SDLNet_UDP_Close(mUDPServerSocket);
        SDLNet_FreePacket(mUDPPacketEnviar);
        return 0;
    }

    datosConfiguracionServidor->estado = ServidorNameSpace::ESPERANDO_CLIENTES;

    bool salir = 0;

    //while(!salir){
    while(!datosConfiguracionServidor->cerrar){

        
        int index_nuevo_cliente;
        if(num_clientes < max_clientes &&
                (index_nuevo_cliente = aceptarNuevoCliente(clients,mTCPServerSocket,mIsPlayerActivado,mIsPlayerAsignado,
                                                           datosConfiguracionServidor->mapa_escogido,
                                                           &next_id_cliente,mUDPPuerto,
                                                           datosConfiguracionServidor->minutos,
                                                           datosConfiguracionServidor->victorias)) > 0){

            enviar_estado_room_clientes(clients,&next_id_update, datosConfiguracionServidor->minutos, datosConfiguracionServidor->victorias,mUDPServerSocket,mUDPPacketEnviar);
            num_clientes++;
            mControlTimer[index_nuevo_cliente].start();
        }

        if(SDLNet_UDP_Recv(mUDPServerSocket,mUDPPacketRecibir)) {
            switch (mUDPPacketRecibir->data[OFFSET_PACKET_FLAG]) {
                case FLAG_KEEP_ALIVE: {
                    uint16_t id_cliente = mUDPPacketRecibir->data[1];
                    for(int i = 1; i < MAX_CLIENTES;i++){
                        if(clients[i]->activo && clients[i]->id_cliente == id_cliente){
                            mControlTimer[i-1].start();
                            id_updates_clientes[i - 1] = mUDPPacketRecibir->data[3];
                            SDL_Log("FLAG_KEEP_ALIVE %d",id_cliente);
                        }
                    }

                }
                    break;
                case FLAG_DISCONNECT:
                    for(int i = 1; i < MAX_CLIENTES;i++){
                        if(clients[i]->activo && clients[i]->id_cliente == mUDPPacketRecibir->data[1]){
                            desconectar_cliente(clients[i]);
                            num_clientes--;
                            SDL_Log("FLAG_DISCONNECT %d",mUDPPacketRecibir->data[1]);
                        }
                    }
                    break;
            }
        }

        for(int i = 1; i < MAX_CLIENTES;i++){
            if(clients[i]->activo){
                if(mControlTimer[i-1].getTicks() >= TIMEOUT_DISCONECT_CLIENT) {
                    SDL_Log("Timeout %d",clients[i]->id_cliente);
                    desconectar_cliente(clients[i]);
                    num_clientes--;
                }
            }
        }

    }

    for(int i=0; i<MAX_CLIENTES; ++i) {
        delete clients[i];
    }
    SDLNet_TCP_Close(mTCPServerSocket);
    SDLNet_UDP_Close(mUDPServerSocket);
    SDLNet_FreePacket(mUDPPacketEnviar);
    SDLNet_FreePacket(mUDPPacketRecibir);
    datosConfiguracionServidor->estado = ServidorNameSpace::CERRADO;
    return 1;
}
