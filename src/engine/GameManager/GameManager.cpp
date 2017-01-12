#include "GameManager.hpp"

/**
 * Inicia el juego
 *  Establece los controles iniciales
 *  Incia el modo de video
 *  Carga los sonidos
 * @return
 */
GameManager::GameManager(std::string caption,std::string ruta_icono, unsigned int width,unsigned int height,bool pantallaCompleta){

    srand((unsigned int) time(0));

    mCaption   = caption;
    mRutaIcono = ruta_icono;

    mWidth  = width;
    mHeight = height;

    nativeSize.x = 0;
    nativeSize.y = 0;
    nativeSize.w = width;
    nativeSize.h = height;

    newWindowSize.x = 0;
    newWindowSize.y = 0;
    newWindowSize.w = nativeSize.w;
    newWindowSize.h = nativeSize.h;

    scaleRatioW = 1.0f;
    scaleRatioH = 1.0f;

    mpTextureBufferTarget = nullptr;

    resize = false;

    mIsPantallaCompleta = pantallaCompleta;
    iniciarLibreriaSDL();

    establecerModoDeVideo(pantallaCompleta);

    /* Notar que solo se activan al inicio, si un joystick se conecta a la PC después, éste no se reconocerá*/
    activarJoysticks();
}



/**
 * Inicia la libreria SDL
 *  Inicia el Subsistema de Audio,Video y Joistick
 *  Inicia la libreria Mixer
 */
void GameManager::iniciarLibreriaSDL(){

   if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0){
       std::cerr << "[ERROR] No se pudo inciar SDL" << SDL_GetError() <<std::endl;
       exit(EXIT_FAILURE);
   }
    //Set the scaling quality to nearest-pixel
    if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") < 0){
        std::cerr << "Failed to set Render Scale Quality" << std::endl;
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0) {
        std::cerr << "[WARNING]%s" << SDL_GetError();
    }else{
        mIniciadoModuloSonido = true;
        Mix_AllocateChannels(mChannels + 1);
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        std::cerr << "[ERROR] SDL_ttf could not initialize!" << SDL_GetError();
        exit(EXIT_FAILURE);
    }

}

/**
 * Establece el modo de video en el juego
 * @param pantalla_completa Dice si se quiere que se ocupe toda la pantalla
 */
