//
// Created by manuggz on 06/12/16.
//

#ifndef OTHELLO_OTHELLO_INTERFAZ_HPP
#define OTHELLO_OTHELLO_INTERFAZ_HPP

#include "../../engine/interfaces/InterfazUI.hpp"
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/layout/LayoutManager/LayoutVertical.hpp"
#include "../../engine/util/CMetaData.hpp"
#include "../../engine/util/LTimer.hpp"

#include "OthelloJuego.hpp"
#include "BitmapFont.hpp"


class OthelloInterfaz : public InterfazUI,public InterfazJuegoOthello {
public:
	OthelloInterfaz(GameManagerInterfazUI *gameManagerInterfaz)
		: InterfazUI(gameManagerInterfaz) {
		std::cout << "OthelloInterfaz::OthelloInterfaz" << std::endl;

	}
	void prepare() override {
		std::cout << "TetrisInterfaz::prepare" << std::endl;
		InterfazUI::prepare();
		mLayoutBackGround = new LayoutAbsolute();
		mOthelloJuego = new OthelloJuego(this,0, 0);
		mMusicaFondo = cargar_musica("resources/music/music.mp3");
		mSfxColocarPieza = cargar_sonido((char *) "resources/music/SFX_GameOver.ogg");
	}


	void playSfx(Mix_Chunk *pSfxChunk) override {
		mGameManagerInterfaz->play(pSfxChunk);
	}

	void start() override {
		std::cout << "TetrisInterfaz::start" << std::endl;
		InterfazUI::start();
		mOthelloJuego->start();
		mControlTimer.start();
		mGameManagerInterfaz->playFadeInSound(mMusicaFondo, MIX_MAX_VOLUME / 2);
	}
	virtual void createUI(SDL_Renderer *renderer)  override {

		std::cout << "TetrisInterfaz::createUI" << std::endl;
		// Establecemos el fondo con los parametros adecuados para que ocupe toda la pantalla
		mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_HEIGHT, LAYOUT_PARAM_TRUE);
		mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_FILL_PARENT_WIDTH, LAYOUT_PARAM_TRUE);
		mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_WIDTH, LAYOUT_PARAM_FALSE);
		mLayoutBackGround->setLayoutParam(LAYOUT_PARAM_WRAP_HEIGHT, LAYOUT_PARAM_FALSE);

		//mLayoutBackGround->setBackgroundColor(SDL_Color {27,63,177,255});
		LTexture * lTexture = new LTexture();
		lTexture->loadFromFile("resources/fondo.png", renderer, false);
		mLayoutBackGround->setBackgroundTexture(lTexture);

		mBitmapFont[NORMAL] = new BitmapFont(renderer, "resources/fuentes/fuente_1.png");
		mBitmapFont[RESALTADO] = new BitmapFont(renderer, "resources/fuentes/fuente_2.png");

		mOthelloJuego->crearUI(renderer);
		SDL_ShowCursor(SDL_ENABLE);//ocultamos el cursor

	}

	virtual void resume() override {
		std::cout << "TetrisInterfaz::resume" << std::endl;
		InterfazUI::resume();
		mLayoutBackGround->setDisabled(true);
		SDL_ShowCursor(SDL_ENABLE);//ocultamos el cursor
	}
	/**
	* Procesa el evento del usuario
	* Se encarga de mover la opcion resaltada al usuario o en caso de que sea ENTER llamar a la funcion enlazada a
	* la opcion.
	* @param evento  Evento producido por SDL
	*/
	void procesarEvento(SDL_Event *evento) override {
		if (evento->type == SDL_KEYDOWN) {
			switch (evento->key.keysym.sym) {
			case SDLK_ESCAPE:
				mGameManagerInterfaz->goBack();
				//mGameManagerInterfaz->showPopUp()
				break;
			default:
				break;
			}
		}

		mOthelloJuego->procesarEvento(evento);
	}

	void update() override {
		InterfazUI::update();
		mOthelloJuego->update();
	}
	void draw(SDL_Renderer *renderer) override {
		if (mLayoutBackGround->isDisabled()) {
			SDL_Rect rect = mGameManagerInterfaz->getRectScreen();
			mLayoutBackGround->pack(renderer);
			mLayoutBackGround->setRectDibujo(rect);
		}
		mLayoutBackGround->draw(renderer);
		//mBitmapHighScorePlayer1Valor->draw(renderer);

		if (mControlTimer.isRunning()) {
			static char hrs[3], min_[3], seg[3], tiempo[6];

			int segundos = mControlTimer.getTicks() / 1000;

			sprintf(seg, "%2d", (segundos) % 60);
			if (seg[0] == ' ')seg[0] = '0';

			int minutos = (segundos - segundos % 60) / 60;
			sprintf(min_, "%2d", minutos % 60);
			if (min_[0] == ' ')min_[0] = '0';

			int horas = (minutos - minutos % 60) / 60;
			sprintf(hrs, "%2d", horas);
			if (hrs[0] == ' ')hrs[0] = '0';

			sprintf(tiempo, "%s:%s:%s", hrs, min_, seg);
			//mBitmapTimePlayer1Valor->setText(tiempo);

		}

		mOthelloJuego->draw(renderer);

	}

	virtual ~OthelloInterfaz() override {
		delete mLayoutBackGround; // Al liberar el layout parent se liberan todos sus mComponentes
		delete mOthelloJuego;
		//delete mLabelComponentScoreActual;

		Mix_FreeMusic(mMusicaFondo);
		Mix_FreeChunk(mSfxColocarPieza);

		for (int i = 0; i < 2; i++) {
			delete mBitmapFont[i];
		}
	}
private:

	LayoutAbsolute *mLayoutBackGround = nullptr;

	OthelloJuego * mOthelloJuego = nullptr;
	enum EstadoTexto {
		NORMAL,
		RESALTADO
	};
	BitmapFont *mBitmapFont[2];
	LTimer mControlTimer;
	Mix_Music * mMusicaFondo;
	Mix_Chunk * mSfxColocarPieza;

};

#endif