//
// Created by manuggz on 14/01/17.
//

#ifndef BOMBERMAN_MENUESCOGERMAPA_HPP
#define BOMBERMAN_MENUESCOGERMAPA_HPP

#include <vector>
#include <iostream>
#include <dirent.h>
#include <zconf.h>
#include <sys/param.h>
#include "../../engine/interfaces/InterfazGrafica.hpp"
#include "../../engine/util/LTexture.hpp"
#include "../../engine/util/SpriteSheet.hpp"
#include "../../niveles/LectorMapa.hpp"
#include "SpriteFlecha.hpp"
#include "../../engine/util/BitmapFont.hpp"
#include "../../personajes/player.hpp"
#include "../../engine/util/MusicaFondo.hpp"
#include "../../engine/util/EfectoSonido.hpp"
#include <unistd.h>
#define GetCurrentDir getcwd


static const int MAX_MINUTOS = 8;

static const int MAX_VICTORIAS = 8;

class MenuEscogerMapa: public InterfazGrafica,public UpdateGroupContainerInterfaz {
public:
    enum MenuOption{
        MENU_OPCION_TIEMPO_RONDA,
        MENU_OPCION_MAX_VICTORIAS,
        MENU_OPCION_MAPA,
        MENU_OPCION_PLAYER_1,
        MENU_OPCION_PLAYER_2,
        MENU_OPCION_PLAYER_3,
        MENU_OPCION_PLAYER_4,
        MENU_OPCION_PLAYER_5,
        _N_OPCIONES_MENU
    };

    MenuEscogerMapa(GameManagerInterfazUI *gameManagerInterfaz) : InterfazGrafica(gameManagerInterfaz) {}

    static std::vector<std::string> getNombresMapas(){
        std::vector<std::string> nombresMapas;
        DIR *dir;
        struct dirent *ent;
        char cCurrentPath[FILENAME_MAX];
        char rutaCompletaMapas[FILENAME_MAX];

        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
            //return errno;
        }

        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

