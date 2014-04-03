#pragma once
#include "Menu.h"

namespace SDX
{
	class 裏画面 : public Object
	{
	private:
		IScene* 描画シーン = nullptr;
	public:
		裏画面( IScene* 描画シーン):
			Object(nullptr,nullptr),
			描画シーン(描画シーン)
		{}

		void Draw() const
		{
			Menu* 現在のメニュー = Menu::Now();
			描画シーン->Draw();
			現在のメニュー->SetNow();			
		}
	};

	class 暗幕 : public Object
	{
	public:
		int 暗さ;
		int 暗さ変化量 = 0;
		bool 暗転フラグ;
		std::function<void()> 消滅時の処理;
		Color 暗転色;

		/**暗さ = 0 なら徐々に暗くなる.*/
		暗幕(int 暗さ , Color 暗転色 = Color::Black , std::function<void()> 消滅時の処理 = nullptr) :
			Object(nullptr, nullptr),
			暗転色(暗転色),
			暗さ(暗さ),
			消滅時の処理(消滅時の処理)
		{
			if(暗さ >= 255)
			{
				暗さ変化量 = -15;
				Menu::SetActive(false);			
			}
			else if(暗さ <= 0)
			{
				暗さ変化量 = 15;
				Menu::SetActive(false);								
			}
		}

		virtual void Draw() const
		{
			Screen::SetBlendMode(BlendMode::Alpha, 暗さ);
			Drawing::Rect(0, 0, 800, 600, Color::Black, true);
			Screen::SetBlendMode(BlendMode::Alpha, 255);
		}

		virtual void Update()
		{
			Object::Update();
			暗さ += 暗さ変化量;

			if(暗さ < -15 || 暗さ > 270)
			{
				this->isRemove = true;
			}
			else if (暗さ < 0 || 暗さ > 255)
			{
				Menu::SetActive(true);
				if (消滅時の処理) 消滅時の処理();
			}
		}
	};

	class 選択枠 : public MenuObject
	{
	public:
		std::function<void()> 押下時の処理;
		bool 暗転フラグ;

		選択枠(double X座標, double Y座標 , double 幅 , double 高さ, const char* 描画する文字列, std::function<void()> 押下時の処理, bool 暗転フラグ = false) :
			MenuObject( X座標 , Y座標 , 幅 , 高さ, MFrame::BMPフレーム[2] ),
			押下時の処理(押下時の処理),
			暗転フラグ(暗転フラグ)
		{
			Add( new SpFrame(&MFrame::BMPフレーム[9],176, 36) );
			Add(new SpFont(&MFont::ゴシック, Color::White, 1, 1, 描画する文字列));

			sprites[1]->MoveGap( 2,2);
			sprites[2]->MoveGap(40,7);
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
			if( !押下時の処理 || !Menu::IsActive() ) return;

			if (暗転フラグ)
			{
				Menu::AddFront(new 暗幕(0, Color::Black, 押下時の処理));
			}
			else
			{
				 押下時の処理();
			}
		}
	};

	class メッセージ枠 : public Object
	{
	public:
		//説明メッセージ

		メッセージ枠( const char* 描画する文字列) :
			Object( new Point(150, 440) , new SpFrame(&MFrame::BMPフレーム[0], 500 , 150) )
		{
			Menu::Message() = 描画する文字列;
			auto 表示文字 = new SpFont(&MFont::ゴシック, Color::Black, 1, 1, Menu::Message() );
			表示文字->MoveGap(20, 32);
			Add(表示文字);
		}
	};

}