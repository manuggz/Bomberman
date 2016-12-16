#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../util/galeria.hpp"
#include "../interfaces/InterfazUI.hpp"
#include "../../util/constantes.hpp"
#include "../util/util.hpp"
#include "../interfaces/PopUpInterfaz.hpp"
#include <ctime>
#include <deque>
#include <stack>

class GameManager : public GameManagerInterfazUI{
    public:

    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    GameManager(std::string caption,std::string ruta_icono = "", unsigned int witdth=320,unsigned int height = 240,bool pantallaCompleta = false);
    void iniciarLibreriaSDL();
    void establecerModoDeVideo(bool pantalla_completa = false);
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
    // Volumen 0-128
    void playSound(Mix_Music *music,Uint8 volumen);

    void play(Mix_Chunk *pSfxChunk) override;
    void playFadeInSound(Mix_Music *music, Uint8 volumen);

private:
    stack<InterfazUI *> interfaces; // Pila de interfaces
    InterfazUI * interfaz_actual = nullptr;
    SDL_Window *mMainWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;

    Galeria * mpGaleria = nullptr;

    SDL_Joystick *joysticks[_PLAYERS] {nullptr};

    bool mIniciadoModuloSonido=false;
    int joys_act = 0;
    bool salir_juego = false;
    //FPSmanager fpsm;
    int mWidth = 0;
    int mHeight = 0;

    PopUpInterfaz * mpPopUp = nullptr;
    void *mpResultPopUp = nullptr;
    // IDentificador del Actual PopUp
    // USado para identificar en el codigo cual es el popup que se cerró
    int mIDCodePopUp;
    string mCaption;
    string mRutaIcono;

    bool cargarTexturas(string rutaTexturas);

    bool cargarSonidos(string rutaSonidos);

    bool mPantallaCompleta = false;

    int mChannels = 5;
    int mJoysticksActivos = 5;

};
#endif