        sprintf(rutaCompletaMapas,"%s/data/niveles/batalla",cCurrentPath);
        //SDL_Log("The current working directory is %s", rutaCompletaMapas);
        if ((dir = opendir (rutaCompletaMapas)) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {

                for(int i = 0; ent->d_name[i];i++){
                    if(ent->d_name[i]=='.'&&
                       ent->d_name[i + 1] != '\0' && ent->d_name[i + 1] == 't'&&
                       ent->d_name[i + 2] != '\0' && ent->d_name[i + 2] == 'm'&&
                       ent->d_name[i + 3] != '\0' && ent->d_name[i + 3] == 'x' &&
                       ent->d_name[i + 4] == '\0'){

                        nombresMapas.push_back(std::string(ent->d_name));
                        printf ("%s\n", ent->d_name);
                    }
                }
            }
            closedir (dir);
        } else {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"No se pudo abrir %s","/data/niveles/batalla");
            perror("");
            /* could not open directory */
            //return EXIT_FAILURE;
        }
        return nombresMapas;
    }

    void prepare() override {
        InterfazGrafica::prepare();
        mNombreMapas = getNombresMapas();
    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazGrafica::createUI(gRenderer);

        mpSfxCambiarOpcionMenuResaltada = new EfectoSonido("data/sonidos/ping_3.wav",100);
        mpSfxCambiarValorOpcionMenuResaltada   = new EfectoSonido("data/sonidos/ping_2.wav",100);
        mpSfxPressJugar   = new EfectoSonido("data/sonidos/ping_5.wav",100);

        mSprites=new DrawGroup(this);

        //Animaciones para los personajes (Hace que parezcan que caminan) cuando se seleccionan
        SpriteSheet *spriteSheetTmp;
        for(int i = 0; i < Player::N_PLAYERS;i++) {
            spriteSheetTmp = new SpriteSheet();
            spriteSheetTmp->cargarDesdeArchivo(gRenderer, "data/imagenes/personajes/player_" + std::to_string(i+1)+".bmp", 1, 12, true);
            mAnimacionPlayer[i] = new Animacion(spriteSheetTmp, "6,6,7,7,8,8");
            mAnimacionPlayer[i]->setRepeticiones(-1);
        }

        musicaFondoMenu = new MusicaFondo("data/sonidos/musica_1.mid");

        LTexture *pTextureFlechaDerecha = new LTexture();
        pTextureFlechaDerecha->cargarDesdeArchivo("data/imagenes/objetos/flecha_menu_apunta_hacia_derecha.png",gRenderer,false);

        LTexture * pTextureFlechaIzquierda = new LTexture();
        pTextureFlechaIzquierda->cargarDesdeArchivo("data/imagenes/objetos/flecha_menu_apunta_hacia_izquierda.png",gRenderer,false);

        flechaIzquierda = new FlechaDinamica(pTextureFlechaIzquierda);
        flechaIzquierda->move(55,54);
        flechaIzquierda->setYDestino(54);

        flechaDerecha = new FlechaDinamica(pTextureFlechaDerecha);
        flechaDerecha->move(260,54);
        flechaDerecha->setYDestino(54);

        mBitmapFont[FUENTE_NORMAL] = new BitmapFont(gRenderer,   "data/fuentes/fuente2_16_normal.png");
        mBitmapFont[FUENTE_RESALTADA] = new BitmapFont(gRenderer,"data/fuentes/fuente2_16_resaltado.png");

        for(int i = 0; i < _N_OPCIONES_MENU;i++) {
            mpBitmapTextoOpcionMenu[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 65, 54 + 20*i);
            mpBitmapTextoValorOpcionMenu[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 0, 54 + 20*i);
            mpBitmapTextoValorOpcionMenu[i]->setRight(255);
        }
        mpBitmapTextoOpcionMenu[MENU_OPCION_TIEMPO_RONDA]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);
        mpBitmapTextoValorOpcionMenu[MENU_OPCION_TIEMPO_RONDA]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);

        mpBitmapTextoOpcionMenu[MENU_OPCION_TIEMPO_RONDA]->setText("TIME X ROUND:");
        mpBitmapTextoOpcionMenu[MENU_OPCION_MAX_VICTORIAS]->setText("MAX VICTORIES:");
        mpBitmapTextoOpcionMenu[MENU_OPCION_MAPA]->setText("MAP:");

        mpBitmapTextoValorOpcionMenu[MENU_OPCION_TIEMPO_RONDA]->setText("NO");
        mpBitmapTextoValorOpcionMenu[MENU_OPCION_MAX_VICTORIAS]->setText("NO");

        for(int i = 0; i < Player::N_PLAYERS;i++) {
            mpBitmapTextoOpcionMenu[i + MENU_OPCION_PLAYER_1]->setText("PLAYER " + std::to_string(i+1)+":");
            mpBitmapTextoValorOpcionMenu[i + MENU_OPCION_PLAYER_1]->setText((mIsPlayerActivado[i]) ? "YES" : "NO");
            mpBitmapValorCopasGanadas[i] = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 42+ i*60,20);
            mpBitmapValorCopasGanadas[i]->setText("0");
        }

        mpTextureHUD = new LTexture();
        mpTextureHUD->cargarDesdeArchivo("data/imagenes/objetos/tablero.bmp",gRenderer,true);

        pTextureFondoMenu = new LTexture();
        pTextureFondoMenu->cargarDesdeArchivo("data/imagenes/objetos/fondo_reglas_mapa.png",gRenderer,true);

        for(int i = 0; i < Player::N_PLAYERS; i++) {
            mpSpriteSheetPlayer[i] = new SpriteSheet(gRenderer, "data/imagenes/personajes/player_" + std::to_string(i + 1) + ".bmp", 1, 12,true);
            mpSpriteSheetPlayer[i]->setAlpha(150);
            mpSpriteSheetPlayer[i]->setCurrentCuadro(6);
        }

        mpSpriteSheetCarasBomberman = new SpriteSheet(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);

        mpGRenderer = gRenderer;

        SpriteSheet *spriteSheet;
        for(int i = 0; i < Player::N_PLAYERS;i++){
            spriteSheet = new SpriteSheet(gRenderer,"data/imagenes/objetos/trofeo.bmp",1,13,true);
            pAnimaTrofeos[i]=new Animacion(spriteSheet,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",19+ i*60,15);
            pAnimaTrofeos[i]->setRepeticiones(-1);
            mSprites->add(pAnimaTrofeos[i]);
        }

        spriteSheet = new SpriteSheet(gRenderer,"data/imagenes/objetos/trofeo.bmp",1,13,true);
        mpAnimacionCopaMaxVictorias=new Animacion(spriteSheet,"7,7,7,7,7,7,7,7,7,7,8,8,9,9,9,10,10,10,11,11,12,12,12",139,-2);
        mpAnimacionCopaMaxVictorias->setRepeticiones(-1);
        mpBitmapValorCopasMax = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 139 + 23,3);

        mpBitmapMaxTimeRonda = new BitmapFontRenderer(mBitmapFont[FUENTE_NORMAL], 139 + 23,3);
        //mpBitmapValorCopasMax->setText("0");
        //mSprites->add(mpAnimacionCopaMaxVictorias);

     establecerTerrenoBatalla(0);
    }

    virtual void eliminarSprite(Sprite *sprite) override {
    }
    /**
     *  Cambia el estado de un player lo establece activo/desactivado
     * @param idPlayer
     */

    void cambiarEstadoPlayer(int idPlayer){
        mIsPlayerActivado[idPlayer]=!mIsPlayerActivado[idPlayer];

        mpBitmapTextoValorOpcionMenu[idPlayer + MENU_OPCION_PLAYER_1]->setText((mIsPlayerActivado[idPlayer]) ? "YES" : "NO");

        if(mIsPlayerActivado[idPlayer]){ // Si debe agregarse al juego
            // Se activan/desactivan las animaciones
            mSprites->add(mAnimacionPlayer[idPlayer]);
        }else{ // Si debe eliminarse del juego
            // Se activan/desactivan las animaciones
            mSprites->erase(mAnimacionPlayer[idPlayer]);
        }

        // Si hay mas de dos botones players activados se muestra el boton de jugar
        //mpSfxTogglePlayerEstado->play();
    }

    void resume() override {
        InterfazGrafica::resume();
        if(!Mix_PlayingMusic()){
            musicaFondoMenu->play();
        }
        SDL_ShowCursor(SDL_DISABLE);
    }
    virtual bool setOpcionResaltada(MenuOption nuevaOpcion) {
        if(nuevaOpcion != mOpcionMenuResaltadaActual){
            mpBitmapTextoOpcionMenu[mOpcionMenuResaltadaActual]->setBitmapFont(mBitmapFont[FUENTE_NORMAL]);
            mpBitmapTextoValorOpcionMenu[mOpcionMenuResaltadaActual]->setBitmapFont(mBitmapFont[FUENTE_NORMAL]);
            mpBitmapTextoOpcionMenu[nuevaOpcion]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);
            mpBitmapTextoValorOpcionMenu[nuevaOpcion]->setBitmapFont(mBitmapFont[FUENTE_RESALTADA]);
            mOpcionMenuResaltadaActual =  nuevaOpcion;
            flechaIzquierda->setYDestino(54 + 20*nuevaOpcion);
            flechaDerecha->setYDestino(54   + 20*nuevaOpcion);
            mpSfxCambiarOpcionMenuResaltada->play();
            return true;
        }

        return false;
    }

    virtual bool configuracionAceptada() = 0;
    /**
 * Establece/Cambia el terreno en el que se jugara
 * @param nuevoTerreno
 * @return
 */
    bool establecerTerrenoBatalla(uint16_t nuevoTerreno) {

        if(nuevoTerreno>=0 && nuevoTerreno < mNombreMapas.size()){

            if(mLectorMapas == nullptr){
                mLectorMapas = new LectorMapa(0,32);
            }
            static char ruta1[50],ruta2[50];
            if(!mLectorMapas->cargar(mpGRenderer,"data/niveles/batalla/" + mNombreMapas[indiceTerrenoActual])){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Error cambiando al mapa %s.",ruta1);
                return false;
            }

            for(int i=0;i<Player::N_PLAYERS;i++){

                mAnimacionPlayer[i]->setX(mLectorMapas->getPosXPlayer((IdPlayer)(PLAYER_1 + i)));
                mAnimacionPlayer[i]->setY(mLectorMapas->getPosYPlayer((IdPlayer)(PLAYER_1 + i)));

            }
            indiceTerrenoActual = nuevoTerreno;
            mpBitmapTextoValorOpcionMenu[MENU_OPCION_MAPA]->setText(
                    mNombreMapas[indiceTerrenoActual].substr(
                            0,
                            mNombreMapas[indiceTerrenoActual].find_last_of('.')
                    )
            );
            return true;
        }

        return false;

    }
    void ejecutarAccionOpcionMenu(MenuOption opcion,SDL_Keycode keycode) {
        switch (opcion) {
            case MENU_OPCION_TIEMPO_RONDA:
                if(keycode == SDLK_RIGHT){
                    minutosEscogidos= ( minutosEscogidos + 1) % MAX_MINUTOS;
                }else{
                    minutosEscogidos= (minutosEscogidos >0)?minutosEscogidos -1:MAX_MINUTOS - 1;
                }
                if(!minutosEscogidos){
                    mpBitmapTextoValorOpcionMenu[opcion]->setText("NO");
                }else{
                    mpBitmapTextoValorOpcionMenu[opcion]->setText(std::to_string(minutosEscogidos));
                    mpBitmapMaxTimeRonda->setText(std::to_string(minutosEscogidos) + ":00");
                }
                if(!victoriasEscogidas){
                    rectPlaceHolderTime.x =128;
                }else {
                    rectPlaceHolderTime.x = 90;
                }
                break;
            case MENU_OPCION_MAX_VICTORIAS:
                if(keycode == SDLK_RIGHT){
                    victoriasEscogidas= ( victoriasEscogidas + 1) % MAX_VICTORIAS;
                }else{
                    victoriasEscogidas= (victoriasEscogidas >0)?victoriasEscogidas -1:MAX_VICTORIAS - 1;
                }
                if(!victoriasEscogidas){
                    mpBitmapTextoValorOpcionMenu[opcion]->setText("NO");
                    mSprites->erase(mpAnimacionCopaMaxVictorias);
                    rectPlaceHolderTime.x =128;
                }else{
                    rectPlaceHolderTime.x =90;
                    mpBitmapTextoValorOpcionMenu[opcion]->setText(std::to_string(victoriasEscogidas));
                    mpBitmapValorCopasMax->setText(std::to_string(victoriasEscogidas));
                    if(!mSprites->contain(mpAnimacionCopaMaxVictorias)){
                        mSprites->add(mpAnimacionCopaMaxVictorias);
                    }
                }
                break;
            case MENU_OPCION_MAPA:
                if(keycode == SDLK_RIGHT){
                    indiceTerrenoActual= ( indiceTerrenoActual + 1) % mNombreMapas.size();
                }else{
                    indiceTerrenoActual= (indiceTerrenoActual >0)?indiceTerrenoActual -1:mNombreMapas.size();
                }
                establecerTerrenoBatalla(indiceTerrenoActual);
                break;
            case MENU_OPCION_PLAYER_1:
            case MENU_OPCION_PLAYER_2:
            case MENU_OPCION_PLAYER_3:
            case MENU_OPCION_PLAYER_4:
            case MENU_OPCION_PLAYER_5:
                cambiarEstadoPlayer(opcion - MENU_OPCION_PLAYER_1);
                break;
            case _N_OPCIONES_MENU:break;
        }
        mpSfxCambiarValorOpcionMenuResaltada->play();
    }
    void procesarEvento(SDL_Event *pEvento) override {
        InterfazGrafica::procesarEvento(pEvento);

        if(pEvento->type==SDL_KEYDOWN){
            switch(pEvento->key.keysym.sym){
                case SDLK_LEFT:
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual,SDLK_LEFT);
                    break;
                case SDLK_RIGHT:
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual,SDLK_RIGHT);
                    break;
                case SDLK_UP:
                    setOpcionResaltada((MenuOption)((mOpcionMenuResaltadaActual > 0 ? mOpcionMenuResaltadaActual - 1 : _N_OPCIONES_MENU - 1)));
                    break;
                case SDLK_DOWN:
                    setOpcionResaltada((MenuOption)((mOpcionMenuResaltadaActual + 1)%_N_OPCIONES_MENU));
                    break;
                case SDLK_RETURN:
                    if(configuracionAceptada()){
                        mpSfxPressJugar->play();
                    }
                    break;
                default:
                    break;
            }
        }else if(pEvento->type == SDL_JOYAXISMOTION&&pEvento->jaxis.type == SDL_JOYAXISMOTION){
            if(pEvento->jaxis.axis == 1){
                if(pEvento->jaxis.value > 10){
                    setOpcionResaltada((MenuOption)((mOpcionMenuResaltadaActual + 1)%_N_OPCIONES_MENU));
                }else if(pEvento->jaxis.value < -10){
                    setOpcionResaltada((MenuOption)((mOpcionMenuResaltadaActual > 0 ? mOpcionMenuResaltadaActual - 1 : _N_OPCIONES_MENU - 1)));
                }
            }else{
                if(pEvento->jaxis.value > 10){
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual,SDLK_RIGHT);
                }else if(pEvento->jaxis.value < -10){
                    ejecutarAccionOpcionMenu(mOpcionMenuResaltadaActual,SDLK_LEFT);
                }
            }
        }else if(pEvento->type == SDL_JOYBUTTONDOWN){
            if(pEvento->jbutton.type == SDL_JOYBUTTONDOWN)
                if(pEvento->jbutton.button + 1==3) {
                    if(configuracionAceptada()){
                        mpSfxPressJugar->play();
                    }
                }else if(pEvento->jbutton.button + 1==1) {
                    mGameManagerInterfaz->goBack();
                }

        }


    }

    void update() override {
        InterfazGrafica::update();
        mSprites->update(nullptr);
        mLectorMapas->update();
        flechaIzquierda->update(nullptr);
        flechaDerecha->update(nullptr);
    }

    void draw(SDL_Renderer *gRenderer) override {

        mLectorMapas->draw(gRenderer);//imprimimos el nivel
        mpTextureHUD->draw(gRenderer, 0, 0);//imprimimos la barra mensage

        for(int i=0;i<Player::N_PLAYERS;i++){
            if(!mIsPlayerActivado[i]){
                mpSpriteSheetPlayer[i]->draw(gRenderer,mAnimacionPlayer[i]->getX(),mAnimacionPlayer[i]->getY());
            }
            mpSpriteSheetCarasBomberman->setCurrentCuadro(i*2 + !mIsPlayerActivado[i]);
            mpSpriteSheetCarasBomberman->draw(gRenderer,6+ i*60,20);
            mpBitmapValorCopasGanadas[i]->draw(gRenderer);

        }

        mSprites->draw(gRenderer);
        pTextureFondoMenu->draw(gRenderer,40,40);

        if(victoriasEscogidas > 0){
            mpBitmapValorCopasMax->draw(gRenderer, mpAnimacionCopaMaxVictorias->getX() + 23,3);
        }

        if(minutosEscogidos > 0){
            SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
            SDL_RenderFillRect(gRenderer,&rectPlaceHolderTime);
            mpBitmapMaxTimeRonda->draw(gRenderer,rectPlaceHolderTime.x + 5,rectPlaceHolderTime.y + 1);
        }

        for(int i = 0; i < _N_OPCIONES_MENU;i++){
            mpBitmapTextoOpcionMenu[i]->draw(gRenderer);
            mpBitmapTextoValorOpcionMenu[i]->draw(gRenderer);
        }
        flechaIzquierda->draw(gRenderer);
        flechaDerecha->draw(gRenderer);

    }

    ~MenuEscogerMapa() override {
        for(int i = 0; i < Player::N_PLAYERS;i++){
            delete mAnimacionPlayer[i];
            delete mpSpriteSheetPlayer[i];
            delete pAnimaTrofeos[i];
            delete mpBitmapValorCopasGanadas[i];
        }
        delete mpSpriteSheetCarasBomberman;
        delete mLectorMapas;
        delete mpTextureHUD;
        delete mBitmapFont[0];
        delete mBitmapFont[1];

        for(int i = 0; i < _N_OPCIONES_MENU;i++) {
            delete mpBitmapTextoOpcionMenu[i];
            delete mpBitmapTextoValorOpcionMenu[i];

        }

        delete mpSfxCambiarOpcionMenuResaltada;
        delete mpSfxPressJugar;
        delete mpSfxCambiarValorOpcionMenuResaltada;
        delete musicaFondoMenu;
        delete pTextureFondoMenu;
        delete mSprites;
        delete mpBitmapMaxTimeRonda;
        delete flechaDerecha;
        delete flechaIzquierda;
        delete mpBitmapValorCopasMax;
        delete mpAnimacionCopaMaxVictorias;
    }

