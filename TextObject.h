#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "LTexture.h"

class TextObject
{
public:
  TextObject();
  ~TextObject();

  enum TextColor
  {
    RED_TEXT  = 0,
    WHITE_TEXT = 1,
    BLACK_TEXT = 2,
  };

  bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);
  void Free();

  void SetColor(const int &type);

  void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip);

  int getWidth() const {return width_;}
  int getHeight() const {return height_;}
  void SetText(const std::string& text) {str_val_ = text;}
  std::string GetText() const {return str_val_;}

private:
  std::string str_val_;
  SDL_Color text_color_;
  SDL_Texture* texture_;
  int width_;
  int height_;

};

#endif
