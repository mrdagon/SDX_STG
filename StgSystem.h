#pragma once
#include <SDXFrameWork.h>

namespace SDX
{
namespace StgSystem
{
	static int 選択ステージ;
	static int 難易度;
	static int 自機タイプ;

	static int 現在スコア;
	static int 現在HP;
    static int 回復HP;
	static int 最大HP;
	static int 現在チャージ;

	static int 素材数[42];
	static int 最高スコア[6][4];
	static bool クリアフラグ[6][4];

	static int コンボ数;
	static int コンボ時間;

	static double 自然回復 = 0.1;
	static double 吸い寄せ範囲 = 1;
	static double レアドロップ率 = 0.01;

	static bool 勲章[15];

    static int 仕事回数の合計;
    static int 強化回数の合計;
}
namespace Config
{
	static int 効果音量;
	static int BGM音量;
	static int ゆっくりボイス;
}
namespace ItemData
{
    enum Type
    {
        れいむ,
        すいか,
        てんこ,
        
        まりさ,
        ありす,
        ぱちぇ,
        
        れみりゃ,
        ふらん,
        さくや,
        
        てい,//レアドロップ,
        ちるの,//当たり判定,
        ゆうぎ,//必殺時間,
        ゆーびぃ,//吸い寄せ,
        テルヨフ,//自然回復,
        いくさん//底力,
    };

	class Data
	{
        public:
        //素材3はレア確定
        Type 種類;
        int 必要素材[3];
        int 必要数[3];
		
		int 強化レベル = 1;
        //現在の性能を得る
        //ボディなら耐久
        //武器なら攻撃力
        //その他は補正値
        double Get(int レベル補正 = 0) const
        {
            const int レベル = 強化レベル + レベル補正;

            switch (種類)
            {
            case Type::れいむ:
                return 100 * (1.0 + レベル*0.03);
            case Type::すいか:
                return 100 * (1.0 + レベル*0.03);
            case Type::てんこ:
                return 100 * (1.0 + レベル*0.03);
            case Type::まりさ:
                return 100 * (1.0 + レベル*0.03);
            case Type::ありす:
                return 100 * (1.0 + レベル*0.03);
            case Type::ぱちぇ:
                return 100 * (1.0 + レベル*0.03);
            case Type::れみりゃ:
                return 100 * (1.0 + レベル*0.03);
            case Type::ふらん:
                return 100 * (1.0 + レベル*0.03);
            case Type::さくや:
                return 100 * (1.0 + レベル*0.03);
            case Type::てい://レアドロップ
                return 100 * (1.0 + レベル*0.02);
            case Type::ちるの://当たり判定
                return 100 * (1.0 + レベル*0.02);
            case Type::ゆうぎ://攻撃補正
                return 100 + レベル;
            case Type::ゆーびぃ://吸い寄せ
                return 100 * (1.0 + レベル*0.02);
            case Type::テルヨフ://自然回復
                return 100 * (1.0 + レベル*0.04);
            case Type::いくさん://耐久補正
                return レベル;
            }
            return 0;
        }

        //武器専用パラメータ
        int 連射力 = 10;

        int 必要数計算(int 番号)
        {
            if( 強化レベル % 5 != 0 && 番号 == 2 && 強化レベル < 50 ) return 0;

            return 必要数[番号] * ( 5 + 強化レベル ) / 5;            
        }
        int 種類計算(int 番号)
        {
            //レベル10毎に種類が変化
            //レベル5の倍数時はレア素材要求
            int no = 必要素材[番号];//0～5
            int ランク = std::min(強化レベル/20 , 3);

            //1つ目、資金or素材

            //0~4ステージ別,5共通
            switch (番号)
            {
                case 0:
                    return std::min(強化レベル/20 , 3) + no * 6;
                break;
                case 1:
                    return std::min((強化レベル+5)/20 , 3) + no * 6;
                break;
                case 2:
                    if(強化レベル > 50 && 強化レベル % 5 == 0 ) return 35;

                    return std::min(強化レベル/30 , 1) + no * 6 + 4;
                break;
            }
            return 0;
        }
	};
    
    static Data dataS[15];

    static void Load()
    {
        File csvFile("File/csv/wepon.csv" , FileMode::Read );

		auto lineS = csvFile.GetCsvS();//1行目飛ばす

        for(int i=0;i<15;++i)
        {
            ItemData::dataS[i].種類 = Type(i);
            ItemData::dataS[i].連射力 = atoi( lineS[i+1][4].c_str() );
            ItemData::dataS[i].強化レベル = 1;
            ItemData::dataS[i].必要素材[0] = atoi( lineS[i+1][1].c_str() );
            ItemData::dataS[i].必要素材[1] = atoi( lineS[i+1][2].c_str() );
            ItemData::dataS[i].必要素材[2] = atoi( lineS[i+1][3].c_str() );
            ItemData::dataS[i].必要数[0] = 10;
            ItemData::dataS[i].必要数[1] = 5;
            ItemData::dataS[i].必要数[2] = 1;
        }
    }
}

namespace StgSystem
{
    //記録するデータ

    //合計仕事回数
    //合計強化回数

    static void SaveData(FileMode 読込or書込)
    {
        File file("save.dat", 読込or書込 , true , SaveMode::Internal);

        //ファイルオープンに失敗
        if( file.GetFileMode() == FileMode::None ) return;

        file.ReadWrite(StgSystem::最高スコア);
        file.ReadWrite(StgSystem::クリアフラグ);       
        file.ReadWrite(StgSystem::勲章);
        file.ReadWrite(StgSystem::仕事回数の合計);
        file.ReadWrite(StgSystem::強化回数の合計);       
        file.ReadWrite(StgSystem::素材数);

        file.ReadWrite(Config::BGM音量);
        file.ReadWrite(Config::ゆっくりボイス);
        file.ReadWrite(Config::効果音量);
        for(int i=0;i<15;++i) file.ReadWrite(ItemData::dataS[i].強化レベル);
    }
}

}