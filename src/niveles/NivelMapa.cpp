#include "NivelMapa.hpp"



/*void Mapa::leerInfTile(char ruta[]){
    char key[50],valor[50];
    std::ifstream ftile(ruta);
    while(!ftile.eof()){
        ftile >> key;
        if(!strcmp(key,"IMG_FONDO")){
            ftile >> valor;
            if(!strcmp(valor,"FONDO_1"))
                idFondo=IMG_FONDO_PARTI;
            else if(!strcmp(valor,"FONDO_2"))
                idFondo=IMG_FONDO_EDIFICIOS;
            else if(!strcmp(valor,"FONDO_3"))
                idFondo=IMG_FONDO_METAL;
        }else if(!strcmp(key,"EJES")){
            ftile>>coorXPredVisualizacion>>coorYPredVisualizacion;
        }else if(!strcmp(key,"Y_TABLERO")){
            ftile>>yTablero;
        }else{
            ftile>>valor;
        }
    }
    ftile.close();
    
}
*/
/*bool Mapa::cargarMapaDeArchivoBin(std::string rutaMapaBin,char * buffer){

    std::ifstream fileMapa(rutaMapaBin,std::ios::in|std::ios::binary);
    if(!fileMapa){
        std::cerr << "WARNING-Error leyendo un archivo: -- Ruta: "<<rutaMapaBin<<std::endl;
        return false;
    }
    fileMapa.read(reinterpret_cast<char *> (buffer),MAXMAP);
    fileMapa.close();
    
    return true;
}
*/

/*int Mapa::setItems(){

    /*int itemsPuestos=0;
    int random_x=0;
    int random_y=0;

    while(itemsPuestos < mDatMapa->getNumItems()){
            if(bloquesMadera>0){
                do{
                    random_x=rand()%COLUMNAS;
                    random_y=rand()%FILAS;
                }while(tilesMap[random_y*COLUMNAS+random_x]!=BLOQUE_MADERA);
    
                tilesMap[random_y*COLUMNAS+random_x]=BLOQUE_ITEM;
                bloquesMadera--;
                if(tileXPuerta==-1||tileYPuerta==-1){ /*Si aun no se ha establecido la puerta nota:la segunda condicional nunca se evaluara*
                    tileXPuerta=random_x;
                    tileYPuerta=random_y;
                }
                itemsPuestos++;
            }
            else{
                break;
            }
    }
    mDatMapa->setNumItems(itemsPuestos);
    return itemsPuestos;*

}*/
/*int Mapa::setEnemigos(){
    int indice,colocados=0;
    for(int i=0;i<FILAS;i++)
        for(int j=0;j<COLUMNAS;j++){
            indice=tilesMap[i*COLUMNAS+j];
            if(indice==BLOQUE_ENEMIGO){
                  tilesMap[i*COLUMNAS+j]=BLOQUE_PISO;
                  colocados++;
//                  parent->addSprite(GLOBO,2,j * W_H_BLOQUE+EJE_X,i * W_H_BLOQUE+EJE_Y);
            }
        }
    return colocados;
}*

bool Mapa::isBloqueRompible(int x,int y){

    int tipoBloque=getTipoBloque(x,y);
    if(tipoBloque!=-1)
        return tipoBloque==BLOQUE_ITEM||tipoBloque==BLOQUE_MADERA;
    
    std::cout << "Warning: Acceso invalido al mapa,X:"<<x <<"Y:"<<y<<std::endl;
    return false;
}

bool Mapa::romperBloque(int x,int y){
    if(isBloqueRompible(x,y)){
        if((y==getEjeYVisualizacion())||\
           (y!=getEjeYVisualizacion()&&getTipoBloque(x,y-16)!=BLOQUE_PISO&&getTipoBloque(x,y-16)!=BLOQUE_PISO_SOMBRA))
            tilesMap[getIndiceMapa(x,y)]=BLOQUE_PISO_SOMBRA;
        else
            tilesMap[getIndiceMapa(x,y)]=BLOQUE_PISO;
        if(y+16!=getEjeYVisualizacion()+getAltoMapa()&&getTipoBloque(x,y+16)==BLOQUE_PISO_SOMBRA)
            tilesMap[getIndiceMapa(x,y+16)]=BLOQUE_PISO;
        return true;
    }
    return false;
}*/



