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

        const int SCREEN_FPS = 60;
        const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
        GameManager();
        void iniciarSDL();
        void setModeVideo(bool pantalla_completa=false);
        void activarJoysticks();
        SDL_Joystick * getJoy(int id);
        int getJoysActivos();
        void cambiarInterfaz(Interfaz * nueva);
        bool procesarEventos();
        void run();
        void quit(){salir_juego=true;};
        void play(CodeMusicEfecto code);
        void playSonido(CodeMusicSonido code);
        SDL_Texture * getImagen(CodeImagen code);
        ~GameManager();

    SDL_Renderer *getRenderer();

private:
        Interfaz * interfaz_actual,* interfaz_anterior;
        SDL_Window *screen;
        SDL_Renderer *gRenderer;
        Galeria * galeria;
        SDL_Joystick *joysticks[_PLAYERS];

        bool snd_disponible;
        int joys_act;
        bool salir_juego;
        //FPSmanager fpsm;
};
#endif
