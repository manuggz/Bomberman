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
#include "../../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../../engine/layout/Componentes/BotonComponent.hpp"
#include "../../engine/util/SpriteSheet.hpp"
#include "../../niveles/LectorMapa.hpp"
#include <unistd.h>
#define GetCurrentDir getcwd

static const int ID_BOTON_FLECHA_IZQUIERDA = 1;
static const int ID_BOTON_FLECHA_DERECHA = 2;


class MenuEscogerMapa: public InterfazGrafica, public BotonInterfaz {
public:
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

        mLayoutParent = new LayoutAbsolute();
        mLayoutParent->setBackgroundTexture(gRenderer,"data/imagenes/fondos/fondo_escoja.bmp",false);

        LTexture * lTexture = new LTexture();
        lTexture->cargarDesdeArchivo("data/imagenes/botones/boton_flecha_2_izquierda.png",gRenderer,false);
        botonFlechaIzquierda = new BotonComponent(lTexture, this, ID_BOTON_FLECHA_IZQUIERDA);
        mLayoutParent->addComponent(botonFlechaIzquierda);
        botonFlechaIzquierda->setLayoutParam(LAYOUT_PARAM_X,"17");
        botonFlechaIzquierda->setLayoutParam(LAYOUT_PARAM_Y,"67");

        lTexture = new LTexture();
        lTexture->cargarDesdeArchivo("data/imagenes/botones/boton_flecha_2_derecha.png",gRenderer,false);
        botonFlechaDerecha = new BotonComponent(lTexture, this, ID_BOTON_FLECHA_DERECHA);
        mLayoutParent->addComponent(botonFlechaDerecha);
        botonFlechaDerecha->setLayoutParam(LAYOUT_PARAM_X,"239");
        botonFlechaDerecha->setLayoutParam(LAYOUT_PARAM_Y,"67");

        pSpriteSheetBotonMapa = new SpriteSheet(gRenderer,"data/imagenes/botones/boton_estranyo.png",2,1,false);

        mpTexturePreviewMapa[0] = SDL_CreateTexture(gRenderer,
                                                     mGameManagerInterfaz->getWindowPixelFormat(),
                                                     SDL_TEXTUREACCESS_TARGET,
                                                     mGameManagerInterfaz->getNativeWidth(),
                                                     13*16);

        mpTexturePreviewMapa[1] = SDL_CreateTexture(gRenderer,
                                                     mGameManagerInterfaz->getWindowPixelFormat(),
                                                     SDL_TEXTUREACCESS_TARGET,
                                                     mGameManagerInterfaz->getNativeWidth(),
                                                    13*16);


        mpSfxSeleccionarMapa = new EfectoSonido("data/sonidos/ping_2.wav",100);
        mpSfxCambiarPagina  = new EfectoSonido("data/sonidos/ping_5.wav",100);

        rectBotonMapa[0].x=26;
        rectBotonMapa[0].y=102;
        rectBotonMapa[0].w=111;
        rectBotonMapa[0].h=121;
        estadosBotonMapa[0]=BotonComponent::NORMAL;

        rectBotonMapa[1].x=177;
        rectBotonMapa[1].y=102;
        rectBotonMapa[1].w=111;
        rectBotonMapa[1].h=121;
        estadosBotonMapa[1]=BotonComponent::NORMAL;

