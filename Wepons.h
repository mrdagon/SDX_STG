#pragma once
#include "StgSystem.h"
#include "Material.h"
#include "Player.h"
#include "Wepon.h"
#include "Shots.h"

namespace SDX
{
namespace 武器
{
class すいか : public Wepon
{
public:
	すいか(Player* 親) :
		Wepon(親, &MIcon::すいか, ItemData::すいか)
	{
        レベル = 1 + std::min( ItemData::dataS[ItemData::すいか].強化レベル / 20 , 3 );
    }

	//前方でフィーバーしている
	void 発射LV1()
	{
		射撃(0.5 ,-7, 0, 20,  0, &MShot::ビーム短);
		射撃(0.5 , 7, 0, 20,  0, &MShot::ビーム短);
	}
	void 発射LV2()
	{
		射撃(0.4 , 7 * 左右, 0, 20,  0, &MShot::ビーム短);
		射撃(0.6 , -7 * 左右, 0, 20,  0, &MShot::ビーム中);
	}

	void 発射LV3()
	{
		射撃(0.25, 10 * 左右, 0, 20,  0, &MShot::ビーム短);
		射撃(0.35, 0, 0, 20,  0, &MShot::ビーム中);
		射撃(0.4, -10 * 左右, 0, 20, 0, &MShot::ビーム中);
	}

	void 発射LV4()
	{
		射撃(0.2 , 20 * 左右, 0, 20, 0, &MShot::ビーム短);
		射撃(0.25, 10 * 左右, 0, 20, 0, &MShot::ビーム中);
		射撃(0.25, 0, 0, 20, 0, &MShot::ビーム中);
		射撃(0.3 , -10 * 左右, 0, 20, 0, &MShot::ビーム長);
	}

};
class てんこ : public Wepon
{
public:
	てんこ(Player* 親) :
		Wepon(親, &MIcon::てんこ, ItemData::てんこ)
	{
        レベル = 1 + std::min( ItemData::dataS[ItemData::てんこ].強化レベル / 20 , 3 );
    }

	//炸裂弾+通常弾やや斜め
	void 発射LV1()
	{
		const double 角度 = 0.1;

		射撃( 0.5 , 0 , 0 , 4 , 0.5 , 角度 , MEffect::プラズマ[5][3]);
		射撃( 0.5 , 0 , 0 , 4 , 0.5 , -角度 , MEffect::プラズマ[5][3]);
	}
	void 発射LV2()
	{
		const double 角度 = 0.15;

		射撃( 0.3 , 0 , 0 , 4 , 0.5 , 角度 , MEffect::プラズマ[5][3]);
		射撃( 0.4 , 0 , 0 , 4 , 0.5 , 0, MEffect::プラズマ[5][1]);
		射撃( 0.3 , 0 , 0 , 4 , 0.5 , -角度, MEffect::プラズマ[5][3]);
	}

	void 発射LV3()
	{
		const double 角度 = 0.1;

		射撃(0.2,0, 0, 4, 0.5, 角度 * 2 , MEffect::プラズマ[5][3]);
		射撃(0.3,0, 0, 4, 0.5, 角度 , MEffect::プラズマ[5][1]);
		射撃(0.3,0, 0, 4, 0.5, -角度 , MEffect::プラズマ[5][1]);
		射撃(0.2,0, 0, 4, 0.5, -角度 * 2 , MEffect::プラズマ[5][3]);
	}

	void 発射LV4()
	{
		const double 角度 = 0.15;

		射撃(0.15, 0, 0, 4, 0.5, 角度 * 2 , MEffect::プラズマ[5][3]);
		射撃(0.2 , 0, 0, 4, 0.5, 角度 , MEffect::プラズマ[5][1]);
		射撃(0.3 , 0, 0, 4, 0.5, 0, MEffect::プラズマ[5][0]);
		射撃(0.2 , 0, 0, 4, 0.5, -角度 , MEffect::プラズマ[5][1]);
		射撃(0.15, 0, 0, 4, 0.5, -角度 * 2 , MEffect::プラズマ[5][3]);
	}

};

class ありす : public Wepon
{
public:
	ありす(Player* 親) :
		Wepon(親, &MIcon::ありす, ItemData::ありす)
	{
        レベル = 1 + std::min( ItemData::dataS[ItemData::ありす].強化レベル / 20 , 3 );
    }

	//広がり弾
	void 発射LV1()
	{
		射撃(0.25, 0, 0, 20, 0.1 * 左右, &MShot::ビーム短);
		射撃(0.25, 0, 0, 20, 0.05 * 左右, &MShot::ビーム短);
		射撃(0.25, 0, 0, 20, 0, &MShot::ビーム短);
		射撃(0.25, -10 * 左右, 0, 20, 0, &MShot::ビーム短);
	}
	void 発射LV2()
	{
		射撃(0.19, 0 , 0, 20, 0.15 * 左右, &MShot::ビーム短);
		射撃(0.19, 0 , 0, 20, 0.1 * 左右, &MShot::ビーム短);
		射撃(0.19, 0 , 0, 20, 0.05 * 左右, &MShot::ビーム短);
		射撃(0.19, 0 , 0, 20, 0, &MShot::ビーム短);
		射撃(0.24, -10 * 左右, 0, 20, 0, &MShot::ビーム中);
	}

