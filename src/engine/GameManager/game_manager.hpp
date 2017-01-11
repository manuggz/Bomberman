#ifndef ENGINE_GAME_MANAGER_HPP
#define ENGINE_GAME_MANAGER_HPP

#include <ctime>
#include <deque>
#include <stack>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../interfaces/InterfazGrafica.hpp"
#include "../interfaces/PopUpInterfaz.hpp"

#include "../util/LTimer.hpp"
#include "../util/util.hpp"


/**
 *
 * <h1> Administra el Juego</h1>
 *
 * Se encarga de manejar la interacción entre las llamadas a SDL y las peticiones de las interfaces.
 *
 * Una Interfaz(@link InterazUI) es aquella que interactua con el usuario así mismo lo hace un Pop Up.

 * Esta clase se encarga:
 *  <ul>
 *      <li> Interacciones entre Interfaces</li>
 *      <li> Interaccion entre Interfaz y PopUp</li>
 *      <li> Interacciones entre Interfaz/PopUp y llamadas a SDL(Sonido,Joystick,Eventos)</li>
 *      <li> Interacciones entre Eventos del Usuario(Salir) e Interfaces</li>
 *  </ul>
 *
 *  Deriva de {@link GameManagerInterfazUI} que basicamente es un Contrato entre la interfaz y el Game Manager.
 *  Un conjunto de funciones que esta clase debe implementar para que una interfaz pueda referenciarla.
 *  Ya que una Interfaz referencia una instancia de {@link GameManagerInterfazUI}.
 *  (Esto es para evitar problemas de doble referenciacion)

 *  @author Manuel González <manuelggonzalezm@gmail.com>
 *
 *
 */
class GameManager : public GameManagerInterfazUI{

public:


    GameManager(std::string caption,std::string ruta_icono, unsigned int witdth,unsigned int height,bool pantallaCompleta);

    SDL_Joystick * getJoy(int id) ;
    int getActiveJoys() ;
    void cambiarInterfaz(InterfazGrafica * nueva) ;

    void run();
    void quit(){salir_juego=true;};

    int getWidth();
    int getHeight();

    ~GameManager();

    void goBack() ;

    void setRoot(InterfazGrafica *nuevaInterfazRoot) ;

    SDL_Rect getRectScreen() ;

    void closePopUp(void * result = nullptr) ;

    void showPopUp(PopUpInterfaz *pPopUp,int showPopUp) ;
    // Volumen 0-128
    void playSound(Mix_Music *music,Uint8 volumen) ;

    void play(Mix_Chunk *pSfxChunk) ;
    void playFadeInSound(Mix_Music *music, Uint8 volumen) ;

private:

    int mFPS = 60;
    int mScreenTicksPerFrame = 1000 / mFPS;

    std::stack<InterfazGrafica *> interfaces; // Pila de interfaces
    InterfazGrafica * interfaz_actual = nullptr;
    SDL_Window *mMainWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;

    SDL_Joystick *joysticks[5] {nullptr};

    bool mIniciadoModuloSonido=false;
    int joys_act = 0;
    bool salir_juego = false;

    int mWidth = 0;
    int mHeight = 0;

    PopUpInterfaz * mpPopUp = nullptr;
    void *mpResultPopUp = nullptr;
    // IDentificador del Actual PopUp
    // USado para identificar en el codigo cual es el popup que se cerró
    int mIDCodePopUp;
    std::string mCaption;
    std::string mRutaIcono;

    int mChannels = 5;
    int mJoysticksActivos = 5;


    bool mPantallaCompleta = false;


    void iniciarLibreriaSDL();
    void establecerModoDeVideo(bool pantalla_completa = false);
    void activarJoysticks();
    bool procesarEventos();
};
#endif
