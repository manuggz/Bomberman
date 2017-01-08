#include "../../engine/GameManager/game_manager.hpp"
#include "OthelloInterfaz.hpp"


int main(int argc, char *argv[]){
    GameManager juego ("Othello v0.1","",1024,768,true);
    juego.cambiarInterfaz(new OthelloInterfaz(&juego));
    juego.run();
    return EXIT_SUCCESS;
}
