#pragma once
#include "Unit.h"
#include "StgSystem.h"
#include "EnemyData.h"
#include "Material.h"
#include "Objects.h"
#include "Item.h"

namespace SDX
{
class Enemy :public Unit
{
protected:
	EnemyData& 性能;
	double 登場角度;
public:

	Enemy(double x, double y, EnemyID type, Image *image, Belong belong = Belong::EnemyF) :
		性能(EnemyData::data[(int)type]),
		Unit(EnemyData::data[(int)type].当り判定->Clone(x, y),
		new SpImage(image),
		EnemyData::data[(int)type].最大耐久 * ( 1 + StgSystem::難易度 * StgSystem::難易度 / 4.0),
		EnemyData::data[(int)type].物理 * ( 1 + StgSystem::難易度 * StgSystem::難易度 / 4.0),
	   	belong)
	{
		sprites[0]->SetGap(性能.ずれX, 性能.ずれY);
		if (x == 0) sprites[0]->isTurn = true;
	}

	Enemy( double x , double y , EnemyID type , Anime *anime, Belong belong = Belong::EnemyF) :
		性能( EnemyData::data[(int)type] ),
		Unit(	EnemyData::data[(int)type].当り判定->Clone( x , y ) ,
				new SpAnime( anime ) ,
				EnemyData::data[(int)type].最大耐久 ,
				EnemyData::data[(int)type].物理 ,
				belong)
	{
		sprites[0]->SetGap( 性能.ずれX , 性能.ずれY );
		if( x == 0 ) sprites[0]->isTurn = true;
	}

	///デフォルト死亡
	void Dead()
	{
		//スコア追加
        const int 加算スコア = 性能.スコア * ( 50 + StgSystem::コンボ数 ) * ( StgSystem::難易度 + 2) / 2;

		StgSystem::現在スコア += 加算スコア;

        StgSystem::コンボ時間 = 30;
        StgSystem::コンボ数++;

		//爆発
		MSound::爆発.Play();
		Scene::Add(new エフェクト( &MEffect::爆発[13] , GetX() , GetY()) );
		
        for(int i=0; i < 加算スコア / 1000 ;++i)
        {
    		Scene::Add(new Item(GetX(), GetY() , 性能.レア率  ,性能.ボスフラグ) );
        }

		DeadSp();
	}

	void Shoot(Image* 画像 , ISpeed* 速度 , double 角度, double 攻撃力 ,int 半径 ,int Xずれ = 0,int Yずれ = 0)
	{
        攻撃力 *= 1 + StgSystem::難易度;

		Scene::Add(new Shot(new Circle(GetX() + Xずれ, GetY()+Yずれ, 半径),new SpImage(画像),速度, 角度,攻撃力,false,Belong::Etc) );
	}
	void Shoot(Anime* 画像, ISpeed* 速度, double 角度, int 攻撃力, int 半径, int Xずれ = 0, int Yずれ = 0)
	{
        攻撃力 *= 1 + StgSystem::難易度;

		Scene::Add(new Shot(new Circle(GetX() + Xずれ, GetY() + Yずれ, 半径), new SpAnime(画像), 速度, 角度, 攻撃力, false, Belong::Etc));
	}

	virtual void DeadSp(){};

};
}