#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP


class InterfazUI{
 public:
    InterfazUI(){
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

    virtual void procesarEvento(SDL_Event * event) {};
    virtual void update(){};
    virtual void updateWhenPopUp(){};
    virtual void resultPopUp(void *result, int i) {};
    virtual void draw(SDL_Renderer * gRenderer) = 0;

    virtual ~InterfazUI(){};

protected:

    bool mIsPaused = false;
    bool mIsStarted = false;

    bool mIsStopped = false;
};

#endif
