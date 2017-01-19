#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include "../../engine/interfaces/InterfazGrafica.hpp"
#include "../../engine/interfaces/PopUpMostrarMensajeTextoTimer.hpp"
#include "../../engine/interfaces/PopUpCountDown.hpp"
#include "../../engine/sprites/CGroup.hpp"
#include "../../engine/sprites/CDrawGroup.hpp"
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/layout/Componentes/LabelComponent.hpp"
#include "../../engine/mapa/TileEnLlamas.hpp"
#include "../../engine/util/LTimer.hpp"

#include "../../niveles/LectorMapa.hpp"
#include "../../util/constantes.hpp"
#include "PopUpJuegoMostrarRondasGan.hpp"

/*Personajes*/
#include "../../personajes/bomba.hpp"
#include "../../personajes/player.hpp"
#include "../../objetos/item.hpp"
#include "../../objetos/explosion.hpp"
#include "../../engine/util/EfectoSonido.hpp"
#include "../../engine/util/MusicaFondo.hpp"
#include "../../engine/util/BitmapFont.hpp"


class ModoJuegoMultiPlayer:public InterfazGrafica,public UpdateGroupContainerInterfaz{
public:

    ModoJuegoMultiPlayer(GameManagerInterfazUI * gameManager,std::string rutaMapa, int nVictorias, int nMinutos, bool isPlayerActivo[Player::N_PLAYERS]);
    void createUI(SDL_Renderer *gRenderer) override;
    void start() override;
    void procesarEvento(SDL_Event * evento) override ;
    void update() override ;
    void updateWhenPopUp() override;
    void draw(SDL_Renderer * ) override ;
    virtual ~ModoJuegoMultiPlayer();

    void eliminarSprite(Sprite *sprite) override;

    bool isOutOfMapBounds(SDL_Rect rect) ;

    Bomba *agregarBomba(Player *playerPropietario) ;

    deque<Sprite *> colisionConBombas(SDL_Rect  rect) ;
    deque<Sprite *> colisionConExplosiones(SDL_Rect rect) ;;
    deque<Sprite *> colisionBloqueEnLlamas(SDL_Rect rect) ;
    deque<Sprite *> colisionConItems(SDL_Rect rect) ;
    LectorMapa::ExtremoColision colisionConMapa(SDL_Rect rect_coli,
                                               int *lado_colision = nullptr,
                                               bool soloBloquesNoTraspasables=false) ;

    int getJoysActivos()  ;
    SDL_Joystick * getJoy(int id)  ;

    //LTexture * getImagen(Galeria::CodeImagen code)  { return mGameManager->getTexture(code);}

    TileEnLlamas *agregarBloqueEnLlamas(int x, int y) ;

    bool esBloqueSolido(int x, int y) ;
    bool esBloqueRompible(int x, int y) ;

    void playerMuerto(Player *pPlayer, Sprite *pPlayerCausante) ;

    void pause() override;

    void resume() override;

    void resultPopUp(InterfazEstandarBackResult *result, int popUpCode) override;


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


    LectorMapa mMapa;
    LTimer mGameTimer ;

    enum{
        FUENTE_NORMAL,
        FUENTE_RESALTADA
    };
    //LayoutAbsolute *mLayoutParent = nullptr;

    BitmapFont *mBitmapFont[2];
    int      mRondasGanadas [Player::N_PLAYERS] {0};
    //int      mPuntajePlayer [Player::N_PLAYERS] {0};

    bool     mIsPlayerActivado[Player::N_PLAYERS] {false};
    Player * mPlayerSprite  [Player::N_PLAYERS] {nullptr};

    std::string mRutaTerrenoMapa;
    int mNVictorias              = 0;
    int mMinutos                 = 0;

    IdPlayer mIdLiderRondasGanadas = PLAYER_NONE;
    SDL_Renderer * mGameRenderer;

    bool mIsPlayingWarningSound = false;

    EfectoSonido * mpSfxCreadaExplosion;
    EfectoSonido * mpSfxPlayerRecogioItem;
    EfectoSonido * mpSfxPlayerPerdioVida;
    MusicaFondo * mpMusicasFondo[2];
    MusicaFondo * mpMusicaAdvertenciaTiempo;

    // HUD
    LTexture * mpTextureHUD;
    Animacion * pAnimaTrofeos[Player::N_PLAYERS] {nullptr};

    SDL_Rect rectPlaceHolderTime {0,2,52,18};
    BitmapFontRenderer *mpBitmapMaxTimeRonda;

    SpriteSheet * mpSpriteSheetCarasBomberman;

    BitmapFontRenderer *mpBitmapValorCopasGanadas[Player::N_PLAYERS] {nullptr};
    BitmapFontRenderer *mpBitmapValorCopasMax;

    Animacion *mpAnimacionCopaMaxVictorias;
    // Fin HUD

    Item::TipoItem getTipoNuevoItem();
    void establecerValoresDeMapaPlayer(IdPlayer idPlayer);
    void drawHUD(SDL_Renderer *);
    void establecerValoresDeMapaPlayers();
    void agregarPlayersActivos();
    bool estaPlayerActivo(IdPlayer);
    void reiniciarEstado();
    int getSegundosInicioNivel();

};

#endif
