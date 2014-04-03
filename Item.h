#pragma once
#include "Unit.h"
#include "Material.h"
#include "StgSystem.h"

namespace SDX
{
class Item :public Object
{
private:
	double 落下速度 = 0;
    double 吹き飛び方向;
	Speed::AccelLimit 拡散速度 = { 6,-0.3, 0};
	bool 追跡フラグ = false;
    int 種類;
public:
	Item(double X座標, double Y座標, double レア率 , bool ボスフラグ):
		Object(new Circle( X座標, Y座標,10), new SpImage(MItem::imageS[36]), 0 , Belong::Item),
        吹き飛び方向(Rand::Get(PAI*2))
	{
        int アイテム種 = StgSystem::選択ステージ;
        int レア度 = Rand::Get(StgSystem::難易度);

        レア率 = レア率 * StgSystem::レアドロップ率 *(1 + StgSystem::難易度 );

        if( ボスフラグ )
        {
            if( Rand::Coin( レア率 / 10 ) )
            {
                レア度 = 4 + Rand::Coin( レア率 * StgSystem::レアドロップ率 );
            }
        }else{
            if( Rand::Coin(レア率) )
            {
                レア度 = std::min( StgSystem::難易度 + 1 , 3);
            }
            
            if( Rand::Coin(0.6) ) アイテム種 = 5;//7割は鉄塊
            
            種類 = アイテム種 * 6 + レア度;
        }

        種類 = アイテム種 * 6 + レア度;

        sprites[0]->SetZoom(2,2);
	}

	/**毎フレームの行動.*/
	void Act()
	{
		//追跡開始判定
		if ( !Scene::GetPlayer()->GetRemoveFlag() && GetDistance(Scene::GetPlayer()) < StgSystem::吸い寄せ範囲 )
		{
			追跡フラグ = true;
		}
        
		//移動処理
		MovePolar(拡散速度.Ease(), 吹き飛び方向 );

		if (追跡フラグ && Scene::GetPlayer()->GetRemoveFlag() == false)
		{
			const double 向き = GetDirect(Scene::GetPlayer());
			MovePolar(10, 向き);
		}
		else
		{
            sprites[0]->Rotate(0.1);
			落下速度 += 0.02;
			Move(0, 落下速度);
		}
	}

	/**自機と衝突.*/
	void Damaged(double 被ダメージ)
	{
		++StgSystem::素材数[種類];

		this->isRemove = true;
	}

};
}