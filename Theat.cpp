#include "Theat.h"
#include "bullet.h"

Threat::Threat()
{
    int random = rand()%7+1;
    x_pos_ = SCREEN_WIDTH;
    y_pos_ = SCREEN_HEIGHT*random/10;
    mWidth = WIDTH_THREAT;
    mHeight = HEIGHT_THREAT;

    x_val_ = 0;
    y_val_ = 0;
}

Threat::~Threat()
{
    if(p_bullet_threat_list_.size() > 0)
    {
        for(int i = 0; i < p_bullet_threat_list_.size(); i++)
        {
            Bullet* p_bullet = p_bullet_threat_list_.at(i);
            if(p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_threat_list_.clear();
    }
}

void Threat::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit, SDL_Renderer* ren)
{
    for(int i = 0; i < p_bullet_threat_list_.size(); i++)
    {
        Bullet* p_bullet = p_bullet_threat_list_.at(i);
        if(p_bullet)
        {
            if(p_bullet->get_is_move())
            {
                p_bullet->render(p_bullet->mPosX, p_bullet->mPosY, ren);
                p_bullet->HandleMoveRight();
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->mPosX = this->x_pos_;
                p_bullet->mPosY = this->y_pos_+ this->mHeight*0.5;
            }
        }
    }
}

void Threat::InitBullet(Bullet* p_bullet, SDL_Renderer* ren)
{
    if(p_bullet)
    {
        bool ret = p_bullet->loadFromFile("bullet1.png", ren);
        if(ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->mPosX = this->x_pos_;
            p_bullet->mPosY = this->y_pos_+ this->mHeight*0.5;
            p_bullet_threat_list_.push_back(p_bullet);
        }
    }
}

void Threat::HandleThreatMove(const int &x_border, const int &y_border)
{
    x_pos_ -= x_val_;
    if(x_pos_ < 0)
    {
        x_pos_ = SCREEN_WIDTH;
        int rand_y = rand()%900;
        if(rand_y > SCREEN_HEIGHT)
        {
            int random = rand()%7 + 1;
            rand_y = SCREEN_HEIGHT*random/10;
        }
        y_pos_ = rand_y;
    }

}

void Threat::HandleInputAction(SDL_Event events)
{

}

void Threat::Reset(const int &xborder)
{
    x_pos_ = xborder;
    int rand_y = rand()%900;
    if(rand_y > SCREEN_HEIGHT)
    {
        rand_y = SCREEN_HEIGHT*0.4;
    }
    y_pos_ = rand_y;

    for(int i = 0; i < p_bullet_threat_list_.size(); i++)
    {
        Bullet* p_bullet = p_bullet_threat_list_.at(i);
        if(p_bullet != NULL)
        {
            ResetBullet(p_bullet);
        }
    }
}

void Threat::ResetBullet(Bullet* p_bullet)
{
    p_bullet->mPosX = this->x_pos_;
    p_bullet->mPosY = this->y_pos_+ this->mHeight*0.5;
}
