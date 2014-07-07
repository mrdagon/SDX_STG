#pragma once//☀SDX_STG
#include <SDXFrameWork.h>

namespace SDX_STG
{
    using namespace SDX;
//所属するレイヤー
enum class Belong
{
    Ally,
    EnemyF,
    EnemyG,
    Item,
    Block,
    Etc
};

template <class T> class Layer;

///ModelにSTG用の機能を追加したクラス
///    \include
class IObject : public IModel
{
template<class T>
friend class Layer;
    
protected:
    int  timer = 0;///発生してから経過したフレーム数
    bool isOutCheck = true;///範囲外処理を行うかフラグ
    double  power;///攻撃力
    int  attribute;///攻撃属性
    int  lifeTime = -1;///生存期間
    Belong belong;///所属するレイヤー

    /// 消滅判定を行う
    virtual bool RemoveCheck(Rect* 存在可能範囲)
    {
        if(
            timer == this->lifeTime ||
            (isOutCheck && 存在可能範囲 && !iShape.Hit( 存在可能範囲 ) )
           )
        {
            this->isRemove = true;
        }

        if (isRemove) Remove();

        return this->isRemove;
    }

    void SetTimer(int フレーム数)
    {
        timer = フレーム数;
    }

public:
    //説明
    IObject( IShape &図形 , ISprite &描画方法 , double 攻撃力 = 0 , Belong 所属 = Belong::Etc):
        IModel(図形, 描画方法),
        power(攻撃力),
        belong(所属)
    {}

    int GetTimer()
    {
        return timer;
    }

    virtual ~IObject(){}

    //状態の更新
    virtual void Update()
    {
        this->timer++;
        AnimeUpdate();
        this->Act();
    }

    Belong GetBelong()
    {
        return belong;
    }
    
    //衝突した相手に攻撃する
    virtual void Attack(IObject *攻撃対象 )
    {
        攻撃対象->Damaged( power );
    }

    //Update時の行動処理
    virtual void Act(){}

    //消滅時の処理
    virtual void Remove(){}

    //ダメージを受けた時の処理
    virtual void React(double ダメージ量){}

    //攻撃された時の処理
    virtual void Damaged(double ダメージ量){}
    
    bool isSelect = false;
};
}