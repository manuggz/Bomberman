#ifndef UTIL_HPP
#define UTIL_HPP
#include <cstdarg>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "constantes.hpp"
#include "engine/util/LTexture.hpp"
using namespace std;

SDL_Texture *cargar_textura(SDL_Renderer *gRenderer, string ruta, bool tiene_color_clave);
Mix_Chunk * cargar_sonido(char ruta[]);
Mix_Music * cargar_musica(const char ruta[]);
void imprimir_desde_grilla(LTexture * src, int cuadro, SDL_Renderer *,int x_dest,int y_dest, int fil, int col,int alpha);
//SDL_Surface * iniciar_modo(Uint16 w,Uint16 h,Uint8 bpp,Uint32 flags);
//int fps_sincronizar (void);
bool rects_colisionan(SDL_Rect & rect_1,SDL_Rect & rect_2);
void mostrar_error_salir(string msg);
inline bool punto_en_rect(Sint16 x,Sint16 y,SDL_Rect * rect_coli){return (x>rect_coli->x&&x<rect_coli->x+rect_coli->w&&y>rect_coli->y&&y<rect_coli->y+rect_coli->h);}
int buscar_dato(string ruta,string nombre_dato);
inline bool punto_en_rect_coordenadas(Sint16 x_1,Sint16 y_1,Sint16 x_2,Sint16 y_2,Sint16 w_2,Sint16 h_2){    return (x_1>x_2&&x_1<x_2+w_2&&y_1>y_2&&y_1<y_2+h_2);};
bool estado_tecla_joy(SDL_Keycode tecla,SDL_Joystick * joy);
EstadoSprite invertir_estado(EstadoSprite estado);
//void sdl_videoinfo(void);
Uint32 get_pixel (SDL_Surface * ima, int x, int y);
//void mostrar_msg (SDL_Surface * screen, SDL_Surface * ima, int x,int y,const char * orden_letras, char * formato, ...);

#endif