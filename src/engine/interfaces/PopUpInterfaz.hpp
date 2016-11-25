//
// Created by manuggz on 25/11/16.
//

#ifndef BOMBERMAN_POPUPMESSAGE_HPP
#define BOMBERMAN_POPUPMESSAGE_HPP

#include <SDL2/SDL.h>
#include <SDL_system.h>
#include <SDL_events.h>
#include "InterfazUI.hpp"

/**
 * Esta clase define un Layout que se va a mostrar en pantalla.
 * Esta clase no es un manejador principal de la pantalla
 */
class PopUpInterfaz : public InterfazUI{
public:
    /**
     * Oscurece el fondo del PopUp
     * @param gRenderer
     */
    void draw(SDL_Renderer *gRenderer) override {
        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(gRenderer,mpColorOscurecer.r,mpColorOscurecer.g,mpColorOscurecer.b,mpColorOscurecer.a);
        SDL_RenderFillRect(gRenderer, nullptr);
    }

private:
    SDL_Color mpColorOscurecer {0,0,0,150};
};
#endif //BOMBERMAN_POPUPMESSAGE_HPP
