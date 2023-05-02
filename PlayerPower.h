#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H
#include "LTexture.h"
#include <vector>

class PlayerPower : public LTexture
{
public:
    PlayerPower();
    ~PlayerPower();
    void SetNumber(const int &num) {number_ = num;}
    void AddPos(const int & xpos);
    void ShowPower(SDL_Renderer *des);
    void Init(SDL_Renderer *des);
    void Decrease();

private:
    int number_;
    std::vector <int> post_list_;
};

#endif // PLAYER_POWER_H
