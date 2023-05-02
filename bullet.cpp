#include "bullet.h"

Bullet::Bullet()
{
    mPosX = 0;
    mPosY = 0;
    is_move_ = false;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMove(const int& x_border,const int& y_border)
{
    mPosX += 5;
    if(mPosX > x_border)
    {
        is_move_ = false;
    }
}

void Bullet::HandleEvent( SDL_Event e )
{

}

bool Bullet::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    ret = loadFromFile("bullet.png", des);
    return ret;
}

void Bullet::HandleMoveRight()
{
    mPosX -= 1.5;
    if(mPosX < 0)
    {
        is_move_ = false;
    }
}
