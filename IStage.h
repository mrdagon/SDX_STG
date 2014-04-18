#pragma once//☀SDX_STG

namespace SDX_STG
{
    using namespace SDX;

    class Unit;
    class Shot;
    class Enemy;
    class Item;

    class IStage : public IScene
    {
    public:
        int  timer = 0;

        virtual Rect* GetMoveArea() = 0;//移動可能な範囲を返す
        virtual Rect* GetLiveArea() = 0;//生存可能な範囲を返す

        virtual void SetPlayer(Unit* 自機) = 0;
        virtual Unit* GetPlayer() = 0;
        virtual bool isPlayerLive() = 0;

        virtual void Add(Unit *追加するUnit, int 待機時間 = 0) = 0;

        virtual void Add(Enemy *追加するEnemy, int 待機時間 = 0) = 0;

        virtual void Add(Shot *追加するShot, int 待機時間 = 0) = 0;

        virtual void Add(Item *追加するItem, int 待機時間 = 0) = 0;

        virtual void Add(Object *追加するObject, int 待機時間 = 0) = 0;

        virtual void AddFront(Object *追加するObject, int 待機時間 = 0) = 0;

        virtual void AddBack(Object *追加するObject, int 待機時間 = 0) = 0;

        virtual void AddEvent(IModule *追加するEvent) = 0;

        virtual Enemy* GetNearEnemy(Object* 比較するObject) = 0;
    };

    namespace{ IStage* SStage; }
}