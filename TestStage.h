#pragma once
#include <SDXFrameWork.h>
#include "Stage.h"
#include "Event.h"
#include "Objects.h"


namespace SDX_STG
{
    using namespace SDX;
class TestStage : public Stage
{
public:

    void Init()
    {
        //Filter::Hsb(&MShot::ビーム短, -90, 0, 0);
        //Filter::Hsb(&MShot::ビーム超, 90, 0, 0);

        //-60 赤
        //-30 赤
        //30 赤
        //60 黄色
        //90 そのまま
        //180 水色
        //240 青

        switch(StgSystem::自機タイプ)
        {
            case 1:SetPlayer(new 自機::れいむ(300, 600));break;
            case 2:SetPlayer(new 自機::まりさ(300, 600)); break;
            case 3:SetPlayer(new 自機::れみりゃ(300, 600)); break;
        }

        //背景の追加
        AddBack(new 背景(0, -3200 + 600, MSystem::マップチップ[0], "File/stage1.csv", 19, 100));
        
        //ゲージ等UI
        AddFront(new システム表示());

        //敵発生イベント
        AddEvent(new デバッグ());
        for (int i = 0; i < 100 ; ++i)
        {
            AddEvent(new 敵配置(EnemyID::雑魚A, Rand::Get(600), 0, i*10) );
        }

        for (int i = 0; i < 20; ++i)
        {
            AddEvent(new 敵配置(EnemyID::戦車, Rand::Get(600), 0, i * 50));
        }

        AddEvent(new 敵配置(EnemyID::ビッグヘリ, 300 , -300, 1000 ));

        //BGM
        MSound::爆発.SetVolume( double(Config::効果音量) / 10);

        MMusic::飛翔.SetVolume( double(Config::BGM音量) / 10);
        MMusic::飛翔.Play();

        StgSystem::現在スコア = 0;
        StgSystem::コンボ時間 = 0;
        StgSystem::コンボ数 = 0;
    }

    void Update()
    {
        Stage::Update();
    
        StgSystem::コンボ時間--;
        if(StgSystem::コンボ時間 <= 0 && StgSystem::コンボ数 > 0) StgSystem::コンボ数--;
    }

};
}