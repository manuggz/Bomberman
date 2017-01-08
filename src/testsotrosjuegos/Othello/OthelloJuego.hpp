#ifndef OTHELLO_OTHELLO_JUEGO_HPP
#define OTHELLO_OTHELLO_JUEGO_HPP
#include <SDL2/SDL.h>

static const int ESTADO_SIN_PIEZA = 0;
static const int ESTADO_PIEZA_BLANCA = 1;
static const int ESTADO_PIEZA_NEGRA = 2;

class InterfazJuegoOthello {
public:

	virtual void playSfx(Mix_Chunk * pSfxChunk) = 0;
};

class OthelloJuego {
public:
	OthelloJuego(InterfazJuegoOthello * parent,int x, int y) {
		mRect.x = x;
		mRect.y = y;
	}

	void start() {

	}

	void crearUI(SDL_Renderer * gRenderer) {

	}
	void procesarEvento(SDL_Event *evento) {
	}
	void update() {
	}
	void draw(SDL_Renderer *renderer) {
	}


private:
	SDL_Rect mRect{0,0,64*8,64*8};
	Uint8 mEstadoTablero[8][8]{{ESTADO_SIN_PIEZA}};
};
#endif