private:


    enum{
        FUENTE_NORMAL,
        FUENTE_RESALTADA
    };
    LectorMapa  * mLectorMapas = nullptr;

    //LayoutAbsolute *mLayoutParent = nullptr;

    BitmapFont *mBitmapFont[2];
    BitmapFontRenderer *mpBitmapTextoOpcionMenu[_N_OPCIONES_MENU] {nullptr};
    BitmapFontRenderer *mpBitmapTextoValorOpcionMenu[_N_OPCIONES_MENU] {nullptr};

    // Animacion del personaje
    Animacion * mAnimacionPlayer[Player::N_PLAYERS] {nullptr};


    SpriteSheet * mpSpriteSheetPlayer[Player::N_PLAYERS];

    SDL_Renderer *mpGRenderer;

    EfectoSonido * mpSfxCambiarOpcionMenuResaltada;
    EfectoSonido * mpSfxPressJugar;
    EfectoSonido * mpSfxCambiarValorOpcionMenuResaltada;

    MenuOption mOpcionMenuResaltadaActual = MENU_OPCION_TIEMPO_RONDA;

    MusicaFondo *musicaFondoMenu;

    //EfectoSonido * mpSfxCambiarPagina;
    DrawGroup *mSprites;
    FlechaDinamica * flechaIzquierda;
    FlechaDinamica * flechaDerecha;

    LTexture * pTextureFondoMenu;

    // Elementos del HUD
    LTexture * mpTextureHUD;

    Animacion * pAnimaTrofeos[Player::N_PLAYERS];

    SDL_Rect rectPlaceHolderTime {0,2,48,18};
    BitmapFontRenderer *mpBitmapMaxTimeRonda;

    SpriteSheet * mpSpriteSheetCarasBomberman;

    BitmapFontRenderer *mpBitmapValorCopasGanadas[Player::N_PLAYERS] {nullptr};
    BitmapFontRenderer *mpBitmapValorCopasMax;

    Animacion *mpAnimacionCopaMaxVictorias;

protected:
    bool mIsPlayerActivado[Player::N_PLAYERS] {false};
    // Minutos Escogidos de duracion de cada ronda
    uint8_t minutosEscogidos = 0;
    std::vector<std::string> mNombreMapas;
    // Victorias escogidas para acabar el juego
    uint8_t victoriasEscogidas = 0;
    uint16_t indiceTerrenoActual = 0;
};
#endif //BOMBERMAN_MENUESCOGERMAPA_HPP
