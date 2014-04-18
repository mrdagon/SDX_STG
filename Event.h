#pragma once//☀SDX_STG
#include <Utility/Module.h>
#include "IStage.h"
#include "Players.h"
#include "Enemys.h"
#include "Boss.h"
#include "Material.h"

namespace SDX_STG
{
    using namespace SDX;
class 敵配置 : public IModule
{
    private:
        EnemyID enemy;
        int  time;
        int  x;
        int  y;
    public:
        敵配置( EnemyID 敵種類 , int X座標 , int Y座標 , int 発生時間):
            enemy(敵種類),
            time(発生時間),
            x(X座標),
            y(Y座標)
        {}

        void Update( )
        {
            if( SStage->timer != time ) return;

            switch(enemy)
            {
                case EnemyID::雑魚A:SStage->Add(new 雑魚0(x, y)); break;
                case EnemyID::戦車:SStage->Add(new 戦車(x, y)); break;
                case EnemyID::ビッグヘリ:SStage->Add(new 大型ヘリボス(x, y)); break;
            }
        }
};
class デバッグ : public IModule
{
    int 残り時間 = 0;
public:
    void Update()
    {        
        if ( !SStage->isPlayerLive() || Input::pad.Button10.on)
        {
            ++残り時間;
            if(残り時間 > 120 || Input::pad.Button10.on) SStage->isEnd = true;
        }
    }
};
}