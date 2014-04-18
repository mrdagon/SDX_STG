#pragma once//☀SDX_STG

#include "IMenu.h"
#include "Layer.h"
#include "Unit.h"
#include "Shot.h"
#include "MenuObject.h"
#include "DMenuObject.h"

namespace SDX_STG
{
    using namespace SDX;
    class Menu : public IMenu
    {
    private:

        Layer<MenuObject> selects;
        Layer<Object> backEffects;
        Layer<Object> midEffects;
        Layer<Object> frontEffects;

        std::vector<std::shared_ptr<IModule>> events;

        Camera camera;

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
            SMenu = this;
            camera.SetActive();
        }

        void SetItemCount(int 横数 ,int 縦数)
        {
            メニュー横数 = 横数;
            メニュー縦数 = 縦数;    
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

            if (     Input::pad.Up.on     && メニュー縦数 > 1) 選択ID -= メニュー横数;
            else if (Input::pad.Down.on     && メニュー縦数 > 1) 選択ID += メニュー横数;
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

        void Add( MenuObject *追加するObject )
        {
            selects.Add(追加するObject);

            if ( selects.GetCount() == 1)
            {
                追加するObject->isSelect = true;
            }
        }

        void Add(Object *追加するObject, int 待機時間 = 0)
        {
            midEffects.Add(追加するObject, 待機時間);
        }

        void AddFront(Object *追加するObject, int 待機時間 = 0)
        {
            frontEffects.Add(追加するObject, 待機時間);
        }

        void AddBack(Object *追加するObject, int 待機時間 = 0)
        {
            backEffects.Add(追加するObject, 待機時間);
        }

        void AddEvent(IModule *追加するEvent)
        {
            events.emplace_back(追加するEvent);
        }

        bool IsActive()
        {
            return isActive;
        }

        void SetActive(bool 入力可能フラグ )
        {
            isActive = 入力可能フラグ;
        }

        std::string& GetMessage()
        {
            return メッセージ;
        }

        virtual void Init(){};

        virtual void Final(){};

        void InitDefault(const char* デフォルトメッセージ)
        {
            SetNow();

            AddFront(new 暗幕(255));
            AddBack(new エフェクト(MSystem::背景[6], 400, 300));

            Add(new メッセージ枠(デフォルトメッセージ));
        }
    };
}