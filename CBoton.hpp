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
        
        Boton(SDL_Renderer * gRenderer,string rutaImagen,T * parent=NULL,int posX=0,int posY=0){
            if(setGrillaImagen(gRenderer,rutaImagen)){
                Boton(imgGrillaBoton,parent,posX,posY);
                desdeFile=true;
            }
        }
        Boton(SDL_Texture * grilla,T * parent=NULL,int posX=0,int posY=0){
            setGrillaImagen(grilla);
            rect.x=posX;
            rect.y=posY;
            SDL_QueryTexture(grilla, NULL, NULL, &rect.w, &rect.h);
            rect.h=rect.h/3;
            estado=NORMAL;
            accionClickClase=NULL;
            accionClickArgBoton=NULL;
            visible=true;
            enable=true;
            padre=parent;
            desdeFile=false;
        }
        bool setGrillaImagen(SDL_Renderer * gRenderer,string ruta){
            imgGrillaBoton=cargar_textura(gRenderer,ruta,false);
            if(!imgGrillaBoton){
                cerr <<"Warning-No se pudo crear la imagen del boton :"<<ruta<<", Error SDL:"<<SDL_GetError()<<endl;
                return false;
            }
            return true;
        }
        bool setGrillaImagen(SDL_Texture * grilla){
            if(imgGrillaBoton != nullptr){
                SDL_DestroyTexture(imgGrillaBoton);
            }
            imgGrillaBoton=grilla;
            return true;
        };
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
            if(visible)
                dibujarDesdeGrilla(imgGrillaBoton,estado,gRenderer,rect.x,rect.y,_ESTADOS,1);
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
            if(desdeFile)SDL_DestroyTexture(imgGrillaBoton);
        }
    private:
        Estado estado;
        SDL_Rect rect;
        SDL_Texture  * imgGrillaBoton;
        
        int idControl;
        
        T * padre;
        void (T::*accionClickClase)(void);
        void (T::*accionClickArgBoton)(Boton<T> *);

        bool visible,enable,desdeFile;

        bool estaPuntoEnRect(int x,int y,SDL_Rect * rect_coli){
            return (x>rect_coli->x&&x<rect_coli->x+rect_coli->w&&y>rect_coli->y&&y<rect_coli->y+rect_coli->h);
        }
        void dibujarDesdeGrilla(SDL_Texture * src, int cuadro, SDL_Renderer *gRenderer,int x_dest,int y_dest, int fil, int col){
        	SDL_Rect srcrect,dest_rect={x_dest,y_dest,0,0};

            SDL_QueryTexture(src, NULL, NULL, &srcrect.w, &srcrect.h);
        	srcrect.w = srcrect.w / col;
        	srcrect.h = srcrect.h / fil;
        	srcrect.x = (cuadro % col) * srcrect.w;
        	srcrect.y = (cuadro / col) * srcrect.h;
            SDL_RenderCopy(gRenderer,src,&srcrect,&dest_rect);
        }
};

#endif
