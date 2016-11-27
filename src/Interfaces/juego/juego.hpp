#ifndef JUEGO_HPP
#define JUEGO_HPP
#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include "../../niveles/NivelMapa.hpp"
#include "../../util/constantes.hpp"
#include "../../engine/interfaces/InterfazUI.hpp"
#include "../../engine/sprites/CGroup.hpp"
/*Personajes*/
#include "../../personajes/bomba.hpp"
#include "../../objetos/item.hpp"
#include "../../objetos/explosion.hpp"
#include "../../engine/mapa/TileEnLlamas.hpp"
#include "../../engine/util/LTimer.hpp"
#include "../../engine/sprites/CDrawGroup.hpp"
//#include "juego_historia.hpp"
#include "InterfazJuego.hpp"
#include "../../personajes/player.hpp"
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/layout/Componentes/TextLabelComponent.hpp"



class Juego:public InterfazUI ,public InterfazJuego,public InterfazSpriteGroup{
public:

    Juego(GameManagerInterfazUI * gameManager,std::string rutaMapa, int nVictorias, int nMinutos, bool isPlayerActivo[_PLAYERS]);
    void prepare() override;
    void createUI(SDL_Renderer *gRenderer) override;
    void start() override;
    void procesarEvento(SDL_Event * evento) override ;
    void update() override ;
    void updateWhenPopUp() override;
    void draw(SDL_Renderer * ) override ;
    virtual ~Juego();

    void eliminarSprite(Sprite *sprite) override;


    bool isOutOfMapBounds(SDL_Rect rect) override;

    Bomba *agregarBomba(Player *playerPropietario) override;

    deque<Sprite *> colisionConBombas(SDL_Rect  rect) override;
    deque<Sprite *> colisionConExplosiones(SDL_Rect rect) override;;
    deque<Sprite *> colisionBloqueEnLlamas(SDL_Rect rect) override;
    deque<Sprite *> colisionConItems(SDL_Rect rect) override;
    NivelMapa::ExtremoColision colisionConMapa(SDL_Rect rect_coli,
                                               int *lado_colision = nullptr,
                                               bool soloBloquesNoTraspasables=false) override;

    int getJoysActivos() override ;
    SDL_Joystick * getJoy(int id) override ;

    LTexture * getImagen(Galeria::CodeImagen code) override { return mGameManagerInterfaz->getTexture(code);}

    TileEnLlamas *agregarBloqueEnLlamas(int x, int y) override;

    bool esBloqueSolido(int x, int y) override;
    bool esBloqueRompible(int x, int y) override;

    void playerMuerto(Player *pPlayer, Sprite *pPlayerCausante) override;

    void pause() override;

    void resume() override;

    void resultPopUp(void *result, int popUpCode) override;

protected:

    static const int ID_POPUP_JUEGO_MOSTRAR_GAN_TERMINAR      = 100;
    static const int ID_POPUP_JUEGO_MOSTRAR_GAN_CONTINUAR     = 101;
    static const int ID_POPUP_JUEGO_NADIE_GANA_RONDA          = 102;
    static const int ID_POPUP_JUEGO_COMIENZA                  = 103;
    static const int ID_POPUP_JUEGO_GANADOR                   = 104;
    // Controlador del Juego en General(Interfaces,SDL y mainloop)

    // Todos los Sprites en pantalla que se dibujaran
    DrawGroup mGrpSprites;

    /**
     * Grupo para cada ente que es colisionable, para manejarlo por separado
     * Si bien se puede manejar con solo mGrpSprites, cuando se detecta una colision
     * entonces habria que estar viendo si lo que se regreso  es un sprite del tipo que se quiere.
     */
    Group mGrpEnemigos;
    Group mGrpExplosiones;
    Group mGrpItems;
    Group mGrpBombas;
    Group mGrpPlayers;
    Group mGrpBloques;


    NivelMapa mMapa;
    LTimer mGameTimer ;

    int      mRondasGanadas [_PLAYERS] {0};
    //int      mPuntajePlayer [_PLAYERS] {0};

    bool     mIsPlayerActivado[_PLAYERS] {false};
    Player * mPlayerSprite  [_PLAYERS] {nullptr};

    std::string mRutaTerrenoMapa;
    int mNVictorias              = 0;
    int mMinutos                 = 0;

    IdPlayer mIdLiderRondasGanadas = PLAYER_NONE;
    SDL_Renderer * mGameRenderer;

    LayoutAbsolute *     mLayoutParent;
    TextLabelComponent * mpTxtTiempoRestante;

    bool mIsPlayingWarningSound = false;

    Item::TipoItem getTipoNuevoItem();
    void establecerValoresDeMapaPlayer(IdPlayer idPlayer);
    void packLayout(SDL_Renderer *pRenderer);
    void drawBarra(SDL_Renderer *);
    void establecerValoresDeMapaPlayers();
    void agregarPlayersActivos();
    bool estaPlayerActivo(IdPlayer);
    void reiniciarEstado();
    int getSegundosInicioNivel();

    TextLabelComponent * mpVidasRestantesPlayer[_PLAYERS];
};

#endif
