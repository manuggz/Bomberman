//
// Created by manuggz on 21/11/16.
//

#ifndef BOMBERMAN_CUPDATEGROW_HPP
#define BOMBERMAN_CUPDATEGROW_HPP

#include "CGroup.hpp"
#include "../interfaces/InterfazSpriteGroup.hpp"

class UpdateGroup : public Group{
public :
    UpdateGroup(InterfazSpriteGroup * parent){
        this->parent = parent;
    };

    /**
     * Actualiza todos los sprites
     * Itera y llama a Sprite->update
     * @param keys
     */
    void update(const Uint8 *keys){
        deque<Sprite*>::iterator p_Sprite= v_personajes.begin();
        Sprite * spriteActual;
        if(keys == nullptr)//si no paso las keys las obtenemos
            keys=SDL_GetKeyboardState(0);

        while(p_Sprite != v_personajes.end()){

            // Notar que el sprite pueda que ya no exista
            // Pueda que el Sprite haya sido eliminado en el parent o en otro grupo
            // Si ocurrio uno de los casos anteriores hay un problema de lógica del juego pero igual
            // hay que revisar
            if((*p_Sprite) == nullptr){
                // Lo sacamos del grupo
                p_Sprite = v_personajes.erase(p_Sprite);
            }else{
                spriteActual = (*p_Sprite);
                // El sprite existe, Ok , lo actualizamos
                spriteActual->update(keys);

                // En este punto, el Sprite pudo llamar a una funcion que hace que se elimine él o otro del grupo
                // por lo que ahora p_Sprite puede apuntar a otro elemento

                if(spriteActual->isKilled()) {
                    parent->killedSprite(spriteActual);
                    //delete spriteActual;
                    p_Sprite = v_personajes.erase(p_Sprite);
                }

                if((*p_Sprite) == spriteActual){
                    p_Sprite++;
                }
            }
        }
    }

protected:
    InterfazSpriteGroup * parent;

};

#endif //BOMBERMAN_CUPDATEGROW_HPP
