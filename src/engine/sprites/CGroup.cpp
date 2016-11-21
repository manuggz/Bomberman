#include "CGroup.hpp"

Group::Group(Interfaz * parent){
    this->parent=parent;
}


void Group::add(Sprite * nu){
    v_personajes.push_back(nu);
}

/*
void Group::kill(Sprite *del,bool del_mem){
    list<Sprite*>::iterator p_Sprite=find( v_personajes.begin(), v_personajes.end(), del );
    if(p_Sprite!=v_personajes.end()){

        //si se eliminara tambien no solo la referencia del grupo, sino ademas de la memoria
        if(del_mem){
            delete (*p_Sprite);
            (*p_Sprite)=NULL;
        }
        
        v_personajes.erase(p_Sprite);
    }
}*/

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
void Group::erase(Sprite * borrar){
     //lo buscamos usando iteradores
    deque<Sprite*>::iterator p_Sprite=v_personajes.begin();
    while(p_Sprite != v_personajes.end()){
        if((*p_Sprite) == borrar){
            v_personajes.erase(p_Sprite);
            return;
        }
        p_Sprite++;
    }
}
void Group::update(const Uint8 *keys){
    deque<Sprite*>::iterator p_Sprite= v_personajes.begin();


    if(keys == nullptr)//si no paso las keys las obtenemos
        keys=SDL_GetKeyboardState(0);

    while(p_Sprite != v_personajes.end()){
        (*p_Sprite)->update(keys);
         if(p_Sprite != v_personajes.end()){
             if((*p_Sprite)->isMuerto()){
                parent->killSprite((*p_Sprite)->getTipo(),(*p_Sprite)->getId());
                delete(*p_Sprite);
                (*p_Sprite) = 0x0;
                p_Sprite = v_personajes.erase(p_Sprite);
             }else{
                 p_Sprite++;
              }
        }
    }
}

void Group::draw(SDL_Renderer * gr){

   for (size_t i=0; i<v_personajes.size(); i++)
        v_personajes[i]->draw(gr);
}

Group::~Group(){
    v_personajes.clear();
}
