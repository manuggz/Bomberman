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

    bool erase(Sprite *sprite) override {
        if(Group::erase(sprite)){
            if(isUpdating)
                mEliminadosEnUpdate.push_back(sprite);
            return true;
        }
        return false;
    }

    /**
     * Actualiza todos los sprites
     * Itera y llama a Sprite->update
     * @param keys
     */
    void update(const Uint8 *keys){

        isUpdating = true;

        deque<Sprite * > copia            = v_personajes;
        deque<Sprite*>::iterator p_Sprite = copia.begin();

        while(p_Sprite != copia.end()){

            // Notar que el sprite pueda que ya no exista
            // Pueda que el Sprite haya sido eliminado en el parent o en otro grupo
            // Si ocurrio uno de los casos anteriores hay un problema de lógica del juego pero igual
            // hay que revisar

            // Si no está eliminado
            bool estaEliminado = false;
            auto iteSprEliminado = mEliminadosEnUpdate.begin();
            while(iteSprEliminado != mEliminadosEnUpdate.end()){
                if(*iteSprEliminado == *p_Sprite){
                    estaEliminado = true;
                    break;
                }
                iteSprEliminado++;
            }

            if(!estaEliminado){
                (*p_Sprite)->update(keys);

                // En este punto, el Sprite pudo llamar a una funcion que hace que se elimine él o otro del grupo
                // por lo que ahora p_Sprite puede apuntar a otro elemento

                if((*p_Sprite)->isKilled())
                    parent->eliminarSprite((*p_Sprite));
            }
            p_Sprite
                    ++;

        }

        isUpdating = false;
        mEliminadosEnUpdate.clear();
    }

protected:
    InterfazSpriteGroup * parent;
    bool isUpdating = false;
    std::deque <Sprite * > mEliminadosEnUpdate;

};

#endif //BOMBERMAN_CUPDATEGROW_HPP
