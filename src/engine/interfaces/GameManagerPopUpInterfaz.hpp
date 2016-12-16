//
// Created by manuggz on 26/11/16.
//

#ifndef BOMBERMAN_GAMEMANAGERDEFINICION_HPP
#define BOMBERMAN_GAMEMANAGERDEFINICION_HPP

#include <SDL2/SDL.h>

class GameManagerPopUpInterfaz{
public:
    virtual void closePopUp(void * result = nullptr)= 0;
    virtual SDL_Rect getRectScreen()=0;
};
#endif //BOMBERMAN_GAMEMANAGERDEFINICION_HPP
