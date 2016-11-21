#include "menu.hpp"

Menu::Menu(GameManager * game):

    botonGuardar(game->getImagen(IMG_BOTON_GUARDAR),this),mapa(this){
    this->game=game;

    // ,114,205

    //ventana 3 (MULTIJUGADOR)

    /*ventana 4*/

    //linea de tecla arriba
    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_BOTON_CAMBIAR].x=190;
    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_BOTON_CAMBIAR].y=68;
    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_BOTON_CAMBIAR].w=81;
    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_BOTON_CAMBIAR].h=18;


    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_CUADRO_MOSTRAR].x=93;
    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_CUADRO_MOSTRAR].y=70;

    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_TEXTO_MOSTRAR].x=27;
    rectConfiguracion[MENU_TECLA_ARRIBA][MENU_TEXTO_MOSTRAR].y=69;

    //linea de tecla abajo
    rectConfiguracion[MENU_TECLA_ABAJO][MENU_BOTON_CAMBIAR].x=190;
    rectConfiguracion[MENU_TECLA_ABAJO][MENU_BOTON_CAMBIAR].y=91;
    rectConfiguracion[MENU_TECLA_ABAJO][MENU_BOTON_CAMBIAR].w=81;
    rectConfiguracion[MENU_TECLA_ABAJO][MENU_BOTON_CAMBIAR].h=18;

    rectConfiguracion[MENU_TECLA_ABAJO][MENU_CUADRO_MOSTRAR].x=93;
    rectConfiguracion[MENU_TECLA_ABAJO][MENU_CUADRO_MOSTRAR].y=93;

    rectConfiguracion[MENU_TECLA_ABAJO][MENU_TEXTO_MOSTRAR].x=27;
    rectConfiguracion[MENU_TECLA_ABAJO][MENU_TEXTO_MOSTRAR].y=93;

    //linea de tecla izquierda
    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_BOTON_CAMBIAR].x=190;
    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_BOTON_CAMBIAR].y=112;
    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_BOTON_CAMBIAR].w=81;
    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_BOTON_CAMBIAR].h=18;

    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_CUADRO_MOSTRAR].x=93;
    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_CUADRO_MOSTRAR].y=112;

    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_TEXTO_MOSTRAR].x=27;
    rectConfiguracion[MENU_TECLA_IZQUIERDA][MENU_TEXTO_MOSTRAR].y=112;

    //linea de tecla derecha
    rectConfiguracion[MENU_TECLA_DERECHA][MENU_BOTON_CAMBIAR].x=190;
    rectConfiguracion[MENU_TECLA_DERECHA][MENU_BOTON_CAMBIAR].y=133;
    rectConfiguracion[MENU_TECLA_DERECHA][MENU_BOTON_CAMBIAR].w=81;
    rectConfiguracion[MENU_TECLA_DERECHA][MENU_BOTON_CAMBIAR].h=18;

    rectConfiguracion[MENU_TECLA_DERECHA][MENU_CUADRO_MOSTRAR].x=93;
    rectConfiguracion[MENU_TECLA_DERECHA][MENU_CUADRO_MOSTRAR].y=133;

    rectConfiguracion[MENU_TECLA_DERECHA][MENU_TEXTO_MOSTRAR].x=27;
    rectConfiguracion[MENU_TECLA_DERECHA][MENU_TEXTO_MOSTRAR].y=133;


    //linea de tecla accion
    rectConfiguracion[MENU_TECLA_ACCION][MENU_BOTON_CAMBIAR].x=190;
    rectConfiguracion[MENU_TECLA_ACCION][MENU_BOTON_CAMBIAR].y=153;
    rectConfiguracion[MENU_TECLA_ACCION][MENU_BOTON_CAMBIAR].w=81;
    rectConfiguracion[MENU_TECLA_ACCION][MENU_BOTON_CAMBIAR].h=18;

    rectConfiguracion[MENU_TECLA_ACCION][MENU_CUADRO_MOSTRAR].x=93;
    rectConfiguracion[MENU_TECLA_ACCION][MENU_CUADRO_MOSTRAR].y=153;

    rectConfiguracion[MENU_TECLA_ACCION][MENU_TEXTO_MOSTRAR].x=27;
    rectConfiguracion[MENU_TECLA_ACCION][MENU_TEXTO_MOSTRAR].y=153;

    //linea de tecla start
    rectConfiguracion[MENU_TECLA_START][MENU_BOTON_CAMBIAR].x=190;
    rectConfiguracion[MENU_TECLA_START][MENU_BOTON_CAMBIAR].y=173;
    rectConfiguracion[MENU_TECLA_START][MENU_BOTON_CAMBIAR].w=81;
    rectConfiguracion[MENU_TECLA_START][MENU_BOTON_CAMBIAR].h=18;

    rectConfiguracion[MENU_TECLA_START][MENU_CUADRO_MOSTRAR].x=93;
    rectConfiguracion[MENU_TECLA_START][MENU_CUADRO_MOSTRAR].y=173;

    rectConfiguracion[MENU_TECLA_START][MENU_TEXTO_MOSTRAR].x=27;
    rectConfiguracion[MENU_TECLA_START][MENU_TEXTO_MOSTRAR].y=173;


    //botones para cambiar de player
    /*
    botonPlayer[PLAYER_1]=new BotonComponent<Menu>(game->getImagen(IMG_BOTON_PLAYER_1),this,3,228);
    botonPlayer[PLAYER_2]=new BotonComponent<Menu>(game->getImagen(IMG_BOTON_PLAYER_2),this,64,228);
    botonPlayer[PLAYER_3]=new BotonComponent<Menu>(game->getImagen(IMG_BOTON_PLAYER_3),this,125,228);
    botonPlayer[PLAYER_4]=new BotonComponent<Menu>(game->getImagen(IMG_BOTON_PLAYER_4),this,189,228);
    botonPlayer[PLAYER_5]=new BotonComponent<Menu>(game->getImagen(IMG_BOTON_PLAYER_5),this,252,228);
*/
    botonGuardar.bindAccion(&Menu::guardarTeclas);
    for(int i=0;i<_PLAYERS;i++)
        botonPlayer[i]->bindAccion(&Menu::cambiarPlayer);

    rect_destino_cara.x=126;
    rect_destino_cara.y=50;


    botones_cambiar[MENU_TECLA_ARRIBA]=BOTON_NORMAL;
    botones_cambiar[MENU_TECLA_ABAJO]=BOTON_NORMAL;
    botones_cambiar[MENU_TECLA_IZQUIERDA]=BOTON_NORMAL;
    botones_cambiar[MENU_TECLA_DERECHA]=BOTON_NORMAL;
    botones_cambiar[MENU_TECLA_ACCION]=BOTON_NORMAL;
    botones_cambiar[MENU_TECLA_START]=BOTON_NORMAL;


