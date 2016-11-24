#include "explosion.hpp"

Explosion::Explosion(InterfazJuego * juego,SDL_Renderer * gRenderer, Player * playerLanzador):
    Animacion(new SpriteSheet(gRenderer,"data/imagenes/objetos/explosion.bmp",5,8,true),"0,1,2,3,4,4,3,2,1,1,0"){

    this->mJuego=juego;
    
    mPlayerCreador = playerLanzador;

}

void Explosion::detectarAlcances(){

    mAlcanceLlamas = mPlayerCreador->getAlcanceBombas();

    // Detectamos el alcance de las flamas en las direcciones posibles
    detectarAlcance(DERECHA,mSprSCuadros->getWidthCuadro(),0);
    detectarAlcance(IZQUIERDA,-mSprSCuadros->getWidthCuadro(),0);
    detectarAlcance(ABAJO,0,mSprSCuadros->getHeightCuadro());
    detectarAlcance(ARRIBA,0,-mSprSCuadros->getHeightCuadro());

}
/**
 * Detecta el alcance de una flama en una direccion tal como hacia la derecha,izquierda,...
 *
 * Al mismo tiempo detecta colisiones con el entorno activando las acciones correspondientes.
 *
 * El aum_x y aum_y dependen de la direccion, si es hacia la derecha entonces aum_x debe ser positivo y aum_y 0
 * @param dir  Direccion hacia donde la flama va a crecer
 * @param aum_x
 * @param aum_y
 */
void Explosion::detectarAlcance(int dir,int aum_x,int aum_y){

    deque<Sprite *> setColisionBombas;
    deque<Sprite *> setColisionItems;
    //int globo_anyadido;

    // Creamos un cuadro de colision del tamaño de un tile ocupado por la flama
    // Este sera el que moveremos para chequear si estamos dentro del mapa y con quien colisonamos
    SDL_Rect coli={0,0,mSprSCuadros->getWidthCuadro(),mSprSCuadros->getWidthCuadro()};

    // Al inicio la explosión tiene alcance de cero en esa direccion
    alcances[dir] = 0;

    // Realizamos un bucle desde 0 hasta el alcance que tenga el player en esa direccion
    // Realizando en cada iteracion una comprobacion de con quien colisionamos y actualizando el alcance
    for(int i=1 ; i < mAlcanceLlamas+1 ; i++){

        // Posicionaos el cuadro de colision en la posicion a evaluar
        // Posicion inicial de la flama adelantada en la direccion a evaluar
        // Notar que no se esta tomando en cuenta el centro de la explosion
        // No tiene sentido de acuerdo a que no debería haber nada ahí si la explosion sigue a la destruccion de una bomba
        coli.x        = x + aum_x*i;
        coli.y        = y + aum_y*i;

        if(mJuego->isOutOfMapBounds(coli)){
            return;;
        }
        /*if(coli.x<juego->getEjeXVisual()||\
           coli.x+coli.w>juego->getEjeXVisual()+juego->getAnchoMapa()||\
           coli.y<juego->getEjeYVisual()||\
           coli.y+coli.h>juego->getEjeYVisual()+juego->getAltoMapa()){
            --alcances[dir];
            return;
        }*/

        setColisionBombas = mJuego->colisionConBombas(coli);
        // Si colisiona con alguna bomba detenemos el alcanze
        if(setColisionBombas.size() > 0){
            // Aceleramos el tiempo de explosion de las bombas con las que colisonamos
            auto pBomba = setColisionBombas.begin();
            while(pBomba != setColisionBombas.end()){
                dynamic_cast<Bomba * >((*pBomba))->setRepeticiones(0);
                pBomba++;
            }

            //juego->setRepeticionBomba(setColisionBombas,0);//se acelera el 'explote'
            return;
        }

//        if(juego->isBloqueDuro(coli.x,coli.y)||esBloqueRompible||setColisionItems!=-1){


        // Si colision con un bloque solido detenemos el alcance por razones obvias
        if(mJuego->esBloqueSolido(coli.x,coli.y)){
            // Si colisiona con un bloque rompible y en esa posicion no hay un bloque en llamas
            // Agregamos un bloque en llamas en esa posicion
            // Fijarse que es necesario verificar que no exista un bloque en llamas en esa posicion
            // Porque otra explosion pudo detectar ese bloque rompible en esa posicion y ya haber agregado un bloque en llamas
            // Esto es porque el tile en esa posicion no se cambia de uno "rompible" a uno con "piso" una vez es alcanzado
            // por una llama, sino, cuando el bloque en llamas termina su animación.
            // Esto es para que las explosiones como es este caso no sigan de largo a travez del bloque en llama
            // Sino que se detengan ahí.
            if(mJuego->esBloqueRompible(coli.x,coli.y) && mJuego->colisionBloqueEnLlamas(coli).size()==0){
                mJuego->agregarBloqueEnLlamas(coli.x,coli.y);
            }
            return;
        }

        setColisionItems  = mJuego->colisionConItems(coli);
        if(setColisionItems.size() > 0) {
            auto pItem = setColisionItems.begin();
            while (pItem != setColisionItems.end()) {
                (*pItem)->kill();
//                mJuego->eliminarSprite((*pItem));
//                        new Animacion(new SpriteSheet("data/imagenes/")
//                juego->getImagen(IMG_ITEM_FIRE), 1, 7, "0,0,0,1,1,2,2,2,3,3,4,4,5,5,6,6", coli.x, coli.y));
//                juego->killSprite((*pItem));
//                pBomba++;
                pItem++;
            }
            return;
        }

            /*if(juego->getTipoItem(setColisionItems)!=Item::ITEM_PUERTA){
                juego->addSprite(new Animacion(juego->getImagen(IMG_ITEM_FIRE),1,7,"0,0,0,1,1,2,2,2,3,3,4,4,5,5,6,6",coli.x,coli.y));
                juego->killSprite(ITEM,setColisionItems);
            }else{*/
//                 int x,y;
//                 juego->getPosicion(ITEM,setColisionItems,x,y);
//                     globo_anyadido=juego->addSprite(GLOBO,new Globox,y);
//                     if(globo_anyadido!=-1)
//                        juego->setProteccion(GLOBO,globo_anyadido,true);
        //}

        alcances[dir] = i;

    }

}

