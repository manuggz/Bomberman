#ifndef GALERIA_HPP
#define GALERIA_HPP
//#define DEBUG
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "constantes.hpp"
#include "util.hpp"

using namespace std;

class Galeria{
      public:
        Galeria();
        SDL_Surface * getImagen(CodeImagen code){
            return baulimgs[code];  /*SIN IMPLEMENTAR*/
        };
        Mix_Chunk * getMusicEfecto(CodeMusicEfecto code){
            if(!sonidoCargado)return NULL;
            return sfx_efectos[code];
        };
        Mix_Music * getMusicSonido(CodeMusicSonido code){
            if(!sonidoCargado)return NULL;
            return snd_musicas[code];
        };
        ~Galeria();
        void cargarSonidos();
      private:
        bool sonidoCargado;
        SDL_Surface  * baulimgs[_IMAGENES];
        Mix_Chunk *sfx_efectos[_EFECTOS];
        Mix_Music *snd_musicas[_SONIDOS];

};

#endif