        mpGRenderer = gRenderer;
        cambiarPagina(0);
    }

    void actualizarFlechasPaginas(){
        botonFlechaIzquierda->setVisible(indicePaginaActual > 0);
        botonFlechaDerecha->setVisible(indicePaginaActual + 2 < mNombreMapas.size());
    }
    void cargarMapasPaginaActual(SDL_Renderer *gRenderer){
        for(int i = 0; i < 2;i++) {
            if (cargarMapa(gRenderer, i)) {
                esVisibleBotonMapa[i] = true;
                capturarPreviewMapa(gRenderer,i);

            }
        }
    }

    void capturarPreviewMapa(SDL_Renderer * gRenderer,int lado){
        SDL_SetRenderTarget(gRenderer, mpTexturePreviewMapa[lado]);
        SDL_RenderClear(gRenderer);

        mLectorMapas->draw(gRenderer);

        SDL_SetRenderTarget(gRenderer, NULL);
    }
    void resume() override {
        InterfazGrafica::resume();
        SDL_ShowCursor(SDL_ENABLE);
    }

    bool cargarMapa(SDL_Renderer * gRenderer, int lado){
        if(indicePaginaActual * 2 + lado == mNombreMapas.size()) return false;

        if(mLectorMapas == nullptr){
            mLectorMapas= new LectorMapa(0,0);
        }

        if(!mLectorMapas->cargar(gRenderer,mNombreMapas[indicePaginaActual*2 + lado])){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Error cargando el mapa %s.",mNombreMapas[indicePaginaActual*2 + lado].c_str());
            return false;
        }
        return true;
    }

    void onClickButton(int id) override {
        switch(id){
            case ID_BOTON_FLECHA_DERECHA:
                cambiarPagina(indicePaginaActual + 1);
                break;
            case ID_BOTON_FLECHA_IZQUIERDA:
                cambiarPagina(indicePaginaActual - 1);
                break;
        }
    }

    float getScaleRatioW() override {
        return mGameManagerInterfaz->getScaleRatioW();
    }

    float getScaleRatioH() override {
        return mGameManagerInterfaz->getScaleRatioH();
    }
    void packLayout(SDL_Renderer * gRenderer){
        SDL_Rect rect = mGameManagerInterfaz->getRectScreen();
        mLayoutParent->pack(gRenderer);
        mLayoutParent->setRectDibujo(rect);
    }

    void cambiarPagina(int nuevoIndice) {
        indicePaginaActual = nuevoIndice;
        actualizarFlechasPaginas();
        cargarMapasPaginaActual(mpGRenderer);
        mpSfxCambiarPagina->play();
    }

    void procesarEvento(SDL_Event *pEvento) override {
        InterfazGrafica::procesarEvento(pEvento);
        mLayoutParent->procesarEvento(pEvento);

        if(pEvento->type==SDL_KEYDOWN){
            switch(pEvento->key.keysym.sym){
                case SDLK_1:
                    if(esVisibleBotonMapa[0]){
                        establecerMapaEscogido(indicePaginaActual*2);
                    }
                    break;
                case SDLK_2:
                    if(esVisibleBotonMapa[1]){
                        establecerMapaEscogido(indicePaginaActual*2 + 1);
                    }
                    break;
                case SDLK_LEFT:
                    if(botonFlechaIzquierda->getVisible()){
                        cambiarPagina(indicePaginaActual - 1);
                    }
                    break;
                case SDLK_RIGHT:
                    if(botonFlechaDerecha->getVisible()){
                        cambiarPagina(indicePaginaActual + 1);
                    }
                    break;
                default:
                    break;
            }

        }else if(pEvento->type == SDL_MOUSEBUTTONDOWN&&pEvento->button.button==SDL_BUTTON_LEFT) {
            for(int i=0;i<2;i++){
                if(esVisibleBotonMapa[i] && punto_en_rect(pEvento->motion.x,pEvento->motion.y,&rectBotonMapa[i])){
                    estadosBotonMapa[i]=BotonComponent::PRESIONADO;
                }
            }
        }
        else if(pEvento->type == SDL_MOUSEBUTTONUP&&pEvento->button.button==SDL_BUTTON_LEFT) {
            for(int i=0;i<2;i++){
                if(esVisibleBotonMapa[i] && estadosBotonMapa[i]==BotonComponent::PRESIONADO&& punto_en_rect(pEvento->motion.x,pEvento->motion.y,&rectBotonMapa[i])){
                    establecerMapaEscogido(indicePaginaActual*2 + i);
                    //game->play(SFX_TONO_SECO);
                }
                estadosBotonMapa[i]=BotonComponent::NORMAL;
            }
        }

    }

    void update() override {
        InterfazGrafica::update();
    }

    void establecerMapaEscogido(int indice){
        SDL_Log("Mapa escogido: %s.",mNombreMapas[indice].c_str());

        mpSfxSeleccionarMapa->play();

        InterfazEstandarBackResult * result =  new InterfazEstandarBackResult();
        result->texto = mNombreMapas[indice];
        mGameManagerInterfaz->goBack(result);
    }

    void draw(SDL_Renderer *gRenderer) override {
        packLayout(gRenderer);
        mLayoutParent->draw(gRenderer);

        for(int i = 0; i < 2;i++) {
            if (esVisibleBotonMapa[i]) {
                pSpriteSheetBotonMapa->setCurrentCuadro(estadosBotonMapa[i] == BotonComponent::PRESIONADO);
                pSpriteSheetBotonMapa->draw(gRenderer, rectBotonMapa[i].x, rectBotonMapa[i].y);

                static SDL_Rect destPreview;
                destPreview.x = rectBotonMapa[i].x + 7;
                destPreview.y = rectBotonMapa[i].y + 5;
                destPreview.w = rectBotonMapa[i].w - 2;
                destPreview.h = rectBotonMapa[i].h - 2;
                SDL_RenderCopy(gRenderer, mpTexturePreviewMapa[i], NULL, &destPreview);
            }

        }

    }

    ~MenuEscogerMapa() override {
        delete mLayoutParent;
        SDL_DestroyTexture(mpTexturePreviewMapa[0]);
        SDL_DestroyTexture(mpTexturePreviewMapa[1]);
        delete mLectorMapas;
        delete pSpriteSheetBotonMapa;
        delete mpSfxSeleccionarMapa;
        delete mpSfxCambiarPagina;
    }

private:

    std::vector<std::string> mNombreMapas;
    int indicePaginaActual = 0;
    LayoutAbsolute *mLayoutParent = nullptr;

    BotonComponent *botonFlechaIzquierda = nullptr;
    BotonComponent *botonFlechaDerecha = nullptr;

    SDL_Texture *mpTexturePreviewMapa[2];

    LectorMapa  * mLectorMapas = nullptr;
    SpriteSheet * pSpriteSheetBotonMapa = nullptr;
    SDL_Rect rectBotonMapa[2];
    BotonComponent::Estado estadosBotonMapa[2] {BotonComponent::NORMAL};
    bool esVisibleBotonMapa[2] {false};
    SDL_Renderer *mpGRenderer;

    EfectoSonido * mpSfxSeleccionarMapa;
    EfectoSonido * mpSfxCambiarPagina;
};
#endif //BOMBERMAN_MENUESCOGERMAPA_HPP
