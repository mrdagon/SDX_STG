#pragma once//☀SDX_STG
#include <SDXFrameWork.h>
#include "Menu.h"
#include "Event.h"
#include "StgSystem.h"
#include "Material.h"

#include "TestStage.h"
#include "Texts.h"

namespace SDX_STG
{
    using namespace SDX;
namespace 画面
{
    class 機体選択 : public Menu
    {
        class 機体ボタン : public MenuObject
        {
        private:
            int 機体番号;
        public:
            機体ボタン(double X座標, double Y座標 , int 機体番号 , const char* ボタン名) :
                MenuObject( X座標 , Y座標 , 240 , 46 , MFrame::BMPフレーム[2]),
                機体番号(機体番号)
            {

                Add( new SpFrame(&MFrame::BMPフレーム[9],236, 42) );
                Add( new SpFont(&MFont::ゴシック, Color::White, 1, 1, ボタン名 ) );

                if(機体番号 == 1) Add( new SpImage( MYukkuri::れいむA[0] ) );
                if(機体番号 == 2) Add( new SpImage( MYukkuri::まりさ[0] ) );
                if(機体番号 == 3) Add( new SpImage( MYukkuri::れみりゃ[0] ) );

                sprites[1]->MoveGap( 2, 2);
                sprites[2]->MoveGap(90,11);
                sprites[3]->MoveGap(40,23);
            }
        
            virtual void Draw() const
            {
                sprites[1]->isVisible = isSelect;
                if(isSelect)
                {
                    sprites[2]->SetColor(Color::Blue);
                }else{
                    sprites[2]->SetColor(Color::White);
                }

                Object::Draw();
            }

            void Push()
            {
                if( !SMenu->IsActive() ) return;

                StgSystem::自機タイプ = 機体番号;
                SMenu->isEnd = true;
                Director::GetScene(1)->isEnd = true;

                switch(StgSystem::選択ステージ)
                {
                    case 0:Director::AddScene( new Stage() ); break;
                    case 1:Director::AddScene( new TestStage() ); break;
                    case 2:Director::AddScene( new TestStage() ); break;
                    case 3:Director::AddScene( new TestStage() ); break;
                    case 4:Director::AddScene( new TestStage() ); break;
                    case 5:Director::AddScene( new TestStage() ); break;
                }
            }
        };

        void Init()
        {
            SetNow();
            SetItemCount(1,4);
            auto funcA = [&]{ isEnd = true ; };
            auto funcB = [&]{ isEnd = true ; };
            
            SetActive(true);

            AddBack(new 裏画面(Director::GetScene(0)) );
            AddBack(new 暗幕(128));
            //選択可能なオブジェクト
            Add(new 機体ボタン( 280, 137 , 1 , "れいむ"    ));
            Add(new 機体ボタン( 280, 187 , 2 , "まりさ"    ));
            Add(new 機体ボタン( 280, 237 , 3 , "れみりゃ" ));
            Add(new 選択枠(      310, 287 , 180 , 40 , "  戻る"     , funcB ));
        }
    };

    class 仕事 : public Menu
    {
    private:
        class 仕事ボタン : public MenuObject
        {
        private:
            int ステージ番号;
            int 難易度;
        public:
            仕事ボタン(int ステージ番号 , int 難易度 ) :
                MenuObject( 360 + 難易度 * 50 , 67 + ステージ番号*50 , 46 , 46 , MFrame::BMPフレーム[2]),
                ステージ番号(ステージ番号),
                難易度(難易度)
            {            
                Add( new SpFrame(&MFrame::BMPフレーム[9],42, 42) );
                switch(難易度)
                {
                    case 0:Add( new SpFont(&MFont::ゴシック,Color::White,1,1,"ゆ") );break;
                    case 1:Add( new SpFont(&MFont::ゴシック,Color::White,1,1,"っ") );break;
                    case 2:Add( new SpFont(&MFont::ゴシック,Color::White,1,1,"く") );break;
                    case 3:Add( new SpFont(&MFont::ゴシック,Color::White,1,1,"り") );break;
                    default:
                        Add( new SpFont(&MFont::ゴシック,Color::White,1,1,"？") );break;
                    break;
                }

                sprites[1]->MoveGap(2,2);
                sprites[2]->MoveGap(13,13);
            }

