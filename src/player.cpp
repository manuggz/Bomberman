#include "player.hpp"


//#define DEBUG

Player::Player(Juego * juego,IdPlayer id,int x,int y,int vidasIni,int numBombasIni,int alcanceBombasIni){
    #ifdef DEBUG
    cout << "Constructor de Player:"<<this<<endl;
    #endif

    this->juego=juego;

    this->id=id;
    
    rect.w=W_COLISION;
    rect.h=H_COLISION;

    mantieneStartPresionado=false;
    self_kill=false;
	estaProtegido=false;

    idUltimaBomba=-1;

    //variables para reiniciarlo
    this->alcanBombIni=alcanceBombasIni;
    this->numBombasIni=numBombasIni;

    xIni=x;
    yIni=y;

    this->vidas=vidasIni;


	estado = ABAJO;//estado del personaje que pasara a ser el anterior(solo para que mire para abajo)
    reiniciar();
//	cambiarEstado(PARADO);
    cargarTeclas();
//	move(x,y);

}

void Player::reiniciar(){
    enPantalla=true;
    muerto=false;
    entroPuerta=false;
    puedeAtravesarBloquesBlandos=false;
    alcanBomb=alcanBombIni;
    numBombas=numBombasIni;
    velocidad=1;
    puedeAtravesarBombas=false;
    puedeGolpearBombas=false;
    estaEnfermo=false;
    corazones=0;
    puntaje=0;
    cambiarEstado(PARADO);
    estaProtegido=false;
    move(xIni,yIni);
//    juego->resetEjes();
//    setProteccion(10);

}

void Player::disable(){
	enPantalla=false;
	juego->erase(PLAYER,getId());
}

void Player::cargarTeclas(){
    char tmp_ruta[40];
    sprintf(tmp_ruta,"data/configuracion/teclado_%d.dat",id+1);

    if(!control.cargar(tmp_ruta,false)){//si no se puede cargar de un archivo
        //se asignan teclas por default
        control.setDefaultKeys((IdPlayer)id);
    }
}



void Player::updateRectColision(){
    //actualiza el cuadro que representa al personaje en la colision
    rect.x=x+X_COLISION;
    rect.y=y+Y_COLISION;

}


void Player::update(const Uint8 * teclas){
    
	avanzarAnimacion ();//avanzamos la animacion
    updateRectColision();
	switch (estado){
		case PARADO:
		    parado (teclas);
			break;

		case IZQUIERDA:
			izquierda(teclas);
			break;

		case DERECHA:
			derecha(teclas);
			break;

		case ARRIBA:
			arriba(teclas);
			break;
		case ABAJO:
			abajo(teclas);
			break;
		case MURIENDO:break;
	}

    if(estado!=MURIENDO){
        if(!estaProtegido){//si no esta protegido
            static int id_explo;
            if(juego->colision(GLOBO,rect)!=-1){
                if(!corazones)
                    cambiarEstado(MURIENDO);
                else{
                    setProteccion(10);
                    corazones--;
                }
            }else if((id_explo=juego->colision(EXPLOSION,rect))!=-1){
                if(!corazones){
                    cambiarEstado(MURIENDO);
                    if(juego->getTipoJuego()==TIPO_BATALLA){
                        /*if(juego->explosiones[id_explo-1]->lanzador!=id)
                            juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]++;
                        else
                            juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]--;
                        juego->kills[id]++;*/
                        if(juego->getLanzador(EXPLOSION,id_explo)!=this->id);
    //                        juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]++;
                        else;
    //                        juego->matadas[personajes->juego->objetos->explosiones[id_explo-1]->lanzador]--;
    //                    juego->kills[id]++;
                        
                    }//fin "si tipo de juego es BATALLA"
                }else{
                    setProteccion(10);
                    corazones--;
                }
            }//fin "si el id de la explosion no es -1"
        }else{//si esta protegido
            if(juego->getTick()-tiempoInicioProteccion>=duracionProteccion){
                estaProtegido=false;
            }
        }
    }//fin "si no esta muriendo"

    /*SI COLISIONA CON ALG�N ITEM*/
      int id_item;//almacena la respuesta de: �con que item esta colisionando?

      id_item=juego->colision(ITEM,rect);
      if(id_item!=-1){//�colisiono con uno?
            int tipo_item=juego->getTipoItem(id_item);
            if(tipo_item==Item::ITEM_PUERTA){
                if(juego->getActivos(GLOBO)==0)
                    entroPuerta=true;
            }else{
                setPuntaje(getPuntaje()+20);
                activarPoderItem(tipo_item);
                juego->killSprite(ITEM,id_item);
                juego->play(SFX_COGER_ITEM);
            }
       }

    /*SI EL PLAYER ESTA MUERTO*/
    if(muerto){//si el player esta muerto
        if(--vidas>=0){//si sigue con vida
            reiniciar();
            setProteccion(5);
            juego->play(SFX_PIERDE_VIDA);
        }
        else
            disable();
    }


    if (entroPuerta&&juego->getTipoJuego()==TIPO_NORMAL){//si entro en la puerta de fin de nivel
            /*entro_puerta=false;
            proteccion=true;
            cambiarEstado(PARADO);
            int bonus=time(0)-juego->getSegundosInicioNivel();
            setPuntaje(getPuntaje()+bonus);
            if(juego->isActivo(PLAYER,PLAYER_2)){
                juego->setPuntaje(PLAYER_2,juego->getPuntaje(PLAYER_2) + bonus);
                juego->cambiarEstadoPlayer(PLAYER_2,PARADO);
            }
            juego->setNivelPlay(juego->getNivelActual() + 1,false);*/
            juego->aumentarNivel();
            
    }
}

