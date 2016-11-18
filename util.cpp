#include "util.hpp"

template <typename T> bool dato_en_array(T dato,T array[],int N){
    int i;
    
     for(i=0;i<N;i++)
        if(array[i]==dato)
           return true;
           
     return false;
     
}

void sort_array(int array_sort[5],int destino_sort[5]){
     int i,index,mayores[5];

     for(i=0;i<5;i++){
        destino_sort[i]=-1000;
        mayores[i]=-1000;
     }
        
     
     for(index=0;index<5;index++){
       for(i=0;i<5;i++){
             if(array_sort[i]>mayores[index]&&!dato_en_array(i,destino_sort,5)){
                destino_sort[index]=i;
                mayores[index]=array_sort[i];
             }
       }
    }
}

SDL_Surface *cargar_imagen(char ruta[],bool keyclave){
	SDL_Surface * imagen;

	imagen = IMG_Load (ruta);

	if (!imagen){
		cout<< "No se puede cargar:"<< ruta<<endl;
		exit(1);
	}
    
    if(keyclave){	
	   SDL_SetColorKey (imagen, SDL_SRCCOLORKEY, \
				SDL_MapRGB (imagen->format, 0, 255, 0));
	}
	
    cout<< "+ cargando:"<< ruta<<endl;
    return imagen;
}

void mostrar_error(char msg[]){
    cerr << "Error:"<<msg<<"Error SDL:"<<SDL_GetError()<<endl;
    exit(1);
}

Mix_Chunk * cargar_sonido(char ruta[]){
    Mix_Chunk * cargado;
    cargado=Mix_LoadWAV(ruta);
    if(cargado==NULL){
        cerr<<"Error cargando sonido:"<<ruta<<Mix_GetError()<<endl;
        exit(1);
    }
	cout << "+ cargando:"<<ruta<<endl;
	return cargado;
}
Mix_Music * cargar_musica(const char ruta[]){
    Mix_Music * cargado;
    cargado=Mix_LoadMUS(ruta);
    if(cargado==NULL){
        cerr<<"Error cargando musica:"<<ruta<<Mix_GetError()<<endl;
        exit(1);
    }
	cout << "+ cargando:"<<ruta<<endl;
	return cargado;
}
bool rects_colisionan(SDL_Rect & rect_1,SDL_Rect & rect_2)
{
    
    return (((rect_1.x+rect_1.w)>rect_2.x) && \
    ((rect_1.y+rect_1.h)>rect_2.y) &&\
    ((rect_2.x+rect_2.w)>rect_1.x) && \
    ((rect_2.y+rect_2.h)>rect_1.y)) ;
}


void imprimir_desde_grilla(SDL_Surface * src, int cuadro, SDL_Surface *dst,int x_dest,int y_dest, int fil, int col,int alpha)
{
	SDL_Rect srcrect,dest_rect={x_dest,y_dest,0,0};

	srcrect.w = src->w / col;
	srcrect.h = src->h / fil;
	srcrect.x = (cuadro % col) * srcrect.w;
	srcrect.y = (cuadro / col) * srcrect.h;

	if(alpha)
    	SDL_SetAlpha(src, SDL_SRCALPHA|SDL_RLEACCEL,150);
    else
    	SDL_SetAlpha(src, SDL_SRCALPHA|SDL_RLEACCEL, 255);

	SDL_BlitSurface(src, &srcrect, dst, &dest_rect);
}


int fps_sincronizar (void)
{
	static int t;
	static int tl = 0;
	static int frecuencia = 1000 / 70;
	static int tmp;

	t = SDL_GetTicks ();

	if (t - tl >= frecuencia)
	{
		tmp = (t - tl) / frecuencia;
		tl += tmp * frecuencia;
		return tmp;
	}
	else
	{
		SDL_Delay (frecuencia - (t - tl));
		tl += frecuencia;
		return 1;
	}

}


/*
 * Relaciona un caracter con un n�mero entero
 */
