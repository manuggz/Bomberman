//
// Created by manuggz on 13/12/16.
//

#ifndef TETRIS_CONTROLAANIMACION_HPP
#define TETRIS_CONTROLAANIMACION_HPP

#include <deque>
#include <SDL.h>
#include "ControlaAnimacionInterfaz.hpp"
#include "SimpleAnimacion.hpp"

class ControlaAnimacion{
public:
    ControlaAnimacion(ControlaAnimacionInterfaz*  parent){
        mParent = parent;
    }

    void add(int groupId,SimpleAnimacion* nuevaAnimacion) {

        nuevaAnimacion->start();
        dequeGrupoAnimaciones[groupId].push_back(nuevaAnimacion);
    }

    bool erase(int grupoId,SimpleAnimacion * pSprite){
        auto pSpriteBusqueda = dequeGrupoAnimaciones[grupoId].begin();
        while(pSpriteBusqueda != dequeGrupoAnimaciones[grupoId].end()){
            if((*pSpriteBusqueda) == pSprite){
                dequeGrupoAnimaciones[grupoId].erase(pSpriteBusqueda);
                return true;
            }
            pSpriteBusqueda++;
        }

        return false;

    }

    int numeroAnimacionesActivas(const int grupoId) {
        return (int) dequeGrupoAnimaciones[grupoId].size();
    }

    void update(){

        auto dequeCopia = dequeGrupoAnimaciones;
        for(auto itGrupoAnimacion = dequeCopia.begin();itGrupoAnimacion != dequeCopia.end();++itGrupoAnimacion){
            for(auto itAnimacion = (*itGrupoAnimacion).second.begin();itAnimacion != (*itGrupoAnimacion).second.end();itAnimacion++){
                (*itAnimacion)->update();
                if((*itAnimacion)->isStopped()){
                    erase((*itGrupoAnimacion).first,*itAnimacion);
                    delete *itAnimacion;
                    if(numeroAnimacionesActivas((*itGrupoAnimacion).first) ==0){
                        mParent->stopped((*itGrupoAnimacion).first);
                    }
                }
            }
        }
    }

    void draw(SDL_Renderer * gRenderer){
        for(auto itGrupoAnimacion = dequeGrupoAnimaciones.begin();itGrupoAnimacion != dequeGrupoAnimaciones.end();++itGrupoAnimacion){
            for(auto itAnimacion = (*itGrupoAnimacion).second.begin();itAnimacion != (*itGrupoAnimacion).second.end();itAnimacion++){
                (*itAnimacion)->draw(gRenderer);
            }
        }
    }
    ~ControlaAnimacion(){

    }

private:

    std::unordered_map<int,std::deque<SimpleAnimacion *>> dequeGrupoAnimaciones;
    ControlaAnimacionInterfaz *mParent;
};
#endif //TETRIS_CONTROLAANIMACION_HPP
