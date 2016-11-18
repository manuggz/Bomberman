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
        
        Boton(char rutaImagen[],T * parent=NULL,int posX=0,int posY=0){
            if(setGrillaImagen(rutaImagen)){
                Boton(imgGrillaBoton,posX,posY);
                desdeFile=true;
            }
        }
        Boton(SDL_Surface * grilla,T * parent=NULL,int posX=0,int posY=0){
            setGrillaImagen(grilla);
            rect.x=posX;
            rect.y=posY;
            rect.w=imgGrillaBoton->w;
            rect.h=imgGrillaBoton->h/3;
            estado=NORMAL;
            accionClickClase=NULL;
            accionClickArgBoton=NULL;
            visible=true;
            enable=true;
            padre=parent;
            desdeFile=false;
        }
        bool setGrillaImagen(char ruta[]){
            imgGrillaBoton=IMG_Load(ruta);
            if(!imgGrillaBoton){
                cerr <<"Warning-No se pudo crear la imagen del boton :"<<ruta<<", Error SDL:"<<SDL_GetError()<<endl;
                return false;
            }
            return true;
        }
        bool setGrillaImagen(SDL_Surface * grilla){imgGrillaBoton=grilla;return true;};
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
        void draw(SDL_Surface * screen){
            if(visible)
                dibujarDesdeGrilla(imgGrillaBoton,estado,screen,rect.x,rect.y,_ESTADOS,1);
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
            if(desdeFile)SDL_FreeSurface(imgGrillaBoton);
        }
    private:
        Estado estado;
        SDL_Rect rect;
        SDL_Surface  * imgGrillaBoton;
        
        int idControl;
        
        T * padre;
        void (T::*accionClickClase)(void);
        void (T::*accionClickArgBoton)(Boton<T> *);

        bool visible,enable,desdeFile;

        bool estaPuntoEnRect(int x,int y,SDL_Rect * rect_coli){
            return (x>rect_coli->x&&x<rect_coli->x+rect_coli->w&&y>rect_coli->y&&y<rect_coli->y+rect_coli->h);
        }
        void dibujarDesdeGrilla(SDL_Surface * src, int cuadro, SDL_Surface *dst,int x_dest,int y_dest, int fil, int col){
        	SDL_Rect srcrect,dest_rect={x_dest,y_dest,0,0};
        
        	srcrect.w = src->w / col;
        	srcrect.h = src->h / fil;
        	srcrect.x = (cuadro % col) * srcrect.w;
        	srcrect.y = (cuadro / col) * srcrect.h;
        
        	SDL_BlitSurface(src, &srcrect, dst, &dest_rect);
        }
};

#endif