/**
 * Detecta si uno de los extremos del rectangulo colisiona con un bloque con la propiedad de solido
 * @param rect rectangulo
 * @param num_colisiones Numero de extremos en colision
 * @param solo_bloques_duros
 * @return El ultimo extremo detectado que colisiona
 */
int NivelMapa::colision(SDL_Rect rect, int * num_colisiones,bool solo_bloques_duros) {
//solo detecta la colision en las esquinas del rect

    int ret=0;

    //std::string tile_id = "0";

     int id_tile = 0;

    for(int i=0;i<4;i++){ // Los 4 extremos

        // obtenemos el id del bloque en el extremo
        id_tile = getBloqueAt(rect.x + (rect.w*(i!=0&&i!=3)),rect.y + rect.h * (i >= 2));

        if(id_tile >= 0){ // Si existe tal tile
            if(getPropertyTile(id_tile, TILE_PROPERTY_SOLIDO) == "1") {
                if(num_colisiones)
                    (*num_colisiones)++;
                ret=i+1;
            }
        }

    }

    /*
    if(!solo_bloques_duros){
        if(  mLayerMapa[indice]!=BLOQUE_PISO
           &&mLayerMapa[indice]!=BLOQUE_PISO_SOMBRA
           &&mLayerMapa[indice]!=BLOQUE_ENEMIGO){
            (*num_colisiones)++;
            ret=i+1;
        }
    }else if(solo_bloques_duros&&mLayerMapa[indice]==BLOQUE_METAL){
        (*num_colisiones)++;
        ret=i+1;
    }*/
    return ret;
}

