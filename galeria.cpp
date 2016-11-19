#include "galeria.hpp"
#include "LTexture.hpp"


Galeria::Galeria(){
    #ifdef DEBUG
    cout << "Constructor de galeria:"<<this<<endl;
    #endif

    sonidoCargado=false;

}

void Galeria::cargarTexturas(SDL_Renderer * gRenderer){
    string ruta;
    bool keyColor;

    ifstream filePar("data/configuracion/images.txt");
    if(!filePar)
        mostrar_error_salir("No se pudo abrir archivo con RUTAS DE IMAGENES");

    for(int j=0;j<_IMAGENES;j++){
        filePar >>ruta;
        filePar >>keyColor;
        baulimgs[j] = new LTexture();
        baulimgs[j]->loadFromFile(ruta,gRenderer,keyColor);
        cout << "Cargando textura: " << ruta <<endl;
    }
    filePar.close();

}

void Galeria::cargarSonidos(){
    char ruta_tmp[50];
    if(!sonidoCargado){
         for(int i=0;i<_SONIDOS;i++){
                sprintf(ruta_tmp,"data/sonidos/musica_%d.mid",i+1);
                snd_musicas[i]=cargar_musica(ruta_tmp);
            }
    
    
    
         for(int i=0;i<_EFECTOS;i++){
                sprintf(ruta_tmp,"data/sonidos/ping_%d.wav",i+1);
                sfx_efectos[i]=cargar_sonido(ruta_tmp);
                Mix_VolumeChunk(sfx_efectos[i], 100);
            }
    
        Mix_VolumeMusic(128);
        sonidoCargado=true;
    }
    
}

Galeria::~Galeria(){
    #ifdef DEBUG
    cout << "Destructor de galeria:"<<this<<endl;
    #endif

    for(int i=0;i<_IMAGENES;i++){
        baulimgs[i]->free();
        delete baulimgs[i];
    }

    if(sonidoCargado){
         for(int i=0;i<_SONIDOS;i++)Mix_FreeMusic(snd_musicas[i]);
         for(int i=0;i<_EFECTOS;i++)Mix_FreeChunk(sfx_efectos[i]);
    }
}

