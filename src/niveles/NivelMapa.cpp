#include "NivelMapa.hpp"






/**
 * Detecta si uno de los extremos del rectangulo colisiona con un bloque con la propiedad de solido
 * @param rect rectangulo
 * @param num_colisiones Numero de extremos en colision
 * @param soloBloquesNoTraspasables
 * @return El ultimo extremo detectado que colisiona
 *
 * Nota, en el caso que sea un player el que quiera detectar la colision éste usa un cuadro de colision(size=10) menor
 * que el de los tiles(size=16) por lo que num_colisiones será 1 o 2.
 *
 * Se regresa i + 1 , para que el 0 represente NO COLISION, el i + 1 significa:
 *
 *  1 --> extremo TOP-LEFT
 *  2 --> extremo TOP-RIGHT
 *  3 --> extremo BOTTOM-RIGHT
 *  4 --> extremo BOTTOM-LEFT
 */
NivelMapa::ExtremoColision NivelMapa::colision(SDL_Rect rect, int * num_colisiones,bool soloBloquesNoTraspasables) {
//solo detecta la colision en las esquinas del rect

    int ret=0;

    //std::string tile_id = "0";

    int id_tile = 0;

    // Se evaluan los extremos en el orden-->
    // TOP-LEFT , TOP-RIGHT , BOTTOM-RIGHT,BOTTOM-LEFT
    for(int i=0;i<4;i++){ // Los 4 extremos

        // obtenemos el id del bloque en el extremo
        id_tile = getTileAt(rect.x + (rect.w * (i != 0 && i != 3)), rect.y + rect.h * (i >= 2));

        if(id_tile >= 0){ // Si existe tal tile

            // Si colisiona con un bloque solido
            if(getPropertyTile(id_tile, TILE_PROPERTY_SOLIDO) == "1") {
                /// Si se quiere que solo sean los bloques que no se pueden traspasar
                // Eso equivale a decir que se quieren los solidos tales que no sean rompibles(por explosiones)
                if(soloBloquesNoTraspasables){
                    if(getPropertyTile(id_tile,TILE_PROPERTY_ROMPIBLE) == "0"){
                        if(num_colisiones)
                            (*num_colisiones)++;
                        ret=i+1;
                    }
                }else{ // Si solo basta con que sean solidos
                    if(num_colisiones)
                        (*num_colisiones)++;
                    ret=i+1;
                }
            }
        }

    }

    return (ExtremoColision) ret;
}

int NivelMapa::getTileAt(int x, int y) {
    //solo detecta la colision en las esquinas del rect

    //int ret             = 0;
    int indice = getIndiceMapaAt(x,y);

    if(indice >=0)return mLayerMapa[indice];

    return -1;

}

int NivelMapa::getIndiceFilaMapaAt(int y){
    if(y < 0) return -1;

    auto index_fila    = y / mTileHeight;
    if(index_fila  >= mMapHeight){
        return -1;
    }
    return index_fila;
}

int NivelMapa::getIndiceColumnaMapaAt(int x){
    if(x < 0) return -1;
    auto index_columna   = x / mTileWidth;
    if(index_columna  >= mMapWidth){
        return -1;
    }
    return index_columna;
}

int NivelMapa::getIndiceMapaAt(int x,int y){

    int index_fila    = getIndiceFilaMapaAt(y);
    if(index_fila  == -1){
        return -1;
    }

    int index_columna   = getIndiceColumnaMapaAt(x);
    if(index_columna  == -1){
        return -1;
    }

    return index_fila * mMapWidth + index_columna;;
}
SDL_Texture * NivelMapa::getPreviewTerreno(char rutaMapa[],MetaData * params,LTexture * img_tile,LTexture * imgs_players[],int x,int y){
/*
    SDL_Surface * preview=SDL_GetVideoSurface(),*imagen_redimensionada;
    char ruta[50],mapa[MAXMAP + 1],variable[50];
    int i;
    SDL_Rect rect_destino;

//    sprintf(ruta,"data/niveles/batalla/%d.map",id + 1);
    cargarMapaDeArchivoBin(rutaMapa,mapa);

    SDL_FillRect(preview,0,0);
    if(params)
        draw(preview,img_tile,mapa,x,y,params->getIdTile());
    else
        draw(preview,img_tile,mapa,x,y,0);

    if(params){
//        sprintf(ruta,"data/niveles/batalla/%d.ini",id + 1);

        for(i=0;i<_PLAYERS;i++){
            rect_destino.x=params->getX(i);
            rect_destino.y=params->getY(i);
            imprimir_desde_grilla(imgs_players[i],6,preview,rect_destino.x,rect_destino.y,1,12,0);
        }

    }


    imagen_redimensionada=(SDL_Surface * )zoomSurface(preview, 0.3515, 0.4979, 1);
    SDL_FreeSurface(preview);
    return imagen_redimensionada;*/
    return nullptr;
}

