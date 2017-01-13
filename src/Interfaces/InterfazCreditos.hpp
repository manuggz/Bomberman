//
// Created by manuggz on 12/01/17.
//

#ifndef BOMBERMAN_INTERFAZCREDITOS_HPP
#define BOMBERMAN_INTERFAZCREDITOS_HPP

#include "../engine/interfaces/InterfazGrafica.hpp"
#include "../engine/layout/LayoutManager/LayoutAbsolute.hpp"

class InterfazCreditos : public InterfazGrafica{
public:
    InterfazCreditos(GameManagerInterfazUI *gameManagerInterfaz) : InterfazGrafica(gameManagerInterfaz) {

    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazGrafica::createUI(gRenderer);
        layoutAbsolute = new LayoutAbsolute();
        layoutAbsolute->setBackgroundTexture(gRenderer,"data/imagenes/fondos/fondo_creditos.bmp",false);
        SDL_Rect rect = mGameManagerInterfaz->getRectScreen();
        layoutAbsolute->pack(gRenderer);
        layoutAbsolute->setRectDibujo(rect);
    }

    void procesarEvento(SDL_Event *event) override {
        InterfazGrafica::procesarEvento(event);
    }

    void draw(SDL_Renderer *gRenderer) override {
        layoutAbsolute->draw(gRenderer);
    }

    ~InterfazCreditos() override {
        delete layoutAbsolute;
    }

private:
    LayoutAbsolute * layoutAbsolute;
};
#endif //BOMBERMAN_INTERFAZCREDITOS_HPP
