#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP
#include <SDL2/SDL.h>
#include "constantes.hpp"
#include "Interfaces/juego.hpp"
#include "engine/sprites/animacion/animacion.hpp"

class Juego;
class Explosion:public Animacion{
   public:
        Explosion(Juego * juego,int x,int y,int alcance_llamas,int lanzador,int id);
        void draw(SDL_Renderer * gRenderer);
        bool colision(SDL_Rect & rect_coli);
    private:
        Juego * juego;
        int alcance_llamas;//alcance que logran en los ejes
        int lanzador;
        Uint8 alcances[4];//alcances en los ejes
        
        void dibujarFlama(int dir,int aum_x,int aum_y,int cuadro_normal,int cuadro_final,SDL_Renderer * gRenderer);
        void detectarAlcance(int dir,int aum_x,int aum_y);
};

#endif
