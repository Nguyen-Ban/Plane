#ifndef BULLET_H_
#define BULLET_H_

#include "LTexture.h"
#include "common.h"

#define BULLET_WIDTH 30
#define BULLET_HEIGHT 10

class Bullet : public LTexture
{
public:
    Bullet();
    ~Bullet();

    void HandleMove(const int& x_border,const int& y_border );
    void HandleMoveRight();
    void HandleEvent(SDL_Event e);
    bool LoadImgBullet(SDL_Renderer* des);
    bool get_is_move(){return is_move_;}
    void set_is_move(bool is_move){is_move_ = is_move;}
    float mPosX;
    float mPosY;
    int width = BULLET_WIDTH;
    int height = BULLET_HEIGHT;
private:
    bool is_move_;
};



#endif // BULLET_H_