//    estado_boton_guardar=BOTON_NORMAL;
    maxTerrenoBatalla=std::stoi(buscar_dato(RUTA_CONFIG_BASE,"MaxTerreno"));
    player_configurando_teclas=PLAYER_NONE;
    previewTerreno=NULL;
    mapa.setImgTiles(game->getImagen(IMG_TILES));
    limpiar();
    updatePreview();
    setSelected(0);
    game->playSonido(SND_MENU);
    dataNivel=NULL;;
    //cambiarVentana(VENTANA_1);

    animacion=false;
    setDesvanecimiento(-1,VENTANA_1);
}

void Menu::setDesvanecimiento(int last,int nueva){
    cambiarVentana(nueva);
  	/*ventanaAnterior=last;
  	ventanaSiguiente=nueva;
    nivelAlpha=0;
    nAnimacion=1;
    if(last==-1){
        nAnimacion=2;
        nivelAlpha=255;
    }else
        dibujar_objeto(SDL_GetVideoSurface(),0,0,fondoVentanaAnterior);
    if(ventanaSiguiente!=-1){
        cambiarVentana(ventanaSiguiente);
        draw(fondoVentanaSiguiente);
    }
    SDL_SetAlpha(fondoNegro, SDL_SRCALPHA|SDL_RLEACCEL,nivelAlpha);
    animacion=true;*/
}

void Menu::setSelected(int nuevo){
    if(nuevo<((ventana==VENTANA_1)?5:4)&&nuevo>=0){
        selected=nuevo;
        game->play(SFX_TONO_ACUATICO);
        cout << "selected on menu: " << nuevo << endl;
    }
}

