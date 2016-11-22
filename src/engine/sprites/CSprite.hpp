#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "../../util.hpp"
#include "SpriteContainer.hpp"
//#define DEBUG
using namespace std;
/**
 * Clase Base para Todos los elementos que integran un juego
 * Inspirada de la clase Sprite de pygame.
 */
class Group;

class Sprite{

  friend class Group;

  public:
     Sprite(){
        #ifdef DEBUG
            cout << "Constructor de Sprite:"<<this<<endl;
        #endif
    };

    /*Funciones para administrar los grupos*/
  /*  void add(Group *);*/
    bool isKilled();
    void kill();

   /* void setRect(const Rect &  rect2){rect=rect2;};*/

    virtual void update(const Uint8 *keys=nullptr)=0;
    virtual void draw(SDL_Renderer * )=0;
    //virtual int getTipo(){return type;};
    //virtual int getId(){return id;};
    //virtual void setId(int nuevo){id=nuevo;};
    virtual bool colision(SDL_Rect & rect_coli);
    virtual int getX(){return x;};
    virtual int getY(){return y;};
    virtual void setX(int nuevo){x=nuevo;};
    virtual void setY(int nuevo){y=nuevo;};
//        virtual void moveIp(int,int){};

    virtual ~Sprite(){
        #ifdef DEBUG
            cout << "Destructor de Sprite:"<<this<<endl;
        #endif
        return;
    };

protected:
    std::vector <SpriteContainer *> v_grupos;

    bool mSelfKill = false; //sera matado?
    int x = 0,y = 0;
    SDL_Rect rect {0,0,0,0};
    //int id;
    //int type;

    void addGroup(SpriteContainer *pGroup);
};
#endif
