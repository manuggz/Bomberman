//
// Created by manuggz on 10/01/17.
//

#ifndef ENGINE_SOUNDEFFECT_HPP
#define ENGINE_SOUNDEFFECT_HPP

#include <string>
//#include <iostream>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class EfectoSonido{
public:
    EfectoSonido(std::string path,int volumen){
        mPath      = path;
        mpRawChunk = Mix_LoadWAV(path.c_str());
        if(mpRawChunk != nullptr){
            std::cout << "+ Efecto de Sonido Cargado: "<<path<<std::endl;
            Mix_VolumeChunk(mpRawChunk, volumen);
        }else{
            std::cerr<<" - [ERROR] Cargando Efecto de Sonido:"<<path<<Mix_GetError()<<std::endl;
        }
    }
    ~EfectoSonido(){
        Mix_FreeChunk(mpRawChunk);
    }

    void play(int channel = -1,int loops = 0) {
        Mix_PlayChannel(channel,mpRawChunk,loops);
    }

private:
    Mix_Chunk * mpRawChunk;
    std::string mPath;
};
#endif //BOMBERMAN_SOUNDEFFECT_HPP
