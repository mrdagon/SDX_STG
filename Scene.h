#pragma once
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>
#include <STG/Layer.h>
#include "Unit.h"
#include "Shot.h"

namespace SDX
{
class Scene : public IScene
{
private:
	Layer<Object> backEffects;
	Layer<Object> midEffects;
	Layer<Object> frontEffects;

	Layer<Object> allys;
	Layer<Object> skyEnemys;
	Layer<Object> earthEnemys;
	Layer<Object> items;

	Layer<Object> allyShots;
	Layer<Object> enemyShots;

	Layer<Object> blocks;

	std::vector<std::shared_ptr<IModule>> events;

	static Scene* sceneNow;

	/** レイヤー等を初期化.*/
	void Clear()
	{
		timer = 0;

		backEffects.Clear();
		midEffects.Clear();
		frontEffects.Clear();

		allys.Clear();
		skyEnemys.Clear();
		earthEnemys.Clear();
		items.Clear();

		allyShots.Clear();
		enemyShots.Clear();

		blocks.Clear();
	}

	/** 当たり判定処理を行う.*/
	void Hit()
	{
		//ブロック
		blocks.Hit( allys );
		blocks.Hit( skyEnemys );
		blocks.Hit( allyShots );
		blocks.Hit( enemyShots );

		//敵,敵弾,自機,自機弾
		allys.Hit( skyEnemys );
		allys.Hit( enemyShots );
		skyEnemys.Hit( allyShots );
		earthEnemys.Hit( allyShots );

		//アイテム
		if ( GetPlayer() && !GetPlayer()->GetRemoveFlag())
		{
			items.Hit(GetPlayer());
		}
	}

public:
	int timer = 0;

	std::unique_ptr<Camera> camera;

	double scrSpeedX = 0;
	double scrSpeedY = 0;

	Rect area = Rect(300 , 300 , 640 , 700);
	Rect moveArea = Rect(300 , 300 , 600 , 600);

	std::shared_ptr<Object> player;

	Scene():
		camera( new Camera( 400 , 300 , 1) )
	{
		SetNow();
	}

	virtual ~Scene(){}

	void SetNow()
	{
		sceneNow = this;
		camera->SetActive();
	}

	static Scene* Now()
	{
		return sceneNow;
	}

	virtual void Update()
	{
		SetNow();
		++timer;

		//イベント処理
		for (auto it : events)
		{
			it->Update();
		}

		//レイヤー処理
		backEffects.Update();
		midEffects.Update();
		frontEffects.Update();
		allys.Update();
		skyEnemys.Update();
		earthEnemys.Update();
		items.Update();
		allyShots.Update();
		enemyShots.Update();
		blocks.Update();

		camera->Update();

		Hit();

		//消滅処理
		backEffects.ExeRemove(&area);
		midEffects.ExeRemove(&area);
		frontEffects.ExeRemove(&area);
		allys.ExeRemove(&area);
		skyEnemys.ExeRemove(&area);
		earthEnemys.ExeRemove(&area);
		items.ExeRemove(&area);
		allyShots.ExeRemove(&area);
		enemyShots.ExeRemove(&area);
		blocks.ExeRemove(&area);

	}

	virtual void Draw()
	{
		SetNow();
		backEffects.Draw();	
		earthEnemys.Draw();

		Screen::SetBright({ 0, 0, 0 });
		Screen::SetBlendMode( BlendMode::Alpha , 128 );
		allys.DrawShadow( 50 , 50 );
		skyEnemys.DrawShadow( 50 , 50 );
		Screen::SetBlendMode( BlendMode::NoBlend , 0 );		
		Screen::SetBright({ 255, 255, 255 });

		midEffects.Draw();
		allyShots.Draw();
		blocks.Draw();
		allys.Draw();
		items.Draw();
		skyEnemys.Draw();
		enemyShots.Draw();
		frontEffects.Draw();
	}

	static void SetPlayer( Unit* player)
	{
		if (player)
		{
			Now()->Add(player);
			Now()->player = Now()->allys.objects[0];
		}
		else
		{
			Now()->player = nullptr;
		}

	}

	static Object* GetPlayer()
	{
		return Now()->player.get();
	}

	static void Add(Unit *unit, int suspendTime = 0)
	{
		switch( unit->GetBelong())
		{
			case Belong::Ally:Now()->allys.Add( unit , suspendTime );break;
			case Belong::EnemyF:Now()->skyEnemys.Add(unit, suspendTime); break;
			case Belong::EnemyG:Now()->earthEnemys.Add(unit, suspendTime); break;
			case Belong::Block:Now()->blocks.Add(unit, suspendTime); break;
			case Belong::Item:Now()->items.Add(unit, suspendTime); break;
		}
	}

	static void Add(Shot *shot, int suspendTime = 0)
	{
		if (shot->GetBelong() == Belong::Ally)
		{
			Now()->allyShots.Add(shot, suspendTime);
		}else{
			Now()->enemyShots.Add(shot, suspendTime);
		}
	}

	static void Add(Object *オブジェクト, int 待機時間 = 0)
	{	
		if (オブジェクト->GetBelong() == Belong::Item)
		{
			Now()->items.Add( オブジェクト, 待機時間);
		}
		else
		{
			Now()->midEffects.Add( オブジェクト , 待機時間);			
		}
	}

	static void AddFront(Object *object, int suspendTime = 0)
	{	
		Now()->frontEffects.Add(object, suspendTime);
	}

	static void AddBack(Object *object, int suspendTime = 0)
	{
		Now()->backEffects.Add(object, suspendTime);
	}

	static void AddEvent(IModule *module)
	{
		Now()->events.emplace_back(module);
	}

	static Object* GetNearEnemy(Object* object)
	{
		if( Now()->skyEnemys.GetCount() == 0 )
		{
			return Now()->earthEnemys.GetNearest(object);
		}
		return Now()->skyEnemys.GetNearest(object);
	}

};
}