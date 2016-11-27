#include <deque>
#include "player.hpp"
#include "bomba.hpp"
#include "../engine/util/LTimer.hpp"
#include "../niveles/NivelMapa.hpp"
#include "../objetos/explosion.hpp"


/**
 * Inicializa lo minimo necesario de la clase
 * @param interfazGaleria
 * @param id
 */
Player::Player(InterfazJuego * interfazGaleria,IdPlayer id){
    //cout << "Constructor de Player:"<<this<<endl;

    mpJuego  = interfazGaleria;

    this->mPlayerId = id;

    // Tama#o del rectangulo el cual se usará para detectar la colision del player con su entorno
    rect.w = W_COLISION;
    rect.h = H_COLISION;

    cargarTeclas();
}

/**
 * Carga la configuracion del teclado del player
 */
void Player::cargarTeclas(){
    char tmp_ruta[40];
    sprintf(tmp_ruta,"data/configuracion/teclado_%d.dat",mPlayerId+1);

    if(!control.cargar(tmp_ruta,false)){//si no se puede cargar de un archivo
        //se asignan teclas por default
        control.setDefaultKeys(mPlayerId);
    }
}


/**
 * Actualiza al posicion del rectangulo de colision de acuerdo a las coordenadas X Y del personaje
 */
void Player::updateRectColision(){
    //actualiza el cuadro que representa al personaje en la colision
    rect.x = x + X_COLISION;
    rect.y = y + Y_COLISION;
}

/**
 * Actualiza al player
 * @param teclas
 */
void Player::update(const Uint8 * teclas){

    // Avanzamos la animacion
	avanzarAnimacion ();
    updateRectColision();

    // Dependiendo del estado actual del player llamamos a la funcion encargada de dicho estado
	switch (estado_actual){
        case EstadoSprite::PARADO:
		    parado (teclas);
			break;
		case EstadoSprite::IZQUIERDA:
			izquierda(teclas);
			break;
		case EstadoSprite::DERECHA:
			derecha(teclas);
			break;
		case EstadoSprite::ARRIBA:
			arriba(teclas);
			break;
		case EstadoSprite::ABAJO:
			abajo(teclas);
			break;
		case EstadoSprite::MURIENDO:break;
        default:
            cerr << "Error, player en estado inconsistente." << endl;
    }

    if(estado_actual != EstadoSprite::MURIENDO){
        // Si el estado es distinto de mueriendo, entonces el player esta activo en el juego
        // En ese caso una vez actualizado su estado se deben detectar colisiones con el entorno
        // Recordar que en mover_ip solo se detectaron colisiones que podian detener el movimiento
        // una vez realizado el movimiento hay que detectar si colisiona por ejemplo con un item
        if(!mEstaProtegido){//si no esta protegido

            // DETECTAMOS COLISIONES CON LAS EXPLOSIONES
            auto setColisionExplosiones = mpJuego->colisionConExplosiones(rect);

            auto pSpriteExplosion = setColisionExplosiones.begin();
            Player *mSpriteCausanteMuerte;
            if(pSpriteExplosion  != setColisionExplosiones.end()){
                // Notar que solo tomamos en cuenta la primera explosion
                // Esto es porque una vez que se colisiona con una explosion o se muere o se activa la proteccion

                // Decimos HEy! este es quien nos ha matado
                mSpriteCausanteMuerte = dynamic_cast<Explosion *>(*pSpriteExplosion)->getCreador();
                // Dejamos que el Juego se encarge de nosotros
                mpJuego->playerMuerto(this,mSpriteCausanteMuerte);
            }

        }else{//si esta protegido
            if(mTimer.getTicks() / 1000 >= mDuracionProteccion){
                mEstaProtegido=false;
            }
        }

        auto setColisionItems  = mpJuego->colisionConItems(rect);
        if(setColisionItems.size() > 0) {
            auto pItem = setColisionItems.begin();
            while (pItem != setColisionItems.end()) {
                (dynamic_cast<Item * >(*pItem))->setPlayerActivador(this);
                (*pItem)->kill(); // Dejamos que el Juego encargado de las eliminaciones se encargue del resto
                pItem++;
            }
            return;
        }

    }//fin "si no esta muriendo"


}

