#ifndef MAPA_HPP
#define MAPA_HPP
//#define DEBUG
#include <SDL2/SDL.h>
//#include <SDL2/SDL_rotozoom.h>
#include "constantes.hpp"
#include "util.hpp"
#include "dat_nivel.hpp"
#include "interfaz.hpp"

/*
*
*   Representaci�n abstracta de un mapa concreto del juego,dibuja y coloca los items y enemigos en el juego
*   definicion: lee los tiles de un archivo en el HD
*   Lo bloques colisionables son BLOQUE_METAL y BLOQUE_MADERA
*
*
*/

class Mapa{
    public:
        enum{
            SIZE_TILE=16,
            
            FILAS=11,
            COLUMNAS=17,
            MAXMAP=FILAS*COLUMNAS,

            //Tipos de bloques
            BLOQUE_METAL=0, //Bloque no traspasable 
            BLOQUE_MADERA, //Bloque traspasable y se rompe con una explosi�n
            BLOQUE_PISO_SOMBRA,
            BLOQUE_PISO, //Bloque que representa donde caminara el jugador
            BLOQUE_ENEMIGO,//Bloque que representa a un enemigo (Esta en proceso de desarrollo solo representa a un "globo")
            BLOQUE_ITEM, //Bloque donde se ubica un �tem
            _BLOQUES//Cantidad de tipos de bloques reconocidos 
        };
        
        Mapa(Interfaz * _parent,int coorXVis=0,int coorYVis=0,SDL_Surface * grillaTiles=NULL);
        void draw(SDL_Surface * screen){draw(screen,imgTiles);};
        void draw(SDL_Surface * screen,SDL_Surface * grillaTiles){draw(screen,grillaTiles,tilesMap,coorXVisualizacion,coorYVisualizacion,datMapa->getIdTile());};
        static void draw(SDL_Surface * screen,SDL_Surface * tiles,char * mapa,int coorX,int coorY,int idTile);
        
        //Carga de un archivo binario la informaci�n del Mapa/
        //El archivo Bin est� creado usando "mapwin"
        //Regresan True si se cargar�n los mapas correctamente
        bool cargarDeArchivoBin(char rutaMapaBin[],char rutaParamText[]);
        static bool cargarMapaDeArchivoBin(char rutaMapaBin[],char * buffer);

        //Retorna las coordenadas X y Y de la puerta en la pantalla
        int getXPuerta(){return tileXPuerta*SIZE_TILE + coorXVisualizacion;};
        int getYPuerta(){return tileYPuerta*SIZE_TILE + coorYVisualizacion; };

        //Retorna los ejes actuales donde se visualiza la pantalla
        int getEjeXVisualizacion(){return coorXVisualizacion;};
        int getEjeYVisualizacion(){return coorYVisualizacion; };
        
        void moveEjeXVisualizacion(int aum){coorXVisualizacion+=aum;};
        void moveEjeYVisualizacion(int aum){coorYVisualizacion+=aum;};
        
        int getAnchoMapa(){return COLUMNAS*SIZE_TILE;};
        int getAltoMapa(){return FILAS*SIZE_TILE;};

        int getIdFondo(){return idFondo;};
        int getYPanel(){return yTablero;};
        int getEjeX(){return coorXPredVisualizacion;};
        int getEjeY(){return coorYPredVisualizacion;};
        
        //Metodos para obtener datos adicionales del mapa
        int getIdTile(){if(datMapa) return datMapa->getIdTile();else return -1;};//Tile con el que se dibujar� el mapa
        int getXIniPlayer(int idPlayer){if(datMapa) return datMapa->getX(idPlayer);else return -1;};//Coordenada x inicial del "id_player"
        int getYIniPlayer(int idPlayer){if(datMapa) return datMapa->getY(idPlayer);else return -1;}; 
        int getBombasIniciales(){if(datMapa) return datMapa->getBombas();else return -1;};//Bombas iniciales para cada player
        int getVidasIniciales(){if(datMapa) return datMapa->getVidas();else return -1;};
        int getAlcanceBombasInicial(){if(datMapa) return datMapa->getAlcanceBombas();else return -1;};
        int getNumItems(){if(datMapa) return datMapa->getNumItems();};//NUMERO DE ITEMS QUE QUEDAN EN EL MAPA

