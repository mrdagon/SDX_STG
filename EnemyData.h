#pragma once

namespace SDX
{

enum class EnemyID
{
	雑魚A,
	戦車,
	ビッグヘリ,
	MAX,	
};

struct EnemyData
{
public:
	static EnemyData data[(int)EnemyID::MAX];
	int 最大耐久;
	int スコア;
	int 物理;
	int 射撃;
	double 速さ;
	Shape* 当り判定;
	int ずれX;
	int ずれY;
	Sprite* 見た目;
	int 爆発アニメ;

    double レア率;
    bool ボスフラグ;

	static void Load()
	{
		File csvFile("File/csv/enemy.csv" , FileMode::Read );

        auto lineS = csvFile.GetCsvS();

		for (int i = 0; i < (int)EnemyID::MAX+1 ; ++i)
		{
			if( i == 0 ) continue;
			data[i-1].最大耐久 = atoi(lineS[i][1].c_str());
			data[i-1].スコア   = atoi(lineS[i][2].c_str());
			data[i-1].物理     = atoi(lineS[i][3].c_str());
			data[i-1].射撃     = atoi(lineS[i][4].c_str());

            data[i-1].レア率     = 0.05;

			int 種類 = atoi(lineS[i][5].c_str());
			int 幅   = atoi(lineS[i][6].c_str());
			int 高さ = atoi(lineS[i][7].c_str());

			data[i-1].ずれX = atoi(lineS[i][8].c_str());
			data[i-1].ずれY = atoi(lineS[i][9].c_str());
			//図形生成
			switch (種類)
			{
				case 0:
					data[i-1].当り判定 = new Circle( 0 , 0 , 幅 );
				break;
				case 1:
					data[i-1].当り判定 = new Rect( 0 , 0 , 幅 , 高さ );
				break;
			}
			data[i - 1].爆発アニメ = 5;
            data[i-1].ボスフラグ = (i == 3);
		}
	}
};
}