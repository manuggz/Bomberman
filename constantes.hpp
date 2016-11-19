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
#define STR_MAX_ESTENDIDA "0123456789abcdefghijklmn�opqrstuvwxyzABCDEFGHIJKLMN�OPQRSTUVWXYZ����������!����$%&/()=?��|@#~�{}��`+.-,<>:;_����������*^[]"


#define DELAY_CAMBIO 2
#define MAX_NIVEL 16

//#define W_H_BLOQUE 16
#define W_SCREEN  320
#define H_SCREEN  240

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

#define RUTA_CONFIG_BASE "data/configuracion/inf.txt"

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
    _ESTADOS,
    PARADO
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
    
    MENU_NUEVO_JUEGO=0,    
    MENU_EDITOR=1,    
    MENU_CONFIGURACION=2,
    MENU_CREDITOS=3,
    MENU_SALIR=4,
    
    MENU_BOTON_SUBIR_TIEMPO=_PLAYERS,
    MENU_BOTON_SUBIR_VICTORIAS,
    MENU_BOTON_CAMBIAR_MAPA,
    MENU_BOTON_JUGAR,
    
    MENU_MODO_HISTORIA=0,
    MENU_MODO_MULTIJUGADOR,
    MENU_MODO_CONEXION,
    MENU_REGRESAR
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

typedef enum Interfaz_juego{
    TIPO_NORMAL,
    TIPO_BATALLA
}InterfazJuego;

/*
typedef enum Interfaz_menu{
    TEXTOS,
    MULTIJUGADORES,
    CONEXION,
    CONFIGURACION
}Interfaz_menu;*/

typedef enum{
    PLAY,//estado del juego activo
    PAUSA,//estado pausado
    GAME_OVER,//estado del juego terminado
    DELAY,//estado en el que solo de llama a 'Flip' y se actualiza el conteo para salirJuego y pasar a 'estado_siguiente'
    DISPLAY_MSG,//estado mostrando un mensage, en el que se actualiza la animacion en 'ciclo_logico'
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

/*
* 
*    CONSTANTES DE GALERIA
*/

typedef enum {
    SFX_COGER_ITEM,
    SFX_TONO_ACUATICO,
    SFX_TONO_SECO,
    SFX_CAMPANADA,
    SFX_EXPLOSION,
    SFX_ESTRANYO,    
    SFX_PIERDE_VIDA,
    _EFECTOS    
}CodeMusicEfecto;

typedef enum {
    SND_MENU=0,
    SND_EDITOR=1,
    SND_LEVEL_START=2,
    SND_WARNING_TIME=3,
    SND_IN_GAME_1=4,
    SND_IN_GAME_2=5,
    _SONIDOS
}CodeMusicSonido;

enum CodeImagen{
    IMG_GLOBO,
    IMG_PLAYER_1,
    IMG_PLAYER_2,
    IMG_PLAYER_3,
    IMG_PLAYER_4,
    IMG_PLAYER_5,
    IMG_PLAYER_1_MURIENDO,
    IMG_PLAYER_2_MURIENDO,
    IMG_PLAYER_3_MURIENDO,
    IMG_PLAYER_4_MURIENDO,
    IMG_PLAYER_5_MURIENDO,
    IMG_FONDO_MENU,
    IMG_FONDO_CREDITOS,
    IMG_FONDO_EDITOR_SELECT_FILE,
    IMG_FONDO_PARTI,
    IMG_FONDO_EDIFICIOS,
    IMG_FONDO_METAL,
    IMG_FONDO_NEGRO,
    IMG_FONDO_BLANCO,
    IMG_FUENTE_1,
    IMG_FUENTE_2,
    IMG_FUENTE_3,
    IMG_FUENTE_4,
    IMG_FUENTE_5,
    IMG_FUENTE_6,
    IMG_FUENTE_7,
    IMG_FUENTE_8,
    IMG_TXT_PUNTAJE,
    IMG_TXT_PRESIONA_START,
    IMG_TXT_TILES,
    IMG_TXT_ARRIBA,
    IMG_TXT_ABAJO,
    IMG_TXT_IZQUIERDA,
    IMG_TXT_DERECHA,
    IMG_TXT_ACCION,
    IMG_TXT_START,
    IMG_TXT_VICTORIAS,
    IMG_TXT_ACTIVADO,
    IMG_TXT_PLAYERS_EN_BATALLA,
    IMG_TXT_PRESIONA_ACCION,
    IMG_TXT_PRESIONA,
    IMG_TXT_TIEMPO_POR_RONDA,
    IMG_TXT_SCOREBOARD,
    IMG_BOTON_ACTIVADO_DESACTIVADO,
    IMG_BOTON_JUGAR,
    IMG_BOTON_ESTRANIO,
    IMG_BOTON_CAMBIAR,
    IMG_BOTON_GUARDAR,
    IMG_BOTON_BORRAR_MAPA, //ad
    IMG_BOTON_FLECHA_PEQUE_DERECHA,
    IMG_BOTON_MAS,
    IMG_BOTON_MENOS,
    IMG_BOTON_FLECHA_GRANDE_IZQUIERDA,
    IMG_BOTON_FLECHA_GRANDE_DERECHA,
    IMG_BOTON_PLAYER_1,
    IMG_BOTON_PLAYER_2,
    IMG_BOTON_PLAYER_3,
    IMG_BOTON_PLAYER_4,
    IMG_BOTON_PLAYER_5,
    IMG_BOTON_CAMBIAR_MAPA,
    IMG_BOTON_JUGAR_2,
    IMG_TABLERO,
    IMG_BLOQUES_FIRE,
    IMG_ITEM_FIRE,
    IMG_GUI_INPUT_TEXT,
    IMG_TABLA_KILLS,
    IMG_CARAS_BOMBERMAN,
    IMG_CARAS_BOMBERMAN_GRANDES,
    IMG_BOMBA,
    IMG_ITEM,
    IMG_EXPLOSION,
    IMG_CUADRO_PEQUENIO,
    IMG_CUADRO_MEDIANO,
    IMG_CUADRO_GRANDE,
    IMG_LLAMA,
    IMG_BOMBA_PEQUE,
    IMG_CORAZON,
    IMG_PREGUNTA,
    IMG_TILES,
    IMG_TROFEO,
    IMG_CUADRO_SCOREBOARD,
    _IMAGENES
};
#endif