	void 発射LV3()
	{
		射撃(0.15, 0, 0, 20, 0.20 * 左右, &MShot::ビーム短);
		射撃(0.15, 0, 0, 20, 0.15 * 左右, &MShot::ビーム短);
		射撃(0.15, 0, 0, 20, 0.1 * 左右, &MShot::ビーム短);
		射撃(0.15, 0, 0, 20, 0.05 * 左右, &MShot::ビーム中);
		射撃(0.2 , 0, 0, 20, 0, &MShot::ビーム中);
		射撃(0.2 , -10 * 左右, 0, 20,  0, &MShot::ビーム中);
	}

	void 発射LV4()
	{
		射撃( 0.1 , 0, 0, 20, 0.25 * 左右, &MShot::ビーム短);
		射撃( 0.1 , 0, 0, 20, 0.20 * 左右, &MShot::ビーム短);
		射撃( 0.1 , 0, 0, 20, 0.15 * 左右, &MShot::ビーム短);
		射撃( 0.15, 0, 0, 20, 0.1 * 左右, &MShot::ビーム中);
		射撃( 0.15, 0, 0, 20, 0.05 * 左右, &MShot::ビーム中);
		射撃( 0.2 , 0, 0, 20, 0, &MShot::ビーム長);
		射撃( 0.2 ,-10 * 左右, 0, 20,  0, &MShot::ビーム長);
	}

};
class ぱちぇ : public Wepon
{
public:
	ぱちぇ(Player* 親) :
		Wepon(親, &MIcon::ぱちぇ, ItemData::ぱちぇ)
	{
        レベル = 1 + std::min( ItemData::dataS[ItemData::ぱちぇ].強化レベル / 20 , 3 );
    }

	int 発射角度 = 0;

	//左右振り、通常弾
	void 発射LV1()
	{
		double 角度 = (発射角度) * 0.025 ;

		射撃( 0.5, 5, 0, 30, 角度, &MShot::ビーム短);
		射撃( 0.5,-5, 0, 30,  角度, &MShot::ビーム短);
	}

	void 発射LV2()
	{
		double 角度 = (発射角度)* 0.025 ;

		射撃( 0.3,5, 0, 30,  角度, &MShot::ビーム短);
		射撃( 0.4,0, 0, 30,  角度, &MShot::ビーム短);
		射撃( 0.3,-5, 0, 30,  角度, &MShot::ビーム短);
	}

	void 発射LV3()
	{
		double 角度 = (発射角度)* 0.025 ;

		射撃( 0.5 , 7, 0, 30,  角度, &MShot::ビーム中);
		射撃( 0.5 ,-7, 0, 30, 角度, &MShot::ビーム中);
	}

	void 発射LV4()
	{
		double 角度 = (発射角度)* 0.025 ;

		射撃( 0.5 ,10, 0, 30,  角度, &MShot::ビーム長);
		射撃( 0.5 , -10, 0, 30,  角度, &MShot::ビーム長);
	}

	void 待機()
	{
		if (Input::pad.Left.hold)
		{
			if (発射角度 > -40) --発射角度;
		}
		else if (Input::pad.Right.hold)
		{
			if (発射角度 < 40) ++発射角度;
		}
		else
		{
			if (発射角度 > 0) --発射角度;
			if (発射角度 < 0) ++発射角度;
		}
	}
};

class ふらん : public Wepon
{
public:
	ふらん(Player* 親) :
		Wepon(親, &MIcon::ふらん, ItemData::ふらん)
	{
        レベル = 1 + std::min( ItemData::dataS[ItemData::ふらん].強化レベル / 20 , 3 );
    }

	//前方射撃
	void 発射LV1()
	{
		射撃( 1, 0, 0, 25,  0, &MShot::ビーム中);
	}
	void 発射LV2()
	{
		射撃( 1,0, 0, 25,  0, &MShot::火);
	}

	void 発射LV3()
	{
		射撃( 0.5,-5, 0, 25,  0, &MShot::火);
		射撃( 0.5, 5, 0, 25, 0, &MShot::火);
	}

	void 発射LV4()
	{
		射撃( 0.3,-10, 0, 25,  0, &MShot::火);
		射撃( 0.4, 0, 0, 25, 0, &MShot::火);
		射撃( 0.3, 10, 0, 25, 0, &MShot::火);
	}

};
class さくや : public Wepon
{
public:
	さくや(Player *親 ) :
		Wepon(親 , &MIcon::さくや , ItemData::さくや )
	{
        レベル = 1 + std::min( ItemData::dataS[ItemData::さくや].強化レベル / 20 , 3 );
    }

	//サイド低速弾
	void 発射LV1()
	{
		int Xずれ = int(sin(timer*0.05) * 10);

		射撃( 0.5 ,-Xずれ, 0, 12,  0, &MShot::ビーム短);
		射撃( 0.5 , Xずれ, 0, 12, 0, &MShot::ビーム短);
	}
	void 発射LV2()
	{
		for (int i = 0; i < 3; ++i)
		{
			int Xずれ = int(sin(timer*0.05 + i * 2 * PAI / 3) * 10);
			射撃( 1.0/3,Xずれ , 0, 12,  0, &MShot::ビーム短);
		}
	}
	void 発射LV3()
	{
		for (int i = 0; i < 3; ++i)
		{
			int Xずれ = int(sin(timer*0.05 + i * 2 * PAI / 3) * 10);
			射撃(1.0 / 3,Xずれ, 0, 12, 0, &MShot::ビーム中);
		}
	}
	void 発射LV4()
	{
		for (int i = 0; i < 3; ++i)
		{
			int Xずれ = int(sin(timer*0.05 + i * 2 * PAI / 3) * 10);
			射撃(1.0 / 3,Xずれ, 0, 12, 0, &MShot::ビーム長);
		}
	}
};
}
}