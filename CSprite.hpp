#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include "util.hpp"
//#define DEBUG
using namespace std;

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
        bool isMuerto();
        void kill();
        
       /* void setRect(const Rect &  rect2){rect=rect2;};*/

        virtual void update(const Uint8 *keys=NULL)=0;
        virtual void draw(SDL_Renderer * )=0;
        virtual int getTipo(){return type;};
        virtual int getId(){return id;};
        virtual void setId(int nuevo){id=nuevo;};
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
      
      /*protected:
        vector <Rect *> v_rects;
        Rect rect;*/
      protected:
//        vector <Group *> v_grupos;
        bool self_kill; //sera matado?
        int x,y;
        SDL_Rect rect;
        int id;
        int type;
        
};
#endif
