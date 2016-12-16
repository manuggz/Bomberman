//
// Created by manuggz on 06/12/16.
//

#ifndef TETRIS_TETRISCUADROSFORMA_HPP
#define TETRIS_TETRISCUADROSFORMA_HPP

#include <cmath>
#include "../../engine/sprites/CSprite.hpp"
#include "../../engine/sprites/CDrawGroup.hpp"
#include "../../engine/sprites/CSpriteCuadro.hpp"
#include "../../engine/util/SpriteSheet.hpp"

class Tetromino :public InterfazSpriteGroup {

public:

    enum TetrisForma{L,J,S,Z,O,I,T};

    static const int N_FORMAS = 7;
    static const int N_GIROS_MAX = 4;
    static const int N_FILAS_ARRAY = 4;
    static const int N_COLUMNAS_ARRAY = 4;

    SDL_Rect obtenerRectCuadrosVisibles(const Uint8 arrayCuadro[N_FILAS_ARRAY][N_COLUMNAS_ARRAY]) {
        
        SDL_Rect rect {N_COLUMNAS_ARRAY*mSizeCuadro,N_FILAS_ARRAY*mSizeCuadro,0,0};
        for(int i = 0; i < N_FILAS_ARRAY ; i++){
            for(int j = 0; j < N_COLUMNAS_ARRAY ; j++){
                if(arrayCuadro[i][j] != 0){
                    rect.x = std::min(j*mSizeCuadro,rect.x);
                    rect.y = std::min(i*mSizeCuadro,rect.y);
                    rect.w = std::max(j*mSizeCuadro + mSizeCuadro - rect.x,rect.w);
                    rect.h = std::max(i*mSizeCuadro + mSizeCuadro - rect.y,rect.h);
                }
            }
        }
        return rect;
    }

    Tetromino(int nFilas, int nColumnas, int left, int top, int size, SpriteSheet *pSheet) {

        mRect.x = left;
        mRect.y = top;
        mRect.h = nFilas*size;
        mRect.w = nColumnas*size;

        mSizeCuadro       = size;

        mTextuBloques = pSheet;

        mFilas = nFilas;
        mColumnas = nColumnas;

        mpBloquesArray = new int[mFilas*mColumnas] {0};

    }
    Tetromino(TetrisForma forma, int left, int top, int sizeTile, SpriteSheet *texturaGrilla) {


        mRect.w = N_COLUMNAS_ARRAY*sizeTile;
        mRect.h = N_FILAS_ARRAY*sizeTile;
        mSizeCuadro       = sizeTile;
        mForma          = forma;

        mRectCuadroVisible = obtenerRectCuadrosVisibles(stArrayFormas[mForma][mRotacionActual]);
        mRect.x = left - mRectCuadroVisible.x;
        mRect.y = top  - mRectCuadroVisible.x;

        mTextuBloques = texturaGrilla;

        mFilas = N_FILAS_ARRAY;
        mColumnas = N_COLUMNAS_ARRAY;
    }

/**
         * Rota la pieza 90 grados, si direccion = 1 clock-wise, si direccion = -1, inverso
         * @param direccion
         */
    void rotate(int direccion = 1){
        if(mpBloquesArray)return;
        if(direccion != 1 && direccion != -1) direccion = 1;

        mRotacionActual += direccion;
        if(mRotacionActual < 0 ){
            mRotacionActual = mMaxRotaciones - 1;
        }else if(mRotacionActual >= mMaxRotaciones){
            mRotacionActual = 0;
        }

        mRectCuadroVisible = obtenerRectCuadrosVisibles(stArrayFormas[mForma][mRotacionActual]);
    }

    void eliminarSprite(Sprite *sprite) override {

    }

    void update(const Uint8 *keys){
    }

    Uint8 valorIndiceAC(int i, int j){
        if(mpBloquesArray){
            return (Uint8) mpBloquesArray[i * mColumnas + j];
        }
        return stArrayFormas[mForma][mRotacionActual][i][j];
    }
    void draw(SDL_Renderer *gRenderer){
        int indice;
        for(int i = 0; i < mFilas ; i++){
            for(int j = 0; j < mColumnas ; j++){
                if(mpBloquesArray){
                    indice = mpBloquesArray[i*mColumnas +j];
                }else{
                    indice = stArrayFormas[mForma][mRotacionActual][i][j];
                }
                if( indice != 0){
                    mTextuBloques->setCurrentCuadro(indice - 1);
                    mTextuBloques->draw(gRenderer,j*mSizeCuadro + mRect.x,i*mSizeCuadro + mRect.y);
                }
            }
        }
    }

