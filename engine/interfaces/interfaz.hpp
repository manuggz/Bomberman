#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP


class Interfaz{
 public:
    Interfaz(){return;}

    // Funciones comunes a todas las escenas
    virtual void prepare(){};
    virtual void createUI(SDL_Renderer * gRenderer){};
    virtual void start(){};
    virtual bool isPaused(){return false;};
    virtual void pause(){};
    virtual void resume() {};
    virtual void procesarEvento(SDL_Event * event) = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer * gRenderer) = 0;

    virtual void killSprite(int,int){return;};
    virtual void erase(int type,int id_sprite){return;};
    virtual int addSprite(int ,int ,int ,int =-1,int =-1){return -1;};
    virtual ~Interfaz(){};	
};

#endif
