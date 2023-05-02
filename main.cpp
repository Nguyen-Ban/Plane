#include "LTexture.h"
#include "Dot.h"
#include "common.h"
#include "bullet.h"
#include "Theat.h"
#include "PlayerPower.h"
#include "TextObject.h"

Dot gMain;

LTexture gBackground;

TTF_Font* g_font_text = NULL;

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    gWindow = SDL_CreateWindow("OneShoot",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

    TTF_Init();
    g_font_text = TTF_OpenFont("ARCADE.ttf", 60);
}
void loadMedia()
{
    gBackground.loadFromFile("rsz_background.jpg",gRenderer);
    gMain.loadFromFile("rsz_main.png",gRenderer);
}
void close()
{
    gMain.free();
    gBackground.free();
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[])
{
    init();
    loadMedia();

    //PlayerPower
    PlayerPower player_power;
    player_power.Init(gRenderer);

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);


    Threat* p_threats = new Threat[NUM_THREATS];

    for(int t = 0; t < NUM_THREATS; t++)
    {
        Threat* p_threat = (p_threats + t);

        p_threat->loadFromFile("rsz_enemy.png", gRenderer);
        p_threat->x_pos_ += t*200;
        p_threat->HandleThreatMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_threat->set_x_val(0.5);
        Bullet* p_bullet = new Bullet();
        p_threat->InitBullet(p_bullet, gRenderer);

    }

    int die_number = 0;
    int mark_val = 0;

    bool quit = false;

    int ret_menu = ShowMenu(gRenderer, g_font_text, "Play Game", "Exit", "backgroundMenu.jpg");
    if (ret_menu == 1)
        quit = true;

    SDL_Event e;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) quit = true;
            gMain.handleEvent(e,gRenderer);

        }
        gMain.SetRect(gMain.mPosX,gMain.mPosY+20,DOT_WIDTH-20,DOT_HEIGHT-20);
        SDL_Rect  main_rect = gMain.GetRect();

        // run screen
        /*int bkg_x = 0;
        bkg_x -= 1;

        gBackground.render(bkg_x, 0, gRenderer);
        gBackground.render(bkg_x + SCREEN_WIDTH, 0, gRenderer);
        if(bkg_x <= -SCREEN_WIDTH)
        {
            bkg_x = 0;
        }*/

        gBackground.render(0, 0, gRenderer);
        player_power.ShowPower(gRenderer);

        gMain.HandleBullet(gRenderer);

        for(int tt = 0; tt < NUM_THREATS; tt++)
        {
            Threat* p_threat = (p_threats + tt);
            if(p_threat)
            {
                p_threat->HandleThreatMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->render(p_threat->x_pos_,p_threat->y_pos_,gRenderer);
                p_threat->MakeBullet(gSurface, SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

                p_threat->SetRect(p_threat->x_pos_,p_threat->y_pos_+25,WIDTH_THREAT-5,HEIGHT_THREAT-30);
                SDL_Rect threat_rect = p_threat->GetRect();

                bool is_col1 = checkCollision(main_rect,threat_rect);
                bool is_col2 = false;
                bool is_col3 = false;

                std::vector<Bullet*> bullet_list = gMain.GetBulletList();
                for(int im = 0; im < bullet_list.size(); im++)
                {
                    Bullet* p_bullet = bullet_list.at(im);
                    if(p_bullet != NULL)
                    {
                        p_bullet->SetRect(p_bullet->mPosX, p_bullet->mPosY, BULLET_WIDTH, BULLET_HEIGHT+20);
                        SDL_Rect bullet_rect = p_bullet->GetRect();
                        is_col2 = checkCollision(bullet_rect, threat_rect);
                        if(is_col2)
                        {
                            mark_val++;
                            p_threat->Reset(SCREEN_WIDTH + tt*200);
                            gMain.RemoveBullet(im);
                        }
                    }
                }

                std::vector<Bullet*> bullet_threat_list = p_threat->GetBulletList();
                for(int am = 0; am < bullet_threat_list.size(); am++)
                {
                    Bullet* p_bullet = bullet_threat_list.at(am);
                    if(p_bullet != NULL)
                    {
                        p_bullet->SetRect(p_bullet->mPosX, p_bullet->mPosY, BULLET_WIDTH, BULLET_HEIGHT);
                        SDL_Rect bullet_rect = p_bullet->GetRect();
                        is_col3 = checkCollision(bullet_rect, main_rect);
                        if(is_col3)
                        {
                            p_threat->ResetBullet(p_bullet);
                        }
                        if(is_col1 || is_col3)
                        {
                            die_number++;

                            if(die_number < LIFE_POINTS)
                            {
                                SDL_Delay(1000);
                                p_threat->Reset(SCREEN_WIDTH + tt*200);
                                gMain.RemoveBullet(am);
                                player_power.Decrease();
                                player_power.ShowPower(gRenderer);

                            }
                            else
                            {
                                if(p_threats)
                                {
                                    delete [] p_threats;
                                    p_threats = NULL;
                                }
                                std::string val_str_mark = std::to_string(mark_val);
                                val_str_mark = "Your score: " + val_str_mark;
                                int ret_menu = ShowMenu(gRenderer, g_font_text, val_str_mark, "Exit", "backgroundMenu.jpg");
                                if (ret_menu == 1)
                                    quit = true;
                                close();
                                mark_game.Free();
                                return 1;
                            }
                        }
                    }
                }
            }

        }
        //Show mark value
        std::string val_str_mark = std::to_string(mark_val);
        std::string strMark("Mark: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.loadFromRenderedText(g_font_text, gRenderer);
        mark_game.RenderText(gRenderer, 400, 0, NULL);

        gMain.move();
        gMain.render(gMain.mPosX,gMain.mPosY,gRenderer);

        SDL_RenderPresent(gRenderer);
        SDL_Delay(1);
    }
    delete [] p_threats;
    mark_game.Free();
    close();

    return 0;
}

