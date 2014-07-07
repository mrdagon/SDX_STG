#pragma once//☀SDX_STG
#include "Material.h"
#include "Player.h"
#include "Shots.h"

namespace SDX_STG
{
    using namespace SDX;
class Wepon : public IObject
{
protected:
    Player *親;
    int 待機中 = 0;
    Point 相対座標;
    int 左右;
    bool 固定砲;
    double 基礎攻撃力;
    int レベル;
public:
    const ItemData::Data &性能;

    Point shape;
    SpImage sprite;

    Wepon(Player* 親 , Image* アイコン画像 , int 武器ID ) :
        IObject(shape,sprite),
        性能( ItemData::dataS[武器ID] ),
        shape(親->GetX(), 親->GetY()),
        sprite(アイコン画像),
        親(親)
    {
        レベル = 1 + std::min( 性能.強化レベル / 20 , 3 );

        基礎攻撃力 = 性能.Get() * 性能.連射力 * ItemData::dataS[ItemData::ゆうぎ].Get() / 100;

        this->isOutCheck = false;

        switch ( 親->GetWeponCount() )
        {
            case 0://前方
                相対座標.SetPos( -15 , -30 );
                固定砲 = true;
                左右 = -1;
            break;
            case 1://前方
                相対座標.SetPos( 15  , -30 );
                固定砲 = true;
                左右 = 1;
            break;
            case 2://側方
                相対座標.SetPos( -50  , 20 );
                固定砲 = false;
                左右 = -1;
            break;
            case 3://側方
                相対座標.SetPos( 50  , 20 );
                固定砲 = false;
                左右 = 1;
            break;
        }
    }

    void Update( )
    {
        if ( 親->GetRemoveFlag() )
        {
            this->isRemove = true;
            return;
        }
        Object::Update( );

        if( ( Input::pad.Button1.hold || Input::touch[0].hold || 親->hyperTime > 0) && 待機中 <= 0)
        {
            待機中 = 性能.連射力;

            switch (レベル)
            {
                case 1:発射LV1(); break;
                case 2:発射LV2(); break;
                case 3:発射LV3(); break;
                case 4:発射LV4(); break;
            }
        }

        待機();
        追従();

        --待機中;
    }

    void Remove()
    {
        SStage->Add(new エフェクト(&MEffect::爆発[16], GetX(), GetY()));
    }

    virtual void 待機(){}

    virtual void 発射LV1() = 0;
    virtual void 発射LV2() = 0;
    virtual void 発射LV3() = 0;
    virtual void 発射LV4() = 0;

    void 射撃(double 威力 , int Xずれ , int Yずれ , double 速度 , double 角度 , Image* 画像 )
    {
        double 攻撃力 = 基礎攻撃力 * 威力;
        if (親->hyperTime > 0)
        {
            Xずれ *= 2;
            Yずれ *= 2;
            角度 *= 2;
            攻撃力 *= 3;

            if (画像 == &MShot::火)
            {
                画像 = &MShot::火炎;
            }
            else
            {
                画像 = &MShot::ビーム超;
            }
        }

        角度 -= PAI / 2;

        SStage->Add(new 弾::通常((int)GetX() + Xずれ, (int)GetY() + Yずれ, 攻撃力, new Speed::Liner(速度), 画像, 画像->GetWidth(), 画像->GetHeight(), 角度));
    }

    void 射撃( double 威力,int Xずれ, int Yずれ, double 初速, double 加速度, double 角度, Image* 画像)
    {
        double 攻撃力 = 基礎攻撃力 * 威力;
        if (親->hyperTime > 0)
        {
            Xずれ *= 2;
            Yずれ *= 2;
            角度 *= 2;
            攻撃力 *= 3;

            画像 = &MShot::緑丸;
        }

        角度 -= PAI / 2;

        SStage->Add(new 弾::通常((int)GetX() + Xずれ, (int)GetY() + Yずれ, 攻撃力, new Speed::Accel(初速, 加速度), 画像, 画像->GetWidth(), 画像->GetHeight(), 角度));
    }

    void 追従()
    {
        if( 固定砲 )
        {
            this->SetPos( 親->GetX() + 相対座標.x , 親->GetY() + 相対座標.y );
            return;
        }

        const double xDis = 親->GetX() - ( GetX() - 相対座標.x );
        const double yDis = 親->GetY() - ( GetY() - 相対座標.y );
                
        double angle = atan2( yDis , xDis );
        double speed = sqrt(xDis * xDis + yDis * yDis) / 3;

        if( speed > 10 ) speed = 10;

        this->MovePolar( speed , angle  );    
    }
};
}