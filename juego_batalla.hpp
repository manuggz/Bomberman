#ifndef JUEGO_BATALLA_HPP
#define JUEGO_BATALLA_HPP
#include "time.hpp"
#include "player.hpp"
//#include "globo.hpp"
#include "engine/util/game_manager.hpp"
#include "item.hpp"
#include "explosion.hpp"
#include "bomba.hpp"
#include "mapa.hpp"
#include "juego.hpp"
#include "menu.hpp"
#include "juego_mostrar_gan.hpp"
//#define DEBUG

class Juego;

class JuegoBatalla:public Juego{
    public:
        JuegoBatalla(GameManager * game,int idTerrenoBatalla,bool playerEnBatalla[_PLAYERS],int minutos,int victorias);
        void crearReferencias();
        void setMapaPlay(int idTerreno,bool comprobar_players=true);
        void estadoPlay();

    virtual bool isPaused() override;

    virtual void pause() override;

    virtual void resume() override;


    void salir();
        int getTipoNuevoItem(bool hacerComprobaciones=true);
        InterfazJuego getTipoJuego(){return TIPO_BATALLA;};
//        void aumentarNivel();
        void drawBarra(SDL_Renderer * );
        ~JuegoBatalla();
    private:
        int idTerrenoActual;
        int batallasGanadas[_PLAYERS];
        IdPlayer id_lider_ganadas;
        bool muertosPorTiempo;
        bool repro_war,iniciado;
        int vic,min;
};

#endif