int NivelMapa::getBloqueAt(int x,int y) {
    //solo detecta la colision en las esquinas del rect

    //int ret             = 0;
    unsigned int indice = 0;

    int index_fila, index_columna;

    index_fila    = y / mTileHeight;
    if(index_fila  == mMapHeight){
        return -1;
    }

    index_columna   = x / mTileWidth;
    if(index_columna  == mMapWidth){
        return -1;
    }

    indice = index_fila * mMapWidth + index_columna;

    return mLayerMapa[indice] - 1;
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

bool NivelMapa::cargar(SDL_Renderer *gRenderer, std::string ruta) {

    if(!Mapa::cargar(gRenderer, ruta)) return false;

    mTileHeight   = mTmxParser.mapInfo.tileHeight;
    mTileWidth    = mTmxParser.mapInfo.tileWidth;
    mMapWidth     = mTmxParser.mapInfo.width;
    mMapHeight    = mTmxParser.mapInfo.height;
    mpTilesMetaData = &mTmxParser.tilesetList[0].tilesMetaData;

    return true;
}

bool NivelMapa::contain(SDL_Rect rect) {
    return !(rect.x < 0 || rect.y < 0
           ||rect.x+rect.w > 0 + mTmxParser.mapInfo.width*mTmxParser.mapInfo.tileWidth
           ||rect.y+rect.h > 0 + mTmxParser.mapInfo.height*mTmxParser.mapInfo.tileHeight);
}

int NivelMapa::getTileWidth() {
    return mTileWidth;
}

int NivelMapa::getTileHeight() {
    return mTileHeight;
}

bool NivelMapa::esBloqueSolido(int x, int y) {

    int id_tile = getBloqueAt(x,y);

    if(id_tile >= 0) { // Si existe tal tile
        return getPropertyTile(id_tile, TILE_PROPERTY_SOLIDO) == "1";
    }
    return false;
}
std::string NivelMapa::getPropertyTile(int id_tile, std::string clave){
    return (*mpTilesMetaData)[std::to_string(id_tile)].property[clave];
}

bool NivelMapa::esBloqueRompible(int x, int y) {
    int id_tile = getBloqueAt(x,y);

    if(id_tile >= 0) { // Si existe tal tile
        return getPropertyTile(id_tile, TILE_PROPERTY_ROMPIBLE) == "1";
    }
    return false;
}

int NivelMapa::getPosYPlayer(IdPlayer player) {
    return mTmxParser.objectGroup[OBJECTSGROUP_PLAYERS_NAME].object[OBJECT_PLAYER_NAME + std::to_string(player + 1)].y;
}

int NivelMapa::getPosXPlayer(IdPlayer player) {
    return mTmxParser.objectGroup[OBJECTSGROUP_PLAYERS_NAME].object[OBJECT_PLAYER_NAME + std::to_string(player + 1)].x;
}

std::vector<std::string> * NivelMapa::getAnimacionFrames(const std::string & id_tile) {
    return &(*mpTilesMetaData)[id_tile].animation;
}

SpriteSheet *NivelMapa::getSpriteSheetTiles() {
    return mSprtSTiles;
}

int NivelMapa::getNFilasTileSet() {
    return mTmxParser.tilesetList[0].tileCount/mTmxParser.tilesetList[0].columns;
}

std::string NivelMapa::getRutaTileSet() {
    return mTmxParser.tilesetList[0].imgSource.source;
}

int NivelMapa::getNColumnasTileSet() {
    return mTmxParser.tilesetList[0].columns;
}


/*
TipoItem Nivel::getTipoNuevoItem(InterfazJuego inter){

    static TipoItem tipos[5]={ITEM_ALCANCE,ITEM_VIDA,ITEM_BOMBA,ITEM_PARED,ITEM_ALEATORIO};
    static int salido_anterior=-1;

    TipoItem indice=ITEM_ALCANCE;

    if(dat_nivel->getNumItems()>=1){
        switch(inter){
            case TIPO_NORMAL:
                 do
                    indice=tipos[rand() % 5 ];
                 while(indice==salido_anterior);
                salido_anterior=indice;
                break;
            case TIPO_BATALLA:
                do{
                    indice=tipos[rand() % 5 ];
                }while(indice==ITEM_PUERTA||indice==ITEM_VIDA||indice==ITEM_ALEATORIO);//mGrpItems no permitidos en modo batalla

                break;
            }

       dat_nivel->setNumItems(dat_nivel->getNumItems()-1); 
    }

    return indice;
}*/

/*
SDL_Surface * Mapa::getPreviewTerreno(int idTerreno,Interfaz * game){
    SDL_Surface * preview;
    SDL_Surface * img_players[5]={game->getImagen(IMG_PLAYER_1),
                              game->getImagen(IMG_PLAYER_2),
                              game->getImagen(IMG_PLAYER_3),
                              game->getImagen(IMG_PLAYER_4),
                              game->getImagen(IMG_PLAYER_5)};
                              
    sprintf(ruta,"data/niveles/batalla/%d.txt",idTerreno+ 1);
    data2=new DatNivel(ruta);
    sprintf(ruta,"data/niveles/batalla/%d.map",idTerreno+ 1);
    preview=Mapa::getPreviewTerreno(ruta,data2,game->getImagen((CodeImagen)(IMG_TILE_1+data2->getIdTile())),img_players,EJE_X,EJE_Y);
//        cout << "Creada: "<<previews_niveles[i]<<endl;
    delete data2;
}
*/
/*
void Nivel::cargarFiles(int num_nivel,InterfazJuego inter)
{
    char ruta1[50],ruta2[50];
    
    switch(inter){
        case TIPO_NORMAL:
            sprintf(ruta1,"data/niveles/historia/nivel_%d.map",num_nivel);
            sprintf(ruta2,"data/niveles/historia/%d.txt",num_nivel);
            break;
        case TIPO_BATALLA:
            sprintf(ruta1,"data/niveles/batalla/%d.map",num_nivel);
            sprintf(ruta2,"data/niveles/batalla/%d.txt",num_nivel);
            break;
        }
    cargarFileNivel(mapa,ruta1);
    
    if(dat_nivel)delete dat_nivel;
    dat_nivel=new DatNivel(ruta2);
}
*/