void Player::activarPoderItem(Item::TipoItem tipo){
    switch(tipo){
        case Item::ITEM_ALCANCE:
            if(mAlcanBombas < MAX_ALCANCE_EXPLOSION)
                mAlcanBombas++;
            break;
        case Item::ITEM_VIDA:
            mVidas++;
            break;
        case Item::ITEM_BOMBA:
            if(mNBombasDisponibles < MAX_BOMBAS)
                mNBombasDisponibles++;
            break;
        case Item::ITEM_ATRAVIESA_PAREDES:
            mPuedeAtravesarBloques=true;
            break;
        case Item::ITEM_ALEATORIO:
            //activarPoderItem(juego->getTipoNuevoItem(false));
            break;
        case Item::ITEM_BOMBA_MAX:
            mNBombasDisponibles = MAX_BOMBAS;
            break;
        case Item::ITEM_ALCANCE_MAX:
            mAlcanBombas        = MAX_ALCANCE_EXPLOSION;
            break;
        case Item::ITEM_PROTECCION:
            setProteccion(20);
            break;
        case Item::ITEM_BOLA_ARROZ:
            //setPuntaje(getPuntaje()+100);
            break;
        case Item::ITEM_PASTEL:
            //setPuntaje(getPuntaje()+120);
            break;
        case Item::ITEM_PALETA:
            //setPuntaje(getPuntaje()+120);
            break;
        case Item::ITEM_BARQUILLA:
            //setPuntaje(getPuntaje()+50);
            break;
        case Item::ITEM_MANZANA:
            //setPuntaje(getPuntaje()+250);
            break;
        case Item::ITEM_PATINETA:
            mVelocidad=2;
            break;
        case Item::ITEM_CORAZON:
            mCorazones++;
            break;
        case Item::ITEM_ATRAVIESA_BOMBAS:
            mPuedeAtravesarBombas=true;
            break;
        case Item::ITEM_PATEA_BOMBA:
            mPuedePatearBombas=true;
            break;
        default:
            break;
        }
}

void Player::draw(SDL_Renderer * gRenderer){
    if(estado_actual!=MURIENDO)
    	imprimir_desde_grilla (mpJuego->getImagen((Galeria::CodeImagen)(Galeria::CodeImagen::IMG_PLAYER_1 + mPlayerId)), cuadro,gRenderer, x,y,1, 12,mEstaProtegido);
    else
    	imprimir_desde_grilla(mpJuego->getImagen((Galeria::CodeImagen)(Galeria::CodeImagen::IMG_PLAYER_1_MURIENDO + mPlayerId)), cuadro,gRenderer,x,y,1, 4,0);
//    if(mEstaProtegido)render_texture(juego->getTexture(IMG_FONDO_BLANCO),x,y,screen);
	/*DIBUJA EL CUADRO QUE REPRESENTA LA COLISION DEL PERSONAJE*/
#ifdef DEBUG
            updateRectColision();
            SDL_FillRect(screen,&rect,SDL_MapRGB (screen->format, 0, 0, 255));
#endif
}


void Player::ponerBomba(const Uint8 * teclas){
    TipoSprite conjun_coli[]={BOMBA,GLOBO,NIVEL,ITEM};

    updateRectColision();
	if(!mMantieneAccionPresionado&&isPressed(TECLA_ACCION,teclas)
       &&mNBombasColocadas < mNBombasDisponibles){

           mpUltimaBomba = mpJuego->agregarBomba(this);
           /*si se logro agregar*/
           if(mpUltimaBomba != nullptr){
               mNBombasColocadas++;
            }
        }

	mMantieneAccionPresionado = isPressed(TECLA_ACCION,teclas);
}

bool Player::colision(SDL_Rect & rect){
    updateRectColision();
    return rects_colisionan(this->rect,rect);
}

void Player::parado(const Uint8 * teclas) {
        if(isPressed(TECLA_ARRIBA,teclas))
            cambiarEstado(ARRIBA);
    
        if(isPressed(TECLA_ABAJO,teclas))
            cambiarEstado (ABAJO);
    
        if(isPressed(TECLA_IZQUIERDA,teclas))
            cambiarEstado (IZQUIERDA);
    
        if(isPressed(TECLA_DERECHA,teclas))
            cambiarEstado(DERECHA);

        ponerBomba(teclas);

}

void Player::izquierda(const Uint8 * teclas) {
	mover_ip(-mVelocidad,0);
	if(!isPressed(TECLA_IZQUIERDA,teclas))
    	cambiarEstado(PARADO);

	ponerBomba(teclas);
}

