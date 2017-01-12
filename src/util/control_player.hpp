#ifndef CONTROL_PLAYER_HPP
#define CONTROL_PLAYER_HPP
#include <iostream>
#include <fstream>
#include <string.h>
#include <SDL2/SDL.h>
#include "constantes.hpp"

using namespace std;

class ControlPlayer{
public:
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
    char guidJoystick[_TECLAS][100];
    bool es_boton_joystick[_TECLAS];
    bool es_direccion_joystick[_TECLAS];

    SDL_Keycode keyboardMapping[_TECLAS];
    Uint8 joybuttonMapping[_TECLAS];

    void reset();
};
#endif