    void move(int x,int y){
        mRect.x = x;
        mRect.y = y;
    }
    void moveIp(int aum_x, int aum_y) {
//        for(auto pCuadro = mSprites->begin();pCuadro!=mSprites->end();pCuadro++){
//            (*pCuadro)->moveIp(aum_x,aum_y);
//        }
        mRect.x += aum_x;
        mRect.y += aum_y;
    }

    int getX(){
        return mRect.x;
    }

    int getY(){
        return mRect.y;
    }

    ~Tetromino(){
        delete mpBloquesArray;
    }

    bool existeIndiceAC(int i, int j) {
        return i >= 0 && i < mFilas && j >= 0 && j < mColumnas;
    }

    int getNFilas() {
        return mFilas;
    }
    int getNColumnas() {
        return mColumnas;
    }

    void setValorIndice(int i, int j, int valor) {
        if(mpBloquesArray){
            mpBloquesArray[i*mColumnas +j] =valor;
        }
    }



private:

    TetrisForma mForma;
    SDL_Rect mRect {0,0,0,0};

    int mSizeCuadro;
    int mRotacionActual = 0;
    int mMaxRotaciones  = 4;

    int * mpBloquesArray = nullptr;
    int mFilas,mColumnas;

    const Uint8 stArrayFormas[N_FORMAS][N_GIROS_MAX][N_FILAS_ARRAY][N_COLUMNAS_ARRAY] = {
            {
                    {
                            {0,1,0},
                            {0,1,0},
                            {0,1,1}
                    },
                    {
                            {0,0,1},
                            {1,1,1},
                            {0,0,0}
                    },
                    {
                            {1,1,0},
                            {0,1,0},
                            {0,1,0}
                    },
                    {
                            {0,0,0},
                            {1,1,1},
                            {1,0,0}
                    },
            },
            {
                    {
                            {0,9,9},
                            {0,9,0},
                            {0,9,0}
                    },
                    {
                            {9,0,0},
                            {9,9,9},
                            {0,0,0}
                    },
                    {
                            {0,9,0},
                            {0,9,0},
                            {9,9,0}
                    },
                    {
                            {0,0,0},
                            {9,9,9},
                            {0,0,9}
                    },
            },
            {
                    {
                            {0,2,2},
                            {2,2,0},
                            {0,0,0}
                    },
                    {
                            {0,2,0},
                            {0,2,2},
                            {0,0,2}
                    },
                    {
                            {0,2,2},
                            {2,2,0},
                            {0,0,0}
                    },
                    {
                            {0,2,0},
                            {0,2,2},
                            {0,0,2}
                    }
            },
            {
                    {
                            {11,11,0},
                            {0,11,11},
                            {0,0,0}
                    },
                    {
                            {0,0,11},
                            {0,11,11},
                            {0,11,0}
                    },
                    {
                            {11,11,0},
                            {0,11,11},
                            {0,0,0}
                    },
                    {
                            {0,0,11},
                            {0,11,11},
                            {0,11,0}
                    }
            },
            {
                    {
                            {3,3,0},
                            {3,3,0},
                            {0,0,0}
                    },
                    {
                            {3,3,0},
                            {3,3,0},
                            {0,0,0}
                    },
                    {
                            {3,3,0},
                            {3,3,0},
                            {0,0,0}
                    },
                    {
                            {3,3,0},
                            {3,3,0},
                            {0,0,0}
                    }
            },
            {
                    {
                            {0,12,0},
                            {0,12,0},
                            {0,12,0},
                            {0,12,0}
                    },
                    {
                            {0,0,0,0},
                            {12,12,12,12},
                            {0,0,0,0}
                    },
                    {
                            {0,12,0},
                            {0,12,0},
                            {0,12,0},
                            {0,12,0}
                    },
                    {
                            {0,0,0},
                            {12,12,12,12},
                            {0,0,0}
                    }
            },
            {
                    {
                            {0,4,0},
                            {4,4,4},
                            {0,0,0}
                    },
                    {
                            {0,4,0},
                            {0,4,4},
                            {0,4,0}
                    },
                    {
                            {0,0,0},
                            {4,4,4},
                            {0,4,0}
                    },
                    {
                            {0,4,0},
                            {4,4,0},
                            {0,4,0}
                    }
            }

    };
    SDL_Rect mRectCuadroVisible {0,0,0,0};
    SDL_Color mColor;
    SpriteSheet *mTextuBloques = nullptr;
};
#endif //TETRIS_TETRISCUADROSFORMA_HPP
