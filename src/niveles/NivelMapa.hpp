#ifndef MAPA_HPP
#define MAPA_HPP
//#define DEBUG
#include <SDL2/SDL.h>
//#include "../constantes.hpp"
#include "../util.hpp"
#include "../engine/util/CMetaData.hpp"
#include "../engine/interfaces/InterfazUI.hpp"
#include "../engine/util/SpriteSheet.hpp"
#include "../engine/mapa/include/TMXParser.h"
#include "../engine/mapa/CMapa.hpp"

//#define MAPA_PROPERTY_X_INIT_PLAYER "x_init_player_"
#define OBJECTSGROUP_PLAYERS_NAME "players"
#define OBJECT_PLAYER_NAME "Player"
#define MAPA_PROPERTY_X_N_VIDAS_PLAYER "n_vidas"
#define MAPA_PROPERTY_N_BOMBAS "n_bombas"
#define MAPA_PROPERTY_ALCANCE_BOMBAS "alcance_bombas"
#define MAPA_PROPERTY_ITEMS "n_items"
#define MAPA_PROPERTY_ID_TILE_LLAMAS "tile_on_fire"
//#define MAPA_PROPERTY_EJE_X_MAPA "eje_x"
//#define MAPA_PROPERTY_EJE_Y_MAPA "eje_y"
//#define MAPA_PROPERTY_Y_TABLERO "y_tablero"
//#define MAPA_PROPERTY_ID_FONDO "id_fondo"

#define TILE_PROPERTY_SOLIDO    "solido"
#define TILE_PROPERTY_ROMPIBLE  "rompible"
/*
*
*   Representaci�n abstracta de un mapa concreto del juego,dibuja y coloca los items y enemigos en el juego
*   definicion: lee los tiles de un archivo en el disco duro
*   Lo bloques colisionables son BLOQUE_METAL y BLOQUE_MADERA
*
*
*/

class NivelMapa: public Mapa{
public:
    virtual bool cargar(SDL_Renderer *gRenderer, std::string ruta) override;
    //NivelMapa();

    //Carga de un archivo binario la informaci�n del Mapa/
    //El archivo Bin est� creado usando "mapwin"
    //Regresan True si se cargar�n los mapas correctamente
    //bool cargar(SDL_Renderer * gRenderer,std::string ruta);
    //void draw(SDL_Renderer * gRenderer,int x,int y);
    //static bool cargarMapaDeArchivoBin(std::string rutaMapaBin,char * buffer);

    //Retorna las coordenadas X y Y de la puerta en la pantalla
    //int getXPuerta(){return tileXPuerta*SIZE_TILE + coorXVisualizacion;};
    //int getYPuerta(){return tileYPuerta*SIZE_TILE + coorYVisualizacion; };

    //Retorna los ejes actuales donde se visualiza la pantalla
    //int getEjeXVisualizacion(){return coorXVisualizacion;};
    //int getEjeYVisualizacion(){return coorYVisualizacion; };

    //void moveEjeXVisualizacion(int aum){coorXVisualizacion+=aum;};
    //void moveEjeYVisualizacion(int aum){coorYVisualizacion+=aum;};

    //int getAnchoMapa(){return COLUMNAS*SIZE_TILE;};
    //int getAltoMapa(){return FILAS*SIZE_TILE;};

    //int getIdFondo(){return idFondo;};
    //int getYPanel(){return yTablero;};
    //int getEjeX(){return coorXPredVisualizacion;};
    //int getEjeY(){return coorYPredVisualizacion;};

    //Metodos para obtener datos adicionales del mapa
    //std::string getMetaData(std::string clave){return mDatMapa->getMetaData(clave);};//Tile con el que se dibujar� el mapa
    //int getXIniPlayer(int idPlayer){if(mDatMapa) return mDatMapa->getX(idPlayer);else return -1;};//Coordenada x inicial del "id_player"
    //int getYIniPlayer(int idPlayer){if(mDatMapa) return mDatMapa->getY(idPlayer);else return -1;};
    //int getBombasIniciales(){if(mDatMapa) return mDatMapa->getBombas();else return -1;};//Bombas iniciales para cada player
    //int getVidasIniciales(){if(mDatMapa) return mDatMapa->getVidas();else return -1;};
    //int getAlcanceBombasInicial(){if(mDatMapa) return mDatMapa->getAlcanceBombas();else return -1;};
    //int getNumItems(){if(mDatMapa) return mDatMapa->getNumItems();};//NUMERO DE ITEMS QUE QUEDAN EN EL MAPA

    //Metodos para establecer datos adicionales del mapa
    /*int getIdTile(){if(mDatMapa) return mDatMapa->getIdTile();else return -1;};//Tile con el que se dibujar� el mapa
    int getXIniPlayer(int idPlayer){if(mDatMapa) return mDatMapa->getX(idPlayer);else return -1;};//Coordenada x inicial del "id_player"
    int getYIniPlayer(int idPlayer){if(mDatMapa) return mDatMapa->getY(idPlayer);else return -1;};
    int getBombasIniciales(){if(mDatMapa) return mDatMapa->getBombas();else return -1;};//Bombas iniciales para cada player
    int getVidasIniciales(){if(mDatMapa) return mDatMapa->getVidas();else return -1;};
    int getAlcanceBombasInicial(){if(mDatMapa) return mDatMapa->getAlcanceBombas();else return -1;};*/
    //int setNumItems(int nuevo){mDatMapa->setNumItems(nuevo);};//NUMERO DE ITEMS QUE QUEDAN EN EL MAPA

