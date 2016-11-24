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
//        static enum TeclasPlayer {X_COLISION=3,Y_COLISION=10,W_COLISION=10,H_COLISION=10};

        Player(InterfazJuego * interfazGaleria,IdPlayer id,int x = 0,int y = 0,int vidasIni=3,int numBombasIni=1,int alcanceBombasIni=1);
        void update(const Uint8 * teclas);
        void draw(SDL_Renderer * );
        void reiniciar();
        void disable();
        int cargarTeclasFile();
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
        void posicionInicial(){move(xIni,yIni);};
        bool isActivo(){return enPantalla;};

        void setVidas(int nuevo){vidas=nuevo;};
        void setPuntaje(int nuevo){puntaje=nuevo;};
        //void setEntroPuerta(bool nuevo){entroPuerta=nuevo;};
        void setProteccion(int segundos);
        void setEnPantalla(bool nuevo){enPantalla=nuevo;};
        
        int getPuntaje(){return puntaje;};
        int getVidas(){return vidas;};
        //int getTipo(){return 4;};
        int getId(){return mPlayerId;};
        int getAlcanceBombas(){return alcanBomb;};
        int getBombas(){return mNBombasDisponibles;};
        
        ~Player();

	void setNBombas(int nBombas);

	void setAlcanceBombas(int alcanceBombas);

    int getBombasColocadas();

	void setBombasColocadas(int n);

private:

	IdPlayer mPlayerId;
	InterfazJuego *mJuego;//referencia al juego que lo cre�

	ControlPlayer  control;//controla el teclado del player
	EstadoSprite estado,//estado actual del player
			estado_anterior;//estado que uso para saber cual cuadro dibujar cuando este en el estado "PARADO"

	int xIni,yIni;//coordenadas del player al inicio del juego

	//Como no controlo por eventos lo de poner bombas
	bool mantieneStartPresionado;//para que el usuario no ponga infinitas bombas

	//para que el player pueda pasar por encima de la bomba que acaba de colocar
	//int idUltimaBomba;//index de la ultima bomba colocada


	//para controlar la animacion
	int paso,cuadro,delay;

	/*Controlan la proteccion*/
	bool estaProtegido;//True si el jugador est� protegido (se representa por el desvanecimiento)
	//int tiempoInicioProteccion;//contador del inicio de proteccion
	int duracionProteccion;//segundos para quitar la proteccion

	int alcanBomb,//alcance que logran las llamas de las bombas
		alcanBombIni;//alcance iniciales cuando se comenz� el modo historia o el mapa en el modo batalla
	int mNBombasDisponibles,//numero de bombas que puede soltar el jugador
		numBombasIni; //numero de bombas iniciales cuando se comenz� el modo historia o el mapa en el modo batalla
	bool puedeAtravesarBloquesBlandos; //True si el player puede atravesar los bloques blandos
	bool puedeAtravesarBombas;//True si el player puede atravesar las bombas
	bool puedePatearBombas;
	bool puedeGolpearBombas;
	bool estaEnfermo;
	int vidas;         //Cantidad de vidas del player
	int puntaje;       //puntaje acumulado del player desde que se inici� el modo historia
	int velocidad;     //Cantidad de px que se mueve el player en las direcciones b�sicas
	int corazones;     //Cantidad de veces que el player puede soportar ser alcanzado por las llamas o colisionar con un enemigo

/*True si el player est� muerto (est� remplaza a "self_kill" ya que los players 
*NO los elimino como lo hago por ejemplo con los items dec�r, los elimino de memoria solo cuando
*finaliza el juego)*/
	//bool muerto;

	//bool entroPuerta; //True si el player est� sobre la puerta

	bool enPantalla;   //True si el player se est� mostrando en pantalla
    Bomba *mUltimaBomba = nullptr;
    int mNBombasColocadas;
    LTimer mTimer;
};

#endif
