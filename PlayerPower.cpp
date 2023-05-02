#include "PlayerPower.h"
#include "common.h"

PlayerPower::PlayerPower()
{

}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int &xpos)
{
    post_list_.push_back(xpos);
}

void PlayerPower::ShowPower(SDL_Renderer *des)
{
    if(number_ == post_list_.size())
    {
        for(int i = 0; i< post_list_.size(); i++)
        {
            rect_.x = post_list_.at(i);
            render(rect_.x, 0, des);
        }
    }
}

void PlayerPower::Init(SDL_Renderer *des)
{
    loadFromFile("playpower.png", des);
    number_ = LIFE_POINTS;
    if(post_list_.size() > 0)
    {
        post_list_.clear();
    }

    for(int i = 1; i <= LIFE_POINTS; i++)
    {
        AddPos(i*20);
    }
}

void PlayerPower::Decrease()
{
    number_ --;
    post_list_.pop_back();
}
