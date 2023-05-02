#include "common.h"
#include "Dot.h"

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

Dot::~Dot()
{

}
void Dot::handleEvent( SDL_Event e,SDL_Renderer* gRenderer )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            mVelY -= DOT_VEL;
            break;
        case SDLK_s:
            mVelY += DOT_VEL;
            break;
        case SDLK_a:
            mVelX -= DOT_VEL;
            break;
        case SDLK_d:
            mVelX += DOT_VEL;
            break;
        case SDLK_SPACE:

            Bullet* bulletObject = new Bullet();
            bulletObject->loadFromFile("bullet.png", gRenderer);
            bulletObject->mPosX = this->mPosX + DOT_WIDTH;
            bulletObject->mPosY = this->mPosY + BULLET_POS;
            bulletObject->set_is_move(true);
            p_bullet_list_.push_back(bulletObject);
            break;
        }
    }


    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            mVelY += DOT_VEL;
            break;
        case SDLK_s:
            mVelY -= DOT_VEL;
            break;
        case SDLK_a:
            mVelX += DOT_VEL;
            break;
        case SDLK_d:
            mVelX -= DOT_VEL;
            break;
        }
    }
}

void Dot::HandleBullet(SDL_Renderer* des)
{
    for(int i=0; i<p_bullet_list_.size(); i++)
        {
            Bullet* bulletObject = p_bullet_list_.at(i);
            if(bulletObject != NULL)
            {

                if(bulletObject->get_is_move())
                {
                    bulletObject->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                    bulletObject->render(bulletObject->mPosX,bulletObject->mPosY,des);

                }
                else
                {
                    if(bulletObject!=NULL)
                    {
                        p_bullet_list_.erase(p_bullet_list_.begin()+i);
                        delete bulletObject;
                        bulletObject = NULL;
                    }
                }
            }
        }
}

void Dot::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }

}

void Dot::RemoveBullet(const int &idx)
{
    if(idx < p_bullet_list_.size() && p_bullet_list_.size() > 0)
    {
        Bullet* p_bullet  = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);
        if(p_bullet != NULL)
        {
            delete p_bullet;
        }
    }

}
