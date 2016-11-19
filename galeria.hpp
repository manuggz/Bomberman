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
        SDL_Texture * getImagen(CodeImagen code){
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
        void cargarTexturas(SDL_Renderer * gRenderer);
        void cargarSonidos();
        ~Galeria();
      private:
        bool sonidoCargado;
        SDL_Texture  * baulimgs[_IMAGENES];
        Mix_Chunk *sfx_efectos[_EFECTOS];
        Mix_Music *snd_musicas[_SONIDOS];

};

#endif
