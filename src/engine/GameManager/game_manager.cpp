#include <zconf.h>
#include <sys/param.h>
#include "game_manager.hpp"
#include "../util/LTimer.hpp"

/**
 * Inicia el juego
 *  Establece los controles iniciales
 *  Incia el modo de video
 *  Carga los sonidos
 * @return
 */
GameManager::GameManager(){
    srand((unsigned int) time(0));
    interfaz_actual   = nullptr;

    snd_disponible=false; // snd_disponible se actualiza en iniciarSDL()
    iniciarSDL();
    setModeVideo();

    /* Notar que solo se activan al inicio, si un joystick se conecta a la PC después, éste no se reconocerá*/
    activarJoysticks();

    salir_juego=false; // Nos dice cuando debemos cerrar el juego

    galeria=new Galeria(); // Almacenamiento de Imagenes/Sonidos en Memoria
    galeria->cargarTexturas(gRenderer);
    // snd_disponible se actualiza en GameManager::iniciarSDL()
    // Este indica si se logró activar el sonido
    if(snd_disponible)galeria->cargarSonidos();
}

/**
 * Inicia la libreria SDL
 *  Inicia el Subsistema de Audio,Video y Joistick
 *  Inicia la libreria Mixer
 */
void GameManager::iniciarSDL(){
    if(!SDL_WasInit(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)){ 
       if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0){
           mostrar_error_salir("No se pudo inciar SDL");
       }

        atexit(SDL_Quit); // Programamos que se cierre SDL al salir

        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0) {
            cerr << "[WARNING]%s" << SDL_GetError();
        }else{
            snd_disponible=true;
            Mix_AllocateChannels(_PLAYERS + 1);
        }

        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            mostrar_error_salir( "SDL_ttf could not initialize!");
        }

        
    }

}

/**
 * Establece el modo de video en el juego
 * @param pantalla_completa Dice si se quiere que se ocupe toda la pantalla
 */
void GameManager::setModeVideo(bool pantalla_completa){
    Uint32 banderas=SDL_WINDOW_INPUT_FOCUS|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_MOUSE_CAPTURE;

    if(pantalla_completa) banderas|= SDL_WINDOW_FULLSCREEN;

    screen = SDL_CreateWindow(
            "DestructionBombs v0.8",                  // window title
            SDL_WINDOWPOS_CENTERED,           // initial x position
            SDL_WINDOWPOS_CENTERED,           // initial y position
            W_SCREEN,                               // mWidth, in pixels
            H_SCREEN,                               // height, in pixels
            banderas                  // flags - see below
    );

    if(!screen){
        mostrar_error_salir("No se pudo crear Frame-buffer");
    }

    SDL_Surface *icono;
    icono =SDL_LoadBMP("data/imagenes/objetos/icono.bmp");
    // Establecemos el icono
    SDL_SetWindowIcon(screen,icono);
    SDL_FreeSurface(icono);

    gRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr){
        mostrar_error_salir("DL_CreateRenderer Error");
    }

    SDL_SetRenderDrawColor(gRenderer, 104, 104, 104, 255);
    mWidth = W_SCREEN;
    mHeight = H_SCREEN;
}

/**
 * Busca _PLAYERS numero de joisticks conectados al sistema, abre una conexion con ellos
 * y los guarda en un array para cada player
 */
void GameManager::activarJoysticks(){
     /*contamos y abrimos los Joysticks que usara nuestro juego, Maximos 5 que pueden ser distintos*/
    joys_act=SDL_NumJoysticks();
     joys_act=(joys_act>5)?5:joys_act;//esto es porque solo podemos manejar 5...mas seria un error en este programa
     for(int i=0;i<joys_act;i++){
          joysticks[i]=SDL_JoystickOpen(i);//abrimos el joystick
     }
     for(int i=joys_act;i<_PLAYERS;i++)
          joysticks[i]= nullptr;//los espacios que sobran los ponemos a NULL
}

/**
 * Obtiene el joistick en la posicion id
 * @param id posicion en el array
 * @return Puntero al SDL_Joystick en el array o NULL en caso que no exista
 */
SDL_Joystick * GameManager::getJoy(int id){
    return joysticks[id];
}

