#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../engine/sprites/CSprite.hpp"
#include "../constantes.hpp"
#include "../control_player.hpp"
#include "../objetos/item.hpp"
#include "../engine/interfaces/InterfazJuego.hpp"
#include "bomba.hpp"
#include "../engine/util/LTimer.hpp"
//#define DEBUG

class Player:public Sprite{
    public:

        enum AreaColision {X_COLISION=3,Y_COLISION=10,W_COLISION=10,H_COLISION=10};

        Player(InterfazJuego * interfazGaleria,IdPlayer id);
        void update(const Uint8 * teclas);
        void draw(SDL_Renderer * );
        void cargarTeclas();
        void updateRectColision();
        void activarPoderItem(int tipo);
        void ponerBomba(const Uint8 * teclas);
        bool colision(SDL_Rect & rect_coli);
        void parado(const Uint8 * teclas);
        void izquierda(const Uint8 * teclas);
        void derecha (const Uint8 * teclas);
        bool isPressed(TeclaPlayer tecla,const Uint8 * teclas);
        void arriba (const Uint8 * teclas);
        void abajo(const Uint8 * teclas);
        void avanzarAnimacion ();
        void cambiarEstado(EstadoSprite nuevo);
        void mover_ip(int incremento_x, int incremento_y);
        void move(int x,int y);
        bool isActivo(){return mEnPantalla;};

        void setVidas(int nuevo){mVidas=nuevo;};
        void setProteccion(int segundos);
        void setEnPantalla(bool nuevo){mEnPantalla=nuevo;};
        
        int getVidas(){return mVidas;};
        int getId(){return mPlayerId;};
        int getAlcanceBombas(){return mAlcanBombas;};
        int getBombasDisponibles(){return mNBombasDisponibles;};
        
        ~Player();

	void setNBombas(int nBombas);

	void setAlcanceBombas(int alcanceBombas);

    int getBombasColocadas();

	void setBombasColocadas(int n);

private:

	IdPlayer mPlayerId = PLAYER_NONE;
	InterfazJuego * mpJuego = nullptr;//referencia al juego que lo cre�

	ControlPlayer  control;//controla el teclado del player
	EstadoSprite estado_actual   = NINGUNO;//estado_actual actual del player
    EstadoSprite estado_anterior = NINGUNO;//estado_actual que uso para saber cual cuadro dibujar cuando este en el estado_actual "PARADO"

	//Como no controlo por eventos lo de poner bombas
	bool mMantieneAccionPresionado = false;//para que el usuario no ponga infinitas bombas

	//para que el player pueda pasar por encima de la bomba que acaba de colocar
	Bomba *mpUltimaBomba = nullptr; // Referencia a la ultima bomba colocada

	//para controlar la animacion
	int paso = 0,cuadro = 0,delay = 0;

	/*Controlan la proteccion*/
	bool mEstaProtegido = false;//True si el jugador est� protegido (se representa por el desvanecimiento)
	//int tiempoInicioProteccion;//contador del inicio de proteccion
	int mDuracionProteccion;//segundos para quitar la proteccion

	int mAlcanBombas        = 1;//alcance que logran las llamas de las bombas
	int mNBombasDisponibles = 1;//numero de bombas que puede soltar el jugador

	bool mPuedeAtravesarBloques = false; //True si el player puede atravesar los bloques blandos
	bool mPuedeAtravesarBombas  = false;//True si el player puede atravesar las bombas
	bool mPuedePatearBombas     = false;
	bool mPuedeGolpearBombas    = false;
	bool mEstaEnfermo           = false;

	int mVidas     = 1;         //Cantidad de mVidas del player
	//int puntaje;       //puntaje acumulado del player desde que se inici� el modo historia
	int mVelocidad = 1;     //Cantidad de px que se mueve el player en las direcciones b�sicas
	int mCorazones = 0;     //Cantidad de veces que el player puede soportar ser alcanzado por las llamas o colisionar con un enemigo


	//bool entroPuerta; //True si el player est� sobre la puerta

	bool mEnPantalla       = false;   //True si el player se est� mostrando en pantalla
    int mNBombasColocadas  = 0; // Numero de Bombas que el Player ha colocado en el mapa
    LTimer mTimer;
};

#endif
