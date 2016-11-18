#ifndef JUEGOMOSTRARGANADAS_HPP
#define JUEGOMOSTRARGANADAS_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include "constantes.hpp"
#include "juego_batalla.hpp"
#include "game_manager.hpp"
#include "interfaz.hpp"

//#define DEBUG


class GameManager;
class JuegoBatalla;
using namespace std;

class JuegoMostrarGanadas:public Interfaz{
      public:
        JuegoMostrarGanadas(GameManager * game,JuegoBatalla * parent,int batallasGanadas[_PLAYERS]);
        void procesarEvento(SDL_Event * evento);
        void update();
        void draw(SDL_Surface * screen);
        void salir();
        ~JuegoMostrarGanadas();
    private:
        GameManager * game;
        JuegoBatalla * juegoEnCurso;
        SDL_Surface * fondoJuego,*fondoNegro;
        Animacion * animaCuadro;
        Animacion * animaTexto,**animaTrofeos;
        
        int batallasGanadas[_PLAYERS];
        int conteo;
        int animacion;
        int totalTrofeosCreados;
};

#endif
