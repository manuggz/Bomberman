#ifndef CONTROL_PLAYER_HPP
#define CONTROL_PLAYER_HPP
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "constantes.hpp"


class ControlPlayer{
public:
    enum TeclaPlayer{
        TECLA_ARRIBA,
        TECLA_ABAJO,
        TECLA_IZQUIERDA,
        TECLA_DERECHA,
        TECLA_ACCION,
        TECLA_START,
        TECLA_NULA=-1
    };
    static const int N_TECLAS = 6;

    ControlPlayer();
    bool cargar(char ruta[]);
    void guardar(char ruta[]);
    char * getJoystickGUID(TeclaPlayer tecla);
    bool isBotonJoystick(TeclaPlayer tecla);
    bool isDireccionJoystick(int tecla);
    SDL_Keycode getKey(TeclaPlayer tecla);
    void setJoystickGUID(TeclaPlayer tecla, const char *name);
    void setIsBotonJoystick(TeclaPlayer tecla,bool nuevo);
    void setIsDireccionJoystick(int tecla,bool nuevo);
    void setKeyboardMapping(TeclaPlayer tecla, SDL_Keycode nuevo);
    void setJoybuttonMapping(TeclaPlayer tecla,Uint8 nuevaTecla);
    Uint8 getJoybuttonMapping(TeclaPlayer tecla);
    void setDefaultKeys(IdPlayer id);

private:
    char guidJoystick[N_TECLAS][100];
    bool es_boton_joystick[N_TECLAS];
    bool es_direccion_joystick[N_TECLAS];

    SDL_Keycode keyboardMapping[N_TECLAS];
    Uint8 joybuttonMapping[N_TECLAS];

    void reset();
};
#endif
