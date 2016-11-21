#include "dat_nivel.hpp"

DatNivel::DatNivel(){
    iniciar();
}

void DatNivel::iniciar(){
    for(int i=0;i<_PLAYERS;i++){
       x_init[i]=0;
       y_init[i]=0;
    }
    bombas_ini=vidas_ini=alcance_ini=id_tile=items=0;
}

DatNivel::DatNivel(char ruta[]){
    id_tile=std::stoi(buscar_dato(ruta,"id_tile"));
    if(id_tile<0)id_tile=0;
    items=std::stoi(buscar_dato(ruta,"items"));
    if(items<0)items=0;
    bombas_ini=std::stoi(buscar_dato(ruta,"bombas"));
    if(bombas_ini<0)bombas_ini=0;
    vidas_ini=std::stoi(buscar_dato(ruta,"vidas"));
    if(vidas_ini<0)vidas_ini=0;
    alcance_ini=std::stoi(buscar_dato(ruta,"alcance"));
    if(alcance_ini<0)alcance_ini=0;
    
    char ruta1[50];
    for(int i=0;i<5;i++){
        sprintf(ruta1,"x_init_player_%d",i+1);
        x_init[i]=std::stoi(buscar_dato(ruta,ruta1));
        if(x_init[i]<0)x_init[i]=0;

        sprintf(ruta1,"y_init_player_%d",i+1);
        y_init[i]=std::stoi(buscar_dato(ruta,ruta1));
        if(y_init[i]<0)y_init[i]=0;
    }
        
}
void DatNivel::guardar(char rutaDestino[]){
    ofstream fnivel(rutaDestino);
    fnivel << "bombas:"<<bombas_ini<<endl;
    fnivel << "vidas:"<<vidas_ini<<endl;
    fnivel << "alcance:"<<alcance_ini<<endl;
    fnivel << "id_tile:"<<id_tile<<endl;
    fnivel << "items:"<<items<<endl;

    for(int i=0;i<5;i++){
        fnivel << "x_init_player_"<<i+1<<":"<<x_init[i]<<endl;
        fnivel << "y_init_player_"<<i+1<<":"<<y_init[i]<<endl;
    }
    fnivel.close();
}


int DatNivel::getX(int id_player){
    return x_init[id_player];
}
int DatNivel::getY(int id_player){
    return y_init[id_player];
}
void DatNivel::setX(int id_player,int nuevo){
    x_init[id_player]=nuevo;
}
void DatNivel::setY(int id_player,int nuevo){
    y_init[id_player]=nuevo;
}
int DatNivel::getBombas(){
    return bombas_ini;
}
int DatNivel::getVidas(){
    return vidas_ini;
}
int DatNivel::getAlcanceBombas(){
    return alcance_ini;
}
int DatNivel::getIdTile(){
    return id_tile;
}
int DatNivel::getNumItems(){
    return items;
}
