#pragma once//☀SDX_STG
#include "Object.h"

namespace SDX_STG
{
    using namespace SDX;

    class IUnit : public IObject
    {
    protected:
        virtual void Dead(){}
    public:
        double hpMax;
        double hp;
        double spRate;
        bool   isDead = false ;
        unsigned int invTime = 0;///無敵時間

        IUnit( IShape &図形 , ISprite &描画方法 , double 最大Hp , double 攻撃力 ,Belong 所属):
            IObject( 図形 , 描画方法 , 攻撃力 ,所属),
            hp(最大Hp),
            hpMax(最大Hp)
        {}

        virtual void Update()
        {
            if(invTime > 0 ) invTime--;
            timer++;
            lifeTime--;
            AnimeUpdate();
            Act();
        }

        virtual void Damaged( double ダメージ )
        {
            if( !invTime && ダメージ > 0)
            {
                this->hp -= ダメージ;
                React(ダメージ);
            }
        }

        virtual bool RemoveCheck(Rect* area)
        {
            if (this->hp <= 0)
            {
                isRemove = true;
                Dead();
            }

            if (
                timer == this->lifeTime ||
                (isOutCheck && !iShape.Hit(area))
                )
            {
                this->isRemove = true;
            }

            if (isRemove) Remove();


            return this->isRemove;
        }
    };
}