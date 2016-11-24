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

/*
bool Group::contain(Sprite * bus){
     //lo vuscamos usando iteradores
    list<Sprite*>::iterator p_Sprite=find( v_personajes.begin(), v_personajes.end(), bus );
    
    //si es distinto del final es porque lo contiene
    return p_Sprite!=v_personajes.end();
}*/
/*
Sprite * Group::collide(Sprite * coli){
    list<Sprite*>::iterator p_Sprite= v_personajes.begin();
    
    while(p_Sprite != v_personajes.end()){
         if(rects_colisionan(coli->rect(),(*p_Sprite)->rect())){
              return (*p_Sprite);
         }
         p_Sprite++;
        
    }
    
    return NULL;
    
}*/
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
