//
// Created by manuggz on 18/11/16.
//

#ifndef BOMBERMAN_LTEXTURE_HPP
#define BOMBERMAN_LTEXTURE_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path ,SDL_Renderer * gRendered,bool tieneColorClave);

    //Creates image from font string
    bool loadFromRenderedText(SDL_Renderer * gRenderer, TTF_Font * gFont, std::string textureText, SDL_Color textColor);

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( SDL_Renderer * gRenderer, int x=0, int y=0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth()const;
    int getHeight()const;
    std::string getPath()const;
private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
    std::string mPath;
};


#endif //BOMBERMAN_LTEXTURE_HPP