void Player::derecha (const Uint8 * teclas) {
	mover_ip(mVelocidad,0);
	if(!isPressed(TECLA_DERECHA,teclas))
    	cambiarEstado ( PARADO);

	ponerBomba(teclas);
}


bool Player::isPressed(TeclaPlayer tecla, const Uint8 * _teclas){
    if(!_teclas)return false;
    if(!control.isBotonJoystick(tecla) && !control.isDireccionJoystick(tecla)){
        return _teclas [control.getKey(tecla)];

    }else{
        for(int i=0;i<mpJuego->getJoysActivos();i++){
            if(!strcmp(SDL_JoystickName(mpJuego->getJoy(i)),control.getName(tecla))){//si coincide con el joistick con el que se configuro
				return estado_tecla_joy(control.getKey(tecla),mpJuego->getJoy(i));
             }
         }
         return false;
     }
}
void Player::arriba (const Uint8 * teclas) {
    mover_ip (0,-mVelocidad);
	if(!isPressed(TECLA_ARRIBA,teclas))
    	cambiarEstado(PARADO);
	ponerBomba(teclas);
}

void Player::abajo(const Uint8 * teclas) {
	mover_ip(0,mVelocidad);
	if(!isPressed(TECLA_ABAJO,teclas))
    	cambiarEstado (PARADO);

	ponerBomba(teclas);
}

/*
 * modifica el cuadro de la animaci�n que se debe mostrar en pantalla
 */
void Player::avanzarAnimacion () {
	static int animaciones [_ESTADOS_ANIMACION][17] = {\
		{3,3, 4,4, 5,5,-1},\
		{9,9, 10,10, 11,11, -1},\
		{6,6,  7,7, 8,8,-1},\
		{0,0, 1,1, 2,2,-1},\
        {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,-1}};
	if (--delay < 1) {
		delay = 3;
		if (animaciones [estado_actual] [paso + 1] == -1){
		    if(estado_actual!=MURIENDO)
    			paso = 0;
    		else
                mpJuego->playerMuerto(this, nullptr);
		}else
			paso ++;
	}


	if(estado_actual!=PARADO)
	   cuadro = animaciones [estado_actual][paso];
	else
	   cuadro = animaciones [estado_anterior][0];

}

void Player::cambiarEstado(EstadoSprite nuevo) {
    estado_anterior = estado_actual;
	estado_actual   = nuevo;
	paso  = 0;
	delay = 3;
}

/**
 * Establece un estado en el que el player es inmune a explosiones
 * @param segundos cantidad de segundos por la que el personaje es inmune
 */
void Player::setProteccion(int segundos){
    mDuracionProteccion=segundos;
    mEstaProtegido=true;
    mTimer.start();
}

/**
 * Mueve al personaje detectando alguna colision
 * Las colisiones que se detectan son solo las que pueden detener el movimiento como colision con una bomba
 * @param incremento_x
 * @param incremento_y
 */