            virtual void Draw() const
            {
                sprites[1]->isVisible = isSelect;
                if(isSelect)
                {
                    sprites[2]->SetColor(Color::Blue);
                }else{
                    sprites[2]->SetColor(Color::White);
                }
                Object::Draw();
            }

            void Push()
            {
                if( !SMenu->IsActive() ) return;

                StgSystem::選択ステージ = ステージ番号;
                StgSystem::難易度 = 難易度;
                Director::AddScene( new 機体選択() );
            }    
        };

    public:
        void Init()
        {
            InitDefault("仕事を選んで下さい");
            SetItemCount(4,7);

            auto funcB = [&]{ isEnd = true; };

            for(int i=0;i<6;++i)
            {
                Add( new エフェクト(&MFrame::BMPフレーム[2],250, 67 + i * 50,106,46) );
                Add( new エフェクト(&MFont::ゴシック, 250+11, 67 + i * 50+11,Color::White,1,{"Stage ", i+1}) );
            }

            //選択可能なオブジェクト
            for( int i=0 ; i<6*4 ; ++i )
            {
                Add(new 仕事ボタン( i/4 , i%4 ) );            
            }

            Add(new 選択枠(310, 367 , 180 , 40 , "  戻る"     , funcB, true));
        }
    };

    class 強化選択 : public Menu
    {
    public:
        強化選択(int 武器ID )
        {
            SetNow();
            SetActive(true);

            AddBack(new 裏画面( Director::GetScene(0) ) );
            AddBack(new 暗幕(128));
        
            Add( new エフェクト(&MFrame::BMPフレーム[2],200,210,400,50));

            if(武器ID == -1)
            {
                //素材が不足
                SetItemCount(1,1);
                Add( new エフェクト(&MFont::ゴシック,234,222,Color::White,1,"素材が不足しています"));
                Add(new 選択枠( 410, 307  , 180 , 40 , "はい" , [&]{isEnd = true;} ));
                return;
            }

            SetItemCount(2,1);

            auto 武器強化 = [=]
            {
                ItemData::Data& dat = ItemData::dataS[武器ID];
                //必要素材
                for(int i=0;i<3;++i)
                {
                    const int 素材ID = dat.種類計算(i);
                    const int 必要数 = dat.必要数計算(i);
                    StgSystem::素材数[素材ID] -= 必要数;
                }
                ItemData::dataS[武器ID].強化レベル++;
                isEnd = true;
            };

            Add( new エフェクト(&MFont::ゴシック,234,222,Color::White,1,"素材を消費して強化しますか？"));

            //選択可能なオブジェクト
            Add(new 選択枠(         210, 307 , 180 , 40  , "はい"     , 武器強化 ));
            Add(new 選択枠(         410, 307 , 180 , 40  , "いいえ" , [&](){isEnd = true;} ));
        }
    };

    class 武器屋 : public Menu
    {
    private:
        class 開発プラン : public MenuObject
        {
            int 装備ID;
        public:
            開発プラン( int X座標 , int Y座標 , int 装備ID ) :
                装備ID(装備ID),
                MenuObject( X座標 , Y座標 , 40 , 40 , MFrame::BMPフレーム[2] )
            {
                Add( new SpFrame(&MFrame::BMPフレーム[9],36,36));
                switch(装備ID)
                {
                    case  0: Add( new SpImage( &MIcon::れいむ ));break;
                    case  1: Add( new SpImage( &MIcon::すいか ));break;
                    case  2: Add( new SpImage( &MIcon::てんこ ));break;

                    case  3: Add( new SpImage( &MIcon::まりさ ));break;
                    case  4: Add( new SpImage( &MIcon::ありす ));break;
                    case  5: Add( new SpImage( &MIcon::ぱちぇ ));break;

                    case  6: Add( new SpImage( &MIcon::れみりゃ ));break;
                    case  7: Add( new SpImage( &MIcon::ふらん ));break;
                    case  8: Add( new SpImage( &MIcon::さくや ));break;

                    case  9: Add( new SpImage( &MIcon::てい ));break;//レアドロップ+
                    case 10: Add( new SpImage( &MIcon::ちるの ));break;//当たり判定小
                    case 11: Add( new SpImage( &MIcon::ゆうぎ ));break;//必殺時間+
                    case 12: Add( new SpImage( &MIcon::ゆーびぃ ));break;//吸い寄せ+
                    case 13: Add( new SpImage( &MIcon::テルヨフ ));break;//自然回復+
                    case 14: Add( new SpImage( &MIcon::いくさん ));break;//底力+
                }

                sprites[1]->MoveGap(2,2);
                sprites[2]->MoveGap(20,20);
            }