        //Metodos para establecer datos adicionales del mapa
        /*int getIdTile(){if(datMapa) return datMapa->getIdTile();else return -1;};//Tile con el que se dibujar� el mapa
        int getXIniPlayer(int idPlayer){if(datMapa) return datMapa->getX(idPlayer);else return -1;};//Coordenada x inicial del "id_player"
        int getYIniPlayer(int idPlayer){if(datMapa) return datMapa->getY(idPlayer);else return -1;}; 
        int getBombasIniciales(){if(datMapa) return datMapa->getBombas();else return -1;};//Bombas iniciales para cada player
        int getVidasIniciales(){if(datMapa) return datMapa->getVidas();else return -1;};
        int getAlcanceBombasInicial(){if(datMapa) return datMapa->getAlcanceBombas();else return -1;};*/
        int setNumItems(int nuevo){datMapa->setNumItems(nuevo);};//NUMERO DE ITEMS QUE QUEDAN EN EL MAPA
        
        //Metodos para cambiar coordenadas desde las mostradas en pantalla a las del Mapa
        int getTileX(int xPantalla){return (xPantalla-coorXVisualizacion)/SIZE_TILE;};
        int getTileY(int yPantalla){return (yPantalla-coorYVisualizacion)/SIZE_TILE;};
        int getIndiceMapa(int xPantalla,int yPantalla){return getTileY(yPantalla)*COLUMNAS+getTileX(xPantalla);};
        
        //Coloca aleatoriamente bloques con �tems en el Mapa
        int setItems();//Regresa los items que se lograron colocar

        //Busca Tiles donde se tenga que poner un enemigo y llama a "addSprite" de la interfaz
        int setEnemigos(); //Regresa los enemigos colocados
        void setImgTiles(SDL_Surface * grilla){imgTiles=grilla;}; 
        void setEjeVisualizacion(int x,int y){coorXVisualizacion=x;coorYVisualizacion=y;};
        
        int getTipoBloque(int x,int y){if(getIndiceMapa(x,y)<=MAXMAP)return tilesMap[getIndiceMapa(x,y)];else return -1;};
        
//        bool isBloqueDuro(int x,int y);
//        bool isItem(int x,int y){if(getIndiceMapa(x,y)<=MAXMAP)return mapa[getIndiceMapa(x,y)]==BLOQUE_ITEM;};
        bool isBloqueRompible(int x,int y);
        
        //Intenta cambiar la condici�n de un tile a "TIPO_PISO" 
        bool romperBloque(int x,int y); 
        
        //regresa True si el rectangulo colisiona con un bloque colisionable del nivel
        bool colision(SDL_Rect * rect, int * num_colisiones,bool solo_bloques_duros=false);

        ~Mapa();
        
        
//        int getNivelActual(){return n_actual;};
//        TipoItem getTipoNuevoItem (InterfazJuego inter);
//        bool getPuertaAbierta()const {return p_abierta;};
//        void setPuertaAbierta(bool nuevo){p_abierta=nuevo;};        

//        void cargarFiles(int num_nivel,InterfazJuego inter);
//        bool quedanBloquesMadera(); /*True si queda al menos un bloque de madera en el mapa*/
        static SDL_Surface * getPreviewTerreno(char rutaMapa[],DatNivel * params,SDL_Surface * img_tile,SDL_Surface * imgs_players[],int x,int y);
//        static SDL_Surface * getPreviewTerreno(int idTerreno);
        void leerInfTile(char ruta[]);
    private:
        DatNivel * datMapa; /*Para buscar los datos del mapa*/
        Interfaz * parent; /*Referencia a la interfaz que lo llama*/
        SDL_Surface *imgTiles;
        
        
        char tilesMap[MAXMAP+1];//almacena los index que representan el nivel
//        int n_actual;//nivel actual en el que se juega
    
//        bool p_abierta; // �se descubrio la puerta?
        int tileXPuerta,tileYPuerta; /*Coordenadas de la puerta en pantalla*/
        
        int coorXVisualizacion,coorYVisualizacion,/*Ejes de visualizaci�n del mapa*/
            coorXPredVisualizacion,coorYPredVisualizacion;
        
        int idFondo,
            yTablero;
        
//        bool mapaCargado;//True si se encuentra un mapa cargado en el momento de consulta
        int bloquesMadera;//Guarda la cantidad actual de bloques de madera
        
};
#endif