/**
 * Dibuja la Flama en una direccion
 * Al igual que detectar_alcance se requiere la direccion y el aum_x y aum_y
 *
 * Las explosiones estan divididas en el cuadro "normal" el cual basicamente no es el final
 * y el cuadro final que representa el "final" de la flama.
 * El cuadro normal se debe alargar tod el alcance de la flama a excepcion del alcance final
 * que es donde se dibuja el cuadro "final"
 * @param dir
 * @param aum_x
 * @param aum_y
 * @param cuadro_normal
 * @param cuadro_final
 * @param gRenderer
 */
void Explosion::dibujarFlama(int dir,int aum_x,int aum_y,int cuadro_normal,int cuadro_final,SDL_Renderer * gRenderer) {
    int i;
	int x,y;

    // Dibujamos los cuadros normales, alargandolo hasta el alcance maximo de la flama - 1(el cuadro final)
    for(i=1 ; i < alcances[dir];i++) {
        x = this->x + aum_x*i;
        y = this->y + aum_y*i;
        //if(x+16>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)

        // Notar el uso de getCuadro(), esto es para obtener el respectivo cuadro de la animacion
        mSprSCuadros->setCurrentCuadro(cuadro_normal + mSprSCuadros->getNColumnas()*getCuadro());
        mSprSCuadros->draw(gRenderer,x,y);
        //imprimir_desde_grilla (mJuego->getImagen(IMG_EXPLOSION),cuadro_normal+COLUMNAS_EXPLO*getCuadro(),gRenderer, x,y,FILAS_EXPLO,COLUMNAS_EXPLO,0);
    }

    // Posicion de la flama final
    x = this->x+aum_x*i;
    y = this->y+aum_y*i;

    //if(x+10>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0){
    if(alcances[dir] > 0){
        if(alcances[dir] == mAlcanceLlamas) { // Si nos hemos extendido el máximo
            // Dibujamos la punta de la flama porque nos hemos extendido tod lo que podiamos
            mSprSCuadros->setCurrentCuadro(cuadro_final + mSprSCuadros->getNColumnas()*getCuadro());
        }else{
            // Dibujamos un cuadro normal porque hemos chocado con algo que nos ha impedido extendernos tod lo que podiamos
            mSprSCuadros->setCurrentCuadro(cuadro_normal + mSprSCuadros->getNColumnas()*getCuadro());
        }
        mSprSCuadros->draw(gRenderer,x,y);
    }
    //}
}


void Explosion::draw(SDL_Renderer * gRenderer){

    //if(x+10>0&&x<W_SCREEN&&y<H_SCREEN&&y+16>0)
    //DIBUJAMOS EL CENTRO
    mSprSCuadros->setCurrentCuadro(2 + mSprSCuadros->getNColumnas()*getCuadro());
    mSprSCuadros->draw(gRenderer,x,y);

    dibujarFlama(DERECHA,mSprSCuadros->getWidthCuadro(),0,3,4,gRenderer);
    dibujarFlama(IZQUIERDA,-mSprSCuadros->getWidthCuadro(),0,1,0,gRenderer);
    dibujarFlama(ABAJO,0,mSprSCuadros->getHeightCuadro(),6,7,gRenderer);
    dibujarFlama(ARRIBA,0,-mSprSCuadros->getHeightCuadro(),6,5,gRenderer);


}

bool Explosion::colision(SDL_Rect & rect_coli){

    //COLISION CON EL EJE X de la bomba
    rect.x=x - alcances[IZQUIERDA]*mSprSCuadros->getWidthCuadro();
    rect.y=y;
    rect.w=alcances[IZQUIERDA]*mSprSCuadros->getWidthCuadro()+mSprSCuadros->getWidthCuadro() +
            alcances[DERECHA]*mSprSCuadros->getWidthCuadro();
    rect.h=16;
    if(rects_colisionan(rect,rect_coli))
        return true;

    //COLISION CON EL EJE Y de la bomba
    rect.w=16;
    rect.x=x;
    rect.y=y - alcances[ARRIBA]*mSprSCuadros->getHeightCuadro();
    rect.h=alcances[ARRIBA]*mSprSCuadros->getHeightCuadro()+mSprSCuadros->getHeightCuadro() +
            alcances[ABAJO]*mSprSCuadros->getHeightCuadro();

    if(rects_colisionan(rect,rect_coli))
        return true;

    return false;
     
}

Player *Explosion::getCreador() {
    return mPlayerCreador;
}
