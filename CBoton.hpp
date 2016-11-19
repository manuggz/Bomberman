#ifndef BOTON_HPP
#define BOTON_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


template <typename T>  //T es la clase madre del Boton
class Boton{
    public:
        enum Estado{
            NORMAL,
            RESALTADO,
            PRESIONADO,
            _ESTADOS
        };
        
        /*Boton(SDL_Renderer * gRenderer,string rutaImagen,T * parent=NULL,int posX=0,int posY=0){
            if(setGrillaImagen(gRenderer,rutaImagen)){
                Boton(imgGrillaBoton,parent,posX,posY);
                desdeFile=true;
            }
        }*/
        Boton(LTexture * grilla,T * parent=NULL,int posX=0,int posY=0){

            imgGrillaBoton=grilla; // Grilla/ Columna con las tres filas representando los estados del boton

            // Rectangulo en la pantalla que ocupa el boton
            rect.x=posX;
            rect.y=posY;
            rect.w = grilla->getWidth();
            rect.h=grilla->getHeight()/_ESTADOS;

            estado=NORMAL;
            accionClickClase=NULL;
            accionClickArgBoton=NULL;
            visible=true;
            enable=true;
            padre=parent;
            desdeFile=false;
        }
        /*bool setGrillaImagen(SDL_Renderer * gRenderer,string ruta){
            imgGrillaBoton=cargar_textura(gRenderer,ruta,false);
            if(!imgGrillaBoton){
                cerr <<"Warning-No se pudo crear la imagen del boton :"<<ruta<<", Error SDL:"<<SDL_GetError()<<endl;
                return false;
            }
            return true;
        }*/
        /*bool setGrillaImagen(SDL_Texture * grilla){
            if(imgGrillaBoton != nullptr){
                SDL_DestroyTexture(imgGrillaBoton);
            }
            imgGrillaBoton=grilla;
            return true;
        };*/
        void procesarEvento(SDL_Event * evento){
            if(enable&&visible){
                if (evento->type==SDL_MOUSEMOTION){
                    if(estado!=PRESIONADO&&estaPuntoEnRect(evento->motion.x,evento->motion.y,&rect)){
                            estado=RESALTADO;
                    }else if(!estaPuntoEnRect(evento->motion.x,evento->motion.y,&rect)){
                        estado=NORMAL;
                    }
                }else if(evento->type==SDL_MOUSEBUTTONDOWN&&evento->button.button==SDL_BUTTON_LEFT){
                    if(estaPuntoEnRect(evento->motion.x,evento->motion.y,&rect)){
                        estado=PRESIONADO;                
                    }
                }else if(evento->type==SDL_MOUSEBUTTONUP&&evento->button.button==SDL_BUTTON_LEFT){
                    if(estado==PRESIONADO&&estaPuntoEnRect(evento->motion.x,evento->motion.y,&rect)){
                        if(accionClickClase)(padre->*accionClickClase)(); 
                        if(accionClickArgBoton)(padre->*accionClickArgBoton)(this);
                        if(enable)
                        estado=NORMAL;      
                      }
                }
            }
        }
        
        void bindAccion(void (T::*pAccion)(void)){accionClickClase=pAccion;};
        void bindAccion(void (T::*pAccion)(Boton<T> *)){accionClickArgBoton=pAccion;};
        void draw(SDL_Renderer * gRenderer){
            if(visible){
                SDL_Rect srcrect;
                srcrect.x = 0;
                srcrect.y = estado*srcrect.h;
                srcrect.w = rect.w;
                srcrect.h = rect.h;
                imgGrillaBoton->render(gRenderer,rect.x,rect.y,&srcrect);
            }
        };
        
        bool getVisible(){return visible;};
        bool getEnable(){return enable;};
        bool estaPresionado(){return estado==PRESIONADO;};
        
        void setVisible(bool nuevo){visible=nuevo;};
        void setEnable(bool nuevo){enable=nuevo;};
        void setEstado(Estado nuevo){estado=nuevo;};
        void setId(int nuevo){idControl=nuevo;};
        int getId(){return idControl;};
        
        ~Boton(){
            if(desdeFile){ // Si la grilla se cargo desde esta clase
                imgGrillaBoton->free();
                delete imgGrillaBoton;
            }
        }
    private:
        Estado estado;
        SDL_Rect rect;
        LTexture  * imgGrillaBoton;
        
        int idControl;
        
        T * padre;
        void (T::*accionClickClase)(void);
        void (T::*accionClickArgBoton)(Boton<T> *);

        bool visible,enable,desdeFile;

        bool estaPuntoEnRect(int x,int y,SDL_Rect * rect_coli){
            return (x>rect_coli->x&&x<rect_coli->x+rect_coli->w&&y>rect_coli->y&&y<rect_coli->y+rect_coli->h);
        }
};

#endif
