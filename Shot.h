#pragma once
#include <STG/Object.h>

namespace SDX
{
class Shot : public Object
{
public:
	bool isPierce;
	std::unique_ptr<ISpeed> speed;

	Shot( Shape *shape , Sprite *sprite , ISpeed *速度 , double 角度 , double power , bool isPierce , Belong belong):
		Object(shape, sprite, power, belong),
		isPierce(isPierce),
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
		if (speed)
		{
			MoveFront(speed->Ease());
		}
	}
};
}