//
// Created by manuggz on 14/12/16.
//

#ifndef TETRIS_ANIMARCAIDABLOQUES_HPP
#define TETRIS_ANIMARCAIDABLOQUES_HPP

#include <deque>
#include "Tetromino.hpp"

class AnimarCaidaBloques{
public:
    ~AnimarCaidaBloques(){

    }

    void agregar(Tetromino * pBloque){
        bloques.push_back(pBloque);
    }

    void update(){

    }
private:
    std::deque<Tetromino *> bloques;
};
#endif //TETRIS_ANIMARCAIDABLOQUES_HPP
