#pragma once//☀SDX_STG
#include "Enemy.h"
#include "Material.h"

namespace SDX_STG
{
    using namespace SDX;
    class 大型ヘリボス : public Enemy
    {
    public:
        int mode = 0;

        大型ヘリボス(double x, double y) :
            Enemy(x, y, EnemyID::ビッグヘリ, &MEnemy::大型ヘリ・本体)
        {
            sprites.emplace_back(new SpAnime(&MEnemy::大型ヘリ・ガドリング));
            sprites[1]->SetGap(68, 52);

            sprites.emplace_back(new SpAnime(&MEnemy::大型ヘリ・ガドリング));
            sprites[2]->SetGap(-68, 52);

            sprites.emplace_back(new SpImage(MEnemy::大型ヘリ・パーツ[0]));
            sprites[3]->SetGap(-108, 0);

            sprites.emplace_back(new SpImage(MEnemy::大型ヘリ・パーツ[1]));
            sprites[4]->SetGap( 108, 0);

            sprites.emplace_back(new SpAnime(&MEnemy::大型ヘリ・砲台));
            sprites[5]->SetGap( 0 , 0);

            sprites.emplace_back(new SpAnime(&MEnemy::大型ヘリ・プロペラ));
            sprites[6]->SetGap(-68 , 0);

            sprites.emplace_back(new SpAnime(&MEnemy::大型ヘリ・プロペラ));
            sprites[7]->SetGap(68 , 0);

            this->SetZoom(2);

            Camera::Now()->SetZoomForcus(0.5);
            SStage->GetLiveArea()->SetZoom(1.5, 2);
            SStage->GetMoveArea()->SetZoom(1.5, 2);
        }

        void Act()
        {
            switch (mode)
            {
            case 0: Mode00(); break;
            case 1: Mode01(); break;
            }
        }

        void Mode00()
        {
            Move(0, 2);
            if (GetY() > 0) mode = 1;
        }

        int 左右移動 = 3;

        void Mode01()
        {
            Move(左右移動, 0);
            if (GetX() < 0) 左右移動 = 3;
            if (GetX() > 600) 左右移動 = -3;

            if (timer % 6 == 0)
            {
                Shoot(&MShot::緑大, new Speed::Liner(4), Rand::Get(PAI / 2) + PAI / 4, 20, 6, 136, 104);
                Shoot(&MShot::緑大, new Speed::Liner(4), Rand::Get(PAI / 2) + PAI / 4, 20, 6, 0, 104);
                Shoot(&MShot::緑大, new Speed::Liner(4), Rand::Get(PAI / 2) + PAI / 4, 20, 6, -136, 104);
            }
        }
    };
}