            void Draw() const
            {
                MenuObject::Draw();
                sprites[1]->isVisible = isSelect;
            
                //Add(new エフェクト(&MFrame::BMPフレーム,340,85,270,285));
                if(isSelect)
                {              
                    ItemData::Data* dat = &ItemData::dataS[装備ID];

                    MFrame::BMPフレーム[2].Draw(350,  95 ,250,40);     
                    MFrame::BMPフレーム[2].Draw(350, 140 ,250,40);

                    MFont::ゴシック.Draw(360, 101,Color::White, Texts::装備[装備ID].name);
                    MFont::ゴシック小.Draw(360,144,Color::White, Texts::装備[装備ID].info);

                    //必要素材
                    for(int i=0;i<3;++i)
                    {
                        const int dy = i*40 + 15;
                        const int 素材ID = dat->種類計算(i);
                        const int 必要数 = dat->必要数計算(i);

                        if(必要数 == 0 ) continue;

                        MFrame::BMPフレーム[2].Draw(350,171 + dy, 30,30);//素材ICON                    
                        MFrame::BMPフレーム[2].Draw(385,168 + dy,215,36);//素材名前枠

                        MFont::ゴシック小.DrawExtend(510,174 + dy ,1,1,Color::White , "所持     必要");

                        MItem::imageS[素材ID]->DrawRotate(365,186 + dy , 1 , 0);
                        MFont::ゴシック.Draw(395,174 + dy,Color::White, Texts::素材[素材ID].name );
                        MFont::ゴシック.Draw(540,174 + dy,Color::White, "/" );
                    
                        if( StgSystem::素材数[素材ID] >= 必要数)
                        {
                            MFont::白絵.DrawExtend(496,190 + dy ,1,1,Color::White , { std::setw(5) , StgSystem::素材数[素材ID] } );
                        }else{
                            MFont::白絵.DrawExtend(496,190 + dy ,1,1,Color::Red   , { std::setw(5) , StgSystem::素材数[素材ID] } );
                        }

                        MFont::白絵.DrawExtend(548,190 + dy ,1,1,Color::White , { std::setw(5) , 必要数 } );
                    }

                    //ラベル
                    std::string 項目;
                    double 改良前 = ItemData::dataS[装備ID].Get();
                    double 改良後 = ItemData::dataS[装備ID].Get(1);
                    switch(装備ID)
                    {
                        case  0:case 3:case 6: 項目 = "耐久";
                            break;
                        case  1:case 2:case 4:
                        case  5:case 7:case 8: 項目 = "攻撃";
                            break;
                        case  9:項目 = "幸運";break;
                        case 10:項目 = "縮小";break;
                        case 11:項目 = "攻撃";break;
                        case 12:項目 = "回収";break;
                        case 13:項目 = "修復";break;
                        case 14:項目 = "耐久";break;                
                    }

                    MFont::ゴシック.Draw(350,305,Color::White,"レベル");
                    MFont::ゴシック.Draw(362,335,Color::White, 項目);
                
                    MFont::白絵.DrawExtend(430,310,2,2, Color::White,{ std::setw(4), dat->強化レベル });
                    MFont::白絵.DrawExtend(520,310,2,2,{120,255,120},{ std::setw(5), dat->強化レベル + 1});

                    MFont::ゴシック.Draw(500,305,Color::White,">>");
                    MFont::ゴシック.Draw(500,335,Color::White,">>");

                    MFont::白絵.DrawExtend(430,340,2,2, Color::White,{ std::setw(4),改良前});
                    MFont::白絵.DrawExtend(520,340,2,2,{120,255,120},{ std::setw(5),改良後});
                }
            }

            void Push()
            {
                if( !SMenu->IsActive() ) return;

                ItemData::Data* dat = &ItemData::dataS[装備ID];
                //必要素材
                for(int i=0;i<3;++i)
                {
                    const int 素材ID = dat->種類計算(i);
                    const int 必要数 = dat->必要数計算(i);

                    if(  StgSystem::素材数[素材ID] < 必要数 )
                    {
                        Director::AddScene( new 強化選択(-1));//素材不足
                        return;
                    }
                }

                Director::AddScene( new 強化選択(装備ID));
            }
        };

