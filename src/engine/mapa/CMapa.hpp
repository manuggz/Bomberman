//
// Created by manuggz on 22/11/16.
//

#ifndef BOMBERMAN_CMAPA_HPP
#define BOMBERMAN_CMAPA_HPP

#include <SDL2/SDL.h>
#include "include/TMXParser.h"
#include "../util/SpriteSheet.hpp"

class Mapa{

public:

    Mapa() = default;

    virtual /**
     * Carga los datos de un mapa de un archivo TMX
     * El archivo TMX esta creado en Tiled
     * @param gRenderer
     * @param ruta
     * @return
     */
    bool cargar(SDL_Renderer * gRenderer,std::string ruta){
        // Cargamos/ Parseamos el Mapa
        mTmxParser.load(ruta.c_str());

        if(mSprtSTiles != nullptr) {
            delete mSprtSTiles;
        }

        mSprtSTiles = new SpriteSheet();
        mSprtSTiles->cargarDesdeArchivo(gRenderer,mTmxParser.tilesetList[0].imgSource.source,
                                        mTmxParser.tilesetList[0].tileCount/mTmxParser.tilesetList[0].columns,
                                        mTmxParser.tilesetList[0].columns
        );
        /**
         * Creamos el mapa con los indices
         */
        auto layer = mTmxParser.tileLayer.begin(); // Obtenemos la primera layer del mapa (solo trabajamos con ella)
        // Obtenemos el tamaño del mapa
        int size_mapa = mTmxParser.tileLayer[layer->first].width*mTmxParser.tileLayer[layer->first].height;
        // Creamos el array a contener el mapa para unr apido acceso
        mLayerMapa = new int[size_mapa] {0};

        // Parseamos el contenido del mapa del archivo
        // Debe estar encodeado con csv sin compresion
        int  i = 0;
        mLayerMapa[i] = std::stoi(strtok((char *) mTmxParser.tileLayer[layer->first].data.contents.c_str(), ","));
        while(++i != size_mapa)
            mLayerMapa[i] = std::stoi(strtok(nullptr,","));
        return true;

    }
    void draw(SDL_Renderer * gRenderer,int x,int y){
        int indice;
        int dest_x,dest_y;

        for(int i=0;i<mTmxParser.mapInfo.height;i++)
            for(int j=0;j<mTmxParser.mapInfo.width;j++){
                // calculo de la posici�n del tile
                dest_x = j * mTmxParser.mapInfo.tileWidth + x;
                dest_y = i * mTmxParser.mapInfo.tileHeight + y;

                indice=mLayerMapa[i*mTmxParser.mapInfo.width+j];
                /*if(indice==BLOQUE_ITEM)
                    indice=BLOQUE_MADERA;
                else if(indice==BLOQUE_ENEMIGO)
                    indice=BLOQUE_PISO;*/
                mSprtSTiles->setCurrentCuadro(indice - 1);
                mSprtSTiles->draw(gRenderer,dest_x,dest_y);
            }

    }

    virtual ~Mapa(){
        delete mSprtSTiles;
    }

    const std::string &getPropertyMap(
            std::basic_string<char, std::char_traits<char>, std::allocator<char>> propertyName){
        return mTmxParser.mapInfo.property[propertyName];
    }

protected:
    TMX::Parser mTmxParser;

    SpriteSheet *mSprtSTiles = nullptr;
    int *mLayerMapa;
};
#endif //BOMBERMAN_CMAPA_HPP
