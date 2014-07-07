#pragma once//☀SDX_STG
#include "Object.h"

namespace SDX_STG
{
    using namespace SDX;
class Shot : public IObject
{
public:
    bool isPierce;
    double speed;

    Shot( IShape &図形 , ISprite &描画方法 , double 速度 , double 角度 , double 攻撃力 , bool is貫通 , Belong 所属):
        IObject(図形, 描画方法, 攻撃力, 所属),
        isPierce(is貫通),
        speed(速度)
    {
        SetAngle(角度);
    }

    virtual void Damaged( double ダメージ量 )
    {
        if( !isPierce )
        {
            this->isRemove = true;
        }
        React(ダメージ量);
    }

    virtual void Act()
    {
        MovePolar(speed, GetAngle());
    }
};
}