/**
 * Obtiene el número de joistick activos
 * @return
 */
int GameManager::getActiveJoys(){
    return joys_act;
}

/**
 * Cambia la interfaz presentada al usuario actualmente
 * @param nueva Nueva interfaz a mostrar
 */
void GameManager::cambiarInterfaz(InterfazUI *  nueva){
    cout << "GameManager::cambiarInterfaz"<<endl;
    if(nueva!=interfaz_actual){
        interfaces.push(nueva);
    }
}

/**
 * Procesa los eventos que ocurren en el sistema
 * @return Booleano indicando si se debe o no llamar a las funciones de la interfaz actual en el frame actual
 */
bool GameManager::procesarEventos(){
    static bool full=1;//pantalla completa
    SDL_Event evento;
    while(SDL_PollEvent(&evento)){
        switch(evento.type){
            case SDL_QUIT:
                salir_juego=true;
                return false;
            case SDL_KEYDOWN:
                if((evento.key.keysym.sym==SDLK_RETURN && evento.key.keysym.mod & SDLK_LSHIFT)||
                (evento.key.keysym.sym==SDLK_f && evento.key.keysym.mod & SDLK_LSHIFT)){
                    setModeVideo(full);
                    full=!full;
                    return false;
                }
                if(evento.key.keysym.sym==SDLK_F4 && evento.key.keysym.mod & SDLK_LALT){
                    salir_juego=true;
                    return false;
                }

            break;
            default:break;
        }

        if(interfaz_actual && (!mpPopUp || !mpPopUp->isStarted()))
            interfaz_actual->procesarEvento(&evento);

        if(mpPopUp && mpPopUp->isStarted())
            mpPopUp->procesarEvento(&evento);
    }
    return true;//se puede continuar
}


/**
 * Controla el bucle principal del juego
 */
void GameManager::run(){


    //The frames per second timer
    LTimer fpsTimer;

    //The frames per second cap timer
    LTimer capTimer;

    //Start counting frames per second
    fpsTimer.start();

    while(!salir_juego){

        //Start cap timer
        capTimer.start();

        if(mpPopUp&& mpPopUp->isStopped()){

            delete mpPopUp;
            mpPopUp = nullptr;

            if(interfaz_actual != nullptr){
                interfaz_actual->resultPopUp(mpResultPopUp, mIDCodePopUp);
                if(!interfaz_actual->isStopped())
                    interfaz_actual->resume();
            }


        }
        // Si el top de nuestra pila de interfazes es distinto de nuestra interfaz actual
        // significa que se ha hecho un cambio de interfaz o que se ha eliminado la actual
        if(interfaces.top() != interfaz_actual){
            // Si la interfaz actual es distinta de null es porque élla es la que ha llamado el cambio de interfaz
            // o se pudo llamar desde otro lado, tal como cuando se inicia el GameManager en un main.
            if(interfaz_actual != nullptr){
                // Si la actual está detenida significa que ésta ya no quiere seguir en el stack de interfaces
                // y por consiguiente se ha incluso eliminado de él
                if(interfaz_actual->isStopped()){
                    delete interfaz_actual; // Se elimina de memoria ya que no tendrá uso
                }else{
                    // Si la actual no esta detenida significa que ésta seguirá viva
                    // y que el usuario puede volver a élla una vez haya acabado de interactuar con la nueva actual
                    // para volver a ella puede presionar ESCAPE
                    interfaz_actual->pause(); // Linea 214
                }
            }
            // Si la interfaz actual es null es porque se está comenzando el juego

            // Se cambia el puntero a la interfaz actual por la nueva actual
            interfaz_actual = interfaces.top();

            // Si la interfaz actual en el top era una en el historial de interfaces
            // esta entonces estaba pausada(ver linea 214~ de este archivo, más arriba)
            if(interfaz_actual->isPaused()){
                // Se resume la interfaz
                interfaz_actual->resume();
            }else{ // Si no estaba pausada significa que es una completamente nueva
                interfaz_actual->prepare();
                interfaz_actual->createUI(gRenderer);
                interfaz_actual->start();
            }
        }

        // Si tenemos un pop up y no se ha iniciado
        if(mpPopUp != nullptr && !mpPopUp->isStarted()){
            // Pausamos la interfaz actual
            interfaz_actual->pause();
            mpPopUp->prepare();
            mpPopUp->createUI(gRenderer);
            mpPopUp->start();
        }

        if(procesarEventos()){ // Si se deben procesar los eventos en este frame

            if(!interfaz_actual->isStopped()) {

                if(mpPopUp && mpPopUp->isStarted()){
                    mpPopUp->update();
                    // A pesar que se esta mostrando un pop up, como esto es un juego
                    // no implica que el juego se debe detener, pueden haber animaciones en el juego ejecutandose
                    interfaz_actual->updateWhenPopUp();
                }else{ // Si n hay pop up entonces actualizamos la interfaz actual
                    interfaz_actual->update();
                }

                interfaz_actual->draw(gRenderer);
                if(mpPopUp && mpPopUp->isStarted()){
                    mpPopUp->draw(gRenderer);
                }
            }
        }

        SDL_RenderPresent(gRenderer); // Muestra la vista

        if(interfaces.empty()){
            quit();
        }
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME ){
            //Wait remaining time
            SDL_Delay((Uint32) (SCREEN_TICKS_PER_FRAME - frameTicks));
        }
    }

}

