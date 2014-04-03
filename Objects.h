#pragma once
#include <STG/Object.h>
#include "Material.h"
#include "StgSystem.h"

namespace SDX
{
class エフェクト : public Object
{
public:
	エフェクト( Image* 画像 , double X座標 , double Y座標 , double 大きさ = 1.0):
			Object( new Point( X座標 , Y座標 ) , new SpImage( 画像 ) )
	{
		sprites[0]->SetZoom(大きさ,大きさ);
	}

	エフェクト( Anime* アニメ画像 , double X座標 , double Y座標 , bool 消滅フラグ = true):
			Object( new Point( X座標 , Y座標 ) , new SpAnime( アニメ画像 ) )
	{
		if (消滅フラグ)
		{
			lifeTime = アニメ画像->GetAnimeTime();
		}
	}

	エフェクト( const IFont *フォント , double X座標 , double Y座標 ,  Color 色 , double 表示倍率 , VString 描画文字  ):
			Object( new Point( X座標 , Y座標 ) , new SpFont( フォント , 色 , 表示倍率 , 表示倍率 , 描画文字.c_str() ) )
	{}

	エフェクト(const BmpFrame *BMPフレーム, double X座標, double Y座標, double 幅, double 高さ ) :
			Object( new Point( X座標 , Y座標 ) , new SpFrame( BMPフレーム , 幅 , 高さ) )
	{}
};

class Acter : public Object
{
    SpImage* 体;
    SpImageS* 目;
    SpImageS* 口;
public:
    Acter( double X座標 , double Y座標 , int ゆっくり種類 ):
        Object( new Point(X座標,Y座標) , nullptr )
    {
        //とりあえずれいむ
        Add( 体 = new SpImage(&MActer::れいむ体));
        Add( 目 = new SpImageS(&MActer::れいむ目));
        Add( 口 = new SpImageS(&MActer::れいむ口));
    }
};

class 背景 : public Object
{
public:
	背景( double 頂点座標X , double 頂点座標Y , ImagePack &マップチップ , const char* ファイル名, int 幅, int 高さ):
		Object( new Point( 頂点座標X , 頂点座標Y ) , new SpMap( マップチップ , ファイル名, 幅, 高さ, 0) )
	{
		this->isOutCheck = false;
	}

	void Act()
	{
		Move(0,0.5);
	}
};

class システム表示 : public Object
{
private:
	int score = 0;
public:
	システム表示() :
		Object(new Point(0, 0), nullptr )
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
		MFont::白絵.Draw(155,  5, Color::Red   , "SCORE");
		MFont::白絵.DrawExtend(160, 15, 2, 2, Color::White , {score});

		MFont::白絵.Draw(455, 5 , Color::Red   , "HISCORE");
		MFont::白絵.DrawExtend(460, 15 , 2, 2, Color::White , {StgSystem::最高スコア[StgSystem::選択ステージ][StgSystem::難易度]});

		//ライフ表示
		MFrame::BMPフレーム[3].Draw(155, 47, StgSystem::最大HP + 6, 20);
		MFont::白絵.Draw(160, 40, Color::Aqua , "SHIELD");
        Drawing::Rect(158, 50, StgSystem::回復HP , 14, Color::Green, true);
        Drawing::Rect(158, 50, StgSystem::現在HP , 14, Color::Red, true);

		//必殺ゲージ表示
		MFrame::BMPフレーム[3].Draw(155, 77, 100 + 6, 20);
		MFont::白絵.DrawExtend(160, 70,1,1 ,Color::Red, "HYPER");
		Drawing::Rect(158, 80, StgSystem::現在チャージ , 14, Color::Red, true);

        //コンボ数表示
        MFrame::BMPフレーム[3].Draw(515, 55, 125 + 6, 30);
        MFont::白絵.DrawExtend(520, 40 , 2 , 2, Color::Lime , "COMBO");
        MFont::白絵.DrawExtend(520, 60 , 3 , 3, Color::White , {"x",std::setw(4),StgSystem::コンボ数});

	}
};

}