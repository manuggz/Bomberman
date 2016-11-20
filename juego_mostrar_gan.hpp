#ifndef JUEGOMOSTRARGANADAS_HPP
#define JUEGOMOSTRARGANADAS_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include "constantes.hpp"
#include "juego_batalla.hpp"
#include "engine/util/game_manager.hpp"
#include "engine/interfaces/interfaz.hpp"

//#define DEBUG


class GameManager;
class JuegoBatalla;
using namespace std;

class JuegoMostrarGanadas:public Interfaz{
      public:
        JuegoMostrarGanadas(GameManager * game,JuegoBatalla * parent,int batallasGanadas[_PLAYERS]);
        void procesarEvento(SDL_Event * evento);
        void update();
        void draw(SDL_Renderer * );

    virtual void start(SDL_Renderer *renderer) override;

    void crearTexturas(SDL_Renderer * );
        void salir();
        ~JuegoMostrarGanadas();

    virtual bool isPaused() override;

    virtual void pause() override;

    virtual void resume() override;

private:
        GameManager * game;
        JuegoBatalla * juegoEnCurso;
        SDL_Texture * fondoJuego,*fondoNegro;
        Animacion * animaCuadro;
        Animacion * animaTexto,**animaTrofeos;
        
        int batallasGanadas[_PLAYERS];
        int conteo;
        int animacion;
        int totalTrofeosCreados;
};

#endif
