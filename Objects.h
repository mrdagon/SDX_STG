#pragma once//☀SDX_STG
#include "Object.h"
#include "Material.h"
#include "StgSystem.h"

namespace SDX_STG
{
    using namespace SDX;
    template<class TSprite>
    class エフェクト : public IObject
    {
    private:
        Point shape;
        TSprite sprite;
    public:
        エフェクト( TSprite &&描画方法 , double X座標 , double Y座標 ):
                IObject( shape , sprite ),
                shape(X座標, Y座標),
                sprite(描画方法)
        {}
    };

    class Acter : public IObject
    {
    private:
        Point shape;
        SpImage sprite;

    public:
        Acter( double X座標 , double Y座標 , int ゆっくり種類 ):
            IObject( shape , sprite ),
            shape(X座標, Y座標),
            sprite(&MActer::れいむ体)
        {
        }
    };

    class 背景 : public IObject
    {
    public:
        Point shape;
        SpMap sprite;

        背景( double 頂点座標X , double 頂点座標Y , ImagePack &マップチップ , const char* ファイル名, int 幅, int 高さ):
            IObject( shape , sprite ),
            shape(頂点座標X, 頂点座標Y),
            sprite(マップチップ, ファイル名, 幅, 高さ, 0)
        {
            this->isOutCheck = false;
        }

        void Act()
        {
            Move(0,0.5);
        }
    };

    class システム表示 : public IObject
    {
    private:
        int score = 0;
    public:
        Point shape;
        SpImage sprite;

        システム表示() :
            IObject(shape,sprite),
            shape(0,0),
            sprite(nullptr)
        {
            this->isOutCheck = false;
        }

        void Act()
        {
            if (StgSystem::現在スコア > score)
            {
                score += std::max( (StgSystem::現在スコア - score) / 100 , 56);
                if (StgSystem::現在スコア < score) score = StgSystem::現在スコア;
            }

            if( StgSystem::最高スコア[StgSystem::選択ステージ][StgSystem::難易度] < score)
            {
                StgSystem::最高スコア[StgSystem::選択ステージ][StgSystem::難易度] = score;
            }        
        }

        void Draw() const
        {
            MSystem::背景[1]->DrawPart(  0, 0, 0, 0,150,600);
            MSystem::背景[1]->DrawPart(650, 0, 0, 0,150,600);

            //スコア表示
            MFont::白絵.Draw({ 155, 5 }, Color::Red, "SCORE");
            MFont::白絵.DrawExtend({ 160, 15 }, 2, 2, Color::White, { score });

            MFont::白絵.Draw({ 455, 5 }, Color::Red, "HISCORE");
            MFont::白絵.DrawExtend({ 460, 15 }, 2, 2, Color::White, { StgSystem::最高スコア[StgSystem::選択ステージ][StgSystem::難易度] });

            //ライフ表示
            MFrame::BMPフレーム[3].Draw({ 155, 47, StgSystem::最大HP + 6, 20 });
            MFont::白絵.Draw({ 160, 40 }, Color::Aqua, "SHIELD");
            Drawing::Rect({ 158, 50, StgSystem::回復HP, 14 }, Color::Green, true);
            Drawing::Rect({ 158, 50, StgSystem::現在HP, 14 }, Color::Red, true);

            //必殺ゲージ表示
            MFrame::BMPフレーム[3].Draw({ 155, 77, 100 + 6, 20 });
            MFont::白絵.DrawExtend({ 160, 70 }, 1, 1, Color::Red, "HYPER");
            Drawing::Rect({ 158, 80, StgSystem::現在チャージ, 14 }, Color::Red, true);

            //コンボ数表示
            MFrame::BMPフレーム[3].Draw({ 515, 55, 125 + 6, 30 });
            MFont::白絵.DrawExtend({ 520, 40 }, 2, 2, Color::Lime, "COMBO");
            MFont::白絵.DrawExtend({ 520, 60 }, 3, 3, Color::White, { "x", std::setw(4), StgSystem::コンボ数 });

        }
    };

}