#ifndef ANIMACION_HPP
#define ANIMACION_HPP
#include <SDL2/SDL.h>
#include "CSprite.hpp"
#include "constantes.hpp"
#include "Control_Animacion.hpp"

class Animacion:public Sprite{
    public:
        Animacion(SDL_Texture * img_grilla,int filas,int columnas,string frames=NULL,int x=0,int y=0,int id=-1);
        void update(const Uint8 *keys=NULL);
        virtual void disable();
        virtual void draw(SDL_Renderer * );

        int getTipo(){return type;};
        int getId(){return id;};
        int getCuadro(){return control_fra.cuadro();};
        int getLoop(){return loop;};
        int setLoop(int nuevo){loop=nuevo;};
        int setCuadroDespues(int nuevo){indexInicioAniEnd=nuevo;cambiarOrden=true;};
        
        void setCuadrosFrames(char * frames);
    private:
        SDL_Texture * imgGrilla;
        ControlAnimacion control_fra;
        bool cambiarOrden;
        int f,c;
        int cuadro,delay,paso;
        int indexInicioAniEnd;//cuando la animacion termine una ejecuci�n, si se especif�ca �sta variable se dibujara solo los frames que comienzen desde su valor
    protected:
        int loop;
};

#endif