void GameManager::establecerModoDeVideo(bool pantalla_completa){
    Uint32 banderas = SDL_WINDOW_INPUT_FOCUS|SDL_WINDOW_MOUSE_CAPTURE;

    if(pantalla_completa) banderas|= SDL_WINDOW_FULLSCREEN;

    mMainWindow = SDL_CreateWindow(
            (mCaption.empty()? "Game":mCaption.c_str()),                  // window title
            SDL_WINDOWPOS_CENTERED,           // initial x position
            SDL_WINDOWPOS_CENTERED,           // initial y position
            mWidth,                               // mWidth, in pixels
            mHeight,                               // height, in pixels
            banderas                  // flags - see below
    );

    int w, h;
    SDL_GetWindowSize(mMainWindow, &w, &h);

    //newWindowSize.w = w;
    //newWindowSize.h = h;

    //scaleRatioW = w / nativeSize.w;
    //scaleRatioH = h / nativeSize.h;  //The ratio from the native size to the new size

    std::cout << "Window < Width : " << w << " , height: " << h << ">" << std::endl;

    if(mMainWindow == nullptr){
        std::cerr << "[ERROR] No se pudo crear Frame-buffer" << SDL_GetError();
        exit(EXIT_FAILURE);
    }

    if(!mRutaIcono.empty()){
        SDL_Surface *icono;
        icono =SDL_LoadBMP(mRutaIcono.c_str());
        // Establecemos el icono
        SDL_SetWindowIcon(mMainWindow,icono);
        SDL_FreeSurface(icono);
    }

    gRenderer = SDL_CreateRenderer(mMainWindow, -1, SDL_RENDERER_ACCELERATED|
                                                    SDL_RENDERER_TARGETTEXTURE);
    if (gRenderer == nullptr){
        std::cerr << "[ERROR] SDL_CreateRenderer" << SDL_GetError();
        exit(EXIT_FAILURE);
    }
    //Similarly, you must use SDL_TEXTUREACCESS_TARGET when you create the texture
    mpTextureBufferTarget = SDL_CreateTexture(gRenderer,
                                   SDL_GetWindowPixelFormat(mMainWindow),
                                   SDL_TEXTUREACCESS_TARGET,
                                   nativeSize.w,
                                   nativeSize.h);

    //IMPORTANT Set the back buffer as the target
    SDL_SetRenderTarget(gRenderer, mpTextureBufferTarget);

    SDL_SetRenderDrawColor(gRenderer, 104, 104, 104, 255);
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
     for(int i=joys_act;i<mJoysticksActivos;i++)
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
void GameManager::cambiarInterfaz(InterfazGrafica *  nueva){
    std::cout << "GameManager::cambiarInterfaz"<<std::endl;
    if(nueva!=interfaz_actual){
        interfaces.push(nueva);
    }
}

/**
 * Procesa los eventos que ocurren en el sistema
 * @return Booleano indicando si se debe o no llamar a las funciones de la interfaz actual en el frame actual
 */
bool GameManager::procesarEventos(){
    SDL_Event evento;
    while(SDL_PollEvent(&evento)){
        switch(evento.type){
            case SDL_QUIT:
                salir_juego=true;
                return false;
            case SDL_KEYDOWN:

                if(!mISFullScreenPressed && evento.key.keysym.sym==SDLK_RETURN && evento.key.keysym.mod & SDLK_LSHIFT){
                    std::cout << "Toggle Fullscreen Mode" << std::endl;
                    if(mIsPantallaCompleta){
                        if(!SDL_SetWindowFullscreen(mMainWindow,0)){
                            mIsPantallaCompleta = false;
                        }else{
                            std::cerr << "[Error] No se pudo cambiar a modo windowed.";
                        }
                    }else{
                        if(!SDL_SetWindowFullscreen(mMainWindow,SDL_WINDOW_FULLSCREEN)){
                            mIsPantallaCompleta = true;
                        }else{
                            std::cerr << "[Error] No se pudo cambiar a pantalla completa.";
                        }
                    }
                    mISFullScreenPressed = true;
                    interfaz_actual->forceDraw();
                    return false;
                }
                if(evento.key.keysym.sym==SDLK_F4 && evento.key.keysym.mod & SDLK_LALT){
                    salir_juego=true;
                    return false;
                }

            break;
            case SDL_KEYUP:
                mISFullScreenPressed = false;
                break;
            case SDL_WINDOWEVENT:
                if(evento.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    resize = true;
                }
            default:break;
        }

        if(interfaz_actual && (!mpPopUp || !mpPopUp->isStarted()))
            interfaz_actual->procesarEvento(&evento);

        if(mpPopUp && mpPopUp->isStarted())
            mpPopUp->procesarEvento(&evento);
    }
    return true;//se puede continuar
}
void GameManager::Resize()
{
    int w, h;

    SDL_GetWindowSize(mMainWindow, &w, &h);

    scaleRatioW = w / nativeSize.w;
    scaleRatioH = h / nativeSize.h;  //The ratio from the native size to the new size

    newWindowSize.w = w;
    newWindowSize.h = h;

    //In order to do a resize, you must destroy the back buffer. Try without it, it doesn't work
    SDL_DestroyTexture(mpTextureBufferTarget);
    mpTextureBufferTarget = SDL_CreateTexture(gRenderer,
                                   SDL_GetWindowPixelFormat(mMainWindow),
                                   SDL_TEXTUREACCESS_TARGET, //Again, must be created using this
                                   nativeSize.w,
                                   nativeSize.h);

    SDL_Rect viewPort;
    SDL_RenderGetViewport(gRenderer, &viewPort);

    if(viewPort.w != newWindowSize.w || viewPort.h != newWindowSize.h)
    {
        //VERY IMPORTANT - Change the viewport over to the new size. It doesn't do this for you.
        SDL_RenderSetViewport(gRenderer, &newWindowSize);
    }

    if(interfaz_actual != nullptr){
        interfaz_actual->forceDraw();
    }
}

/**
 * Controla el bucle principal del juego
 */
void GameManager::run(){

    if(interfaces.empty()) return;

    //The frames per second timer
    //LTimer fpsTimer;

    //The frames per second cap timer
    LTimer capTimer;

    //Start counting frames per second
    //fpsTimer.start();

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
        SDL_SetRenderTarget(gRenderer, NULL); //Set the target back to the window

        if(resize) //If a resize is neccessary, do so.
        {
            this->Resize();
            resize = false;
        }

        SDL_RenderCopy(gRenderer, mpTextureBufferTarget, &nativeSize, &newWindowSize); //Render the backBuffer onto the
        //screen at (0,0)
        SDL_RenderPresent(gRenderer);
        //SDL_RenderClear(gRenderer); //Clear the window buffer

        SDL_SetRenderTarget(gRenderer, mpTextureBufferTarget); //Set the target back to the back buffer
        //SDL_RenderClear(gRenderer); //Clear the back buffer

        if(interfaces.empty()){
            quit();
        }

        int frameTicks = capTimer.getTicks();
        if( frameTicks < mScreenTicksPerFrame ){
            //Wait remaining time
            SDL_Delay((Uint32) (mScreenTicksPerFrame - frameTicks));
        }
    }

}


void GameManager::play(Mix_Chunk *pSfxChunk) {
    if(mIniciadoModuloSonido)Mix_PlayChannel(-1,pSfxChunk, 0);
}


void GameManager::playSound(Mix_Music * music,Uint8 volumen){
    /*Reproduce una musica de fondo*/
    //static int t_ini=0;
    //static int t_pas=0;

    if(mIniciadoModuloSonido){
        Mix_VolumeMusic(volumen);
        Mix_PlayMusic(music, -1);
    }
}

void GameManager::playFadeInSound(Mix_Music * music,Uint8 volumen){
    /*Reproduce una musica de fondo*/
    //static int t_ini=0;
    //static int t_pas=0;

    if(mIniciadoModuloSonido){
        Mix_VolumeMusic(volumen);
        Mix_FadeInMusic(music, -1,2000);
    }
}


GameManager::~GameManager(){
    std::cout << "GameManager::~GameManager()" << std::endl;

    SDL_DestroyRenderer(gRenderer);
    // Close and destroy the window
    SDL_DestroyWindow(mMainWindow);

    while(interfaces.size() > 0){
        delete interfaces.top();
        interfaces.pop();
    }


    //delete mpGaleria;

    for(int i=0;i<joys_act;i++){
        if(joysticks[i]) {
            SDL_JoystickClose(joysticks[i]);
        }
    }

    if(mIniciadoModuloSonido)
        Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}


int GameManager::getWidth() {
    return mWidth;
}

int GameManager::getHeight() {
    return mHeight;
}

void GameManager::goBack() {
    std::cout << "GameManager::popInterface"<< std::endl;
    interfaces.pop();
    interfaz_actual->stop();
    if(mpPopUp){
        mpPopUp->stop();
    }
}

void GameManager::setRoot(InterfazGrafica *nuevaInterfazRoot) {

    InterfazGrafica * interfazUI;

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

