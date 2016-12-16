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

    Uint32 getpixel(int x, int y)
    {
        int bpp = mSurface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = (Uint8 *)mSurface->pixels + y * mSurface->pitch + x * bpp;

        switch(bpp) {
            case 1:
                return *p;
                break;

            case 2:
                return *(Uint16 *)p;
                break;

            case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    return p[0] << 16 | p[1] << 8 | p[2];
                else
                    return p[0] | p[1] << 8 | p[2] << 16;
                break;

            case 4:
                return *(Uint32 *)p;
                break;

            default:
                return 0;       /* shouldn't happen, but avoids warnings */
        }
    }

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
    SDL_Texture* mTexture = nullptr;
    SDL_Surface * mSurface = nullptr;

    //Image dimensions
    int mWidth;
    int mHeight;
    std::string mPath;
};


#endif //BOMBERMAN_LTEXTURE_HPP
