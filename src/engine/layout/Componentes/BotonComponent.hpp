#ifndef BOTON_HPP
#define BOTON_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../LayoutManager/LayoutComponent.hpp"


template <typename T>  //T es la clase madre del BotonComponent
class BotonComponent : public LayoutComponent{
    public:
        enum Estado{
            NORMAL,
            RESALTADO,
            PRESIONADO,
            _ESTADOS
        };
        
        BotonComponent(LTexture * grilla,T * parent=NULL){

            imgGrillaBoton=grilla; // Grilla/ Columna con las tres filas representando los estados del boton

            // Rectangulo en la pantalla que ocupa el boton

            estado=NORMAL;
            accionClickClase=NULL;
            accionClickArgBoton=NULL;
            visible=true;
            enable=true;
            padre=parent;
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

        void pack(SDL_Renderer * gRenderer) override {
            mInternalRect.x=0;
            mInternalRect.y=0;
            mInternalRect.w = imgGrillaBoton->getWidth();
            mInternalRect.h=imgGrillaBoton->getHeight()/_ESTADOS;
        }


        void procesarEvento(SDL_Event * evento){
            if(enable&&visible){
                if (evento->type==SDL_MOUSEMOTION){
                    if(estado!=PRESIONADO&&estaPuntoEnRect(evento->motion.x,evento->motion.y,&mDrawRect)){
                            estado=RESALTADO;
                    }else if(!estaPuntoEnRect(evento->motion.x,evento->motion.y,&mDrawRect)){
                        estado=NORMAL;
                    }
                }else if(evento->type==SDL_MOUSEBUTTONDOWN&&evento->button.button==SDL_BUTTON_LEFT){
                    if(estaPuntoEnRect(evento->motion.x,evento->motion.y,&mDrawRect)){
                        estado=PRESIONADO;                
                    }
                }else if(evento->type==SDL_MOUSEBUTTONUP&&evento->button.button==SDL_BUTTON_LEFT){
                    if(estado==PRESIONADO&&estaPuntoEnRect(evento->motion.x,evento->motion.y,&mDrawRect)){
                        if(accionClickClase)(padre->*accionClickClase)(); 
                        if(accionClickArgBoton)(padre->*accionClickArgBoton)(this);
                        if(enable)
                        estado=NORMAL;      
                      }
                }
            }
        }
        
        void bindAccion(void (T::*pAccion)(void)){accionClickClase=pAccion;};
        void bindSubmitCallBack(void (T::*pAccion)(BotonComponent<T> *)){accionClickArgBoton=pAccion;};
        void draw(SDL_Renderer * gRenderer) override {
            LayoutComponent::draw(gRenderer);
            if(visible){
                SDL_Rect srcrect;
                srcrect.x = 0;
                srcrect.y = estado*mInternalRect.h;
                srcrect.w = mInternalRect.w;
                srcrect.h = mInternalRect.h;
                imgGrillaBoton->render(gRenderer,mDrawRect.x,mDrawRect.y,&srcrect);
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
        
        ~BotonComponent(){
            delete imgGrillaBoton;
        }
    private:
        Estado estado;
        LTexture  * imgGrillaBoton;
        
        int idControl;
        
        T * padre;
        void (T::*accionClickClase)(void);
        void (T::*accionClickArgBoton)(BotonComponent<T> *);

        bool visible,enable;

        bool estaPuntoEnRect(int x,int y,SDL_Rect * rect_coli){
            return (x>rect_coli->x&&x<rect_coli->x+rect_coli->w&&y>rect_coli->y&&y<rect_coli->y+rect_coli->h);
        }
};

#endif
