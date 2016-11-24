#include "engine/util/game_manager.hpp"
#include "Interfaces/menu.hpp"
#include "Interfaces/MenuPrincipal.hpp"

/*
  Name: DestructionBombs
  Copyright: GNU/GPL v3
  Author: Manuel Gonzalez @manuelggz
  Date: 21/04/12 22:14
  Description: Remake del famoso bomberman
  me puedes dar tus comentarios por aqui deathmanuel@gmail.com o en mi blog http://baulprogramas.blogspot.com

  si no entiendes algo hazmelo saber con gusto te respondere
  Lineas de codigo a esta fecha:5672
*/

int main(int argc, char *argv[]){
    GameManager * juego=new GameManager();
    juego->cambiarInterfaz(new MenuPrincipal(juego));
    juego->run();
    delete juego;
    return EXIT_SUCCESS;
}
