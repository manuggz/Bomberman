//
// Created by manuggz on 21/11/16.
//

#ifndef BOMBERMAN_INTERFAZSPRITEGROUP_HPP
#define BOMBERMAN_INTERFAZSPRITEGROUP_HPP
/**
 * Esta clase contiene las funciones que puede llamar un Grupo.
 *
 * Si una Interfaz va a usar un UpdateGroup o derivado, debe implementar esta Clase.
 *
 * Ya que un Sprite cuando quiere eliminarse del juego completamente llama a Sprite->kill(), el cual
 * establece una variable en él kill=true.
 *
 * Cuando una instancia de UpdateGroup recorre los sprites y en una llamada a Sprite->isKilled()[retorna true cuando kill=true]
 *  éste descubre que el sprite está en ese estado, el grupo llama InterfazGroup->eliminarSprite(Sprite),
 * y después elimina al Sprite de su lista.
 *
 * El grupo no elimina al Sprite de memoria, por lo que es responsabilidad de la Interfaz eliminarla.
 *
 * La función eliminarSprite(Sprite * k) , se puede usar para ejecutar acciones dependiendo del Sprite eliminado.
 *
 * Por ejemplo, si el Sprite es un Enemigo de un Juego, se le puede subir el puntaje al Usuario.
 * Esta función solo se llama una vez así el sprite esté en varios grupos.
 */

class Sprite;
class InterfazSpriteGroup{
public:
    /**
     * Elimina un Sprite de Memoria.
     * Esta función es llamada desde un UpdateGroup/Derivado cuando se elimina un Sprite con kill().
     */
    virtual void eliminarSprite(Sprite *) = 0;
};
#endif //BOMBERMAN_INTERFAZSPRITEGROUP_HPP
