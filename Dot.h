#ifndef DOT_H_
#define DOT_H_

#include "LTexture.h"
#include "bullet.h"
#include "common.h"


class Dot : public LTexture
{
    public:
		//The dimensions of the dot

		static const int BULLET_POS = 54;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 1;

		//Initializes the variables
		Dot();

        ~Dot();
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event e, SDL_Renderer*  gRenderer );

        void HandleBullet(SDL_Renderer* des);
		//Moves the dot
		void move();

		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        void SetBulletList(std::vector<Bullet*> bullet_list){p_bullet_list_ = bullet_list;}
        std::vector<Bullet*> GetBulletList() const {return p_bullet_list_;}

        void RemoveBullet(const int &idx);

    private:
        std::vector<Bullet*>p_bullet_list_;
};

#endif // DOT_H_

