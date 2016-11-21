#ifndef WORLD_HPP
#define WORLD_HPP
//#define DEBUG
#include <iostream>
#include <SDL2/SDL.h>
#include "../../galeria.hpp"
#include "../interfaces/interfaz.hpp"
#include "../../constantes.hpp"
#include "../../util.hpp"
#include <ctime>
#include <deque>
#include <stack>

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
    LTexture * getImagen(CodeImagen code);
    int getWidth();
    int getHeight();

    ~GameManager();


    void popInterface();

private:
    stack<Interfaz *> interfaces; // Pila de interfaces
    Interfaz * interfaz_actual;
    SDL_Window *screen;
    SDL_Renderer *gRenderer;
    Galeria * galeria;
    SDL_Joystick *joysticks[_PLAYERS];

    bool snd_disponible;
    int joys_act;
    bool salir_juego;
    //FPSmanager fpsm;
    int mWidth;
    int mHeight;

};
#endif
