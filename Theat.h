#ifndef THREAT_H_
#define THREAT_H_
#include "common.h"
#include "LTexture.h"
#include "bullet.h"

#define WIDTH_THREAT 124
#define HEIGHT_THREAT 50

class Threat : public LTexture
{
public:
    Threat();
    ~Threat();

    void HandleThreatMove(const int &x_border, const int &y_border);
    void HandleInputAction(SDL_Event events);

    void set_x_val(const float &val) {x_val_ = val;}
    void set_y_val(const float &val) {y_val_ = val;}
    float get_x_val() const {return x_val_;}
    float get_y_val() const {return y_val_;}

    void SetBulletList(std::vector<Bullet*> bullet_list){p_bullet_threat_list_ = bullet_list;}
    std::vector<Bullet*> GetBulletList() const {return p_bullet_threat_list_;}
    void InitBullet(Bullet* p_bullet, SDL_Renderer* ren);
    void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit, SDL_Renderer* ren);

    void Reset(const int &xborder);
    void ResetBullet(Bullet* p_bullet);

    float x_pos_, y_pos_;

    int mWidth = WIDTH_THREAT;
    int mHeight = HEIGHT_THREAT;
    float x_val_;
    float y_val_;
private:
    std::vector<Bullet*>p_bullet_threat_list_;
};

#endif // THREAT_H_
