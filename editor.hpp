#ifndef EDITOR_HPP
#define EDITOR_HPP
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "interfaz.hpp"
#include "game_manager.hpp"
#include "control_player.hpp"
#include "constantes.hpp"
#include "util.hpp"
#include "dat_nivel.hpp"
#include "mapa.hpp"
#include "menu.hpp"
#include "CBoton.hpp"
//#define DEBUG

using namespace std;

class Editor:public Interfaz{
      public:
             Editor(GameManager * game);
            void cambiarVentana(int nueva);
            void cambiarPagina(unsigned int num_pagina);
            void iniciarEdicion(int id);
            void update(void){return;};
            bool EditPointMap(SDL_Event * evento);
            void guardarMapa();
            void borrarMapa();
            void procesarEvento(SDL_Event * evento);
            void draw(SDL_Surface * screen);
            ~Editor();
      private:
            GameManager * game;
            DatNivel * data;
            int ventana;
        
//            para el editor como tal
            SDL_Rect rects_botones[5][2];
            Estados_boton estados_botones[5][2];
        
            int tile_activo;
            IdPlayer player_activo;
            bool mantiene_presionado;
            int id_nivel;
        
            char mapa[Mapa::MAXMAP + 1];
        
            //para la especie de ventana donde se escoge al nivel a editar
            SDL_Rect rects_botones_elegir_terreno[4];
            Estados_boton estados_botones_elegir_terreno[4];
            bool boton_visible[4];
            
            SDL_Surface ** previews_niveles;
            int maxTerrenoBatalla;
            int pagina;
            
            Boton<Editor> botonBorrar;

            int EjeX,EjeY,yTablero,idFondo;
            
            void crearReferencias();
            void leerInfTile();
};

#endif
