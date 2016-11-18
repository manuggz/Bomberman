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
        ControlPlayer(bool ini=false);
        void iniciar();
        bool cargar(char ruta[],bool ini=true);
        void guardar(char ruta[]);
        char * getName(TeclaPlayer tecla);
        bool isBotonJoystick(TeclaPlayer tecla);
        bool isDireccionJoystick(int tecla);
        SDL_Keycode getKey(TeclaPlayer tecla);
        void setName(TeclaPlayer tecla,const char name[]);
        void setIsBotonJoystick(TeclaPlayer tecla,bool nuevo);
        void setIsDireccionJoystick(int tecla,bool nuevo);
        void setKey(TeclaPlayer tecla,SDL_Keycode nuevo);
        void setDefaultKeys(IdPlayer id);
        
    private:
        char nombres_joysticks[_TECLAS][100];
        bool es_boton_joystick[_TECLAS];
        bool es_direccion_joystick[_TECLAS];

        SDL_Keycode keys_players[_TECLAS];
};
#endif
