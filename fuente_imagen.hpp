#ifndef FUENTE_IMAGEN_HPP
#define FUENTE_IMAGEN_HPP
#include <SDL2/SDL.h>
#include "util.hpp"

const int MAX_LETRAS_RECONOCIDAS=200;

class FuenteImagen{
    public:
        FuenteImagen(SDL_Surface *imagen,char orden[]);
        void draw (SDL_Surface * screen, int x, int y, char * cadena);
    private:
        SDL_Surface * ima;
        SDL_Rect fuentes[MAX_LETRAS_RECONOCIDAS];
        char ordenLetras[MAX_LETRAS_RECONOCIDAS];
        bool esColumnaVacia(int columna);
        void identificarRects ();
        int obtener_indice (char caracter);
        int imprimir_letra (SDL_Surface * dst,int x, int y, char letra);
};
#endif
