#pragma once//☀SDX_STG
#include <Framework/IScene.h>

namespace SDX_STG
{
    using namespace SDX;

    class MenuObject;

    class IMenu : public IScene
    {
    public:
        virtual void Add(MenuObject *追加するObject) = 0;

        virtual void Add(Object *追加するObject, int 待機時間 = 0) = 0;

        virtual void AddFront(Object *追加するObject, int 待機時間 = 0) = 0;

        virtual void AddBack(Object *追加するObject, int 待機時間 = 0) = 0;

        virtual void AddEvent(IModule *追加するEvent) = 0;

        virtual bool IsActive() = 0;

        virtual void SetActive(bool 入力可能フラグ) = 0;

        virtual std::string& GetMessage() = 0;
    };

    namespace{ IMenu* SMenu; }
}