#ifndef EDITOR_HPP
#define EDITOR_HPP
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "engine/interfaces/InterfazUI.hpp"
#include "engine/util/game_manager.hpp"
#include "control_player.hpp"
#include "constantes.hpp"
#include "util.hpp"
#include "engine/util/CMetaData.hpp"
#include "niveles/NivelMapa.hpp"
#include "menu.hpp"
#include "engine/layout/Componentes/BotonComponent.hpp"
//#define DEBUG

using namespace std;

class Editor:public InterfazUI{
//      public:
//             Editor(GameManager * game);
//            void cambiarVentana(int nueva);
//            void crearTexturas(SDL_Renderer *);
//            void cambiarPagina(unsigned int num_pagina);
//            void iniciarEdicion(int id);
//            void update(void){return;}
//
//    virtual bool isPaused() override;
//
//    virtual void pause() override;
//
//    virtual void resume() override;;
//            bool EditPointMap(SDL_Event * evento);
//            void guardarMapa();
//
//
//    void borrarMapa();
//            void procesarEvento(SDL_Event * evento);
//            void draw(SDL_Renderer * );
//            ~Editor();
//      private:
//            GameManager * game;
//            MetaData * data;
//            int ventana;
//
////            para el editor como tal
//            SDL_Rect rects_botones[5][2];
//            Estados_boton estados_botones[5][2];
//
//            int tile_activo;
//            IdPlayer player_activo;
//            bool mantiene_presionado;
//            int id_nivel;
//
//            //char mapa[Mapa::MAXMAP + 1];
//
//            //para la especie de ventana donde se escoge al nivel a editar
//            SDL_Rect rects_botones_elegir_terreno[4];
//            Estados_boton estados_botones_elegir_terreno[4];
//            bool boton_visible[4];
//
//            SDL_Texture ** previews_niveles;
//            int maxTerrenoBatalla;
//            int pagina;
//
//            BotonComponent<Editor> botonBorrar;
//
//            int EjeX,EjeY,yTablero,idFondo;
//
//            void crearReferencias();
//            void leerInfTile();
};

#endif
