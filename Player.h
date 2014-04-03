#pragma once
#include "Unit.h"
#include "StgSystem.h"
#include "Scene.h"
#include "Objects.h"

namespace SDX
{
class Wepon;

class Player : public Unit
{
protected:
	int weponCount = 0;

	virtual void Update()
	{
		if (invTime > 0)
		{
			if (invTime % 2)
			{
				SetColor({ 255, 255, 255, 255 });
			}
			else
			{
				SetColor({ 255, 255, 255, 0 });
			}
			--invTime;
		}

        if(残り自然回復 > 0)
        {
            if(残り自然回復 < StgSystem::自然回復) hp += 残り自然回復;
            else                                   hp += StgSystem::自然回復;
            残り自然回復 -= StgSystem::自然回復;       
        }

		++timer;
		AnimeUpdate();
		カーソル移動();

        //自爆
        if( Input::key.C.on || Input::touch[2].on) this->hp = 0;

		if (hyperGage < 100 && hyperTime <= 0) hyperGage += 0.1;

		if (Input::pad.Button2.hold | Input::touch[1].on && hyperGage >= 100)
		{
			hyperTime = 200;
			hyperGage = 0;
		}
		--hyperTime;

		StgSystem::最大HP = (int)hpMax;
		StgSystem::現在HP = (int)hp;
		StgSystem::現在チャージ = (int)hyperGage;
        StgSystem::回復HP = (int)(残り自然回復+hp);

		Act();
		カメラ制御();
	}

	void AddWepon( Object *wepon )
	{
		Scene::Add(wepon);
		++weponCount;
	}

public:
	int hyperTime = 0;
	int changeTime = 0;
	double hyperGage = 0;
	double speed;
    double 残り自然回復 = 0;

	int GetWeponCount()
	{
		return weponCount;
	}

	Player( Shape *当たり判定 , Sprite *前進絵 , Sprite *横絵 , double 最大HP ,double 速さ) :
		Unit(当たり判定, 前進絵, 最大HP,  ItemData::dataS[ItemData::ゆうぎ].Get(), Belong::Ally),
		speed(速さ)
	{
		Model::Add(横絵);
		StgSystem::最大HP = (int)hpMax;
		StgSystem::現在HP = (int)hpMax;
		StgSystem::現在チャージ = 0;
		isOutCheck = false;
	}

	void カーソル移動()
	{
		double vx = Input::pad.Right.hold - Input::pad.Left.hold;
		double vy = Input::pad.Down.hold  - Input::pad.Up.hold;

        if( this->hp == this->hpMax)
        {
            StgSystem::コンボ時間 = 100;
        }

		if (vx != 0 && vy != 0)
		{
			vx *= 0.7;
			vy *= 0.7;
		}
        
        vx += Input::touch[0].moveX / speed;
        vy += Input::touch[0].moveY / speed;

		Move(vx * speed, vy * speed);

		if (vx != 0)
		{
			sprites[0]->isVisible = false;
			sprites[1]->isVisible = true;
			sprites[1]->isTurn = (vx < 0);
			changeTime = 5;
		}

		changeTime--;

		if (changeTime == 0)
		{
			sprites[0]->isVisible = true;
			sprites[1]->isVisible = false;
		}

		const double left	= Scene::Now()->moveArea.GetLeft();
		const double top	= Scene::Now()->moveArea.GetTop();
		const double right	= Scene::Now()->moveArea.GetRight();
		const double bottom = Scene::Now()->moveArea.GetBottom();

		if ( GetX() < left	 ) SetPos(left	, GetY() );
		if ( GetY() < top	 ) SetPos(GetX(), top	 );
		if ( GetY() > bottom ) SetPos(GetX(), bottom );
		if ( GetX() > right	 ) SetPos(right	, GetY() );
	}

	void Remove()
	{
		Scene::Add(new エフェクト(&MEffect::爆発[12], GetX(), GetY()));
		StgSystem::現在HP = 0;
        StgSystem::回復HP = 0;
		StgSystem::現在チャージ = 0;
		isRemove = true;
	}

	void React(double ダメージ量)
	{
        残り自然回復 = ダメージ量 / 2;
		this->invTime = 30;
	}

	void カメラ制御()
	{
		const int nowX = (int)GetX();

		if (Camera::Now()->GetZoom() >= 1)
		{
			Camera::Now()->SetForcus(250 + nowX / 6, 300);
		}
		else
		{
			Camera::Now()->SetForcus(300, 300);
		}
	}
};
}