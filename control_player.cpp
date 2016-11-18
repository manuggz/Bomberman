#include "control_player.hpp"

using namespace std;

ControlPlayer::ControlPlayer(bool ini){
    if(ini)iniciar();
    
};

void ControlPlayer::iniciar(){
    for(int i=0;i<_TECLAS;i++){
        es_boton_joystick[i]=false;
        es_direccion_joystick[i]=false;
        keys_players[i]=static_cast<SDL_Keycode >(0);
        strcpy(nombres_joysticks[i],"sin asig.");
    }
}

bool ControlPlayer::cargar(char ruta[],bool ini){
    ifstream fs2(ruta,ios::in|ios::binary);
    if(!fs2){
        cerr<<"Error leyendo control en:"<<ruta<<endl;
        if(ini)iniciar();
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

char * ControlPlayer::getName(TeclaPlayer tecla){
    return nombres_joysticks[tecla];
};
bool ControlPlayer::isBotonJoystick(TeclaPlayer tecla){
    return es_boton_joystick[tecla];
};
bool ControlPlayer::isDireccionJoystick(int tecla){
    return es_direccion_joystick[tecla];
};
SDL_Keycode ControlPlayer::getKey(TeclaPlayer tecla){
    return keys_players[tecla];
};

void ControlPlayer::setName(TeclaPlayer tecla,const char name[]){
    strcpy(nombres_joysticks[tecla],name);
};
void ControlPlayer::setIsBotonJoystick(TeclaPlayer tecla,bool nuevo){
    es_boton_joystick[tecla]=nuevo;
};
void ControlPlayer::setIsDireccionJoystick(int tecla,bool nuevo){
    es_direccion_joystick[tecla]=nuevo;
};
void ControlPlayer::setKey(TeclaPlayer tecla,SDL_Keycode nuevo){
    keys_players[tecla]=nuevo;
};

void ControlPlayer::setDefaultKeys(IdPlayer id){
    iniciar();
    if(id==PLAYER_1){
    	keys_players[TECLA_IZQUIERDA] = SDLK_a;
    	keys_players[TECLA_DERECHA] = SDLK_d;
    	keys_players[TECLA_ARRIBA] = SDLK_w;
    	keys_players[TECLA_ABAJO] = SDLK_s;
        keys_players[TECLA_ACCION]=SDLK_e;
        keys_players[TECLA_START]=SDLK_q;
//        keys_players[TECLA_ACCION_2]=SDLK_1;
    }else if(id==PLAYER_2){
    	keys_players[TECLA_IZQUIERDA] = SDLK_LEFT;
    	keys_players[TECLA_DERECHA] = SDLK_RIGHT;
    	keys_players[TECLA_ARRIBA] = SDLK_UP;
    	keys_players[TECLA_ABAJO] = SDLK_DOWN;
        keys_players[TECLA_ACCION]=SDLK_KP_ENTER;
        keys_players[TECLA_START]=SDLK_p;
//        keys_players[TECLA_ACCION_2]=SDLK_KP1; 
    }else if(id==PLAYER_3){
    	keys_players[TECLA_IZQUIERDA] = SDLK_f;
    	keys_players[TECLA_DERECHA] = SDLK_h;
    	keys_players[TECLA_ARRIBA] = SDLK_t;
    	keys_players[TECLA_ABAJO] = SDLK_g;
        keys_players[TECLA_ACCION]=SDLK_r;
        keys_players[TECLA_START]=SDLK_y;
//        keys_players[TECLA_ACCION_2]=SDLK_5; 
    
    }else if(id==PLAYER_4){
    	keys_players[TECLA_IZQUIERDA] = SDLK_j;
    	keys_players[TECLA_DERECHA] = SDLK_l;
    	keys_players[TECLA_ARRIBA] = SDLK_i;
    	keys_players[TECLA_ABAJO] = SDLK_k;
        keys_players[TECLA_ACCION]=SDLK_u;
        keys_players[TECLA_START]=SDLK_o;
//        keys_players[TECLA_ACCION_2]=SDLK_8;
        
    }else if(id==PLAYER_5){
    	keys_players[TECLA_IZQUIERDA] = SDLK_1;
    	keys_players[TECLA_DERECHA] = SDLK_2;
    	keys_players[TECLA_ARRIBA] = SDLK_3;
    	keys_players[TECLA_ABAJO] = SDLK_4;
        keys_players[TECLA_ACCION]=SDLK_5;
        keys_players[TECLA_START]=SDLK_6;
//        keys_players[TECLA_ACCION_2]=SDLK_8;

    }
}
