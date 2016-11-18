#ifndef WORLD_HPP
#define WORLD_HPP
//#define DEBUG
#include <iostream>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_framerate.h>		// SDL_gfx Framerate Manager
#include "galeria.hpp"
#include "interfaz.hpp"
#include "constantes.hpp"
#include "util.hpp"
#include <ctime>

using namespace std;

class GameManager{
    public:
        GameManager();
        void iniSDL();
        void setModeVideo(bool pantalla_completa=false);
        void activarJoysticks();
        SDL_Joystick * getJoy(int id);
        int getJoysActivos();
        void cambiarInterfaz(Interfaz * nueva);
        int procesarEventos();
        void run();
        void quit(){salir=true;};
        void play(CodeMusicEfecto code);
        void playSonido(CodeMusicSonido code);
        SDL_Surface * getImagen(CodeImagen code);
        ~GameManager();

    private:
        Interfaz * inter,* interfaz_last;
        SDL_Window *screen;
        SDL_Renderer *ren;
        Galeria * galeria;
        SDL_Joystick *joysticks[_PLAYERS];

        bool snd_disponible;
        int joys_act;
        bool salir;
        //FPSmanager fpsm;
};
#endif
