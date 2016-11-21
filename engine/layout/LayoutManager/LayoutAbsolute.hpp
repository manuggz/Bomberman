//
// Created by manuggz on 20/11/16.
//

#ifndef BOMBERMAN_LAYOUTABSOLUTE_HPP
#define BOMBERMAN_LAYOUTABSOLUTE_HPP

#include <deque>
#include "LayoutComponent.hpp"
#include "../../../util.hpp"

class LayoutAbsolute: public LayoutComponent{
public:

    void addComponent(Component * nuevoComponente){


        nuevoComponente->setLayoutParam(LAYOUT_PARAM_WRAP_WIDTH,LAYOUT_PARAM_TRUE);
        nuevoComponente->setLayoutParam(LAYOUT_PARAM_WRAP_HEIGHT,LAYOUT_PARAM_TRUE);

        nuevoComponente->setLayoutParam(LAYOUT_PARAM_X,"0");
        nuevoComponente->setLayoutParam(LAYOUT_PARAM_Y,"0");

        nuevoComponente->setLayoutParam(LAYOUT_PARAM_WIDTH,"0");
        nuevoComponente->setLayoutParam(LAYOUT_PARAM_HEIGHT,"0");

        mComponentes.push_back(nuevoComponente);
    }


    /**
     * Chequea si hay algun componente con disable = true o si el layout en si esta en ese estado
     * @return True si hay alguno con ese estado
     */
    bool isDisabled() {
        std::deque<Component*>::iterator pComponente= mComponentes.begin();

        while(pComponente != mComponentes.end()){
            if((*pComponente)->isDisabled()){
                return true;
            }
            pComponente++;
        }

        return mDisabled;
    }

    /**
     * Llama a los compactadores de los componentes agregados
     * @param gRenderer
     */
    void pack(SDL_Renderer * gRenderer) override {

        std::deque<Component*>::iterator pComponente= mComponentes.begin();

        mInternalRect.w = 0;
        mInternalRect.h = 0;
        SDL_Rect rectComponente,rectInternoCopia;
        while(pComponente != mComponentes.end()){
            (*pComponente)->pack(gRenderer);

            rectInternoCopia = mInternalRect;

            unir_rects(rectComponente,rectInternoCopia,mInternalRect);
            pComponente++;
        }
    }

    /**
     * Dibuja el layout y sus componentes de arriba hacia abajo / verticalmente
     * @param renderer
     */
    void setRectDibujo(SDL_Rect & rect) override {
        Component::setRectDibujo(rect);

        // Iterador de los componentes del layout
        std::deque<Component*>::iterator pComponente= mComponentes.begin();

        SDL_Rect drawRect = {rect.x,rect.y,0,0};

        while(pComponente != mComponentes.end()){

            drawRect.x = rect.x;
            drawRect.y = rect.y;
            drawRect.w = std::stoi((*pComponente)->getLayoutParam(LAYOUT_PARAM_WIDTH));
            drawRect.h = std::stoi((*pComponente)->getLayoutParam(LAYOUT_PARAM_HEIGHT));

            if((*pComponente)->getLayoutParam(LAYOUT_PARAM_WRAP_WIDTH) == LAYOUT_PARAM_TRUE){
                drawRect.w = (*pComponente)->getInternalWidth();
            }

            // Solo deberia haber un componente agregado si se usa una de estas variables
            if((*pComponente)->getLayoutParam(LAYOUT_PARAM_WRAP_HEIGHT) == LAYOUT_PARAM_TRUE){
                drawRect.h = (*pComponente)->getInternalHeight();
            }

            drawRect.x +=  std::stoi((*pComponente)->getLayoutParam(LAYOUT_PARAM_X));
            drawRect.y += std::stoi((*pComponente)->getLayoutParam(LAYOUT_PARAM_Y));

            // Dibujamos el componente
            (*pComponente)->setRectDibujo(drawRect);
            pComponente++; // siguiente cmoponente
        }
    }

};
#endif //BOMBERMAN_LAYOUTABSOLUTE_HPP