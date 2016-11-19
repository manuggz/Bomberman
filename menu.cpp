#include "menu.hpp"

Menu::Menu(GameManager * game):

    botonGuardar(game->getImagen(IMG_BOTON_GUARDAR),this,114,205),mapa(this){
    #ifdef DEBUG
    cout << "Constructor de Menu:"<<this<<endl;
    #endif
    this->game=game;

    
    // ventana 1
    strcpy(texto[VENTANA_1][MENU_NUEVO_JUEGO],"NUEVO JUEGO");
    strcpy(texto[VENTANA_1][MENU_EDITOR],"EDITOR");
    strcpy(texto[VENTANA_1][MENU_CONFIGURACION],"CONFIGURAR");
    strcpy(texto[VENTANA_1][MENU_CREDITOS],"CREDITOS");
    strcpy(texto[VENTANA_1][MENU_SALIR],"SALIR");

    //ventana 2
    strcpy(texto[VENTANA_2][MENU_MODO_HISTORIA],"HISTORIA");
    strcpy(texto[VENTANA_2][MENU_MODO_MULTIJUGADOR],"MULTIPLAYER");
    strcpy(texto[VENTANA_2][MENU_MODO_CONEXION],"CONEXI�N");
    strcpy(texto[VENTANA_2][MENU_REGRESAR],"REGRESAR");


    /*RECTS PARA IMPRIMIR LOS MENSAGES DE LA VENTANA*/
    //ventana 1
    rectsImpresion[VENTANA_1][MENU_NUEVO_JUEGO].x=38;
    rectsImpresion[VENTANA_1][MENU_NUEVO_JUEGO].y=77;

    rectsImpresion[VENTANA_1][MENU_EDITOR].x=102;
    rectsImpresion[VENTANA_1][MENU_EDITOR].y=115;

    rectsImpresion[VENTANA_1][MENU_CONFIGURACION].x=49;
    rectsImpresion[VENTANA_1][MENU_CONFIGURACION].y=145;

    rectsImpresion[VENTANA_1][MENU_CREDITOS].x=102;
    rectsImpresion[VENTANA_1][MENU_CREDITOS].y=175;

    rectsImpresion[VENTANA_1][MENU_CREDITOS].x=64;
    rectsImpresion[VENTANA_1][MENU_CREDITOS].y=175;

    rectsImpresion[VENTANA_1][MENU_SALIR].x=91;
    rectsImpresion[VENTANA_1][MENU_SALIR].y=200;

    //ventana 2
    rectsImpresion[VENTANA_2][MENU_MODO_HISTORIA].x=66;
    rectsImpresion[VENTANA_2][MENU_MODO_HISTORIA].y=77;

    rectsImpresion[VENTANA_2][MENU_MODO_MULTIJUGADOR].x=42;
    rectsImpresion[VENTANA_2][MENU_MODO_MULTIJUGADOR].y=115;

    rectsImpresion[VENTANA_2][MENU_MODO_CONEXION].x=66;
    rectsImpresion[VENTANA_2][MENU_MODO_CONEXION].y=153;

    rectsImpresion[VENTANA_2][MENU_REGRESAR].x=69;
    rectsImpresion[VENTANA_2][MENU_REGRESAR].y=195;

    //ventana 3 (MULTIJUGADOR)
    sprites=new Group(this);

    btnSubirTiempo=new Boton<Menu>(game->getImagen(IMG_BOTON_FLECHA_PEQUE_DERECHA),this,194,8);
    btnSubirVictorias=new Boton<Menu>(game->getImagen(IMG_BOTON_FLECHA_PEQUE_DERECHA),this,295,8);
    btnCambiarMapa=new Boton<Menu>(game->getImagen(IMG_BOTON_CAMBIAR_MAPA),this,160,225);
    btnJugar=new Boton<Menu>(game->getImagen(IMG_BOTON_JUGAR_2),this,240,225);
    
    btnSubirTiempo->setId(MENU_BOTON_SUBIR_TIEMPO);
    btnSubirVictorias->setId(MENU_BOTON_SUBIR_VICTORIAS);
    btnCambiarMapa->setId(MENU_BOTON_CAMBIAR_MAPA);
    btnJugar->setId(MENU_BOTON_JUGAR);
    
    btnSubirTiempo->bindAccion(&Menu::clickControl);
    btnSubirVictorias->bindAccion(&Menu::clickControl);
    btnCambiarMapa->bindAccion(&Menu::clickControl);
    btnJugar->bindAccion(&Menu::clickControl);    
    btnJugar->setVisible(false);
    
    animaPlayer[0]=new Animacion(game->getImagen(IMG_PLAYER_1),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_1,Y_INIT_PLAYER_1,0);
    animaPlayer[1]=new Animacion(game->getImagen(IMG_PLAYER_2),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_2,Y_INIT_PLAYER_2,1);
    animaPlayer[2]=new Animacion(game->getImagen(IMG_PLAYER_3),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_3,Y_INIT_PLAYER_3,2);
    animaPlayer[3]=new Animacion(game->getImagen(IMG_PLAYER_4),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_4,Y_INIT_PLAYER_4-20,3);
    animaPlayer[4]=new Animacion(game->getImagen(IMG_PLAYER_5),1,12,"6,6,7,7,8,8",X_INIT_PLAYER_5,Y_INIT_PLAYER_5,4);

    for(int i=0;i<_PLAYERS;i++){
        animaPresiona[i]=new Animacion(game->getImagen(IMG_TXT_PRESIONA),2,1,"0,0,1,1",animaPlayer[i]->getX()-9,animaPlayer[i]->getY()+20,i);
        animaActivado[i]=new Animacion(game->getImagen(IMG_TXT_ACTIVADO),2,1,"0,0,0,1,1,1",animaPlayer[i]->getX()-9,animaPlayer[i]->getY()+20,i);
        animaPlayer[i]->setLoop(-1);
        animaActivado[i]->setLoop(-1);
        animaPresiona[i]->setLoop(-1);
        sprites->add(animaPresiona[i]);
    }
    
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

    botonPlayer[PLAYER_1]=new Boton<Menu>(game->getImagen(IMG_BOTON_PLAYER_1),this,3,228);
    botonPlayer[PLAYER_2]=new Boton<Menu>(game->getImagen(IMG_BOTON_PLAYER_2),this,64,228);
    botonPlayer[PLAYER_3]=new Boton<Menu>(game->getImagen(IMG_BOTON_PLAYER_3),this,125,228);
    botonPlayer[PLAYER_4]=new Boton<Menu>(game->getImagen(IMG_BOTON_PLAYER_4),this,189,228);
    botonPlayer[PLAYER_5]=new Boton<Menu>(game->getImagen(IMG_BOTON_PLAYER_5),this,252,228);

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
    maxTerrenoBatalla=buscar_dato(RUTA_CONFIG_BASE,"MaxTerreno");
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

void Menu::crearTexturas(SDL_Renderer * gRenderer) {
    /*SDL_Surface * tmp =  SDL_CreateRGBSurface(SDL_SWSURFACE,W_SCREEN, H_SCREEN, 24,0,0, 0, 255);
    fondoVentanaAnterior= SDL_CreateTextureFromSurface(gRenderer,tmp);
    SDL_FreeSurface(tmp);

    tmp = SDL_CreateRGBSurface(SDL_SWSURFACE,W_SCREEN, H_SCREEN, 24,0,0, 0, 255);
    fondoVentanaSiguiente= SDL_CreateTextureFromSurface(gRenderer,tmp);
    SDL_FreeSurface(tmp);

    tmp = SDL_CreateRGBSurface(SDL_SWSURFACE,W_SCREEN, H_SCREEN, 24,0,0, 0, 0);
    fondoNegro= SDL_CreateTextureFromSurface(gRenderer,tmp);
    SDL_FreeSurface(tmp);*/
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
          botonPlayer[player_configurando_teclas]->setEstado(Boton<Menu>::NORMAL);
          botonPlayer[player_configurando_teclas]->setEnable(true);  
      }      
      player_configurando_teclas=id;// guarda el id del nuevo player
      id_espera_tecla=TECLA_NULA; //variable que dice si se espera la pulsacion de una tecla[del joy] para un boton del juego
      botonPlayer[id]->setEstado(Boton<Menu>::PRESIONADO);
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
void Menu::clickControl(Boton<Menu> * control_click){
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
        case VENTANA_1:
            switch(selected){
                case MENU_NUEVO_JUEGO:
                    cout << "MENU_NUEVO_JUEGO"<< endl;
//                    cambiarVentana(VENTANA_2);
                    setDesvanecimiento(VENTANA_1,VENTANA_2);
                    break;
                case MENU_EDITOR:
                    cout << "MENU_EDITOR"<< endl;
                     game->cambiarInterfaz(new Editor(game));
                    break;
                case MENU_CONFIGURACION:
                    cout << "MENU_CONFIGURACION"<< endl;
//                    cambiarVentana(VENTANA_4);
                    setDesvanecimiento(VENTANA_1,VENTANA_4);
                    break;
                case MENU_CREDITOS:
                    cout << "MENU_CREDITOS"<< endl;
//                    cambiarVentana(VENTANA_CREDITOS);
                    setDesvanecimiento(VENTANA_1,VENTANA_CREDITOS);
                    break;
                case MENU_SALIR:
                    cout << "MENU_SALIR"<< endl;
                    setDesvanecimiento(VENTANA_1,-1);
//                    game->quit();
                    break;
                }
            break;
        case VENTANA_2:
            switch(selected){
                case MENU_MODO_HISTORIA:
                    game->cambiarInterfaz(new JuegoHistoria(game));
                    break;
                case MENU_MODO_MULTIJUGADOR:
                    setDesvanecimiento(VENTANA_2,VENTANA_3);
//                    cambiarVentana(VENTANA_3);
                    break;
                case MENU_MODO_CONEXION:
                    break;
                case MENU_REGRESAR:
                    setDesvanecimiento(VENTANA_2,VENTANA_1);
//                    cambiarVentana(VENTANA_1);
                    break;
                }
            break;
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
                    case MENU_BOTON_SUBIR_TIEMPO:
                        if(++minutosEscogidos>5)minutosEscogidos=1;
                        break;
                    case MENU_BOTON_SUBIR_VICTORIAS:
                        if(++victoriasEscogidas>8)victoriasEscogidas=1;
                        break;
                    case MENU_BOTON_CAMBIAR_MAPA:
                        if(++terrenoActual==maxTerrenoBatalla)terrenoActual=0;
                        updatePreview();
                        game->play(SFX_TONO_ACUATICO);
                        break;
                    case MENU_BOTON_JUGAR:
                        int total_players=player_batalla[PLAYER_1]+ player_batalla[PLAYER_2]+ player_batalla[PLAYER_3] + player_batalla[PLAYER_4] + player_batalla[PLAYER_5];
                        if(total_players>=2){
                            game->cambiarInterfaz(new JuegoBatalla(game,terrenoActual,player_batalla,minutosEscogidos,victoriasEscogidas)); //iniciamos en modo batalla, le pasamos el array con los players seleccionados por el usuario
                            game->play(SFX_EXPLOSION);
                        }
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
                if(evento->type==SDL_KEYDOWN){
                    switch(evento->key.keysym.sym){
                        case SDLK_ESCAPE:
                            setDesvanecimiento(-1,VENTANA_2);
                            limpiar();
                            break;
                        case SDLK_RETURN:
    						selected=MENU_BOTON_JUGAR;
    						clickSelected();
                            break;
                        case SDLK_KP_1:case SDLK_KP_2:case SDLK_KP_3:case SDLK_KP_4:case SDLK_KP_5:
    						selected=(evento->key.keysym.sym-SDLK_KP_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
    						clickSelected();
    						break;
                        case SDLK_1:case SDLK_2:case SDLK_3:case SDLK_4:case SDLK_5:
    						selected=(evento->key.keysym.sym-SDLK_1); //seleccionamos el player con una formula mate. SDK_1:49 y SDLK_5:53
    						clickSelected();
                            break;
                        case SDLK_LEFT:case SDLK_RIGHT:
    					    selected=MENU_BOTON_CAMBIAR_MAPA;
    						clickSelected();
                            break;
                        default:
                            break;
                    }
                }
                btnSubirTiempo->procesarEvento(evento);
                btnSubirVictorias->procesarEvento(evento);
                btnCambiarMapa->procesarEvento(evento);
                btnJugar->procesarEvento(evento);
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
                for(int i=0;i<5;i++)
                    if(!(ventana==VENTANA_2 && i==4))
                        imprimir_palabra(gRenderer,(i==selected)?game->getImagen(IMG_FUENTE_8):game->getImagen(IMG_FUENTE_7),
                                        rectsImpresion[ventana][i].x,
                                        rectsImpresion[ventana][i].y,
                                        texto[ventana][i],STR_MAX_ESTENDIDA);
                    
                break;
            case VENTANA_3://multijugador
                game->getImagen((CodeImagen)mapa.getIdFondo())->render(gRenderer,0,0);
                game->getImagen(IMG_TABLERO)->render(gRenderer,0,mapa.getYPanel());//imprimimos la barra mensage
                game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,177,7+mapa.getYPanel());//imprimimos la barra mensage
                game->getImagen(IMG_CUADRO_PEQUENIO)->render(gRenderer,280,7+mapa.getYPanel());//imprimimos la barra mensage
                game->getImagen(IMG_TXT_PLAYERS_EN_BATALLA)->render(gRenderer,15,24+mapa.getYPanel());//imprimimos la barra mensage
                game->getImagen(IMG_TXT_TIEMPO_POR_RONDA)->render(gRenderer,140,24+mapa.getYPanel());//imprimimos la barra mensage
                game->getImagen(IMG_TXT_VICTORIAS)->render(gRenderer,261,24+mapa.getYPanel());//imprimimos la barra mensage

                static char tmp[50];
                
                sprintf(tmp,"%d",minutosEscogidos);
                imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_6),178,8+mapa.getYPanel(),tmp,STR_MAX_ESTENDIDA);
                sprintf(tmp,"%d",victoriasEscogidas);
                imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_6),280,8+mapa.getYPanel(),tmp,STR_MAX_ESTENDIDA);
    
                btnSubirTiempo->draw(gRenderer);
                btnSubirVictorias->draw(gRenderer);
                mapa.draw(gRenderer);//imprimimos el nivel
                
                sprites->draw(gRenderer);
                for(int i=0;i<_PLAYERS;i++){
                    if(!player_batalla[i]){
                	   imprimir_desde_grilla(game->getImagen((CodeImagen)(IMG_PLAYER_1 + i)), 6,gRenderer, animaPlayer[i]->getX(),animaPlayer[i]->getY(),1, 12,true);
                       sprintf(tmp,"%d",i+1);
                       imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_6),animaPlayer[i]->getX()-9+41,animaPlayer[i]->getY()+19,tmp,STR_MAX_ESTENDIDA);
                    }else{
                       imprimir_desde_grilla(game->getImagen(IMG_CARAS_BOMBERMAN),i*2,gRenderer,i*16+20,mapa.getYPanel()+2,1,10,0);
                    }
                }
                btnCambiarMapa->draw(gRenderer);
                btnJugar->draw(gRenderer);
                
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
                    imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_6),rectConfiguracion[i][MENU_CUADRO_MOSTRAR].x,rectConfiguracion[i][MENU_CUADRO_MOSTRAR].y,nombre_tecla,STR_MAX_ESTENDIDA);
    
                    //imprimimos el texto
                    imprimir_desde_grilla(game->getImagen((CodeImagen)(IMG_TXT_ARRIBA + i)),id_espera_tecla==i,gRenderer,rectConfiguracion[i][MENU_TEXTO_MOSTRAR].x,rectConfiguracion[i][MENU_TEXTO_MOSTRAR].y,2,1,0);
                }
                for(int i=0;i<_PLAYERS;i++)
                     botonPlayer[i]->draw(gRenderer);
                     
    
    
                botonGuardar.draw(gRenderer);
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
    //SDL_DestroyTexture(fondoVentanaAnterior);
    //SDL_DestroyTexture(fondoVentanaSiguiente);
    //SDL_DestroyTexture(fondoNegro);
//    delete fuente7; 
}
