#pragma once//☀SDX_STG
#include "Shot.h"
#include "Material.h"

namespace SDX_STG
{
    using namespace SDX;
namespace 弾
{
/**自機用、通常弾.*/
class 通常 : public Shot
{
    public:
    通常(int X座標 ,int Y座標, double 攻撃力, ISpeed *速度, Image *画像, double 幅, double 高さ, double 角度) :
        Shot
        (
            new Rect( X座標, Y座標, 幅, 高さ),
            new SpImage( 画像 ),
            速度,
            角度,
            攻撃力,
            false,
            Belong::Ally
        )
    {}
};

///**炸裂ダメージ.*/
//class 炸裂攻撃 : public Shot
//{
//public:
//    炸裂攻撃(Shot* 炸裂元 , Anime* 炸裂画像) :
//        Shot
//        (
//        new Circle(炸裂元->GetX(), 炸裂元->GetY(),16),
//        new SpAnime(炸裂画像),
//        nullptr,
//        0,
//        炸裂元->power / 8,//最大で命中時の５倍ダメージ
//        true,
//        Belong::Ally
//        )
//    {
//        lifeTime = int(炸裂画像->GetAnimeTime());
//    }
//};
//
///**自機用、範囲攻撃弾.*/
//class 炸裂 : public Shot
//{
//public:
//    //円形のみ
//    炸裂(Wepon* 発射武器, int Xずれ, int Yずれ, ISpeed *速度, Image *画像, double 当たり半径, double 角度) :
//        Shot
//        (
//        new Circle(発射武器->GetX() + Xずれ, 発射武器->GetY() + Yずれ, 当たり半径),
//        new SpImage(画像),
//        速度,
//        角度,
//        発射武器->性能->通常攻撃力,
//        false,
//        Belong::Ally
//        )
//    {}
//    
//    //ぶつかると爆風を出す
//    void React()
//    {
//        Scene::Add(new 炸裂攻撃(this , &MEffect::プラズマ[0]));
//    }
//};

}}