    public:
        void Init()
        {
            InitDefault("改造する装備を選んで下さい");
            SetItemCount(3,6);

            auto funcA = [&]{ isEnd = true; };
            //選択すると左に現在性能と強化後性能、必要素材を表示
            AddBack(new エフェクト(&MFrame::BMPフレーム[2],340,85,270,285));

            //Body3種
            //Add(new エフェクト(&MFont::白絵, 40 , 70 ,Color::Blue,2,"Body"));
            Add(new 開発プラン(190,85, 0 ));
            Add(new 開発プラン(240,85, 1 ));
            Add(new 開発プラン(290,85, 2 ));

            //MainWepon武器6種
            //Add(new エフェクト(&MFont::白絵, 35 , 135 ,Color::Blue,2,"Front"));
            Add(new 開発プラン(190,150, 3 ));
            Add(new 開発プラン(240,150, 4 ));
            Add(new 開発プラン(290,150, 5 ));

            //SideWepon
            //Add(new エフェクト(&MFont::白絵, 40 , 200 ,Color::Red,2,"Side"));
            Add(new 開発プラン(190,215, 6));
            Add(new 開発プラン(240,215, 7));
            Add(new 開発プラン(290,215, 8));

            //Option
            //Add(new エフェクト(&MFont::白絵, 30 , 265 ,Color::Blue,2,"Option"));
            Add(new 開発プラン(190,280, 9));
            Add(new 開発プラン(240,280,10));
            Add(new 開発プラン(290,280,11));

            Add(new 開発プラン(190,330,12));
            Add(new 開発プラン(240,330,13));
            Add(new 開発プラン(290,330,14));

            //選択可能なオブジェクト
            Add(new 選択枠( 310, 380 , 180 , 40 , "  戻る"     , funcA, true));
        }
    };

    class 倉庫 : public Menu
    {
        class 素材アイコン : public MenuObject
        {
            int 素材ID;
        public:
            素材アイコン( int X座標 , int Y座標 , int 素材ID) :
                MenuObject( X座標 , Y座標 , 60 , 30 , MFrame::BMPフレーム[2]),
                素材ID(素材ID)
            {
                説明文 = Texts::素材[素材ID].info;
                Add( new SpFrame(&MFrame::BMPフレーム[9],56,26));
                Add( new SpImage(MItem::imageS[素材ID]));
                sprites[1]->MoveGap(2,2);
                sprites[2]->MoveGap(15,15);
            }

            void Draw() const
            {
                sprites[1]->isVisible = isSelect;
                MenuObject::Draw();

                MFont::白絵.Draw((int)GetX()+25,(int)GetY()+15,Color::White,{ std::setw(4) , StgSystem::素材数[素材ID] });
            }
        };

    public:
        void Init()
        {
            InitDefault("素材の数を確認出来ます");
            SetItemCount(6,7);

            auto funcA = [&]{ isEnd = true; };
            //一覧と数を表示

            //カテゴリ1
            //素材4種
            //資金4種

            //ゼリー4種 - ボディ系
            //コア4種 - 武器
                
            //レアアイテム
            //6面        

            //選択可能なオブジェクト
            for(int i=0;i<36;++i)
            {
                Add(new 素材アイコン( 220 + i%6 * 60 , 150 + i/6 * 30 , i ) );            
            }
            Add(new 選択枠(310, 370 , 180 , 40 , "  戻る", funcA, true));

        }
    };

    class 戦績 : public Menu
    {
    public:
        class 勲章枠 : public MenuObject
        {
        public:
            勲章枠( int X座標 , int Y座標 ,int 勲章ID) :
                MenuObject( X座標 , Y座標 , 160 , 40 , MFrame::BMPフレーム[2] )
            {
            
                説明文 = Texts::勲章[勲章ID].info;

                Add( new SpFrame(&MFrame::BMPフレーム[9], 156 , 36));
                Add( new SpImage(&MIcon::いくさん));
                Add( new SpFont(&MFont::ゴシック,Color::White,1,1, Texts::勲章[勲章ID].name ));
                sprites[1]->MoveGap(2,2);
                sprites[2]->MoveGap(20,20);
                sprites[3]->MoveGap(40,8);
            }

