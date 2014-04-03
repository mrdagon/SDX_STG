#pragma once
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>
#include <STG/Layer.h>
#include "Unit.h"
#include "Shot.h"
#include "MenuObject.h"

namespace SDX
{
class Menu : public IScene
{
private:

	Layer<MenuObject> selects;
	Layer<Object> backEffects;
	Layer<Object> midEffects;
	Layer<Object> frontEffects;

	std::vector<std::shared_ptr<IModule>> events;

	Camera camera;

	static Menu* menuNow;

	bool isActive = false;//入力停止フラグ

	int 選択ID = 0;
	int メニュー横数 = 1;
	int メニュー縦数 = 1;

	std::string メッセージ;

protected:
	bool isCancel = true;//キャンセル時に一番最後のオブジェクトを起動
public:

	int timer = 0;

	Menu() :
		camera(400, 300, 1)
	{}

	virtual ~Menu(){}

	void SetNow()
	{
		camera.SetActive();
		menuNow = this;
	}

	void SetItemCount(int 横数 ,int 縦数)
	{
		メニュー横数 = 横数;
		メニュー縦数 = 縦数;	
	}

	static Menu* Now()
	{
		return menuNow;
	}

	virtual void Update()
	{
		SetNow();
		++timer;

		if( isCancel && Input::pad.Button2.on )
		{
			selects[selects.GetCount()-1]->Push();
		}

		//選択の変更
		ChangeSelect();

		//イベント処理
		for (auto it : events)
		{
			it->Update();
		}

		//オブジェクトの更新
		selects.Update();
		backEffects.Update();
		midEffects.Update();
		frontEffects.Update();

		selects.ExeRemove(nullptr);
		backEffects.ExeRemove( nullptr );
		midEffects.ExeRemove(nullptr);
		frontEffects.ExeRemove(nullptr);
	}

	void ChangeSelect()
	{
		if (selects.GetCount() == 0) return;

		if (	 Input::pad.Up.on	 && メニュー縦数 > 1) 選択ID -= メニュー横数;
		else if (Input::pad.Down.on	 && メニュー縦数 > 1) 選択ID += メニュー横数;
		else if (Input::pad.Left.on  && メニュー横数 > 1) 選択ID --;
		else if (Input::pad.Right.on && メニュー横数 > 1) 選択ID ++;
		else return;

		const int メニュー合計 = メニュー縦数 * メニュー横数;

		int 仮ID;

		if (選択ID < 0)
		{
			選択ID += メニュー合計;
		}
		else if (選択ID >= メニュー合計 )
		{
			選択ID -= メニュー合計;
		}

		仮ID = 選択ID;

		if (選択ID >= selects.GetCount() )
		{
			仮ID = selects.GetCount() - 1;
		}

		Select(仮ID);
		if( selects[仮ID]->説明文.length() > 0) this->メッセージ = selects[仮ID]->説明文;
	}

	virtual void Draw()
	{
		SetNow();
		backEffects.Draw();
		selects.Draw();
		midEffects.Draw();
		frontEffects.Draw();
	}

	void Select(int インデックス)
	{
		for (int i = 0; i < selects.GetCount(); ++i)
		{
			selects[i]->isSelect = (i == インデックス);
		}
	}

	void ToEnd()
	{
		isEnd = true;
	}

	static void Add( MenuObject *オブジェクト )
	{
		Now()->selects.Add( オブジェクト );

		if (Now()->selects.GetCount() == 1)
		{
			オブジェクト->isSelect = true;
		}
	}

	static void Add(Object *オブジェクト, int 待機時間 = 0)
	{
		Now()->midEffects.Add(オブジェクト, 待機時間);
	}

	static void AddFront(Object *オブジェクト, int 待機時間 = 0)
	{
		Now()->frontEffects.Add(オブジェクト, 待機時間);
	}

	static void AddBack(Object *オブジェクト, int 待機時間 = 0)
	{
		Now()->backEffects.Add(オブジェクト, 待機時間);
	}

	static void AddEvent(IModule *モジュール)
	{
		Now()->events.emplace_back(モジュール);
	}

	static bool IsActive()
	{
		return Now()->isActive;
	}

	static void SetActive(bool 入力可能フラグ )
	{
		Now()->isActive = 入力可能フラグ;
	}

	static std::string& Message()
	{
		return Now()->メッセージ;
	}

	virtual void Init(){};
	virtual void Final(){};
};
}