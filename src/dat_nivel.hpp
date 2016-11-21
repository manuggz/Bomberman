#ifndef DAT_NIVEL_HPP
#define DAT_NIVEL_HPP
#include <iostream>
#include <fstream>
#include "constantes.hpp"
#include "util.hpp"

using namespace std;

class DatNivel{
    public:
        DatNivel();
        DatNivel(char ruta[]);
        /*getters*/
        int getX(int id_player);
        int getY(int id_player);
        int getBombas();
        int getVidas();
        int getAlcanceBombas();
        int getIdTile();
        int getNumItems();
        /*setters*/
        void setX(int id_player,int nuevo);
        void setY(int id_player,int nuevo);
        void setBombas(int nuevo){bombas_ini=nuevo;};
        void setVidas(int nuevo){vidas_ini=nuevo;};
        void setAlcanceBombas(int nuevo){alcance_ini=nuevo;};
        void setIdTile(int nuevo){id_tile=nuevo;};
        void setNumItems(int nuevo){items=nuevo;};

        /*Guarda el file como bin*/
        void guardar(char rutaDestino[]);
        
        /*Incia los datos*/
        void iniciar();    
    private:
        int bombas_ini;
        int vidas_ini;
        int alcance_ini;
        int x_init[_PLAYERS];
        int y_init[_PLAYERS];
        int id_tile;
        int items;
};


#endif