void Player::mover_ip(int incremento_x, int incremento_y) {

    // Movemos el cuadro de colision primero
    rect.x += incremento_x;
    rect.y += incremento_y;

    // Detectamos si colisiona con BOMBAS
    auto setBombasColision = mpJuego->colisionConBombas(rect);
    // assert 0 <= setBombasColision.size() <= 1

    if(setBombasColision.size() > 0){ // Si colisiona con alguna bomba
        auto pBomba = setBombasColision.begin();
        while(pBomba != setBombasColision.end()){
            // Si colisiona con una bomba que no es la ultima colocada no movemos al personaje
            if((*pBomba) != mpUltimaBomba && !mPuedeAtravesarBombas){
                return;
            }
            pBomba++;
        }
    }else{
        // Si no colisiona con una bomba y teniamos una referencia a la ultima bomba la quitamos
        // Esta referencia solo era para permitir al usuario moverse arriba de la bomba que él puso hasta que
        // se salga del cuadro de colision
        mpUltimaBomba= nullptr;
    }

    // Si se sale del mapa no actualizamos la posicion del personajes, nos salimos
    if(mpJuego->isOutOfMapBounds(rect))return;

    /*
     * DETECTAMOS ALGUNA COLISION CON EL MAPA
     */
    // Nos dice cual de los extremos colision con el mapa
    NivelMapa::ExtremoColision extremoQueColisiona;
    int numeroDeColisiones = 0;
    extremoQueColisiona    = mpJuego->colisionConMapa(rect, &numeroDeColisiones, mPuedeAtravesarBloques);

    if(extremoQueColisiona != NivelMapa::ExtremoColision::NINGUNO){

        // Si colision en una sola esquina entonces deslizamos un poco al personaje para que le sea más facil
        // manejarse por el mapa :)
        if(numeroDeColisiones == 1){
            if(estado_actual == EstadoSprite::IZQUIERDA){
                if(extremoQueColisiona == NivelMapa::ExtremoColision::TOPLEFT){
                    y += 1; // Hacia Abajo
                }else if(extremoQueColisiona == NivelMapa::ExtremoColision::BOTTOMLEFT){
                    y -= 1; // Hacia Arriba
                }
            }else if (estado_actual == EstadoSprite::DERECHA){
                if(extremoQueColisiona == NivelMapa::ExtremoColision::TOPRIGHT){
                    y += 1;// Hacia Abajo
                }else if(extremoQueColisiona == NivelMapa::ExtremoColision::BOTTOMRIGHT){
                    y -= 1;// Hacia Arriba
                }
            }else if(estado_actual == EstadoSprite::ARRIBA){
                if(extremoQueColisiona == NivelMapa::ExtremoColision::TOPLEFT){
                    x += 1; // Hacia la derecha
                }else if(extremoQueColisiona == NivelMapa::ExtremoColision::TOPRIGHT){
                    x -= 1;// Hacia la izquierda
                }
            }else if(estado_actual == EstadoSprite::ABAJO){
                if(extremoQueColisiona == NivelMapa::ExtremoColision::BOTTOMRIGHT){
                    x -= 1;// Hacia la izquierda
                }else if(extremoQueColisiona == NivelMapa::ExtremoColision::BOTTOMLEFT){
                    x += 1;// Hacia la derecha
                }
            }
        }
    }else{
        move(x+incremento_x,y+incremento_y);
    }
}

/**
 * Establece al personaje en la posicion indicada
 * No actualiza su rectangulo de colision
 * @param x
 * @param y
 */
void Player::move(int x,int y){
    //establece al jugador en la posicion indicada
    this->x=x;
    this->y=y;
}

Player::~Player(){
    //cout << "Destructor de Player:"<<this<<endl;
}

void Player::setNBombas(int nBombas) {
    mNBombasDisponibles = nBombas;
}

void Player::setAlcanceBombas(int alcanceBombas) {
    mAlcanBombas = alcanceBombas;

}

int Player::getBombasColocadas() {
    return mNBombasColocadas;
}

void Player::setBombasColocadas(int n) {
    mNBombasColocadas = n;
}

int Player::getNCorazones() {
    return mCorazones;
}

EstadoSprite Player::getEstado() {
    return estado_actual;
}

void Player::setNCorazones(int nuevosNCorazones) {
    mCorazones = nuevosNCorazones;

}

bool Player::isMPuedeAtravesarBloques() const {
    return mPuedeAtravesarBloques;
}

void Player::setMPuedeAtravesarBloques(bool mPuedeAtravesarBloques) {
    Player::mPuedeAtravesarBloques = mPuedeAtravesarBloques;
}

bool Player::isMPuedeAtravesarBombas() const {
    return mPuedeAtravesarBombas;
}

void Player::setMPuedeAtravesarBombas(bool mPuedeAtravesarBombas) {
    Player::mPuedeAtravesarBombas = mPuedeAtravesarBombas;
}

bool Player::isMPuedePatearBombas() const {
    return mPuedePatearBombas;
}

void Player::setMPuedePatearBombas(bool mPuedePatearBombas) {
    Player::mPuedePatearBombas = mPuedePatearBombas;
}

bool Player::isMPuedeGolpearBombas() const {
    return mPuedeGolpearBombas;
}

void Player::setMPuedeGolpearBombas(bool mPuedeGolpearBombas) {
    Player::mPuedeGolpearBombas = mPuedeGolpearBombas;
}

bool Player::isMEstaEnfermo() const {
    return mEstaEnfermo;
}

void Player::setMEstaEnfermo(bool mEstaEnfermo) {
    Player::mEstaEnfermo = mEstaEnfermo;
}

