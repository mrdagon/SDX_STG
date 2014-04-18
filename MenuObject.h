#pragma once//☀SDX_STG
namespace SDX_STG
{
    using namespace SDX;

class MenuObject :public Object
{
public:
    MenuObject(double X座標, double Y座標 , double 幅 , double 高さ , const BmpFrame &フレーム画像 ) :
        Object(new Rect(X座標 , Y座標 , 幅 , 高さ,0,0), new SpFrame(&フレーム画像, 幅 , 高さ))
    {}

    std::string 説明文;

    virtual void Update()
    {
        Object::Update();
#ifdef TABLET
        isSelect = Hit();        
        if( isSelect && Input::mouse.Left.off) Push();
#endif
        if ( isSelect && Input::pad.Button1.on )
        {
            Push();
        }
    }

    virtual void Push(){}
};
}