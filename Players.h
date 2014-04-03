#pragma once
#include "Player.h"
#include "Wepons.h"

namespace SDX
{
namespace 自機
{

class れいむ : public Player
{
public:
	//バランスタイプ
	れいむ(double X座標 , double Y座標):
		Player(
				new Circle(X座標, Y座標, 2000 / ItemData::dataS[ItemData::ちるの].Get() ),
				new SpImage(MYukkuri::れいむ後[0]),
				new SpImage(MYukkuri::れいむ後[1]),
				ItemData::dataS[ItemData::れいむ].Get() +
                ItemData::dataS[ItemData::いくさん].Get(),
				8
			  )
	{
        AddWepon(new 武器::すいか(this));
		AddWepon(new 武器::すいか(this));
		AddWepon(new 武器::てんこ(this));
		AddWepon(new 武器::てんこ(this));

        StgSystem::吸い寄せ範囲    = ItemData::dataS[ItemData::ゆーびぃ].Get();
        StgSystem::レアドロップ率  = ItemData::dataS[ItemData::てい].Get() / 100;
        StgSystem::自然回復        = ItemData::dataS[ItemData::テルヨフ].Get() / 5000;
	}
};

class まりさ : public Player
{
public:
	//低速、高耐久
	まりさ( double X座標 , double Y座標):
		Player(
		    new Circle(X座標, Y座標, 2000 / ItemData::dataS[ItemData::ちるの].Get() ),
		    new SpImage(MYukkuri::まりさ後[0]),
		    new SpImage(MYukkuri::まりさ後[1]),
		    ItemData::dataS[ItemData::まりさ].Get() +
            ItemData::dataS[ItemData::いくさん].Get(),
		    6   //速度
		)
	{
		AddWepon(new 武器::ありす(this));
		AddWepon(new 武器::ありす(this));
		AddWepon(new 武器::ぱちぇ(this));
		AddWepon(new 武器::ぱちぇ(this));

        StgSystem::吸い寄せ範囲    = ItemData::dataS[ItemData::ゆーびぃ].Get() * 1.2;
        StgSystem::レアドロップ率  = ItemData::dataS[ItemData::てい].Get() / 100;
        StgSystem::自然回復        = ItemData::dataS[ItemData::テルヨフ].Get() / 4000;

	}
};

class れみりゃ : public Player
{
public:
	//高速、紙耐久
	れみりゃ(double X座標, double Y座標) :
		Player(
		    new Circle(X座標, Y座標, 2000 / ItemData::dataS[ItemData::ちるの].Get() ),
		    new SpImage(MYukkuri::れみりゃ後[0]),
		    new SpImage(MYukkuri::れみりゃ後[1]),
		    ItemData::dataS[ItemData::れみりゃ].Get() +
            ItemData::dataS[ItemData::いくさん].Get(),
		    10   //速度
		)
	{
		AddWepon(new 武器::ふらん(this));
		AddWepon(new 武器::ふらん(this));
		AddWepon(new 武器::さくや(this));
		AddWepon(new 武器::さくや(this));
        
        StgSystem::吸い寄せ範囲    = ItemData::dataS[ItemData::ゆーびぃ].Get() * 0.7;
        StgSystem::レアドロップ率  = ItemData::dataS[ItemData::てい].Get() / 100;
        StgSystem::自然回復        = ItemData::dataS[ItemData::テルヨフ].Get() / 6000;
	}
};

}
}