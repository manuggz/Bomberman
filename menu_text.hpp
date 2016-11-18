#ifndef MENU_TEXT_HPP
#define MENU_TEXT_HPP
#include <SDL2/SDL.h>
#include "interfaz.hpp"
#include "game_manager.hpp"
#include "editor.hpp"
#include "juego_historia.hpp"

class MenuText:public Interfaz{
    public:
        MenuText(GameManager * game,char rutaParse[]);
        void setSelected(int nuevo);
        void procesarEvento(SDL_Event * evento);
        void draw(SDL_Surface * screen);       
        void execCommand(char key[],char accion[]);
        void update(){return;};
        void killSprite(int,int){return;};
        ~MenuText();
    private:
        GameManager * game;
        SDL_Rect **rectsImpresion;
        char **mensages,**acciones,**keys;
        char key_escape[50],accion_escape[50];
        
        int n_mensages;
        int selected;
        
};


#endif //fin MENU_TEXT_HPP
