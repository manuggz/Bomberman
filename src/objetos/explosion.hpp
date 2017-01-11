#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP
#include <SDL2/SDL.h>
#include "../engine/sprites/animacion/animacion.hpp"
#include "../util/constantes.hpp"
#include "../Interfaces/juego/ModoJuegoMultiPlayer.hpp"

class ModoJuegoMultiPlayer;
class Explosion:public Animacion{
public:

    Explosion(ModoJuegoMultiPlayer * juego,SDL_Renderer * gRenderer, Player * playerLanzador);
    void draw(SDL_Renderer * gRenderer);
    bool colision(SDL_Rect & rect_coli);

    void detectarAlcances();

    Player *getCreador();

private:

    enum {
        DERECHA,
        IZQUIERDA,
        ABAJO,
        ARRIBA,
    };
    //Juego * juego;
    //int alcance_llamas;//alcance que logran en los ejes
    //int lanzador;
    Uint8 alcances[4] {0};//alcances en los ejes

    void dibujarFlama(int dir,int aum_x,int aum_y,int cuadro_normal,int cuadro_final,SDL_Renderer * gRenderer);
    void detectarAlcance(int dir,int aum_x,int aum_y);

    Player *        mPlayerCreador = nullptr;
    ModoJuegoMultiPlayer * mJuego = nullptr;
    int mAlcanceLlamas = 0;

};

#endif
