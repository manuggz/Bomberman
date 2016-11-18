#include "game_manager.hpp"

GameManager::GameManager(){
     /*inicializa la clase GameManager y la libreria*/
     srand(time(0));
     inter=NULL;
     interfaz_last=NULL;

     iniSDL();
     setModeVideo();
     
     activarJoysticks();/*solo se activan al inicio, si un joystick se conecta a la PC despues de haber corrido esta

     salir=false;
     /*creamos las clases en memoria*/
     galeria=new Galeria();
     if(snd_disponible)galeria->cargarSonidos();
     salir=false;

	// Initialize Frame Rate Manager
	//SDL_initFramerate(&fpsm);
	//SDL_setFramerate(&fpsm, 60); // 60 Frames Per Second
    //SDL_WM_SetCaption("DestructionBombs",NULL);
//    sdl_videoinfo();
}
void GameManager::iniSDL(){
    if(!SDL_WasInit(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)){ 
       if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0){
           mostrar_error("No se pudo inciar SDL");
       }

        atexit(SDL_Quit);

        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0) {
            cerr << "[WARNING]%s" << SDL_GetError();
            snd_disponible=false;
        }else{
            snd_disponible=true;
            Mix_AllocateChannels(_PLAYERS + 1);
        }
        
    }

}

void GameManager::setModeVideo(bool pantalla_completa){
    Uint32 banderas=0;

    if(pantalla_completa)
        banderas|=SDL_WINDOW_FULLSCREEN;

    /*SDL_Surface *icono;
    icono =SDL_LoadBMP("data/imagenes/objetos/icono.bmp");
     // Establecemos el icono
    SDL_WM_SetIcon(icono, NULL); // Compatible con  Windows
    SDL_FreeSurface(icono);
    */
    screen = SDL_CreateWindow(
            "DestructionBombs",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            W_SCREEN,                               // width, in pixels
            H_SCREEN,                               // height, in pixels
            banderas                  // flags - see below
    );

    if(!screen){
        mostrar_error("No se pudo crear Frame-buffer");
    }

    ren = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        mostrar_error("DL_CreateRenderer Error");
    }

    SDL_SetRenderDrawColor(ren, 104, 104, 104, 255);
    SDL_RenderClear(ren);
}

void GameManager::activarJoysticks(){
     /*contamos y abrimos los Joysticks que usara nuestro juego, Maximos 5 que pueden ser distintos*/
    joys_act=SDL_NumJoysticks();
     joys_act=(joys_act>5)?5:joys_act;//esto es porque solo podemos manejar 5...mas seria un error en este programa
     for(int i=0;i<joys_act;i++){
          joysticks[i]=SDL_JoystickOpen(i);//abrimos el joystick
     }
     for(int i=joys_act;i<_PLAYERS;i++)
          joysticks[i]=NULL;//los espacios que sobran los ponemos a NULL
}


SDL_Joystick * GameManager::getJoy(int id){
    return joysticks[id];
}
int GameManager::getJoysActivos(){
    return joys_act;
}

void GameManager::cambiarInterfaz(Interfaz *  nueva){
     /*cambia la interfaz del juego*/
    #ifdef DEBUG
        cout << "Cambiando interfaz a "<<nueva<<endl;
    #endif
//    cout << "1"<<endl;
    if(interfaz_last&&nueva!=interfaz_last){        
        #ifdef DEBUG
            cout << "Eliminando interfaz:"<<interfaz_last<<endl;
        #endif
        delete interfaz_last; //Para evitar una mala accion
        interfaz_last=NULL;
    }
//    cout << "Interfaz(ante la asignaci�n):"<<inter<<" Nueva:"<<nueva<<endl;
    interfaz_last=inter;
//    cout << "1"<<endl;
    inter=nueva;
    nueva->crearTexturas(ren);
    #ifdef DEBUG
        cout << "Interfaz:"<<inter<<endl;
        cout << "Interfaz anterior:"<<interfaz_last<<endl;
    #endif
}