            void Draw() const
            {    
                sprites[1]->isVisible = isSelect;
                if(isSelect)
                {
                    sprites[3]->SetColor(Color::Blue);
                }else{
                    sprites[3]->SetColor(Color::White);
                }

                MenuObject::Draw();
            }
        };

        void Init()
        {
            InitDefault("条件を満たすと、職歴を得ます");
            SetItemCount(3,6);

            auto funcA = [&]{ isEnd = true; };

            //選択可能なオブジェクト
            for(int i=0;i<15;++i)
            {
                Add(new 勲章枠( 150 +i %3 * 170 , 70+i/3*50 , i ));
            }

            Add(new 選択枠(310 , 320 , 180 , 40  , " 戻る"     , funcA, true));
        }
    };

    class システム : public Menu
    {
    public:
        class 音量枠 : public 選択枠
        {
        public:
            int &音量;
        
            音量枠(double X座標, double Y座標 , const char* 描画する文字列 , int& 音量):
                選択枠( X座標 , Y座標 , 180 , 40 , 描画する文字列, nullptr , false ),
                音量(音量)
            {}

            virtual void Draw() const
            {
                選択枠::Draw();
                MFont::ゴシック.Draw((int)GetX() + 120,(int)GetY()+7 ,Color::White, { std::setw(3) , 音量 * 10});

                MFrame::BMPフレーム[2].Draw((int)GetX() + 180 ,(int)GetY(), 220 , 40 );
                for(int i=0;i<音量;++i)
                {
                    Drawing::Rect((int)GetX() + 195 + i * 19 , (int)GetY() +5 , 17 , 30, Color::Red , true);            
                }
            }

            virtual void Update()
            {
                選択枠::Update();

    #ifdef TABLET
                if( Input::mouse.Left.hold &&
                    Input::mouse.x > GetX() + 180 &&
                    Input::mouse.x < GetX() + 400 &&
                    Input::mouse.y > GetY() &&
                    Input::mouse.y < GetY() + 40
                    )
                {
                    音量 = ( Input::mouse.x - 180 - this->GetX() ) / 20;
                }
    #endif
                //非選択時は処理しない
                if( !isSelect ) return;

                if(Input::pad.Left.on)  音量 = std::max(0 , 音量-1);
                if(Input::pad.Right.on) 音量 = std::min(10, 音量+1);
            }
        };

        void Init()
        {
            InitDefault("音量を設定します");
            SetItemCount(1,4);

            Add(new 音量枠(200, 170 , "ＢＧＭ"    , Config::BGM音量));
            Add(new 音量枠(200, 220 , "効果音"    , Config::効果音量));
            Add(new 音量枠(200, 270 , "ボイス"    , Config::ゆっくりボイス));

            Add(new 選択枠(310, 320  , 180 , 40 , "戻る"    , [&]{ isEnd = true; } , true));
        }
    };

    class ホーム : public Menu
    {
    public:
        void Init()
        {
            InitDefault("ゆっくりしていってね！！！");
            SetItemCount(1,5);

            isCancel = false;

            auto funcA = [&] { Add(new 暗幕(255)); Director::AddScene(new 画面::仕事()); };
            auto funcB = [&] { Add(new 暗幕(255)); Director::AddScene(new 画面::武器屋());};
            auto funcC = [&] { Add(new 暗幕(255)); Director::AddScene(new 画面::倉庫());};
            auto funcD = [&] { Add(new 暗幕(255)); Director::AddScene(new 画面::戦績());};
            auto funcE = [&] { Add(new 暗幕(255)); Director::AddScene(new 画面::システム());};
    
            //選択可能なオブジェクト
            Add(new 選択枠(310, 120 , 180 , 40  , " ハロワ ", funcA , true));
            Add(new 選択枠(310, 170 , 180 , 40  , " 武器屋 ", funcB , true));
            Add(new 選択枠(310, 220 , 180 , 40  , "  倉庫　", funcC , true));
            Add(new 選択枠(310, 270 , 180 , 40  , "  職歴  ", funcD , true));
            Add(new 選択枠(310, 320 , 180 , 40  , "　設定　", funcE , true));
        }
    };

}
}