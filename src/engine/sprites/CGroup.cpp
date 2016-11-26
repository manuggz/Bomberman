#include "CGroup.hpp"


void Group::add(Sprite * pSprite){
    v_personajes.push_back(pSprite);
    pSprite->addGroup(this);
}

void Group::kill(Sprite *pSpriteBorrar){
    //lo buscamos usando iteradores
    auto pSpriteBusqueda=v_personajes.begin();
    while(pSpriteBusqueda != v_personajes.end()){
        if((*pSpriteBusqueda) == pSpriteBorrar){
            v_personajes.erase(pSpriteBusqueda);
            delete (*pSpriteBusqueda);
            (*pSpriteBusqueda) = 0x0;
            return;
        }
        pSpriteBusqueda++;
    }
}
void Group::erase(Sprite * pSpriteBorrar){
     //lo buscamos usando iteradores

    // Si se esta actualizando el grupo de sprites no se hacen eliminaciones
    // Este sprite se debería eliminar en la actualizacion si se establece selfkill
    if(isUpdating)
        return;

    auto pSpriteBusqueda = v_personajes.begin();
    while(pSpriteBusqueda != v_personajes.end()){
        if((*pSpriteBusqueda) == pSpriteBorrar){
            v_personajes.erase(pSpriteBusqueda);
            // Remover Este grupo de los grupos que guarda (*pSpriteBusqueda)
            return;
        }
        pSpriteBusqueda++;
    }
}


Group::~Group(){
    v_personajes.clear();
}

std::deque<Sprite *> Group::collide(SDL_Rect & rect) {
    std::deque<Sprite *> setColision;
    auto pSpriteBusqueda = v_personajes.begin();
    while(pSpriteBusqueda != v_personajes.end()){
        if((*pSpriteBusqueda)->colision(rect)){
            setColision.push_back((*pSpriteBusqueda));
        }
        pSpriteBusqueda++;
    }

    return setColision;
}

std::deque<Sprite *> Group::collide(Sprite * sprite) {
    return collide(sprite->rect);
}
