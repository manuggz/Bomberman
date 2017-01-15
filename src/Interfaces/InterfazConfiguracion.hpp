//
// Created by manuggz on 12/01/17.
//

#ifndef BOMBERMAN_CONFIGURACIONINTERFAZ_HPP
#define BOMBERMAN_CONFIGURACIONINTERFAZ_HPP

static const int ID_BOTON_GUARDAR = 5;

#include "../engine/interfaces/InterfazGrafica.hpp"
#include "../engine/util/LTexture.hpp"
#include "../engine/util/SpriteSheet.hpp"
#include "../util/constantes.hpp"
#include "../engine/layout/Componentes/BotonComponent.hpp"
#include "../engine/layout/LayoutManager/LayoutAbsolute.hpp"
#include "../util/control_player.hpp"
#include "../engine/util/CFont.hpp"
#include "../engine/layout/Componentes/LabelComponent.hpp"
#include "../engine/util/EfectoSonido.hpp"

class InterfazConfiguracion: public InterfazGrafica, public BotonInterfaz {
public:
    InterfazConfiguracion(GameManagerInterfazUI *gameManagerInterfaz) : InterfazGrafica(gameManagerInterfaz) {
        SDL_Log("InterfazConfiguracion::InterfazCofiguracion()");
    }

    void prepare() override {
        InterfazGrafica::prepare();
    }

    void cargarTeclas(IdPlayer idPlayer) {
        char str_tmp[40];
        sprintf(str_tmp,"data/configuracion/teclado_%d.dat",idPlayer+1);
        control_edit.cargar(str_tmp);

    }

    void guardarTeclas(IdPlayer idPlayer){
        char tmp[40];
        sprintf(tmp,"data/configuracion/teclado_%d.dat",idPlayer+1);
        control_edit.guardar(tmp);
    }

    void cambiarPlayerConfigurandoTeclas(IdPlayer idPlayer) {
        if(idPlayerConfigurandoTeclas!=PLAYER_NONE){
            botonPlayer[idPlayerConfigurandoTeclas]->setEstado(BotonComponent::NORMAL);
            botonPlayer[idPlayerConfigurandoTeclas]->setEnable(true);
        }
        idPlayerConfigurandoTeclas=idPlayer;// guarda el id del nuevo player
        idTeclaCambiando=ControlPlayer::TECLA_NULA; //variable que dice si se espera la pulsacion de una tecla[del joy] para un boton del juego
        botonPlayer[idPlayerConfigurandoTeclas]->setEstado(BotonComponent::PRESIONADO);
        botonPlayer[idPlayerConfigurandoTeclas]->setEnable(false);
        cargarTeclas(idPlayerConfigurandoTeclas);//carga las teclas del File

    }

