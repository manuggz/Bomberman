#ifndef MAPA_HPP
#define MAPA_HPP
//#define DEBUG
#include <SDL2/SDL.h>
//#include "../constantes.hpp"
#include "../engine/util/util.hpp"
#include "../engine/util/CMetaData.hpp"
#include "../engine/interfaces/InterfazGrafica.hpp"
#include "../engine/util/SpriteSheet.hpp"
#include "../engine/mapa/include/TMXParser.h"
#include "../engine/mapa/CMapa.hpp"

//#define MAPA_PROPERTY_X_INIT_PLAYER "x_init_player_"
#define OBJECTSGROUP_PLAYERS_NAME "players"
#define OBJECT_PLAYER_NAME "Player"
#define MAPA_PROPERTY_N_VIDAS_PLAYER       "player_n_vidas"
#define MAPA_PROPERTY_N_BOMBAS             "player_n_bombas"
#define MAPA_PROPERTY_ALCANCE_BOMBAS       "player_alcance_bombas"
#define MAPA_PROPERTY_ID_TILE_LLAMAS                "id_tile_on_fire"
#define MAPA_PROPERTY_TILE_PISO_SIN_SOMBRA          "id_tile_piso_sin_sombra"
#define MAPA_PROPERTY_TILE_PISO_SOMBRA_ROMPIBLE     "id_tile_piso_sombra_rompible"
#define MAPA_PROPERTY_TILE_PISO_SOMBRA_NO_ROMPIBLE  "id_tile_piso_sombra_no_rompible"

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

class NivelMapa: public Mapa {
public:

    enum ExtremoColision{
        NINGUNO,
        TOPLEFT,
        TOPRIGHT,
        BOTTOMRIGHT,
        BOTTOMLEFT
    };

    NivelMapa(int x, int y);

    static SDL_Texture * getPreviewTerreno(char rutaMapa[],MetaData * params,LTexture * img_tile,LTexture * imgs_players[],int x,int y);
    bool contain(SDL_Rect rect);
    int getTileAt(int x, int y);
    ExtremoColision colision(SDL_Rect  rect, int * num_colisiones, bool soloBloquesNoTraspasables=false);

    int getTileWidth();

    int getTileHeight();

    bool esBloqueSolido(int x, int y);

    bool esBloqueRompible(int x, int y);

    std::string getPropertyTile(int id_tile, std::string clave);

    int getPosXPlayer(IdPlayer player);

    int getPosYPlayer(IdPlayer player);

    std::vector<std::string> * getAnimacionFrames(const std::string &basic_string);

    SpriteSheet * getSpriteSheetTiles();

    std::string getRutaTileSet();

    int getNFilasTileSet();

    int getNColumnasTileSet();

    bool romperBloque(int x, int y);

    int getIndiceMapaAt(int x, int y);

    int getIndiceFilaMapaAt(int y);

    int getIndiceColumnaMapaAt(int x);

    int getX();

    int getY();
};
#endif