int GameManager::procesarEventos(){
    static bool full=1;//pantalla completa
    SDL_Event evento;
    while(SDL_PollEvent(&evento)){
        switch(evento.type){
            case SDL_QUIT:
                salir=1;
                return 0;
            break;
            case SDL_KEYDOWN:
                if((evento.key.keysym.sym==SDLK_RETURN && evento.key.keysym.mod & SDLK_LALT)||
                (evento.key.keysym.sym==SDLK_f && evento.key.keysym.mod & SDLK_LALT)){
                    setModeVideo(full);
                    full=!full;
                    return 0;
                }
                if(evento.key.keysym.sym==SDLK_F4 && evento.key.keysym.mod & SDLK_LALT){
                    salir=1;
                    return 0;
                }

            break;
        }
        
        inter->procesarEvento(&evento);
    }
    return 1;//se puede continuar
}


void GameManager::run(){
    if(!inter)return;
    while(!salir){
        if(procesarEventos()){
            inter->update();
            inter->draw(ren);
        }
        SDL_RenderPresent(ren);
        //SDL_framerateDelay(&fpsm);
        SDL_Delay(60);
    }

}

void GameManager::play(CodeMusicEfecto code){
    /*Reproduce un Chunk*/
    if(snd_disponible)Mix_PlayChannel(-1,galeria->getMusicEfecto(code), 0);
}
void GameManager::playSonido(CodeMusicSonido code){
    /*Reproduce una musica de fondo*/
    static int t_ini=0;
    static int t_pas=0;
    
    if(snd_disponible){
        if(SDL_GetTicks()-t_ini<1000){/*Si se reproduce este sonido seguidamente del anterior (1 s)*/
            cerr << "WARNING:Reproducci�n apresurada del sonido:"<<code<<endl;
        }
        Mix_PlayMusic(galeria->getMusicSonido(code), -1);
        t_ini=SDL_GetTicks();
    }
}

SDL_Surface * GameManager::getImagen(CodeImagen code){
    return galeria->getImagen(code);
}

GameManager::~GameManager(){
    #ifdef DEBUG
        cout << "Destructor de GameManager:"<<this<<endl;
    #endif

    // Close and destroy the window
    SDL_DestroyWindow(window);

    delete inter;
    delete interfaz_last;
    delete galeria;

    for(int i=0;i<joys_act;i++)
        if(joysticks[i]&&SDL_JoystickOpened(i))
            SDL_JoystickClose(joysticks[i]);
            
    if(snd_disponible)
        Mix_CloseAudio();
    cout <<"Fin del juego... visita:http://baulprogramas.blogspot.com/\n";
}

/*
void GameManager::cargarDatos(){  
    ifstream fs(RUTA_CONFIG);
    if(!fs){
        cerr << "Error abriendo:--"<<RUTA_CONFIG<<endl;
        maxTerrenosBatalla=0;
        puntaje_mayor=0;
    }
    fs >>maxTerrenosBatalla;
    fs >>puntaje_mayor;
    fs.close();
}



void GameManager::guardarDatos(){
    ofstream fs(RUTA_CONFIG);
    fs <<maxTerrenosBatalla << endl;
    fs <<puntaje_mayor<<endl;
    fs.close();
}

int GameManager::getMaxTerrenoBatalla(){
    return maxTerrenosBatalla;
}
*/


/*SDL_Surface GameManager::getPreviewTerreno(int id,int id_tile){
     return Nivel::getPreviewTerreno(id,id_tile,galeria);
}

void GameManager::cargarFileNivel(char * buffer,char ruta[]){
     Nivel::cargarFileNivel(buffer,ruta);
}

void GameManager::dibujarNivel(char * mapa,int id_tile,SDL_Surface * super){
     Nivel::draw(mapa,galeria->tiles[id_tile],super);
*/
