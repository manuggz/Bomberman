#ifndef WORLD_HPP
#define WORLD_HPP
//#define DEBUG
#include <iostream>
#include <SDL2/SDL.h>
#include "../../galeria.hpp"
#include "../interfaces/InterfazUI.hpp"
#include "../../constantes.hpp"
#include "../../util.hpp"
#include "../interfaces/PopUpInterfaz.hpp"
#include <ctime>
#include <deque>
#include <stack>

using namespace std;

class GameManager : public GameManagerInterfazUI{
    public:

    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    GameManager();
    void iniciarSDL();
    void setModeVideo(bool pantalla_completa=false);
    void activarJoysticks();
    SDL_Joystick * getJoy(int id);
    int getActiveJoys();
    void cambiarInterfaz(InterfazUI * nueva);
    bool procesarEventos();
    void run();
    void quit(){salir_juego=true;};
    void play(Galeria::CodeMusicEfecto code) override ;
    void playSound(Galeria::CodeMusicSonido code) override ;
    LTexture * getTexture(Galeria::CodeImagen code) override ;
    int getWidth();
    int getHeight();

    ~GameManager();


    void goBack();

    void setRoot(InterfazUI *nuevaInterfazRoot);

    SDL_Rect getRectScreen() override;

    void closePopUp(void * result = nullptr) override;

    void showPopUp(PopUpInterfaz *pPopUp,int showPopUp);

private:
    stack<InterfazUI *> interfaces; // Pila de interfaces
    InterfazUI * interfaz_actual;
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

    PopUpInterfaz * mpPopUp = nullptr;
    void *mpResultPopUp = nullptr;
    // IDentificador del Actual PopUp
    // USado para identificar en el codigo cual es el popup que se cerró
    int mIDCodePopUp;
};
#endif