int obtener_indice (char caracter,char * orden_letras)
{
	int i;
				
	for (i = 0; orden_letras [i]; i ++)
	{
		if (caracter == orden_letras [i])
			return i;
	}
	
	return -1;
}


/*
 * imprime un caracter sobre la superficie dst (generalmente screen)
 */
int imprimir_letra (SDL_Surface * dst, SDL_Surface * ima,int x, int y, char letra,char * orden_letras)
{
	SDL_Rect srcrect;
	SDL_Rect dstrect = {x, y, 0, 0};
	
	int cantidad_de_letras=strlen(orden_letras);
	
	srcrect.w=ima->w/cantidad_de_letras;
	srcrect.x=srcrect.w*obtener_indice(letra,orden_letras);
	srcrect.y=0;
	srcrect.h=ima->h;
	if(srcrect.x>=0)
    	SDL_BlitSurface(ima, &srcrect, dst, &dstrect);
	
	return ima->w/cantidad_de_letras;
}


/*
 * imprime una cadena de textos completa sobre la superficie referenciada
 * por el primer par�metro
 */
void imprimir_palabra (SDL_Surface * screen, SDL_Surface * ima, int x, int y,const char * cadena,char * orden_letras)
{
	int i;
	int dx = x;

	for (i = 0; cadena [i]; i ++)
		dx += imprimir_letra (screen, ima, dx, y, cadena [i],orden_letras);
}
void mostrar_msg (SDL_Surface * screen, SDL_Surface * ima, int x,int y,const char * orden_letras, char * formato, ...)
{
    va_list lista;
    char buffer [1024];
    va_start (lista, formato);
        vsprintf (buffer, formato, lista);
        imprimir_palabra (screen, ima, x, y,orden_letras, buffer);
    va_end (lista);
}

Uint32 get_pixel (SDL_Surface * ima, int x, int y)
{
	int bpp = ima->format->BytesPerPixel;
	Uint8 *p = (Uint8 *) ima->pixels + y * ima->pitch + x * bpp;

	switch (bpp)
	{
		case 1:
			return *p;
		
		case 2:
			return *(Uint16 *)p;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;
	}
}


int buscar_dato(string ruta,string nombre_dato){
    static FILE *fscript;
    
    int valor;
    char linea[100],*identificador;
    
    if(!(fscript=fopen(ruta,"r"))){
      sprintf(linea,"Error leyendo archivo(Buscar Dato):%s\n",ruta);
      mostrar_error(linea);
    }

    while(!feof(fscript)){    
        fgets(linea,100,fscript);
        
        identificador = strtok(linea , ":") ;
        if(!strcmp(identificador,nombre_dato.c_str())){
            sscanf(strtok( NULL , " "),"%d",&valor);
            fclose(fscript);
            return valor;
        }
    }
    fclose(fscript);
    return -1;
}

bool estado_tecla_joy(SDL_Keycode tecla,SDL_Joystick * joy){
	switch(tecla){
		case SDLK_LEFT:
				return SDL_JoystickGetAxis(joy, 0) < -10;
			break;
		case SDLK_RIGHT:
				return SDL_JoystickGetAxis(joy, 0) > 10;
			break;
		case SDLK_UP:
				return SDL_JoystickGetAxis(joy, 1) <-10;
			break;
		case SDLK_DOWN:
				return SDL_JoystickGetAxis(joy, 1) > 10;
			break;
		default:
			return SDL_JoystickGetButton(joy, tecla);
	}
}
void dibujar_objeto(SDL_Surface *src,Sint16 x,Sint16 y,SDL_Surface *dst){

    if(src==NULL||dst==NULL){
       cerr<<"WARNING:intento de dibujado en funcion:dibujar_objeto sobre o con valor NULL"<<endl;

       return;
    }

    SDL_Rect dest={x,y,src->w,src->h};
    SDL_BlitSurface(src,NULL,dst,&dest);

}



EstadoSprite invertir_estado(EstadoSprite estado){
    switch(estado){
        case DERECHA:
            return IZQUIERDA;
        case IZQUIERDA:
            return DERECHA;
        case ARRIBA:
            return ABAJO;
        case ABAJO:
            return ARRIBA;
        default:
            printf("no implementado para ese estado:%d\n",estado);
            return ABAJO;
        }
}

