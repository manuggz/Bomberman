//
// Created by manuggz on 25/11/16.
//

#ifndef BOMBERMAN_POPUPMESSAGE_HPP
#define BOMBERMAN_POPUPMESSAGE_HPP

#include <SDL2/SDL.h>
#include <SDL_system.h>
#include <SDL_events.h>
#include "InterfazUI.hpp"
#include "../util/GameManagerPopUpInterfaz.hpp"

/**
 * Esta clase define un Layout que se va a mostrar en pantalla.
 * Esta clase no es un manejador principal de la pantalla
 */
class PopUpInterfaz{
public:

    PopUpInterfaz(GameManagerPopUpInterfaz * gameManager){
        mGameManager = gameManager;
        mIsPaused = false;
        mIsStarted = false;
    }

    virtual void start(){mIsStarted=true;};
    virtual bool isPaused(){return mIsPaused&&mIsStarted&&!mIsStopped;};
    virtual bool isStarted(){return mIsStarted;};
    virtual bool isStopped(){return mIsStopped;};
    virtual void stop(){mIsStopped = true;}; // La detiene marcandola  para eliminacion
    virtual void prepare(){};
    virtual void update(){};
    virtual void createUI(SDL_Renderer * gRenderer){};
    virtual void procesarEvento(SDL_Event *event) {
        switch(event->type) {
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_ESCAPE:
                        mGameManager->closePopUp(nullptr);
                        break;
                }
        }
    }

    /**
     * Oscurece el fondo del PopUp
     * @param gRenderer
     */
    virtual void draw(SDL_Renderer *gRenderer) {
        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(gRenderer,mpColorOscurecer.r,mpColorOscurecer.g,mpColorOscurecer.b,mpColorOscurecer.a);
        SDL_RenderFillRect(gRenderer, nullptr);
    }

protected:
    SDL_Color mpColorOscurecer {0, 0, 0, 150};
    GameManagerPopUpInterfaz * mGameManager;
    bool mIsPaused = false;
    bool mIsStarted = false;

    bool mIsStopped = false;
};
#endif //BOMBERMAN_POPUPMESSAGE_HPP
