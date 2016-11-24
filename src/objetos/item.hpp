#ifndef ITEM_HPP
#define ITEM_HPP
#include <SDL2/SDL.h>
#include "../engine/sprites/animacion/animacion.hpp"
//#include "Interfaces/juego.hpp"
#include "../constantes.hpp"

class Juego;

class Item:public Animacion{
    public:

        enum {
            ITEM_BOMBA,
            ITEM_ALCANCE,
            ITEM_BOMBA_MAX,
            ITEM_ALCANCE_MAX,
            ITEM_ATRAVIESA_BOMBAS,
            ITEM_MUERTE,
            ITEM_PROTECCION,
            ITEM_CONTROLA_BOMBA,
            ITEM_ATRAVIESA_PAREDES,
            ITEM_PATINETA,
            ITEM_PATEA_BOMBA,
            ITEM_BOLA_ARROZ,
            ITEM_GUANTE,
            ITEM_PUERTA,
            ITEM_VIDA,
            ITEM_RELOJ,
            ITEM_CORAZON,
            ITEM_PASTEL,
            ITEM_ALEATORIO,
            ITEM_MARTILLO,
            ITEM_MANZANA,
            ITEM_EXTINGUIDOR,
            ITEM_PALETA,
            ITEM_BARQUILLA    
        };

        Item(Juego * juego,int x,int y, int tipo,int id);
        int getTipoItem(){return tipo;};   
        void draw(SDL_Renderer * gRenderer);
    private:
        Juego * juego;
        int tipo;
};

#endif
