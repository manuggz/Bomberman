#include "control_player.hpp"

using namespace std;

ControlPlayer::ControlPlayer(){
    reset();
};

void ControlPlayer::reset() {
    for(int i=0;i<_TECLAS;i++){

        es_boton_joystick[i]     = false;
        es_direccion_joystick[i] = false;

        keyboardMapping[i]= SDLK_UNKNOWN;
        joybuttonMapping[i] = 0;
        strcpy(guidJoystick[i],"sin asig.");
    }

}

bool ControlPlayer::cargar(char ruta[]){
    ifstream fs2(ruta,ios::in|ios::binary);
    if(!fs2){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Error leyendo control en: %s",ruta);
        reset();
        return false;
    }else{
        fs2.read(reinterpret_cast<char *> (this),sizeof(ControlPlayer));
        fs2.close();
    }
    return true;
};

void ControlPlayer::guardar(char ruta[]){
    ofstream fs2(ruta,ios::out|ios::binary);    
    fs2.write(reinterpret_cast<char *> (this),sizeof(ControlPlayer));
    fs2.close();
};

char * ControlPlayer::getJoystickGUID(TeclaPlayer tecla){
    return guidJoystick[tecla];
};
bool ControlPlayer::isBotonJoystick(TeclaPlayer tecla){
    return es_boton_joystick[tecla];
};
bool ControlPlayer::isDireccionJoystick(int tecla){
    return es_direccion_joystick[tecla];
};
SDL_Keycode ControlPlayer::getKey(TeclaPlayer tecla){
    return keyboardMapping[tecla];
};

void ControlPlayer::setJoystickGUID(TeclaPlayer tecla, const char *name){
    strcpy(guidJoystick[tecla],name);
};
void ControlPlayer::setIsBotonJoystick(TeclaPlayer tecla,bool nuevo){
    es_boton_joystick[tecla]=nuevo;
};
void ControlPlayer::setIsDireccionJoystick(int tecla,bool nuevo){
    es_direccion_joystick[tecla]=nuevo;
};
void ControlPlayer::setKeyboardMapping(TeclaPlayer tecla, SDL_Keycode nuevo){
    keyboardMapping[tecla]=nuevo;
};

void ControlPlayer::setDefaultKeys(IdPlayer id){
    /*if(id==PLAYER_1){
    	keys_players[TECLA_IZQUIERDA] = SDL_SCANCODE_A;
    	keys_players[TECLA_DERECHA] = SDL_SCANCODE_D;
    	keys_players[TECLA_ARRIBA] = SDL_SCANCODE_W;
    	keys_players[TECLA_ABAJO] = SDL_SCANCODE_S;
        keys_players[TECLA_ACCION]=SDL_SCANCODE_E;
        keys_players[TECLA_START]=SDL_SCANCODE_Q;
//        keys_players[TECLA_ACCION_2]=SDLK_1;
    }else if(id==PLAYER_2){
    	keys_players[TECLA_IZQUIERDA] = SDL_SCANCODE_LEFT;
    	keys_players[TECLA_DERECHA] = SDL_SCANCODE_RIGHT;
    	keys_players[TECLA_ARRIBA] = SDL_SCANCODE_UP;
    	keys_players[TECLA_ABAJO] = SDL_SCANCODE_DOWN;
        keys_players[TECLA_ACCION]=SDL_SCANCODE_KP_ENTER;
        keys_players[TECLA_START]=SDL_SCANCODE_P;
//        keys_players[TECLA_ACCION_2]=SDLK_KP1; 
    }else if(id==PLAYER_3){
    	keys_players[TECLA_IZQUIERDA] = SDL_SCANCODE_F;
    	keys_players[TECLA_DERECHA] = SDL_SCANCODE_H;
    	keys_players[TECLA_ARRIBA] = SDL_SCANCODE_T;
    	keys_players[TECLA_ABAJO] = SDL_SCANCODE_G;
        keys_players[TECLA_ACCION]=SDL_SCANCODE_R;
        keys_players[TECLA_START]=SDL_SCANCODE_Y;
//        keys_players[TECLA_ACCION_2]=SDLK_5; 
    
    }else if(id==PLAYER_4){
    	keys_players[TECLA_IZQUIERDA] = SDL_SCANCODE_J;
    	keys_players[TECLA_DERECHA] = SDL_SCANCODE_J;
    	keys_players[TECLA_ARRIBA] = SDL_SCANCODE_I;
    	keys_players[TECLA_ABAJO] = SDL_SCANCODE_K;
        keys_players[TECLA_ACCION]=SDL_SCANCODE_U;
        keys_players[TECLA_START]=SDL_SCANCODE_O;
//        keys_players[TECLA_ACCION_2]=SDLK_8;
        
    }else if(id==PLAYER_5){
    	keys_players[TECLA_IZQUIERDA] = SDL_SCANCODE_1;
    	keys_players[TECLA_DERECHA] = SDL_SCANCODE_2;
    	keys_players[TECLA_ARRIBA] = SDL_SCANCODE_3;
    	keys_players[TECLA_ABAJO] = SDL_SCANCODE_4;
        keys_players[TECLA_ACCION] = SDL_SCANCODE_5;
        keys_players[TECLA_START] =
                SDL_SCANCODE_6;
//        keys_players[TECLA_ACCION_2]=SDLK_8;

    }*/
}

Uint8 ControlPlayer::getJoybuttonMapping(TeclaPlayer tecla) {
    return joybuttonMapping[tecla];
}

void ControlPlayer::setJoybuttonMapping(TeclaPlayer tecla, Uint8 nuevaTecla) {
    joybuttonMapping[tecla] = nuevaTecla;
}
