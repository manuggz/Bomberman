#ifndef OTHELLO_OTHELLO_JUEGO_HPP
#define OTHELLO_OTHELLO_JUEGO_HPP
#include <SDL2/SDL.h>

static const int ESTADO_SIN_PIEZA = -1;
static const int ESTADO_PIEZA_BLANCA = 0;
static const int ESTADO_PIEZA_NEGRA = 1;

class InterfazJuegoOthello {
public:

	virtual void playSfx(Mix_Chunk * pSfxChunk) = 0;
    virtual void seleccionadaPosicionInvalida(int turnoActual) = 0;
    virtual void cambiadoTurno(int turnoActual, int nVolteadasTurnoAnterior) = 0;

    virtual void cambioEstadoTablero(int nBlancas, int nNegras) = 0;
    virtual void seAcaboElJuego(int nBlancas, int nNegras) = 0;
};

class OthelloJuego {
public:

    enum TurnoJuego{
        BLANCAS,
        NEGRAS
    };

	OthelloJuego(InterfazJuegoOthello * parent,int x, int y) {
		mRect.x = x;
		mRect.y = y;
        mpPiezas[0] = new LTexture();
        mpPiezas[1] = new LTexture();
        mParent = parent;
	}

	void start() {

        for(int i = 0; i < 8;i++)
            std::fill_n(mEstadoTablero[i], 8, ESTADO_SIN_PIEZA);
        mEstadoTablero[3][3] = ESTADO_PIEZA_BLANCA;
        mEstadoTablero[4][3] = ESTADO_PIEZA_NEGRA;
        mEstadoTablero[3][4] = ESTADO_PIEZA_NEGRA;
        mEstadoTablero[4][4] = ESTADO_PIEZA_BLANCA;
        nPiezas[0] = 2;
        nPiezas[1] = 2;
	}
    ~OthelloJuego(){
        delete mpPiezas[0];
        delete mpPiezas[1];
    }
	void crearUI(SDL_Renderer * gRenderer) {
        mpPiezas[0]->loadFromFile("resources/blanca.png",gRenderer,false);
        mpPiezas[1]->loadFromFile("resources/negra.png",gRenderer,false);
	}
	void procesarEvento(SDL_Event *evento) {

        if(evento->type == SDL_MOUSEBUTTONDOWN && evento->button.button==SDL_BUTTON_LEFT) {
            if(punto_en_rect(evento->motion.x,evento->motion.y,&mRect)){
                int iEstado = (evento->motion.y - mRect.y) / 64;
                int jEstado = (evento->motion.x - mRect.x) / 64;

                if(mEstadoTablero[iEstado][jEstado] == ESTADO_SIN_PIEZA){
                    TurnoJuego turnoSiguiente = (mTurnoActual == NEGRAS) ? BLANCAS : NEGRAS;

                    if(puedeVoltearAlguna(iEstado,jEstado,mTurnoActual,turnoSiguiente)) {
                        mEstadoTablero[iEstado][jEstado] = mTurnoActual;
                        int nVolteadas = voltearPiezas(iEstado,jEstado,turnoSiguiente,mTurnoActual);
                        nPiezas[mTurnoActual]++;

                        if(puedeVoltearAlguna(turnoSiguiente,mTurnoActual)){
                            mTurnoActual = turnoSiguiente;
                        }

                        if(mTurnoActual != turnoSiguiente && !puedeVoltearAlguna(mTurnoActual,turnoSiguiente)){
                            mParent->seAcaboElJuego(nPiezas[0],nPiezas[1]);
                        }else{
                            if(nPiezas[0] + nPiezas[1] >= 8*8){
                                mParent->seAcaboElJuego(nPiezas[0],nPiezas[1]);
                            }else{
                                mParent->cambiadoTurno(mTurnoActual, nVolteadas);
                                mParent->cambioEstadoTablero(nPiezas[0],nPiezas[1]);
                            }
                        }
                    }else{
                        mParent->seleccionadaPosicionInvalida(mTurnoActual);
                    }
                }
            }
        }
	}

