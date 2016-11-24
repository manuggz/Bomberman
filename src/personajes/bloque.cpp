#include "bloque.hpp"


Bloque::Bloque(SpriteSheet *spriteSheet, std::string frames, int x, int y, int delayCambioFrame) : Animacion(
        spriteSheet, frames, x, y, delayCambioFrame) {
    //cout << "frames"<<frames<<endl;
}