void Menu::cambiarPlayer(){
    for(int i=0;i<_PLAYERS;i++){
        if(i!=player_configurando_teclas&&botonPlayer[i]->estaPresionado()){
            cambiarPlayerConfi((IdPlayer)i);          
            return;
        }
    }
}
void Menu::cambiarPlayerConfi(IdPlayer id){
     //cambia el estado de las variables asociadas al cambio de player al que se le configuran las teclas
      if(player_configurando_teclas!=PLAYER_NONE){
          botonPlayer[player_configurando_teclas]->setEstado(BotonComponent<Menu>::NORMAL);
          botonPlayer[player_configurando_teclas]->setEnable(true);  
      }      
      player_configurando_teclas=id;// guarda el id del nuevo player
      id_espera_tecla=TECLA_NULA; //variable que dice si se espera la pulsacion de una tecla[del joy] para un boton del juego
      botonPlayer[id]->setEstado(BotonComponent<Menu>::PRESIONADO);
      botonPlayer[id]->setEnable(false);
      cargarTeclas();//carga las teclas del File 
}

void Menu::cargarTeclas(){
     //carga las teclas de una player
    char str_tmp[40];
    sprintf(str_tmp,"data/configuracion/teclado_%d.dat",player_configurando_teclas+1);
    control_edit.cargar(str_tmp);

}
void Menu::guardarTeclas(){
    char tmp[40];
    sprintf(tmp,"data/configuracion/teclado_%d.dat",player_configurando_teclas+1);
    control_edit.guardar(tmp);
}

void Menu::limpiar(){
    cambiarPlayerConfi(PLAYER_1);
    for(int i=0;i<_PLAYERS;i++)
          player_batalla[i]=false;
     terrenoActual=0;
     minutosEscogidos=1;
     victoriasEscogidas=1;
}
void Menu::clickControl(BotonComponent<Menu> * control_click){
    selected=control_click->getId();
    clickSelected();
}


void Menu::cambiarVentana(int nueva_ventana){
    ventana=nueva_ventana;
    selected=0;
    SDL_ShowCursor(SDL_DISABLE);//ocultamos el cursor
    
    if(ventana==VENTANA_3){//si es la de multijugador
        SDL_ShowCursor(SDL_ENABLE);
    }
    else if(ventana==VENTANA_4){ //si es la de configuracion
        cargarTeclas();
        id_espera_tecla=TECLA_NULA;
        SDL_ShowCursor(SDL_ENABLE);
//        game->cambiarInterfaz(new EfectoDesvanecimiento(game,this,this));
    }
}


void Menu::cambiarTerrenoBatalla(int aum){
    terrenoActual+=aum;
    if(terrenoActual==maxTerrenoBatalla)//si es el ultimo
        terrenoActual=0;//ponemos el primero
    else if(terrenoActual<0)
        terrenoActual=maxTerrenoBatalla-1;//ponemos el ultimo

}

void Menu::clickSelected(){
    int tmp;

    switch(ventana){
        case VENTANA_3:
                switch(selected){
                    case PLAYER_1:case PLAYER_2:case PLAYER_3:case PLAYER_4:case PLAYER_5:
                          player_batalla[selected]=!player_batalla[selected];
                          if(player_batalla[selected]){
                                sprites->add(animaPlayer[selected]);
                                sprites->add(animaActivado[selected]);
                                sprites->erase(animaPresiona[selected]);
                          }else{
                                sprites->erase(animaPlayer[selected]);
                                sprites->erase(animaActivado[selected]);
                                sprites->add(animaPresiona[selected]);
                          }
                          btnJugar->setVisible(player_batalla[PLAYER_1]+ player_batalla[PLAYER_2]+ player_batalla[PLAYER_3] + player_batalla[PLAYER_4] + player_batalla[PLAYER_5]>1);
                          game->play(SFX_TONO_SECO);
                      break;
                }
            break;
            }
}
void Menu::updatePreview(){
    static char ruta1[50],ruta2[50];
    sprintf(ruta1,"data/niveles/batalla/%d.map",terrenoActual+1);
    sprintf(ruta2,"data/niveles/batalla/%d.txt",terrenoActual+1);
    mapa.cargarDeArchivoBin(ruta1,ruta2);
    mapa.setEjeVisualizacion(mapa.getEjeX(),mapa.getEjeY());

}
void Menu::update(){
    if(!animacion){
        switch(ventana){
                case VENTANA_1:case VENTANA_2:
                    break;
                case VENTANA_3://multijugador
                    sprites->update();
                    break;
                case VENTANA_4://configuracion
                    break;
                case VENTANA_CREDITOS://configuracion
                    break;
            }
    }else{
        if(nAnimacion==1&&(nivelAlpha+=6)>=255){
            nAnimacion=2;
            nivelAlpha=255;
            if(ventanaSiguiente==-1)game->quit();
        }else if(nAnimacion==2&&(nivelAlpha-=6)<=0){
            animacion=false;
        }
        //SDL_SetAlpha(fondoNegro, SDL_SRCALPHA|SDL_RLEACCEL,nivelAlpha);
    }
}