void GameManager::play(Galeria::CodeMusicEfecto code){
    /*Reproduce un Chunk*/
    if(snd_disponible)Mix_PlayChannel(-1,galeria->getMusicEfecto(code), 0);
}
void GameManager::playSound(Galeria::CodeMusicSonido code){
    /*Reproduce una musica de fondo*/
    static int t_ini=0;
    //static int t_pas=0;
    
    if(snd_disponible){
        if(SDL_GetTicks()-t_ini<1000){/*Si se reproduce este sonido seguidamente del anterior (1 s)*/
            cerr << "WARNING:Reproducci�n apresurada del sonido:"<<code<<endl;
        }
        Mix_PlayMusic(galeria->getMusicSonido(code), -1);
        t_ini=SDL_GetTicks();
    }
}

LTexture * GameManager::getTexture(Galeria::CodeImagen code){
    return galeria->getImagen(code);
}

GameManager::~GameManager(){

    SDL_DestroyRenderer(gRenderer);
    // Close and destroy the window
    SDL_DestroyWindow(screen);

    while(interfaces.size() > 0){
        delete interfaces.top();
        interfaces.pop();
    }


    delete galeria;

    for(int i=0;i<joys_act;i++){
        if(joysticks[i]) {
            SDL_JoystickClose(joysticks[i]);
        }
    }

    if(snd_disponible)
        Mix_CloseAudio();
    TTF_Quit();
}

int GameManager::getWidth() {
    return mWidth;
}

int GameManager::getHeight() {
    return mHeight;
}

void GameManager::goBack() {
    cout << "GameManager::popInterface"<<endl;
    interfaces.pop();
    interfaz_actual->stop();
    if(mpPopUp){
        mpPopUp->stop();
    }
}

void GameManager::setRoot(InterfazUI *nuevaInterfazRoot) {

    InterfazUI * interfazUI;

    while(interfaces.size() > 0){
        interfazUI = interfaces.top();
        interfazUI->stop();

        if(interfazUI != interfaz_actual){
            delete interfazUI;
        }
        interfaces.pop();
    }

    interfaces.push(nuevaInterfazRoot);

    if(mpPopUp){
        mpPopUp->stop();
    }
}

SDL_Rect GameManager::getRectScreen() {
    return {0,0,mWidth,mHeight};
}

void GameManager::closePopUp(void * result) {

    if(mpPopUp){
        if(!mpPopUp->isStopped())
            mpPopUp->stop();
    }
    mpResultPopUp = result;
}

void GameManager::showPopUp(PopUpInterfaz *pPopUp,int CodePopUp) {

    if(mpPopUp){
        if(!mpPopUp->isStopped())
            mpPopUp->stop();

        interfaz_actual->resultPopUp(nullptr,mIDCodePopUp);
        delete mpPopUp;
    }

    mpPopUp      = pPopUp;
    mIDCodePopUp = CodePopUp;
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