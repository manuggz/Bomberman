#ifndef JUEGO_HPP
#define JUEGO_HPP
#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include "time.hpp"
#include "mapa.hpp"
#include "engine/util/game_manager.hpp"
#include "constantes.hpp"
#include "engine/interfaces/interfaz.hpp"
#include "engine/sprites/CGroup.hpp"
/*Personajes*/
#include "bomba.hpp"
#include "item.hpp"
#include "explosion.hpp"
#include "player.hpp"
#include "bloque.hpp"
//#define DEBUG


class Mapa;

class Juego:public Interfaz{
      public:
        Juego(GameManager * mundo);
        void procesarEvento(SDL_Event * evento);
        virtual void salir()=0;
        void update ();
        void crearTexturas(SDL_Renderer * gr){};
        void draw(SDL_Renderer * );

        void estadoDisplayMensage();
        virtual void estadoPlay()=0;
        virtual void drawBarra(SDL_Renderer *)=0;
        void displayMensage(const char * mensage);
        virtual int getEjeXVisual(){return mapa->getEjeXVisualizacion();};
        virtual int getEjeYVisual(){return mapa->getEjeYVisualizacion();};
        virtual int getAnchoMapa(){return mapa->getAnchoMapa();};
        virtual int getAltoMapa(){return mapa->getAltoMapa();};
        virtual void resetEjes(){mapa->setEjeVisualizacion(EjeX,EjeY);};

        virtual bool moveLeftEjeXVisual(){
            if(getEjeXVisual()+getAnchoMapa()>W_SCREEN){
                mapa->moveEjeXVisualizacion(-1);
                moveAllSprites(-1,0);
                return true;
            }
            return false;
        }
        virtual bool moveRightEjeXVisual(){
            if(getEjeXVisual()<0){
                mapa->moveEjeXVisualizacion(1);
                moveAllSprites(1,0);
                return true;
            }
            return false;
        }
        virtual bool moveDownEjeYVisual(){
            if(getEjeYVisual()<40){
                mapa->moveEjeYVisualizacion(1);
                moveAllSprites(0,1);
                return true;
            }
            return false;
        }


        void play(CodeMusicEfecto code);
        void playSonido(CodeMusicSonido code);


        void setPuertaAbierta(bool nuevo);
        void setPuntaje(IdPlayer id,int nuevo);
        void setActivos(TipoSprite type,int nuevo);
        virtual void setMapaPlay(int,bool=false){}; 
        void setProteccion(TipoSprite type, int id,int nuevo);
        void setRepeticionBomba(int id,int nuevo);
        void setEstadoPlayer(IdPlayer id,EstadoSprite nuevo);

        void crearReferencias();
        int addSprite(int type,int x,int y,int lanzador=-1,int otra_var=-1);
        void addSprite(Sprite * );
        void erase(int type,int id_sprite);
        void killSprite(int type,int id_sprite);
        void soloKill(int type,int id_sprite);
        void clearSprites(bool elimina_players=false);
        
        virtual InterfazJuego getTipoJuego()=0;
//        TipoItem getTipoNuevoItem();
        int getTipoItem(int id_item);
        int getJoysActivos();
        int getActivos(TipoSprite type);
        int getLanzador(TipoSprite type,int id_spri);
        int getPuntaje(IdPlayer id);
        int getSegundosInicioNivel();
        int getActivos(TipoSprite type,int & id);
        int getActivosId(TipoSprite type,IdPlayer  id);
        int getXPuerta()const{return mapa->getXPuerta();};
        int getYPuerta()const{return mapa->getYPuerta();};
        int getIdTile()const{return mapa->getIdTile();};
//        int getNivelActual();
        void getPosicion(TipoSprite type, int id,int & x,int & y);
        bool getPuertaAbierta();
        int getTick(){
            if(clockTick)return clockTick->getMiliSegundos();
        }
        
        LTexture * getImagen(CodeImagen code){ return game->getImagen(code);};
        SDL_Joystick * getJoy(int id);
        virtual int getTipoNuevoItem(bool disminuir_de_mapa=true);


        int colision(SDL_Rect & rect_coli,int * lado_colision,bool solo_bloques_duros);
        int colision(TipoSprite  type[],int tamanyo,SDL_Rect & rect_coli);
        int colision(TipoSprite type,SDL_Rect & rect_coli,int id_ignorar=-1);
        int colision(TipoSprite type,SDL_Rect & rect_coli,int & lado_colision,bool solo_bloques_duros);

        bool isBloqueRompible(int x,int y);
        bool isBloqueDuro(int x,int y);
        bool isBloqueItem(int x,int y);
        bool isActivo(TipoSprite type,int id);

        void romperBloque(int x,int y);
        
        virtual void aumentarNivel(){};
        void controlaPausa(const Uint8 * keys);
        void moveAllSprites(int aumX,int aumY);
        
        virtual ~Juego();

    protected:
        GameManager * game;
        Group * sprites;
        Mapa *mapa;
        Sprite ** refeSprites[_REFERENCIADOS];
        bool pausado;/*True si el juego esta pausado/si se esta mostrando la imagen de pausa (carita mas pausa)*/
        bool hold_start;/*_True si un player mantiene start presionado*/
        int spriteActivos[_REFERENCIADOS],totalSprite[_REFERENCIADOS];
        TimeController * clockTick;
        
        int inicio_pausa; /*almacena el tiempo cuando se inicio la pausa*/
        
        IdPlayer id_quien_pauso;/*Almacena el ID del player que acciono la pausa*/
        IdPlayer id_quien_pauso_anterior;/*Almacena el ID del player que acciono la pausa anteriormente*/

        EstadoJuego estado,estado_siguiente;
                        
        int x_msg,y_msg;
        float vel_y;
        char msg_mostrar[50];
//        int retraso;
        int n_actual;
        bool p_abierta;
        
        bool animandoEntradaMapaVertical;;
        int desplazamiento;

        int mayor_puntaje;
        
        bool _quit;
        bool patinesLanzados,bombasMaxLanzado,alcanceMaxLanzado;

        DatNivel * data;
        int EjeX,EjeY;
};

#endif
