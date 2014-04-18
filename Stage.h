#pragma once//☀SDX_STG

#include "IStage.h"
#include "Layer.h"
#include "Unit.h"
#include "Shot.h"
#include "Enemy.h"
#include "Item.h"

namespace SDX_STG
{
    using namespace SDX;
    class Stage : public IStage
    {
    private:
        Layer<Object> backEffects;
        Layer<Object> midEffects;
        Layer<Object> frontEffects;

        Layer<Unit> allys;
        Layer<Enemy> skyEnemys;
        Layer<Enemy> earthEnemys;
        Layer<Item> items;

        Layer<Shot> allyShots;
        Layer<Shot> enemyShots;

        std::vector<std::shared_ptr<IModule>> events;

        /** レイヤー等を初期化.*/
        void Clear()
        {
            timer = 0;

            backEffects.Clear();
            midEffects.Clear();
            frontEffects.Clear();

            allys.Clear();
            skyEnemys.Clear();
            earthEnemys.Clear();
            items.Clear();

            allyShots.Clear();
            enemyShots.Clear();
        }

        /** 当たり判定処理を行う.*/
        void Hit()
        {
            //敵,敵弾,自機,自機弾
            allys.Hit( skyEnemys );
            allys.Hit( enemyShots );
            skyEnemys.Hit( allyShots );
            earthEnemys.Hit( allyShots );

            //アイテム
            if ( GetPlayer() && !GetPlayer()->GetRemoveFlag())
            {
                items.Hit(GetPlayer());
            }
        }

    public:

        std::unique_ptr<Camera> camera;

        double scrSpeedX = 0;
        double scrSpeedY = 0;

        Rect liveArea = Rect(300 , 300 , 640 , 700);
        Rect moveArea = Rect(300 , 300 , 600 , 600);

        std::shared_ptr<Unit> player;

        Stage():
            camera( new Camera( 400 , 300 , 1) )
        {
            SetNow();
        }

        virtual ~Stage(){}

        void SetNow()
        {
            SStage = this;
            camera->SetActive();
        }

        void Update() override
        {
            SetNow();
            ++timer;

            //イベント処理
            for (auto it : events)
            {
                it->Update();
            }

            //レイヤー処理
            backEffects.Update();
            midEffects.Update();
            frontEffects.Update();
            allys.Update();
            skyEnemys.Update();
            earthEnemys.Update();
            items.Update();
            allyShots.Update();
            enemyShots.Update();

            camera->Update();

            Hit();

            //消滅処理
            backEffects.ExeRemove(&liveArea);
            midEffects.ExeRemove(&liveArea);
            frontEffects.ExeRemove(&liveArea);
            allys.ExeRemove(&liveArea);
            skyEnemys.ExeRemove(&liveArea);
            earthEnemys.ExeRemove(&liveArea);
            items.ExeRemove(&liveArea);
            allyShots.ExeRemove(&liveArea);
            enemyShots.ExeRemove(&liveArea);

        }

        void Draw() override
        {
            SetNow();
            backEffects.Draw();    
            earthEnemys.Draw();

            Screen::SetBright({ 0, 0, 0 });
            Screen::SetBlendMode( BlendMode::Alpha , 128 );
            allys.DrawShadow( 50 , 50 );
            skyEnemys.DrawShadow( 50 , 50 );
            Screen::SetBlendMode( BlendMode::NoBlend , 0 );        
            Screen::SetBright({ 255, 255, 255 });

            midEffects.Draw();
            allyShots.Draw();
            allys.Draw();
            items.Draw();
            skyEnemys.Draw();
            enemyShots.Draw();
            frontEffects.Draw();
        }

        Rect* GetMoveArea() override
        {
            return &moveArea;
        }

        Rect* GetLiveArea() override
        {
            return &liveArea;
        }

        void SetPlayer( Unit* 自機) override
        {
            if ( 自機 )
            {
                Add(自機);
                player = allys.objectS[0];
            }
            else
            {
                player = nullptr;
            }
        }

        Unit* GetPlayer() override
        {
            return player.get();
        }

        bool isPlayerLive() override
        {
            return !player->GetRemoveFlag();
        }

        void Add(Unit *追加するUnit, int 待機時間 = 0) override
        {
            allys.Add(追加するUnit, 待機時間);
        }

        void Add(Enemy *追加するEnemy, int 待機時間 = 0) override
        {
            switch (追加するEnemy->GetBelong())
            {
            case Belong::EnemyF:
                skyEnemys.Add(追加するEnemy, 待機時間); break;
            case Belong::EnemyG:
                earthEnemys.Add(追加するEnemy, 待機時間); break;
            }
        }

        void Add(Shot *追加するShot, int 待機時間 = 0) override
        {
            if (追加するShot->GetBelong() == Belong::Ally)
            {
                allyShots.Add(追加するShot, 待機時間);
            }else{
                enemyShots.Add(追加するShot, 待機時間);
            }
        }

        void Add(Item *追加するItem, int 待機時間 = 0) override
        {
            items.Add(追加するItem, 待機時間);
        }

        void Add(Object *追加するObject, int 待機時間 = 0) override
        {
            midEffects.Add(追加するObject, 待機時間);
        }

        void AddFront(Object *追加するObject, int 待機時間 = 0) override
        {    
            frontEffects.Add(追加するObject, 待機時間);
        }

        void AddBack(Object *追加するObject, int 待機時間 = 0) override
        {
            backEffects.Add(追加するObject, 待機時間);
        }

        void AddEvent(IModule *追加するEvent) override
        {
            events.emplace_back(追加するEvent);
        }

        Enemy* GetNearEnemy(Object* 比較するObject) override
        {
            if( skyEnemys.GetCount() == 0 )
            {
                return earthEnemys.GetNearest(比較するObject);
            }
            return skyEnemys.GetNearest(比較するObject);
        }

    };
}