#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP


class InterfazUI{
 public:
    InterfazUI(int x=0,int y=0){
        mX=x;
        mY=y;
        mIsPaused = false;
        mIsStarted = false;
    }

    // Funciones comunes a todas las escenas
    virtual void prepare(){};
    virtual void createUI(SDL_Renderer * gRenderer){};

    virtual void start(){mIsStarted=true;};
    virtual bool isPaused(){return mIsPaused&&mIsStarted&&!mIsStopped;};
    virtual bool isStarted(){return mIsStarted;};
    virtual bool isStopped(){return mIsStopped;};
    virtual void pause(){mIsPaused = true;};
    virtual void stop(){mIsStopped = true;}; // La detiene marcandola  para eliminacion
    virtual void resume() {mIsPaused = false;};

    virtual void procesarEvento(SDL_Event * event) = 0;
    virtual void update(){};
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
    virtual ~InterfazUI(){};

protected:

    // Coordenadas donde se dibujara la Interfaz
    int mX = 0,mY = 0;
    bool mIsPaused = false;
    bool mIsStarted = false;

    bool mIsStopped = false;
};

#endif