void Menu::procesarEvento(SDL_Event * evento){
    if(!animacion){
        switch(ventana){
            case VENTANA_1:case VENTANA_2:
                if(evento->type==SDL_KEYDOWN){
                        switch(evento->key.keysym.sym){
                            case SDLK_ESCAPE:
                                 if(ventana==VENTANA_2){
                                    setDesvanecimiento(-1,VENTANA_1);
                                 }else{
                                    setDesvanecimiento(ventana,-1);
                                 }
                                break;
                            case SDLK_DOWN:case SDLK_UP:
                                setSelected(selected + (int)pow(-1,evento->key.keysym.sym-272));
                                break;
                            case SDLK_RETURN:
                                clickSelected();
                                break;
                            default:
                                break;
                            }
                }else if(evento->type == SDL_JOYAXISMOTION&&evento->jaxis.type == SDL_JOYAXISMOTION){
                        if(evento->jaxis.axis != 0){
                             if(evento->jaxis.value > 10){
                               setSelected(selected + 1);
                            }else if(evento->jaxis.value < -10){
                               setSelected(selected - 1);
                            }
                        }
                }else if(evento->type == SDL_JOYBUTTONDOWN){
                     if(evento->jbutton.type == SDL_JOYBUTTONDOWN)
                        if(evento->jbutton.button + 1==3)
                                clickSelected();
    
                }
    
            break;
            case VENTANA_3://Multijugador
                break;
                
            case VENTANA_4:
                        if(evento->type == SDL_JOYBUTTONDOWN && id_espera_tecla >-1){
                            if(evento->jbutton.type == SDL_JOYBUTTONDOWN){
                                    control_edit.setKey(id_espera_tecla,(SDL_Keycode)evento->jbutton.button);
                                    control_edit.setIsBotonJoystick(id_espera_tecla,true);;
                                    control_edit.setIsDireccionJoystick((int)id_espera_tecla,false);
                                    control_edit.setName(id_espera_tecla,
                                                         SDL_JoystickName(SDL_JoystickFromInstanceID(evento->jbutton.which)));
                                    id_espera_tecla=TECLA_NULA;//dejamos de esperar a que el usuario presione una tecla
                                }
    
                        }else if(evento->type == SDL_JOYAXISMOTION && id_espera_tecla >= 0){
                                bool modificado=false;
                                if(evento->jaxis.axis == 0) {
                                     if(evento->jaxis.value > 0){
                                            control_edit.setKey(id_espera_tecla,SDLK_RIGHT);
                                            modificado=1;
                                        }
    
                                     else if(evento->jaxis.value < 0){
                                            control_edit.setKey(id_espera_tecla,SDLK_LEFT);
                                            modificado=1;
                                        }
                                } else {
    
                                     if(evento->jaxis.value > 0){
                                            control_edit.setKey(id_espera_tecla,SDLK_DOWN);
                                       modificado=1;
                                    }else if(evento->jaxis.value < 0){
                                            control_edit.setKey(id_espera_tecla,SDLK_UP);
                                            modificado=1;
                                    }
                                }
    
                                if(modificado){
                                    control_edit.setIsBotonJoystick(id_espera_tecla,false);;
                                    control_edit.setIsDireccionJoystick((int)id_espera_tecla,true);
                                    control_edit.setName(id_espera_tecla,
                                                         SDL_JoystickName(SDL_JoystickFromInstanceID(evento->jbutton.which)));
                                    id_espera_tecla=TECLA_NULA;
                                }
                        }else if(evento->type==SDL_KEYDOWN){
                                switch(evento->key.keysym.sym){
                                    case SDLK_RIGHT:
                                        if(player_configurando_teclas==PLAYER_5)break;
                                    case SDLK_LEFT:
                                        if(evento->key.keysym.sym==SDLK_LEFT&&player_configurando_teclas==PLAYER_1)break;
                                        if(id_espera_tecla==TECLA_NULA)
                                            cambiarPlayerConfi((IdPlayer)(player_configurando_teclas + (int)pow(-1,evento->key.keysym.sym-271)));//el pow es para tener 1 o -1 dependiendo de la tecla, notar que si es SDLK_LEFT sera -1
                                        break;
    
                                    case SDLK_ESCAPE:
                                        if(id_espera_tecla !=TECLA_NULA){//si se esperaba la pulsacion de una tecla
                                            id_espera_tecla=TECLA_NULA;
                                        }else{
                                            setDesvanecimiento(-1,VENTANA_1);
                                            limpiar();
                                        }
                                        break;
                                    default:
                                        break;
                                }
    
                                if(id_espera_tecla !=TECLA_NULA){
                                    control_edit.setKey(id_espera_tecla,evento->key.keysym.sym);
                                    control_edit.setIsBotonJoystick(id_espera_tecla,false);;
                                    control_edit.setIsDireccionJoystick((int)id_espera_tecla,false);
                                    id_espera_tecla=TECLA_NULA;
                                }
                        }
                        else if(evento->type == SDL_MOUSEMOTION){
                                static int i;
                                for(i=0;i<6;i++){
                            		if(punto_en_rect(evento->motion.x,evento->motion.y,&rectConfiguracion[i][MENU_BOTON_CAMBIAR])){
                                        if(botones_cambiar[i]!=BOTON_PRESIONADO)
                                				botones_cambiar[i]=BOTON_RESALTADO;
                                    }
                                    else{
                                        botones_cambiar[i]=BOTON_NORMAL;
                                    }
                                }
    
                        }
    
                    	else if(evento->type == SDL_MOUSEBUTTONDOWN&&evento->button.button==SDL_BUTTON_LEFT) {
                                static int i;
                                for(i=0;i<6;i++)
                            		if(punto_en_rect(evento->motion.x,evento->motion.y,&rectConfiguracion[i][MENU_BOTON_CAMBIAR]))
                                				botones_cambiar[i]=BOTON_PRESIONADO;
    
    
    
    
    
                    	}
                    	else if(evento->type == SDL_MOUSEBUTTONUP&&evento->button.button==SDL_BUTTON_LEFT) {
                                for(int i=0;i<6;i++)
                            		if((botones_cambiar[i]==BOTON_PRESIONADO)&&punto_en_rect(evento->motion.x,evento->motion.y,&rectConfiguracion[i][MENU_BOTON_CAMBIAR])){
                                                    id_espera_tecla=(TeclaPlayer)i;
                                                    botones_cambiar[i]=BOTON_NORMAL;
                                                    game->play(SFX_TONO_ACUATICO);
                                     }
                        }
                        for(int i=0;i<_PLAYERS;i++)
                            botonPlayer[i]->procesarEvento(evento);
                        botonGuardar.procesarEvento(evento);
                    break;
            case VENTANA_CREDITOS://configuracion
                if(evento->type==SDL_KEYDOWN){
                     setDesvanecimiento(-1,VENTANA_1);
                }
                break;
    
    	        }
        }
}


