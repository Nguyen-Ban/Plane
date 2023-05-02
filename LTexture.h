#ifndef LTEXTURE_H_
#define LTEXTURE_H_
#include<bits/stdc++.h>
#include "common.h"

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* gRenderer);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y ,SDL_Renderer* screen);

    //Gets image dimensions
    int getWidth();
    int getHeight();

    void SetRect(const int &x, const int &y, const int &w, const int &h)
    {
        rect_.x = x;
        rect_.y = y;
        rect_.w = w;
        rect_.h = h;
    }
    SDL_Rect GetRect()
    {
        return rect_;
    }


protected:
    //The actual hardware texture
    SDL_Texture* mTexture;
    SDL_Rect rect_;
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // LTEXTURE_H_

