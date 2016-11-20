#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP


class Interfaz{
 public:
    Interfaz(){return;}

    // Funciones comunes a todas las escenas
    virtual void start(SDL_Renderer *) = 0;
    virtual bool isPaused() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void procesarEvento(SDL_Event * ) = 0;
    virtual void update(void) = 0;
    virtual void draw(SDL_Renderer * ) = 0;

    virtual void killSprite(int,int){return;};
    virtual void erase(int type,int id_sprite){return;};
    virtual int addSprite(int ,int ,int ,int =-1,int =-1){return -1;};
    virtual ~Interfaz(){};	
};

#endif