void Menu::draw(SDL_Renderer * gRenderer){
    if(!animacion){
        SDL_Rect rect={0,0,0,0};
    
        
        switch(ventana){
            case VENTANA_1:case VENTANA_2:
                game->getImagen(IMG_FONDO_MENU)->render(gRenderer,0,0);
                for(int i=0;i<5;i++) {
                    if (!(ventana == VENTANA_2 && i == 4)) {

                        LTexture * texture =  mFuente->createTextureFromText(gRenderer,texto[ventana][i]);
                        texture->render(gRenderer,rectsImpresion[ventana][i].x,rectsImpresion[ventana][i].y);
                        delete texture;
                    }
                }

                break;
            case VENTANA_3://multijugador

                break;
            case VENTANA_4://configuracion
                game->getImagen(IMG_FONDO_MENU)->render(gRenderer,0,0);

                static char nombre_tecla[20];
                for(int i=0;i<6;i++){
                    //imprimimos el boton
                    imprimir_desde_grilla(game->getImagen(IMG_BOTON_CAMBIAR),(id_espera_tecla==i)?3:botones_cambiar[i],gRenderer,rectConfiguracion[i][MENU_BOTON_CAMBIAR].x,rectConfiguracion[i][MENU_BOTON_CAMBIAR].y,4,1,0);
    
                    //imprimimos la caja de mensaje
                    imprimir_desde_grilla(game->getImagen(IMG_GUI_INPUT_TEXT),id_espera_tecla==i,gRenderer,rectConfiguracion[i][MENU_CUADRO_MOSTRAR].x,rectConfiguracion[i][MENU_CUADRO_MOSTRAR].y,2,1,0);
    
    
                    if(control_edit.isBotonJoystick((TeclaPlayer)i))
                        sprintf(nombre_tecla,"joy %d",control_edit.getKey((TeclaPlayer)i) + 1);
                    else if(control_edit.isDireccionJoystick(i))
                        sprintf(nombre_tecla,"joy %s",SDL_GetKeyName(control_edit.getKey((TeclaPlayer)i)));
                    else if(!strcmp(SDL_GetKeyName(control_edit.getKey((TeclaPlayer)i)),"unknown key")) 
                        strcpy(nombre_tecla,"unknown"); 
                    else
                        strcpy(nombre_tecla,SDL_GetKeyName(control_edit.getKey((TeclaPlayer)i)));
    
                    //imprimimos la tecla
                    //imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_6),rectConfiguracion[i][MENU_CUADRO_MOSTRAR].x,rectConfiguracion[i][MENU_CUADRO_MOSTRAR].y,nombre_tecla,STR_MAX_ESTENDIDA);
    
                    //imprimimos el texto
                    imprimir_desde_grilla(game->getImagen((CodeImagen)(IMG_TXT_ARRIBA + i)),id_espera_tecla==i,gRenderer,rectConfiguracion[i][MENU_TEXTO_MOSTRAR].x,rectConfiguracion[i][MENU_TEXTO_MOSTRAR].y,2,1,0);
                }
/*                for(int i=0;i<_PLAYERS;i++)
                     botonPlayer[i]->draw(gRenderer);
                     
    
    
                botonGuardar.draw(gRenderer);*/
                imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),player_configurando_teclas*2,gRenderer,rect_destino_cara.x,rect_destino_cara.y,1,10,0);
    
    
                break;
            case VENTANA_CREDITOS://Creditos
                //SDL_RenderCopy(gRenderer,game->getImagen(IMG_FONDO_CREDITOS),NULL,NULL); //Dibujamos el fondo
                game->getImagen(IMG_FONDO_CREDITOS)->render(gRenderer,0,0);
                break;
            }
        }else{
            /*if(nAnimacion==1)
                dibujar_objeto(fondoVentanaAnterior,0,0,gRenderer);
            else if(nAnimacion==2)
                dibujar_objeto(fondoVentanaSiguiente,0,0,gRenderer);
            dibujar_objeto(fondoNegro,0,0,gRenderer);*/
      }

}



Menu::~Menu(){
    #ifdef DEBUG
    cout << "Destructor de Menu:"<<this<<endl;
    #endif
    for(int i=0;i<_PLAYERS;i++){
        delete botonPlayer[i];
        delete animaPlayer[i];
        delete animaPresiona[i];
        delete animaActivado[i];
    }
    SDL_FreeSurface(previewTerreno);
    delete dataNivel;
    delete sprites;
    delete btnSubirTiempo;
    delete btnSubirVictorias;
    delete btnCambiarMapa;
    delete btnJugar;
    delete mFuente;
    //SDL_DestroyTexture(fondoVentanaAnterior);
    //SDL_DestroyTexture(fondoVentanaSiguiente);
    //SDL_DestroyTexture(fondoNegro);
//    delete fuente7; 
}


bool Menu::isPaused() {
    return false;
}

void Menu::pause() {

}

void Menu::resume() {

}