    //Metodos para cambiar coordenadas desde las mostradas en pantalla a las del Mapa
    //int getTileX(int xPantalla){return (xPantalla-coorXVisualizacion)/SIZE_TILE;};
    //int getTileY(int yPantalla){return (yPantalla-coorYVisualizacion)/SIZE_TILE;};
    ///int getIndiceMapa(int xPantalla,int yPantalla){return getTileY(yPantalla)*COLUMNAS+getTileX(xPantalla);};

    //Coloca aleatoriamente bloques con �tems en el Mapa
    //int setItems();//Regresa los mGrpItems que se lograron colocar

    //Busca Tiles donde se tenga que poner un enemigo y llama a "addSprite" de la interfaz
    //int setEnemigos(); //Regresa los enemigos colocados
    /*void setImgTiles(LTexture * grilla){

        if(imgTiles != nullptr) {
            imgTiles->free();
            delete imgTiles;
        }
        imgTiles=grilla;
    };*/
    //void setEjeVisualizacion(int x,int y){coorXVisualizacion=x;coorYVisualizacion=y;};

    //int getTipoBloque(int x,int y){if(getIndiceMapa(x,y)<=MAXMAP)return tilesMap[getIndiceMapa(x,y)];else return -1;};

//        bool isBloqueDuro(int x,int y);
//        bool isItem(int x,int y){if(getIndiceMapa(x,y)<=MAXMAP)return mapa[getIndiceMapa(x,y)]==BLOQUE_ITEM;};
    //bool isBloqueRompible(int x,int y);

    //Intenta cambiar la condici�n de un tile a "TIPO_PISO"
    //bool romperBloque(int x,int y);

    //regresa True si el rectangulo colisiona con un bloque colisionable del nivel
    int colision(SDL_Rect  rect, int * num_colisiones,bool solo_bloques_duros=false);

    //~NivelMapa();
    int getBloqueAt(int x, int y);


//        int getNivelActual(){return n_actual;};
//        TipoItem getTipoNuevoItem (InterfazJuego inter);
//        bool getPuertaAbierta()const {return p_abierta;};
//        void setPuertaAbierta(bool nuevo){p_abierta=nuevo;};        

//        void cargarFiles(int num_nivel,InterfazJuego inter);
//        bool quedanBloquesMadera(); /*True si queda al menos un mGrpBloques de madera en el mapa*/
    static SDL_Texture * getPreviewTerreno(char rutaMapa[],MetaData * params,LTexture * img_tile,LTexture * imgs_players[],int x,int y);
//        static SDL_Surface * getPreviewTerreno(int idTerreno);
    //void leerInfTile(char ruta[]);
    //const std::string &getMapProperty(std::basic_string<char, std::char_traits<char>, std::allocator<char>> propertyName);

    bool contain(SDL_Rect rect);
    //TMX::Parser mTmxParser;
    //MetaData    * mDatMapa  = nullptr; /*Para buscar los datos del mapa*/
    //InterfazUI  * parent   = nullptr; /*Referencia a la interfaz que lo llama*/
    //LTexture    * imgTiles = nullptr;

    //char tilesMap[MAXMAP+1]  {0};//almacena los index que representan el nivel
//        int n_actual;//nivel actual en el que se juega

//        bool p_abierta; // �se descubrio la puerta?
   //int tileXPuerta = -1;
    //int tileYPuerta = -1; /*Coordenadas de la puerta en pantalla*/

    //int coorXVisualizacion = 0;
    //int coorYVisualizacion = 0;
    //int coorXPredVisualizacion = 0;/*Ejes de visualizaci�n del mapa*/
    //int coorYPredVisualizacion = 0;

    //int idFondo = -1;
    //int yTablero = 0;

//        bool mapaCargado;//True si se encuentra un mapa cargado en el momento de consulta
    //int bloquesMadera = 0;//Guarda la cantidad actual de bloques de madera

    //SpriteSheet *mSprtSTiles = nullptr;
    //int mFilaTiles;
    //int *mLayerMapa;


    unsigned int mTileHeight = 0;
    unsigned int mMapWidth   = 0;
    unsigned int mMapHeight  = 0;
    unsigned int mTileWidth  = 0;
    std::map<std::string, TMX::Parser::Tile> *  mpTilesMetaData;

    int getTileWidth();

    int getTileHeight();

    bool esBloqueSolido(int x, int y);

    bool esBloqueRompible(int x, int y);

    std::string getPropertyTile(int id_tile, std::string clave);

    int getPosXPlayer(IdPlayer player);

    int getPosYPlayer(IdPlayer player);

    std::vector<std::string> * getAnimacionFrames(const std::string &basic_string);

    SpriteSheet *getSpriteSheetTiles();

    std::string getRutaTileSet();

    int getNFilasTileSet();

    int getNColumnasTileSet();
};
#endif
