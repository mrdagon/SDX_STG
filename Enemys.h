#pragma once
#include "Enemy.h"
#include "Material.h"
#include "Objects.h"

namespace SDX
{
/** aaa.*/ 
///	直進して突っ込むだけ
class 雑魚0 : public Enemy
{
public:
	雑魚0(double x , double y ):
		Enemy( x , y , EnemyID::雑魚A ,  &MEnemy::雑魚機 )
	{
		int			  spRate = 1;
		if( x < 400 ) spRate *= - 1;

		SetAngle(  ( 80 +Rand::Get(20) ) * DEG );
	}

	void Act()
	{
		if (timer == 30 )
		{
			Shoot(&MShot::緑大, new Speed::Liner(3), Rand::Get(PAI / 2) + PAI / 4, 20, 6);
		}

		MoveFront(2);
	}
};

class 戦車 : public Enemy
{
public:
	戦車(double x, double y) :
		Enemy(x, y, EnemyID::戦車, &MEnemy::戦車 , Belong::EnemyG)
	{
		Add(new SpImage( &MEnemy::戦車砲A));
		//sprites[1]->SetGap(0,-10);

		int			  spRate = 1;
		if (x < 400) spRate *= -1;

		SetAngle((80 + Rand::Get(20)) * DEG);
	}

	void Act()
	{
		if (timer % 30 == 0)
		{
			Shoot(&MShot::緑大,new Speed::Liner(3),Rand::Get(PAI/2)+PAI/4,20,6);
		}

		MoveFront(1);
	}

};
}