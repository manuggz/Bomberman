#include "../../engine/GameManager/game_manager.hpp"
#include "Menu.hpp"


int main(int argc, char *argv[]){
    GameManager juego ("Tetris v0.1","",1024,768,true);
    juego.cambiarInterfaz(new Menu(&juego));
    juego.run();
    return EXIT_SUCCESS;
}