bool NivelMapa::contain(SDL_Rect rect) {
    return !(rect.x < 0 || rect.y < 0
           ||rect.x+rect.w > 0 + mTmxParser->mapInfo.width*mTmxParser->mapInfo.tileWidth
           ||rect.y+rect.h > 0 + mTmxParser->mapInfo.height*mTmxParser->mapInfo.tileHeight);
}

int NivelMapa::getTileWidth() {
    return mTileWidth;
}

int NivelMapa::getTileHeight() {
    return mTileHeight;
}

bool NivelMapa::esBloqueSolido(int x, int y) {

    int id_tile = getTileAt(x, y);

    if(id_tile >= 0) { // Si existe tal tile
        return getPropertyTile(id_tile, TILE_PROPERTY_SOLIDO) == "1";
    }
    return false;
}
std::string NivelMapa::getPropertyTile(int id_tile, std::string clave){
    return mTmxParser->tilesetList[0].tilesMetaData[std::to_string(id_tile)].property[clave];
}

bool NivelMapa::esBloqueRompible(int x, int y) {
    int id_tile = getTileAt(x, y);

    if(id_tile >= 0) { // Si existe tal tile
        return getPropertyTile(id_tile, TILE_PROPERTY_ROMPIBLE) == "1";
    }
    return false;
}

int NivelMapa::getPosYPlayer(IdPlayer player) {
    return mTmxParser->objectGroup[OBJECTSGROUP_PLAYERS_NAME].object[OBJECT_PLAYER_NAME + std::to_string(player + 1)].y;
}

int NivelMapa::getPosXPlayer(IdPlayer player) {
    return mTmxParser->objectGroup[OBJECTSGROUP_PLAYERS_NAME].object[OBJECT_PLAYER_NAME + std::to_string(player + 1)].x;
}

std::vector<std::string> * NivelMapa::getAnimacionFrames(const std::string & id_tile) {
    return &mTmxParser->tilesetList[0].tilesMetaData[id_tile].animation;
}

SpriteSheet *NivelMapa::getSpriteSheetTiles() {
    return mSprtSTiles;
}

int NivelMapa::getNFilasTileSet() {
    return mTmxParser->tilesetList[0].tileCount/mTmxParser->tilesetList[0].columns;
}

std::string NivelMapa::getRutaTileSet() {
    return mTmxParser->tilesetList[0].imgSource.source;
}

int NivelMapa::getNColumnasTileSet() {
    return mTmxParser->tilesetList[0].columns;
}

bool NivelMapa::romperBloque(int x, int y) {

    if(!esBloqueRompible(x,y)) return false;

    // Obtenemos el indice del tile a esa posicion
    int indice = getIndiceMapaAt(x,y);

    int id_tile_piso_sombra_rompible = std::stoi(getMapProperty(MAPA_PROPERTY_TILE_PISO_SOMBRA_ROMPIBLE));
    int id_tile_piso_sombra_no_rompible = std::stoi(getMapProperty(MAPA_PROPERTY_TILE_PISO_SOMBRA_NO_ROMPIBLE));
    int id_tile_piso_sin_sombra = std::stoi(getMapProperty(MAPA_PROPERTY_TILE_PISO_SIN_SOMBRA));

    //Buscamos el tile animado que representaba el tile en esa posición
    auto setTileAnimado = mGrpTilesAnimados.collide(SDL_Rect {x + getX(),y + getY(),(int)mTileWidth,(int)mTileHeight});

    //Eliminamos las animaciones en esa posicion
    auto pitTileAnimado = setTileAnimado.begin();
    while(pitTileAnimado != setTileAnimado.end()){
        (*pitTileAnimado)->kill();
        pitTileAnimado++;
    }

    // Si el que esta arriba de él es solido ponemos un tile con sombra debajo
    if(esBloqueSolido(x, y - mTileHeight)){
        if(esBloqueRompible(x,y-mTileHeight))
            mLayerMapa[indice] =  id_tile_piso_sombra_rompible;
        else
            mLayerMapa[indice] =  id_tile_piso_sombra_no_rompible;
    }else{
        mLayerMapa[indice] = id_tile_piso_sin_sombra;
    }

    // si el que esta debajo es un tile piso con sombra lo ponemos sin sombra ya que no hay quien le genere la sombra
    indice = getTileAt(x,y + mTileHeight);
    if(indice == id_tile_piso_sombra_rompible || indice == id_tile_piso_sombra_no_rompible){
        mLayerMapa[getIndiceMapaAt(x,y+mTileHeight)] = id_tile_piso_sin_sombra;
    }

    return true;

}

int NivelMapa::getX() {
    return mRectDest.x;
}
int NivelMapa::getY() {
    return mRectDest.y;
}

NivelMapa::NivelMapa(int x, int y) : Mapa(x, y) {}


