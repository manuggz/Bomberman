//
// Created by manuggz on 22/11/16.
//

#ifndef BOMBERMAN_INTERFAZGALERIA_HPP
#define BOMBERMAN_INTERFAZGALERIA_HPP

#include "../util/LTexture.hpp"
#include "../../constantes.hpp"

class InterfazGaleria{

public:
   virtual LTexture * getImagen(CodeImagen code) = 0;
};
#endif //BOMBERMAN_INTERFAZGALERIA_HPP
