#pragma once//☀Unicode
#include "Object.h"

namespace SDX_STG
{
    using namespace SDX;
    /**Objectのコンテナクラス.*/
    template <class TObject>
    class Layer
    {
    public:
        std::vector<std::shared_ptr<TObject>> objectS;
        std::vector<std::shared_ptr<TObject>> suspendS;

        /**.*/
        void Add(TObject *object , int suspend = 0)
        {
            object->SetTimer(-suspend);

            if( object->GetTimer() >= 0 )
            {
                this->objectS.push_back( std::shared_ptr<TObject>(object) );
            }else{
                this->suspendS.push_back( std::shared_ptr<TObject>(object) );
            }
        }

        /**.*/
        void Update( )
        {
            auto it = suspendS.begin();

            while( it != suspendS.end() )
            {
                (*it)->SetTimer( (*it)->GetTimer() + 1 );
                if( (*it)->GetTimer() >= 0 )
                {
                    objectS.push_back( (*it) );
                    it = suspendS.erase( it );
                    continue;
                }
                ++it;
            }

            for (unsigned int i = 0; i < objectS.size(); i++)
            {
                objectS[i]->Update();
            }
        }

        void Draw()
        {
            for( auto it : objectS )
            {
                it->Draw();
            }
        }

        void DrawShadow(double X座標ずれ , double Y座標ずれ )
        {
            for( auto it : objectS )
            {
                it->DrawShadow( X座標ずれ , Y座標ずれ);
            }
        }

        void ExeRemove(Rect* area)
        {
            for (unsigned int i = 0; i < objectS.size(); i++)
            {
                objectS[i]->RemoveCheck(area);
            }

            auto it = objectS.begin();
            while( it != objectS.end() )
            {
                if( (*it)->GetRemoveFlag() )
                {
                    it = objectS.erase( it );                    
                }else{
                    ++it;
                }
            }
        }

        void Clear()
        {
            objectS.clear();
            suspendS.clear();
        }

        int GetCount()
        {
            return (int)objectS.size();
        }

        TObject* GetNearest(Object* object)
        {
            double nearest = -1;
            TObject* nearObject = nullptr;

            for( auto it : objectS )
            {
                double dist = object->GetDistance( it.get() );
                if( dist < nearest || nearest == -1)
                {
                    nearest = dist;
                    nearObject = it.get();
                }
            }

            return nearObject;
        }

        template<class TLayer>
        void Hit( Layer<TLayer> &layer)
        {
            for (unsigned int i = 0; i < objectS.size(); ++i)
            {
                for (unsigned int j = 0; j < layer.objectS.size(); ++j)
                {
                    if (layer.objectS[j]->GetRemoveFlag()) continue;

                    if (objectS[i]->Hit( layer.objectS[j].get() ))
                    {
                        objectS[i]->Attack(layer.objectS[j].get());
                        layer.objectS[j]->Attack(objectS[i].get());
                    }
                }

            }
        }
            
        void Hit( Object* objcet )
        {
            for (unsigned int i = 0; i < objectS.size(); ++i)
            {
                if( objectS[i]->GetRemoveFlag() ) continue;

                if (objectS[i]->Hit(objcet))
                {
                    objectS[i]->Attack(objcet);
                    objcet->Attack(objectS[i].get());
                }
            }
        }

        TObject* operator[](int index)
        {
            return objectS[index].get();
        }

    };
}