    void createUI(SDL_Renderer *gRenderer) override {
        InterfazGrafica::createUI(gRenderer);

        mLayoutParent = new LayoutAbsolute();

        pTextureFondo = new LTexture();
        pTextureFondo->cargarDesdeArchivo("data/imagenes/fondos/fondo_menu.bmp",gRenderer,false);

        pSpriteSheetBotonCambiarTecla = new SpriteSheet(gRenderer,"data/imagenes/botones/boton_cambiar.png",4,1,false);
        pSpriteSheetMensajeIntroducirTecla = new SpriteSheet(gRenderer,"data/imagenes/objetos/entrada_texto.png",2,1,false);
        pSpriteSheetCarasBomberman = new SpriteSheet(gRenderer,"data/imagenes/objetos/caras_bomberman.bmp",1,10,true);

        idTeclaCambiando = ControlPlayer::TECLA_NULA;

        //linea de tecla arriba
        for(int i = 0; i < ControlPlayer::N_TECLAS ; i++){
            pSpriteSheetMensajeNombreTecla[i] = new SpriteSheet(gRenderer,
                                                                "data/imagenes/textos/txt_" + std::to_string(i + 1) + ".png",2,1,false);

            pLabelNombreTecla[i]  = new LabelComponent();
            pLabelNombreTecla[i] ->setFont("data/fuentes/OpenSans-BoldItalic.ttf",15);
            pLabelNombreTecla[i] ->setTextColor(SDL_Color {0,0,255,255});
            //pLabelNombreTecla[i] ->setText("");
            mLayoutParent->addComponent(pLabelNombreTecla[i] );
            pLabelNombreTecla[i]->setLayoutParam(LAYOUT_PARAM_X,"95");
            pLabelNombreTecla[i]->setLayoutParam(LAYOUT_PARAM_Y,std::to_string(68 + 20*i));
        }

        for(int i = 0; i < Player::N_PLAYERS;i++){
            LTexture * lTexture = new LTexture();
            lTexture->cargarDesdeArchivo("data/imagenes/botones/boton_player_" + std::to_string(i + 1) + ".png",gRenderer,false);
            botonPlayer[i] = new BotonComponent(lTexture,this,i);
            mLayoutParent->addComponent(botonPlayer[i]);
            botonPlayer[i]->setLayoutParam(LAYOUT_PARAM_X,std::to_string(3 + 60*i));
            botonPlayer[i]->setLayoutParam(LAYOUT_PARAM_Y,"228");
        }

        LTexture * lTexture = new LTexture();
        lTexture->cargarDesdeArchivo("data/imagenes/botones/boton_guardar.png",gRenderer,false);
        botonGuardar = new BotonComponent(lTexture, this, ID_BOTON_GUARDAR);
        mLayoutParent->addComponent(botonGuardar);
        botonGuardar->setLayoutParam(LAYOUT_PARAM_X,"114");
        botonGuardar->setLayoutParam(LAYOUT_PARAM_Y,"205");

        pSfxClickGuardar = new EfectoSonido("data/sonidos/ping_3.wav",100);

        idPlayerConfigurandoTeclas = PLAYER_NONE;
        cambiarPlayerConfigurandoTeclas(PLAYER_1);

        SDL_ShowCursor(SDL_ENABLE);

    }

