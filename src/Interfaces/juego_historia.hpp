#ifndef JUEGO_HISTORIA_HPP
#define JUEGO_HISTORIA_HPP
#include "../time.hpp"
#include "../player.hpp"
//#include "globo.hpp"
#include "../engine/util/game_manager.hpp"
#include "../item.hpp"
#include "../explosion.hpp"
#include "../bomba.hpp"
#include "../mapa.hpp"
#include "juego.hpp"
#include "../menu.hpp"
//#define DEBUG
/*
class Juego;

class JuegoHistoria:public Juego{
    public:
        JuegoHistoria (GameManager * game);

//        void crearReferencias();
        void setMapaPlay(int id_nivel,bool reiniciar_jugadores=false);
        void estadoPlay();
        void salir();
        InterfazJuego getTipoJuego(){return TIPO_NORMAL;};
        void aumentarNivel();
        void drawBarra(SDL_Renderer * gRenderer);
        ~JuegoHistoria();

    virtual bool isPaused() override;

    virtual void pause() override;

    virtual void resume() override;

private:
        bool repro_war; /*True si se esta reproduciendo el sonido de advertencia de poco tiempo
};
*/
#endif