void sdl_videoinfo(void)
{

    const SDL_VideoInfo *propiedades;
    SDL_Surface *pantalla;
    SDL_Rect **modos;

    //Variables auxiliares
    char driver[20];
    int maxlen = 20;
    int i = 0;

    // Obtenemos la información del sistema de video
    propiedades = SDL_GetVideoInfo();
    if(propiedades == NULL) {
	 fprintf(stderr, "No se pudo obtener la información %s\n",
		  SDL_GetError());
	 exit(1);
    }

    // Obtenemos los modos de video disponibles
    modos = SDL_ListModes(NULL, SDL_HWSURFACE);

    printf("\n\n == MODOS DE VIDEO DISPONIBLES == \n");

    // Comprobamos que métodos están disponibles
    if(modos == (SDL_Rect **)0)
	 printf("No existen modos disponibles \n");
    else if(modos == (SDL_Rect **)-1)
	 printf("Todos los modos disponibles \n");
    else {
	 printf("Lista de modos disponibles\n");
	 for(i = 0; modos[i]; i++)
	     printf("%d x %d\n", modos[i]->w, modos[i]->h);
    }

    // Comprobamos que el modo a seleccionar sea compatible
    if(SDL_VideoModeOK(640, 480, 24, SDL_SWSURFACE) == 0) {
	 fprintf(stderr, "Modo no soportado: %s\n", SDL_GetError());
	 exit(1);
    }

 
    // Una vez comprobado establecemos el modo de video
    pantalla = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
    if(pantalla == NULL)
	 printf("SDL_SWSURFACE 640x480x24 no compatible. Error: %s\n",
		 SDL_GetError());


    // Obtenemos información del driver de video
    printf("\n\n == INFORMACIÓN DRIVER VIDEO == \n");
    SDL_VideoDriverName(driver, maxlen);

    if(driver == NULL) {
	 fprintf(stderr, "No se puede obtener nombre driver video\n");
	 exit(1);
    }

    printf("Driver: %s\n", driver);

    
    // Obtenemos información sobre las capacidades de nuestro
    // sistema respecto a SDL
    printf("\n == INFORMACION SDL_INFO == \n\n");
    if(propiedades->hw_available == 1)
	 printf("HW Compatible\n");
    else
	 printf("HW no compatible\n");

    if(propiedades->wm_available == 1)
	 printf("Hay un manejador de ventanas disponible\n");
    else
	 printf("No hay un manejador de ventanas disponible\n");

    if(propiedades->blit_hw == 1)
	 printf("El blitting hardware - hardware está acelerado\n");
    else
	 printf("El blitting hardware - hardware NO está acelerado\n");

    if(propiedades->blit_hw_CC == 1) {
	 printf("El blitting con transparencias hardware - hardware ");
	 printf("está acelerado\n");
    }
    else {
	 printf("El blitting con transparencias hardware - hardware ");
	 printf("NO está acelerado\n");
    }

    if(propiedades->blit_sw == 1)
	 printf("El blitting software - hardware está acelerado.\n");
    else
	 printf("El blitting software - hardware NO está acelerado. \n");
    
    if(propiedades->blit_sw_CC == 1) {
	 printf("El blitting software - hardware con transparencias");
	 printf(" está acelerado\n");
    }
    else {
	 printf("El blitting software - hardware con transparencias");
	 printf(" NO está acelerado\n");
    }

    if(propiedades->blit_sw_A == 1)
	 printf("El blitting software - hardware con alpha está acelerado\n");
    else
	 printf("El blitting software - hardware con alpha NO está acelerado\n");

    if(propiedades->blit_fill == 1)
	 printf("El rellenado de color está acelerado\n");
    else
	 printf("El rellenado de color NO está acelerado\n");

    printf("La memoria de video tiene %f MB\n", (float) propiedades->video_mem);
				
}


