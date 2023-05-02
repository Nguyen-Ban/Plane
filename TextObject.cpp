#include "TextObject.h"


TextObject::TextObject()
{

}


TextObject::~TextObject()
{
}


bool TextObject::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen)
{
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);
  if( textSurface != NULL )
  {
    //Create texture from surface pixels
    texture_ = SDL_CreateTextureFromSurface(screen, textSurface );
    if( texture_ != NULL )
    {
      //Get image dimensions
      width_ = textSurface->w;
      height_ = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
  }

  return texture_ != NULL;
}

void TextObject::Free()
{
  if(texture_ != NULL)
  {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
  }
}


void TextObject::SetColor(const int &type)
{
  if (type == RED_TEXT)
  {
    SDL_Color color = {255, 0, 0};
    text_color_ = color;
  }
  else if (type == WHITE_TEXT)
  {
    SDL_Color color = {255, 255, 255};
    text_color_ = color;
  }
  else
  {
    SDL_Color color = {0, 0, 0};
    text_color_ = color;
  }
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip)
{
  SDL_Rect renderQuad = { x, y, width_, height_ };

  if( clip != NULL )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopy(screen, texture_, clip, &renderQuad);
}
