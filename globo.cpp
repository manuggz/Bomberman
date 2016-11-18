/*#include "globo.h"
#include "objetos.h"
#include "nivel.h"
#include "player.h"
#include "engine/util.h"

Globo * globo_crear(){
    Globo * globo;
    globo=(Globo *)malloc(sizeof(Globo));
    if(globo==NULL)mostrar_error("Error asignando memoria a un globo");
    return globo;
}

void globo_iniciar(Globo * globo,Personajes *personajes,int id){
    globo->personajes=personajes;
    globo->en_pantalla=0;
	globo->rect_coli.w=13;//rectangulo que representa a nuestro personaje
	globo->rect_coli.h=10;//rectangulo que representa a nuestro personaje
    globo->id=id;
    globo->protegido=0;
}

void globo_activar(Globo * globo,int x, int y){
    static int estados_rand[4]={DERECHA,IZQUIERDA,ABAJO,ARRIBA};

    globo->delay_mover=0;
    globo->delay_para_morir=0;
    globo->paso=0;
    globo->delay_quitar_proteccion=0;
    globo->cuadro=0;
    globo->delay=0;
//    globo->vidas=1;
    globo->incremento_x=0;
    globo->incremento_y=0;
    globo->en_pantalla=1;
	globo->muerto=0;
    globo_set_coor(globo,x,y);
    globo_cambiar_estado(globo,estados_rand[rand()%4]);
 }
void globo_actualizar (Globo * globo)
{
    static const int estados_rand[4]={DERECHA,IZQUIERDA,ABAJO,ARRIBA};
    int colision_explo;

	globo_avanzar_animacion (globo);//avanzamos la animacion

    if(globo->estado!=MURIENDO){
        globo_actualizar_rect_colision(globo);

        if(!globo_mover (globo))
            globo_cambiar_estado(globo,estados_rand[rand()%4]);

        if(!globo->protegido){
            colision_explo=objetos_colision_con_explosiones(globo->personajes->juego->objetos,&globo->rect_coli,-1);
            if(colision_explo){
                globo_cambiar_estado (globo, MURIENDO);
                player_aumentar_puntaje(globo->personajes->players[globo->personajes->juego->objetos->explosiones[colision_explo-1]->lanzador],50);
            }
        }
        else if(++globo->delay_quitar_proteccion>DELAY_PROTECCCION){
            globo->protegido=0;
            globo->delay_quitar_proteccion=0;
        }

        }else if(globo->estado==MURIENDO&&globo->delay_para_morir++>100){
            globo_desactivar(globo);
            globo->delay_para_morir=0;
        }


}

int globo_colision(Globo * globo,SDL_Rect * rect_coli){
    globo_actualizar_rect_colision(globo);
    return rects_colisionan(&globo->rect_coli,rect_coli);
}

int globo_colision_con_otros(Globo * globo){
    register int i;
        /*este codigo se debe modificar si pongo un enemigo que no sea el "GLOBO" o sino no detectara la colision con el*/

	   /* for(i=0;i<globo->personajes->globos_actuales;i++){
            //basicamente lo que hace esto es comprobar colision con los globos de los alrededores
	       if((globo->personajes->globos[i]->en_pantalla)&&(i!=globo->id)){
                if(globo->personajes->globos[i]->estado!=MURIENDO&&globo_colision(globo->personajes->globos[i],&globo->rect_coli)){
                        return i+1;

                }//fin if colision con globo

            }//fin if globo activo
        }//fin for
    return 0;
}

int globo_mover (Globo * globo){
    int null=0; variable nula cuya unica funcion es pasarla como parametro a "niveles_colisiona" para no generar un error logico
    /*Estados estado_globo_colision;
    static const int estados_rand[4]={DERECHA,IZQUIERDA,ABAJO,ARRIBA};

    if(++globo->delay_mover>3){//para que el enemigo no se mueva a la misma velocidad que el personaje principal
        globo->delay_mover=0;
        globo->rect_coli.x+=globo->incremento_x;
        globo->rect_coli.y+=globo->incremento_y;


        if(nivel_colisiona(globo->personajes->juego->nivel,&globo->rect_coli,&null))
            return 0;

        null=globo_colision_con_otros(globo);
        if(null){
            estado_globo_colision=globo->personajes->globos[null-1]->estado;
            do
                globo_cambiar_estado(globo,estados_rand[rand()%4]);
            while(globo->estado==invertir_estado(estado_globo_colision));
        }

        if(objetos_colision_con_bombas(globo->personajes->juego->objetos,&globo->rect_coli))
            return 0;
        globo->x+=globo->incremento_x;
        globo->y+=globo->incremento_y;
    }
    return 1;

}

void globo_imprimir(Globo * globo,SDL_Surface * screen){
    	imprimir_desde_grilla (globo->personajes->juego->mundo->galeria->grilla_globo,globo->cuadro, screen, globo->x,globo->y,1, 6,globo->estado==MURIENDO||globo->protegido);


}

void globo_desactivar(Globo * globo){
    globo->en_pantalla=0;
	globo->muerto=1;
}

void globo_actualizar_rect_colision(Globo * globo){
    globo->rect_coli.x=globo->x+2;
    globo->rect_coli.y=globo->y+2;
}


void globo_avanzar_animacion (Globo * globo)
{
	static int animacion [7] = {0,1,2,3,4,5,-1};
	if (++globo->delay > 15){
		globo->delay = 0;
		if(animacion  [++globo->paso] == -1)
    		globo->paso = 0;
	}
	globo->cuadro = animacion[globo->paso];

}

void globo_cambiar_estado (Globo * globo, Estados nuevo){
	globo->estado = nuevo;
	switch(globo->estado){
        case DERECHA:
            globo->incremento_x=1;
            globo->incremento_y=0;
            break;
        case IZQUIERDA:
            globo->incremento_x=-1;
            globo->incremento_y=0;
            break;
        case ARRIBA:
            globo->incremento_x=0;
            globo->incremento_y=-1;
            break;
        case ABAJO:
            globo->incremento_x=0;
            globo->incremento_y=1;
            break;
        case MURIENDO:break;
        default:
            printf("error en estados del globo\n");
        }

}


void globo_set_coor(Globo * globo, int x, int y){
    globo->x=x;
    globo->y=y;
}*/