void Player::activarPoderItem(int tipo){
//    cout <<"activando poder item:"<<tipo<<endl;
    switch(tipo){
        case Item::ITEM_ALCANCE:
            if(alcanBomb < MAX_ALCANCE_EXPLOSION)
                alcanBomb++;
            break;
        case Item::ITEM_VIDA:
            vidas++;
            break;
        case Item::ITEM_BOMBA:
            if(numBombas < MAX_BOMBAS)
                numBombas++;
            break;
        case Item::ITEM_ATRAVIESA_PAREDES:
            puedeAtravesarBloquesBlandos=true;
            break;
        case Item::ITEM_ALEATORIO:
            activarPoderItem(juego->getTipoNuevoItem(false));
            break;
        case Item::ITEM_BOMBA_MAX:
            numBombas=MAX_BOMBAS;
            break;
        case Item::ITEM_ALCANCE_MAX:
            alcanBomb=MAX_ALCANCE_EXPLOSION;
            break;
        case Item::ITEM_PROTECCION:
            setProteccion(20);
            break;
        case Item::ITEM_BOLA_ARROZ:
            setPuntaje(getPuntaje()+100);
            break;
        case Item::ITEM_PASTEL:
            setPuntaje(getPuntaje()+120);
            break;
        case Item::ITEM_PALETA:
            setPuntaje(getPuntaje()+120);
            break;
        case Item::ITEM_BARQUILLA:
            setPuntaje(getPuntaje()+50);
            break;
        case Item::ITEM_MANZANA:
            setPuntaje(getPuntaje()+250);
            break;
        case Item::ITEM_PATINETA:
            velocidad=2;
            break;
        case Item::ITEM_CORAZON:
            corazones++;
            break;
        case Item::ITEM_ATRAVIESA_BOMBAS:
            puedeAtravesarBombas=true;
            break;
        case Item::ITEM_PATEA_BOMBA:
            puedePatearBombas=true;
            break;
        default:
            break;
        }
}

