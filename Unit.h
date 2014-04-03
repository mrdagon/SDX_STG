#pragma once
#include <STG/Object.h>

namespace SDX
{
using namespace SDX;

class Unit : public Object
{
protected:
	virtual void Dead(){}

	virtual void Update()
	{
		if(invTime > 0 ) invTime--;
		timer++;
		lifeTime--;
		AnimeUpdate();
		Act();
	}

	/** 説明.*/
	virtual bool RemoveCheck(Rect* area)
	{
		if (this->hp <= 0)
		{
			isRemove = true;
			Dead();
		}

		if (
			timer == this->lifeTime ||
			(isOutCheck && !shape->Hit(area))
			)
		{
			this->isRemove = true;
		}

		if (isRemove) Remove();


		return this->isRemove;
	}

public:
	double hpMax;
	double hp;
	double spRate;
	bool   isDead = false ;
	unsigned int invTime = 0;///無敵時間

	Unit( Shape *shape , Sprite *sprite , double hpMax , double power ,Belong belong):
		Object( shape , sprite , power ,belong),
		hp(hpMax),
		hpMax(hpMax)
	{}

	virtual void Damaged( double ダメージ )
	{
		if( !invTime && ダメージ > 0)
		{
			this->hp -= ダメージ;
			React(ダメージ);
		}
	}
};
}