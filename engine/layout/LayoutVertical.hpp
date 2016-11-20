//
// Created by manuggz on 19/11/16.
//

#ifndef BOMBERMAN_LAYOUTVERTICAL_HPP
#define BOMBERMAN_LAYOUTVERTICAL_HPP

#include <deque>
#include "LayoutComponent.hpp"

using namespace std;

class LayoutVertical: public LayoutComponent{
public:

    void addComponent(LayoutComponent * nuevoComponente){
        mComponentes.push_back(nuevoComponente);
    }


    /**
     * Chequea si hay algun componente con disable = true o si el layout en si esta en ese estado
     * @return True si hay alguno con ese estado
     */
    bool isDisabled() {
        deque<LayoutComponent*>::iterator pComponente= mComponentes.begin();

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
    void pack(SDL_Renderer * gRenderer){
        deque<LayoutComponent*>::iterator pComponente= mComponentes.begin();

        while(pComponente != mComponentes.end()){
            (*pComponente)->pack(gRenderer);
            pComponente++;
        }
    }

    /**
     * Calcula el rectangulo donde se dibujara el layout
     * Este lo calcula primero calculando el de los componentes agregados
     * @param rectDisponible
     */
    void calculateSize(int widthDisponible,int heightDisponible) override {
        LayoutComponent::calculateSize(widthDisponible,heightDisponible);
        deque<LayoutComponent *>::iterator pComponente = mComponentes.begin();

        // Rectangulo en donde se propone al componente que se dibuje
        //SDL_Rect rectComponent = {rectDisponible.x,rectDisponible.y,rectDisponible.w,rectDisponible.h};

        while (pComponente != mComponentes.end()) {

            (*pComponente)->calculateSize(widthDisponible, heightDisponible);

            // Si el ancho es mayor que el que llevamos actual lo guardamos
            // Por si estamos en wrap_content = TRUE
            if (mWrapWidth && (*pComponente)->getWidth() > mDrawRect.w) {
                mDrawRect.w = (*pComponente)->getWidth();
            }

            // Aumentamos la altura del rectangulo que contiene a todos los componentes
            if(mWrapHeight)
                mDrawRect.h += (*pComponente)->getHeight();
            //cout << "mdra:"  << mDrawRect.h<< endl;
            // Establecemos la nueva posicion Y del siguiente componente a dibujar
            // La cual es debajo del just anterior dibujado porque así es este layout
            //rectComponent.y += (*pComponente)->getHeight();
            // Restamos la altura de este componente para hacer el rectangulo en donde puede dibujar el siguiente
            // más pequeño
            heightDisponible -= (*pComponente)->getHeight();

            pComponente++;

        }
    }

    void calcularPosicion(SDL_Rect & dest) override {

        LayoutComponent::calcularPosicion(dest);
        deque<LayoutComponent *>::iterator pComponente = mComponentes.begin();


        SDL_Rect destComponente = {mDrawRect.x,mDrawRect.y,mDrawRect.w,mDrawRect.h};

        while (pComponente != mComponentes.end()) {

            //dest.w = (*pComponente)->getWidth();
            (*pComponente)->calcularPosicion(destComponente);

            // Aumentamos la altura del rectangulo que contiene a todos los componentes
            //mDrawRect.h += (*pComponente)->getHeight();
            //cout << "mdra:"  << mDrawRect.h<< endl;
            // Establecemos la nueva posicion Y del siguiente componente a dibujar
            // La cual es debajo del just anterior dibujado porque así es este layout
            destComponente.y += (*pComponente)->getHeight();
            // Restamos la altura de este componente para hacer el rectangulo en donde puede dibujar el siguiente
            // más pequeño
            destComponente.h -= (*pComponente)->getHeight();

            pComponente++;

        }

    }

    /**
     * Dibuja el layout y sus componentes de arriba hacia abajo / verticalmente
     * @param renderer
     */
    void draw(SDL_Renderer * gRenderer) override {
        LayoutComponent::draw(gRenderer);

        // Iterador de los componentes del layout
        deque<LayoutComponent*>::iterator pComponente= mComponentes.begin();

        while(pComponente != mComponentes.end()){

            // Dibujamos el componente
            (*pComponente)->draw(gRenderer);
            (*pComponente)->setDisabled(false);
            pComponente++; // siguiente cmoponente
        }
        setDisabled(false);
    }

private:
    deque <LayoutComponent * > mComponentes;
};
#endif //BOMBERMAN_LAYOUTVERTICAL_HPP