    void onClickButton(int id) override {
        switch(id){
            case ID_BOTON_GUARDAR:
                guardarTeclas(idPlayerConfigurandoTeclas);
                pSfxClickGuardar->play();
                break;
            default:
                cambiarPlayerConfigurandoTeclas((IdPlayer) id);
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

    void procesarEvento(SDL_Event *evento) override {

        for(int i = 0; i < Player::N_PLAYERS;i++){
            botonPlayer[i]->procesarEvento(evento);
        }
        botonGuardar->procesarEvento(evento);

        if(evento->type == SDL_JOYBUTTONDOWN && idTeclaCambiando!= ControlPlayer::TECLA_NULA){
            if(evento->jbutton.type == SDL_JOYBUTTONDOWN){

                control_edit.setJoybuttonMapping(idTeclaCambiando,evento->jbutton.button);
                control_edit.setIsBotonJoystick(idTeclaCambiando,true);
                control_edit.setIsDireccionJoystick((int)idTeclaCambiando,false);

                SDL_Joystick * joystick = SDL_JoystickFromInstanceID(evento->jbutton.which);
                //SDL_Log("Joystick Boton %d Presionado.",evento->jbutton.button);
                SDL_JoystickGUID guidj = SDL_JoystickGetGUID(joystick);
                char temp[33];
                SDL_JoystickGetGUIDString(guidj,temp,33);
                control_edit.setJoystickGUID(idTeclaCambiando,temp);
                idTeclaCambiando=ControlPlayer::TECLA_NULA;//dejamos de esperar a que el usuario presione una tecla
            }

        }else if(evento->type == SDL_JOYAXISMOTION && idTeclaCambiando >= 0){
            bool modificado=false;
            if(evento->jaxis.axis == 0) {
                if(evento->jaxis.value > 0){
                    control_edit.setKeyboardMapping(idTeclaCambiando, SDLK_RIGHT);
                    modificado=1;
                }

                else if(evento->jaxis.value < 0){
                    control_edit.setKeyboardMapping(idTeclaCambiando, SDLK_LEFT);
                    modificado=1;
                }
            } else {

                if(evento->jaxis.value > 0){
                    control_edit.setKeyboardMapping(idTeclaCambiando, SDLK_DOWN);
                    modificado=1;
                }else if(evento->jaxis.value < 0){
                    control_edit.setKeyboardMapping(idTeclaCambiando, SDLK_UP);
                    modificado=1;
                }
            }

            if(modificado){
                control_edit.setIsBotonJoystick(idTeclaCambiando,false);;
                control_edit.setIsDireccionJoystick((int)idTeclaCambiando,true);

                SDL_Joystick * joystick = SDL_JoystickFromInstanceID(evento->jbutton.which);
                SDL_JoystickGUID guidj = SDL_JoystickGetGUID(joystick);
                char temp[33];
                SDL_JoystickGetGUIDString(guidj,temp,33);
                control_edit.setJoystickGUID(idTeclaCambiando,temp);

                idTeclaCambiando=ControlPlayer::TECLA_NULA;
            }
        }else if(evento->type==SDL_KEYDOWN){
            switch(evento->key.keysym.sym){
                case SDLK_RIGHT:
                    if(idTeclaCambiando == ControlPlayer::TECLA_NULA){
                        if(idPlayerConfigurandoTeclas != PLAYER_5){
                            cambiarPlayerConfigurandoTeclas((IdPlayer)(idPlayerConfigurandoTeclas + 1));
                        }
                    }
                    break;
                case SDLK_LEFT:
                    if(idTeclaCambiando == ControlPlayer::TECLA_NULA){
                        if(idPlayerConfigurandoTeclas != PLAYER_1){
                            cambiarPlayerConfigurandoTeclas((IdPlayer)(idPlayerConfigurandoTeclas - 1));
                        }
                    }
                    break;

                case SDLK_ESCAPE:
                    if(idTeclaCambiando !=ControlPlayer::TECLA_NULA){//si se esperaba la pulsacion de una tecla
                        idTeclaCambiando=ControlPlayer::TECLA_NULA;
                    }else{
                        mGameManagerInterfaz->goBack();
                    }
                    break;
                default:
                    break;
            }

            if(idTeclaCambiando !=ControlPlayer::TECLA_NULA){
                control_edit.setKeyboardMapping(idTeclaCambiando, evento->key.keysym.sym);
                control_edit.setIsBotonJoystick(idTeclaCambiando,false);;
                control_edit.setIsDireccionJoystick((int)idTeclaCambiando,false);
                idTeclaCambiando=ControlPlayer::TECLA_NULA;
            }
        }
        else if(evento->type == SDL_MOUSEMOTION){
            static int i;
            for(i=0 ; i<ControlPlayer::N_TECLAS;i++){
                if(punto_en_rect_coordenadas(evento->motion.x,evento->motion.y,190,72 + 20*i,81,18)){
                    if(estadoBotonTecla[i]!=BOTON_PRESIONADO)
                        estadoBotonTecla[i]=BOTON_RESALTADO;
                }
                else{
                    estadoBotonTecla[i]=BOTON_NORMAL;
                }
            }

        }

        else if(evento->type == SDL_MOUSEBUTTONDOWN&&evento->button.button==SDL_BUTTON_LEFT) {
            static int i;
            for(i=0;i<6;i++)
                if(punto_en_rect_coordenadas(evento->motion.x,evento->motion.y,190,72 + 20*i,81,18))
                    estadoBotonTecla[i]=BOTON_PRESIONADO;

        }
        else if(evento->type == SDL_MOUSEBUTTONUP&&evento->button.button==SDL_BUTTON_LEFT) {
            for(int i=0;i<6;i++)
                if((estadoBotonTecla[i]==BOTON_PRESIONADO)&&
                        punto_en_rect_coordenadas(evento->motion.x,evento->motion.y,190,72 + 20*i,81,18)){
                    idTeclaCambiando=(ControlPlayer::TeclaPlayer)i;
                    estadoBotonTecla[i]=BOTON_NORMAL;
                    //game->play(SFX_TONO_ACUATICO);
                }
        }
    }

    void update() override {
        InterfazGrafica::update();
    }

    void draw(SDL_Renderer *gRenderer) override {
        static char nombre_tecla[20];

        pTextureFondo->draw(gRenderer, 0, 0);
        for( int i = 0 ; i < ControlPlayer::N_TECLAS ; i++){

            pSpriteSheetBotonCambiarTecla->setCurrentCuadro((idTeclaCambiando==i)?3:estadoBotonTecla[i]);
            pSpriteSheetBotonCambiarTecla->draw(gRenderer,190,72 + 20*i);

            pSpriteSheetMensajeIntroducirTecla->setCurrentCuadro(idTeclaCambiando == i);
            pSpriteSheetMensajeIntroducirTecla->draw(gRenderer,93,72 + 20*i);

            if(control_edit.isBotonJoystick((ControlPlayer::TeclaPlayer)i))
                sprintf(nombre_tecla,"joy %d",control_edit.getJoybuttonMapping((ControlPlayer::TeclaPlayer)i) + 1);
            else if(control_edit.isDireccionJoystick(i))
                sprintf(nombre_tecla,"joy %s",SDL_GetKeyName(control_edit.getKey((ControlPlayer::TeclaPlayer)i)));
            else if(!strcmp(SDL_GetKeyName(control_edit.getKey((ControlPlayer::TeclaPlayer)i)),"unknown key"))
                strcpy(nombre_tecla,"unknown");
            else if(control_edit.getKey((ControlPlayer::TeclaPlayer)i) == SDLK_UNKNOWN){
                strcpy(nombre_tecla,"Sin Asignar.");
            }else
                strcpy(nombre_tecla,SDL_GetKeyName(control_edit.getKey((ControlPlayer::TeclaPlayer)i)));

            //imprimimos la teclaBitmap
            pLabelNombreTecla[i]->setText(nombre_tecla);
            //imprimir_palabra(screen,game->getImagen(IMG_FUENTE_6),rectBotonTecla[i][MENU_CUADRO_MOSTRAR].x,rectBotonTecla[i][MENU_CUADRO_MOSTRAR].y,nombre_tecla,STR_MAX_ESTENDIDA);

            pSpriteSheetMensajeNombreTecla[i]->setCurrentCuadro(idTeclaCambiando == i);
            pSpriteSheetMensajeNombreTecla[i]->draw(gRenderer,27,72 + 20*i);

        }

        packLayout(gRenderer);

        mLayoutParent->draw(gRenderer);
        pSpriteSheetCarasBomberman->setCurrentCuadro(idPlayerConfigurandoTeclas*2);
        pSpriteSheetCarasBomberman->draw(gRenderer,126,50);

    }

    ~InterfazConfiguracion() override {
        SDL_Log("InterfazConfiguracion::~InterfazCofiguracion()");
        delete pTextureFondo;
        delete pSpriteSheetBotonCambiarTecla;
        delete pSpriteSheetMensajeIntroducirTecla;

        for(int i = 0; i < ControlPlayer::N_TECLAS;i++){
            delete pSpriteSheetMensajeNombreTecla[i];
        }
        delete mLayoutParent;
        delete pSpriteSheetCarasBomberman;
        delete pSfxClickGuardar;
        //delete pFuente;
    }

private:

    LTexture * pTextureFondo;

    SpriteSheet * pSpriteSheetBotonCambiarTecla;
    SpriteSheet * pSpriteSheetMensajeIntroducirTecla;
    SpriteSheet * pSpriteSheetMensajeNombreTecla[ControlPlayer::N_TECLAS];
    SpriteSheet * pSpriteSheetCarasBomberman;

    LabelComponent * pLabelNombreTecla[ControlPlayer::N_TECLAS];

    ControlPlayer::TeclaPlayer idTeclaCambiando;

    EstadoBoton estadoBotonTecla[ControlPlayer::N_TECLAS] {BOTON_NORMAL};
    BotonComponent * botonPlayer[Player::N_PLAYERS];
    LayoutAbsolute * mLayoutParent;
    BotonComponent *botonGuardar;
    IdPlayer idPlayerConfigurandoTeclas;

    EfectoSonido * pSfxClickGuardar;
    ControlPlayer control_edit;
};
#endif //BOMBERMAN_CONFIGURACIONINTERFAZ_HPP
