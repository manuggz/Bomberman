#ifndef MENU_HPP
#define MENU_HPP
#include <math.h>
#include <SDL2/SDL.h>
#include "engine/interfaces/interfaz.hpp"
#include "engine/util/game_manager.hpp"
#include "control_player.hpp"
#include "constantes.hpp"
#include "util.hpp"
#include "juego_historia.hpp"
#include "juego_batalla.hpp"
#include "editor.hpp"
#include "engine/layout/Componentes/BotonComponent.hpp"
#include "fuente_imagen.hpp"
#include "engine/util/CFont.hpp"

class Menu:public Interfaz{

public:
    Menu(GameManager * game);
    void setSelected(int nuevo);
    void cargarTeclas();

    virtual bool isPaused() override;

    virtual void pause() override;

    virtual void resume() override;

    void cambiarPlayerConfi(IdPlayer id);
    void guardarTeclas();
    void limpiar();
    void cambiarVentana(int nueva_ventana);
    void cambiarTerrenoBatalla(int aum);
    void procesarEvento(SDL_Event * evento);
    void draw(SDL_Renderer * gRenderer);
    void clickSelected();
    void update();
    void killSprite(int a,int b){return;};
    void erase(int ,int ){return;};
    void updatePreview();
    ~Menu();

private:
    GameManager * game;

    //Ventana 1 y 2
    SDL_Rect rectsImpresion[3][5];
    char  texto[2][5][20];

    //ventana 3(Multijugador)
    Group * sprites;
    Mapa mapa;
    DatNivel * dataNivel;
    SDL_Surface * previewTerreno;

    BotonComponent<Menu> *btnSubirTiempo,*btnSubirVictorias,*btnCambiarMapa,*btnJugar;
    Animacion *animaPlayer[5],* animaPresiona[5],* animaActivado[5];

    bool player_batalla[_PLAYERS];
    int terrenoActual,minutosEscogidos,victoriasEscogidas;

    //para ventana 4(Configuraci�n)
    ControlPlayer control_edit;
    SDL_Rect rectConfiguracion[_TECLAS][3],rectBotonPlayer[_PLAYERS],rect_destino_cara;
    Estados_boton botones_cambiar[_TECLAS];
    BotonComponent<Menu>  botonGuardar;
    BotonComponent<Menu> * botonPlayer[_PLAYERS];

    IdPlayer player_configurando_teclas;
    TeclaPlayer id_espera_tecla;
    int selected,ventana;
    int maxTerrenoBatalla;

    void cambiarPlayer();
    void clickControl(BotonComponent<Menu> * control_click);

    ///  Para los efectos de desvanecimientos
    SDL_Texture *fondoVentanaAnterior,*fondoVentanaSiguiente,*fondoNegro;
    int ventanaSiguiente,ventanaAnterior,nivelAlpha,nAnimacion;
    bool animacion;

    CFont * mFuente;

    void setDesvanecimiento(int last,int nueva);

};

#endif