    bool puedeVoltearAlguna(int colorPiezaAColocar,int colorPiezaAVoltear){
        for(int i = 0; i < 8 ; i++){
            for(int j = 0; j < 8 ; j++){
                if(mEstadoTablero[i][j] == ESTADO_SIN_PIEZA){
                    if(puedeVoltearAlguna(i,j,colorPiezaAColocar,colorPiezaAVoltear)){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    int voltearPiezas(int i, int j, int colorPiezaAVoltear,int colorPiezaAEstablecer){

        int nVolteadas = voltearPiezaAuxiliar(i + 1,j,1,0,colorPiezaAVoltear,colorPiezaAEstablecer,0);
        nVolteadas += voltearPiezaAuxiliar(i - 1,j,-1,0,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        nVolteadas += voltearPiezaAuxiliar(i ,j + 1,0,1,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        nVolteadas += voltearPiezaAuxiliar(i ,j - 1,0,-1,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        nVolteadas += voltearPiezaAuxiliar(i + 1,j + 1,1,1,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        nVolteadas += voltearPiezaAuxiliar(i - 1,j + 1,-1,1,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        nVolteadas += voltearPiezaAuxiliar(i - 1,j - 1,-1,-1,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        nVolteadas += voltearPiezaAuxiliar(i + 1,j - 1,1,-1,colorPiezaAVoltear,colorPiezaAEstablecer,nVolteadas);
        return nVolteadas;
    }

    /**
     * Va volteando las piezas que se vaya encontrando en una direccinó comprobando si se puede o no voltear
     * @param i Posicion actual i en el tablero
     * @param j Posicion actual j en el tablero
     * @param i_aum Direccion i(Eje Y) en el cual moverse en el tablero
     * @param j_aum  Direccion j(Eje X) en el cual moverse en el tablero
     * @param colorPiezaAVoltear Color de las piezas a las cuales se les volteará el color
     * @param colorPiezaAEstablecer Color el cual establecerle a las piezas que se puedan voltear
     * @param acum Acumulado actual de piezas que se han volteado
     * @return Regresa el acumulado total de piezas volteadas acum
     */
    int voltearPiezaAuxiliar(int i, int j,int i_aum,int j_aum,int colorPiezaAVoltear,int colorPiezaAEstablecer,int acum){
        // Comprueba que estemos en uyna posicion valida del tablero
        if( i < 0 || i >= 8 || j < 0 || j >= 8) return acum;

        // Si estamos en una posicion de una pieza que queremos voltear
        if(mEstadoTablero[i][j] == colorPiezaAVoltear){

            // Si al movernos a la siguiente pieza en la linea estamos en euna posición válida
            if(!( i + i_aum < 0 || i + i_aum >= 8 || j + j_aum < 0 || j + j_aum >= 8)){

                // Si la siguiente posición en la linea es una pieza del color que queremos establecer significa
                // que tenemos una linea hasta esta posicion (i,j) que podemos voltear
                if(mEstadoTablero[i + i_aum][j + j_aum]  == colorPiezaAEstablecer) {
                    // Volteamos la actual y la pila de recursion actual voltea las que queden de la linea
                    // Sí estas existen estaran esperando en la siguiente condición del if
                    // Esta es la condicion para terminar las recursiónes(esta y que nos salgamos del tablero)
                    nPiezas[mEstadoTablero[i][j]]--;
                    mEstadoTablero[i][j] = colorPiezaAEstablecer;
                    nPiezas[mEstadoTablero[i][j]]++;
                    return acum + 1;
                }else
                // En caso que la siguiente pieza en la linea es una posible pieza a voltear
                if(mEstadoTablero[i + i_aum][j + j_aum]  == colorPiezaAVoltear){
                    // Mandamos a voltearla recursivamente
                    int nAccumAux = voltearPiezaAuxiliar(i + i_aum,j + j_aum,i_aum,j_aum,colorPiezaAVoltear,colorPiezaAEstablecer,acum + 1);
                    // En caso que se haya volteada (y todas las siguientes después de élla)
                    if( nAccumAux != acum){
                        // Volteamos la actual
                        nPiezas[mEstadoTablero[i][j]]--;
                        mEstadoTablero[i][j] = colorPiezaAEstablecer;
                        nPiezas[mEstadoTablero[i][j]]++;
                    }

                    return nAccumAux + 1;

                }

            }
        }

        return acum;

    }

    bool puedeVoltearAlguna(int i, int j, int colorPiezaAColocar,int colorPiezaAVoltear){

        if(puedeVoltearAlgunaAux(i + 1,j,1,0,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i - 1,j,-1,0,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i,j + 1,0,1,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i,j - 1,0,-1,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i + 1,j + 1,1,1,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i - 1,j - 1,-1,-1,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i + 1,j - 1,1,-1,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;
        if(puedeVoltearAlgunaAux(i - 1,j + 1,-1,1,colorPiezaAVoltear,colorPiezaAColocar,false)) return true;

        return false;
    }

    bool  puedeVoltearAlgunaAux(int i, int j,int i_aum,int j_aum,int colorPiezaAVoltear,int colorPiezaAColocar,bool algunaPiezaVolteable){
        if( i < 0 || i >= 8 || j < 0 || j >= 8) return false;

        if(mEstadoTablero[i][j] == colorPiezaAVoltear){
            algunaPiezaVolteable = true;
        }else{
            if (mEstadoTablero[i][j] == colorPiezaAColocar) {
                if (algunaPiezaVolteable) {
                    return true;
                }
            }
            return false;
        }

        return puedeVoltearAlgunaAux(i + i_aum,j + j_aum,i_aum,j_aum,colorPiezaAVoltear,colorPiezaAColocar,algunaPiezaVolteable);
    }

	void update() {
	}

	void draw(SDL_Renderer *renderer) {

		for(int i = 0; i < 8 ; i++){
            for(int j = 0; j < 8 ; j++){
                if(mEstadoTablero[i][j] != ESTADO_SIN_PIEZA){
                    mpPiezas[mEstadoTablero[i][j]]->render(renderer,j*64 + mRect.x,i*64 + mRect.y);
                }
            }
        }
	}


private:
	SDL_Rect mRect{0,0,64*8,64*8};
	int mEstadoTablero[8][8] {{ESTADO_SIN_PIEZA}};
    LTexture *mpPiezas[2];
    int nPiezas[2] {0,0};
    TurnoJuego mTurnoActual = NEGRAS;
    InterfazJuegoOthello *mParent;
};
#endif