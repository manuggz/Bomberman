#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP


class Interfaz{
 public:
    Interfaz(int x=0,int y=0){
        mX=x;
        mY=y;
        mIsPaused = false;
        mIsStarted = false;
    }

    // Funciones comunes a todas las escenas
    virtual void prepare(){};
    virtual void createUI(SDL_Renderer * gRenderer){};
    virtual void start(){mIsStarted=true;};
    virtual bool isPaused(){return mIsPaused&&mIsStarted;};
    virtual bool isStarted(){return mIsStarted;};
    virtual void pause(){mIsPaused = true;};
    virtual void resume() {mIsPaused = false;};
    virtual void procesarEvento(SDL_Event * event) = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer * gRenderer) = 0;

/*    virtual void setX(int nuevaX){
        mX = nuevaX;
    }
    virtual void setY(int nuevaY){
        mY = nuevaY;
    }
    */virtual int getX(){
        return mX;
    }
    virtual int getY(){
        return mY;
    }
    /*virtual void killSprite(int,int){return;};
    virtual void erase(int type,int id_sprite){return;};
    virtual int addSprite(int ,int ,int ,int =-1,int =-1){return -1;};*/
    virtual ~Interfaz(){};

protected:
    int mX,mY;
    bool mIsPaused;
    bool mIsStarted;
};

#endif