void Player::draw(SDL_Renderer * gRenderer){
    if(estado!=MURIENDO)
    	imprimir_desde_grilla (juego->getImagen((CodeImagen)(IMG_PLAYER_1 + id)), cuadro,gRenderer, x,y,1, 12,estaProtegido);
    else
    	imprimir_desde_grilla(juego->getImagen((CodeImagen)(IMG_PLAYER_1_MURIENDO + id)), cuadro,gRenderer,x,y,1, 4,0);
//    if(estaProtegido)render_texture(juego->getImagen(IMG_FONDO_BLANCO),x,y,screen);
	/*DIBUJA EL CUADRO QUE REPRESENTA LA COLISION DEL PERSONAJE*/
#ifdef DEBUG
            updateRectColision();
            SDL_FillRect(screen,&rect,SDL_MapRGB (screen->format, 0, 0, 255));
#endif
}


void Player::ponerBomba(const Uint8 * teclas){
    TipoSprite conjun_coli[]={BOMBA,GLOBO,NIVEL,ITEM};
    
    SDL_Rect rect_bomb={0,0,16,16};
    updateRectColision();
	if(!mantieneStartPresionado&&\
        isPressed(TECLA_ACCION,teclas)&&\
        (juego->getActivosId(BOMBA,(IdPlayer)id) < numBombas)&&\
        (juego->colision(conjun_coli,4,rect)==-1)){

                /*anyadimos la bomba inocentemente*/
               int id_bomba_colocada=juego->addSprite(BOMBA,(x+7-juego->getEjeXVisual())/16*16+juego->getEjeXVisual(),(y+11-juego->getEjeYVisual())/16*16+juego->getEjeYVisual(),(int)id);
               /*si se logro anyadir*/
    	       if(id_bomba_colocada!=-1){
                    /*si la bomba que colocamos colisiona con un personaje la quitamos porque el PLAYER CON EL QUE COLISIONA
                    NO SE MOVERA NUNCA*/
                    int x,y;
                   juego->getPosicion(BOMBA,id_bomba_colocada,x,y);
                   rect_bomb.x=x;
                   rect_bomb.y=y;
    	           if(juego->colision(PLAYER,rect_bomb,id)!=-1||juego->colision(GLOBO,rect_bomb)!=-1){
                            juego->soloKill(BOMBA,id_bomba_colocada);
                            return;
                    }
                    /*sino ocurre lo de arriba continuamos  */
                   idUltimaBomba=id_bomba_colocada;
                }
        }

	mantieneStartPresionado=isPressed(TECLA_ACCION,teclas);
}

bool Player::colision(SDL_Rect & rect){

    updateRectColision();
    return rects_colisionan(this->rect,rect);
}

void Player::parado(const Uint8 * teclas)
{
//     if(!es_bot){
        if(isPressed(TECLA_ARRIBA,teclas))
            cambiarEstado(ARRIBA);
    
        if(isPressed(TECLA_ABAJO,teclas))
            cambiarEstado (ABAJO);
    
        if(isPressed(TECLA_IZQUIERDA,teclas))
            cambiarEstado (IZQUIERDA);
    
        if(isPressed(TECLA_DERECHA,teclas))
            cambiarEstado(DERECHA);

        ponerBomba(teclas);
    /*}else{
       static int delay;
       static int estados
          if(++delay>=100){
               delay=0;
               
          }
    }   */


}

void Player::izquierda(const Uint8 * teclas)
{
	mover_ip(-velocidad,0);
	if(!isPressed(TECLA_IZQUIERDA,teclas))
    	cambiarEstado(PARADO);

	ponerBomba(teclas);


}

void Player::derecha (const Uint8 * teclas)
{
	mover_ip(velocidad,0);
	if(!isPressed(TECLA_DERECHA,teclas))
    	cambiarEstado ( PARADO);

	ponerBomba(teclas);
}


