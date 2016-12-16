#ifndef COMMON_H
#define COMMON_H

#define _TIME_POR_NIVEL 200

#define DELAY_PROTECCCION  300
#define DELAY_PARPADEO 17
#define REPETICION 2
#define RETRASO_CAMBIO 2
#define MAX_BOMBAS 10
#define MAX_ALCANCE_EXPLOSION 12
#define FILAS_EXPLO 5
#define COLUMNAS_EXPLO 8
#define STR_NORMAL "0123456789abcdefghijklmnopqrstuvwxyz"
#define STR_ESTENDIDA "0123456789abcdefghijklmnopqrstuvwxyz.`+�-,�-<���*/"
#define STR_MAX_ESTENDIDA "0123456789abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZáéíóúÁÉÍÓÚ!¡..·$%&/()=?¿ç|@#~¬{}´Ç`+.-,<>:;_ÄËÏÖÜäëïöü*^[]"


#define DELAY_CAMBIO 2
#define MAX_NIVEL 16

//#define W_H_BLOQUE 16
//#define W_SCREEN  320
//#define H_SCREEN  240

#define _PLAYERS 5


//coordenadas por default
#define X_INIT_PLAYER_1 25
#define Y_INIT_PLAYER_1 50

#define X_INIT_PLAYER_2 270
#define Y_INIT_PLAYER_2 50

#define X_INIT_PLAYER_3 25
#define Y_INIT_PLAYER_3 208

#define X_INIT_PLAYER_4 270
#define Y_INIT_PLAYER_4 208

#define X_INIT_PLAYER_5 161
#define Y_INIT_PLAYER_5 110

#define RUTA_CONFIG_BASE "data/configuracion/inf"

#define NAME_MAX_TERRENO_BATALLA "MaxTerreno"
#define NIVEL_BASE -1


enum TeclaPlayer{
    TECLA_ARRIBA,
    TECLA_ABAJO,
    TECLA_IZQUIERDA,
    TECLA_DERECHA,
    TECLA_ACCION,
    TECLA_START,
//    TECLA_ACCION_2,
    _TECLAS,
    TECLA_NULA=-1
};

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


enum{
    EDITOR_BOTON_FLECHA=0,
    EDITOR_BOTON_GUARDAR=1,
    EDITOR_BOTON_MAS=0,
    EDITOR_BOTON_MENOS=1,
    
    EDITOR_MODIF_BOMBA=1,
    EDITOR_MODIF_EXPLOSION=2,
    EDITOR_MODIF_VIDAS=3,
    EDITOR_MODIF_ITEMS=4,

    EDITOR_FLECHA_IZQUIERDA=0,
    EDITOR_FLECHA_DERECHA=1,
    EDITOR_MAPA_1=2,
    EDITOR_MAPA_2=3,

    EDITOR_ABRIR_NIVEL=0,
    EDICION_NIVEL=1
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

enum{
    VENTANA_1=0,
    VENTANA_2=1,
    VENTANA_3=2,
    VENTANA_4=3,
    VENTANA_CREDITOS=4,
    
    MENU_TECLA_ARRIBA=0,
    MENU_TECLA_ABAJO=1,
    MENU_TECLA_IZQUIERDA=2,
    MENU_TECLA_DERECHA=3,
    MENU_TECLA_ACCION=4,
    MENU_TECLA_START=5,
    
    MENU_BOTON_CAMBIAR=0,
    MENU_CUADRO_MOSTRAR,
    MENU_TEXTO_MOSTRAR,
    
};

typedef enum Estados_boton{
    BOTON_NORMAL,
    BOTON_RESALTADO,
    BOTON_PRESIONADO
}Estados_boton;

/*
typedef enum Escenas{
    JUEGO,
    EDITOR,
    MENU,
    CARGANDO,
    CREDITOS
}Escenas;*/


/*
typedef enum Interfaz_menu{
    TEXTOS,
    MULTIJUGADORES,
    CONEXION,
    CONFIGURACION
}Interfaz_menu;*/

typedef enum{
    PLAY,//estado_actual del juego activo
    PAUSA,//estado_actual pausado
    GAME_OVER,//estado_actual del juego terminado
    DELAY,//estado_actual en el que solo de llama a 'Flip' y se actualiza el conteo para salirJuego y pasar a 'estado_siguiente'
    DISPLAY_MSG,//estado_actual mostrando un mensage, en el que se actualiza la animacion en 'ciclo_logico'
    NONE
}EstadoJuego;

enum IdPlayer{
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    PLAYER_5,
    PLAYER_NONE=-1
};

#endif
