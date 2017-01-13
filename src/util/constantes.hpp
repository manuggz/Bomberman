#ifndef COMMON_H
#define COMMON_H



enum TipoSprite{
    GLOBO,
    EXPLOSION,
    ITEM,
    BOMBA,
    PLAYER,
    BLOQUE,
    ANIMACION,
    _REFERENCIADOS,
    NIVEL,
};


enum EstadoSprite{
    DERECHA, 
    IZQUIERDA,
    ABAJO,
    ARRIBA,
    MURIENDO,
    _ESTADOS_ANIMACION,
    PARADO,
    NINGUNO,
};


typedef enum Estados_boton{
    BOTON_NORMAL,
    BOTON_RESALTADO,
    BOTON_PRESIONADO
}EstadoBoton;

enum IdPlayer{
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    PLAYER_5,
    PLAYER_NONE=-1
};

#endif