bool Player::isPressed(TeclaPlayer tecla, const Uint8 * _teclas){
    if(!control.isBotonJoystick(tecla) && !control.isDireccionJoystick(tecla)){
        return _teclas [control.getKey(tecla)];

    }else{
        for(int i=0;i<juego->getJoysActivos();i++){
            if(!strcmp(SDL_JoystickName(juego->getJoy(i)),control.getName(tecla))){//si coincide con el joistick con el que se configuro
				return estado_tecla_joy(control.getKey(tecla),juego->getJoy(i));
             }
         }
         return false;
     }
}
void Player::arriba (const Uint8 * teclas)
{
    mover_ip (0,-velocidad);
	if(!isPressed(TECLA_ARRIBA,teclas))
    	cambiarEstado(PARADO);

	ponerBomba(teclas);


}

void Player::abajo(const Uint8 * teclas)
{
	mover_ip(0,velocidad);
	if(!isPressed(TECLA_ABAJO,teclas))
    	cambiarEstado (PARADO);

	ponerBomba(teclas);


}

/*
 * modifica el cuadro de la animaci�n que se debe mostrar en pantalla
 */
void Player::avanzarAnimacion ()
{
	static int animaciones [_ESTADOS][17] = {\
		{3,3, 4,4, 5,5,-1},\
		{9,9, 10,10, 11,11, -1},\
		{6,6,  7,7, 8,8,-1},\
		{0,0, 1,1, 2,2,-1},\
        {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,-1}};
	if (--delay < 1)
	{
		delay = 3;

		if (animaciones [estado] [paso + 1] == -1){
		    if(estado!=MURIENDO)
    			paso = 0;
    		else
    		   muerto=1;
		}else
			paso ++;
	}


	if(estado!=PARADO)
	   cuadro = animaciones [estado][paso];
	else
	   cuadro = animaciones [estado_anterior][0];

}

void Player::cambiarEstado(EstadoSprite nuevo)
{
    estado_anterior=estado;
	estado = nuevo;
	paso = 0;
	delay = 3;
}

void Player::setProteccion(int segundos){
    duracionProteccion=segundos;
    tiempoInicioProteccion=juego->getTick();
    estaProtegido=true;
}
void Player::mover_ip(int incremento_x, int incremento_y)
{//mueve al personaje detectando alguna colision
    int temp,num_colision=0;

    rect.x+=incremento_x;
    rect.y+=incremento_y;
    temp=juego->colision(BOMBA,rect);

    if(temp!=-1&&temp!=idUltimaBomba&&!puedeAtravesarBombas){ /*si esta sobre una bomba que no es la que el puso*/
        return;
     }else if(temp==-1&&idUltimaBomba!=-1){
        idUltimaBomba=-1;
    }    

    
    if(rect.x<juego->getEjeXVisual()||\
       rect.x+rect.w>juego->getEjeXVisual()+juego->getAnchoMapa()||\
       rect.y<juego->getEjeYVisual()||\
       rect.y+rect.h>juego->getEjeYVisual()+juego->getAltoMapa())return;

    if(!puedeAtravesarBloquesBlandos)
        temp=juego->colision(rect,&num_colision,false);
    else
        temp=juego->colision(rect,&num_colision,true);
    
    if(temp){
        if(num_colision==1){//ESTO ES PARA DESPLAZAR EL PERSONAJE UN POCO
            if(estado==IZQUIERDA||estado==DERECHA){
                if(temp==1||temp==2)
                    y-=1;
                else
                    y+=1;
            }else{
                if(temp==1||temp==4)
                    x-=1;
                else
                    x+=1;
            }
        }
    }else{
        move(x+incremento_x,y+incremento_y);
    }

}
void Player::move(int x,int y){
    //establece al jugador en la posicion indicada

    this->x=x;
    this->y=y;
    if(x>W_SCREEN/3*2&&estado==DERECHA){
        if(juego->moveLeftEjeXVisual()){
            this->x=W_SCREEN/3*2;
        }
        
    }
    if(x<W_SCREEN/3&&estado==IZQUIERDA){
        if(juego->moveRightEjeXVisual()){
            this->x=W_SCREEN/3;
        }
    }
}

Player::~Player(){
    #ifdef DEBUG
    cout << "Destructor de Player:"<<this<<endl;
    #endif
}
