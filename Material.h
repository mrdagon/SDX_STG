#pragma once//☀SDX_STG
#include <SDXFrameWork.h>

namespace SDX_STG
{
    using namespace SDX;

namespace MIcon
{
    static Image ゆーびぃ;
    static Image ふらん;
    static Image さくや;
    static Image れみりゃ;
    static Image きめぇまる;
    static Image ありす;
    static Image まりさ;
    static Image れいむ;
    static Image ちるの;
    static Image ぱちぇ;
    static Image いくさん;
    static Image てんこ;
    static Image ゆうぎ;
    static Image すいか;
    static Image テルヨフ;
    static Image うどんげ;
    static Image てい;
    static ImagePack 素材;

    static void Load()
    {
        ゆーびぃ.Load("File/icon/icon000.png");
        ふらん.Load("File/icon/icon001.png");
        さくや.Load("File/icon/icon002.png");
        れみりゃ.Load("File/icon/icon003.png");
        きめぇまる.Load("File/icon/icon004.png");

        ありす.Load("File/icon/icon005.png");
        まりさ.Load("File/icon/icon006.png");
        れいむ.Load("File/icon/icon007.png");
        ちるの.Load("File/icon/icon008.png");
        いくさん.Load("File/icon/icon009.png");

        ぱちぇ.Load("File/icon/icon010.png");
        てんこ.Load("File/icon/icon011.png");
        てい.Load("File/icon/icon012.png");
        ゆうぎ.Load("File/icon/icon013.png");
        すいか.Load("File/icon/icon014.png");

        テルヨフ.Load("File/icon/icon015.png");
        うどんげ.Load("File/icon/icon016.png");
    }
};

namespace MEnemy
{
    static Image 雑魚機;
    static Anime 小型機[8];
    static Anime 戦車;
    static Image 戦車砲A;
    static Image 戦車砲B;

    static Image 大型ヘリ・本体;
    static Image 大型ヘリ・大破;
    static Anime 大型ヘリ・砲台;
    static ImagePack 大型ヘリ・パーツ;
    static Anime 大型ヘリ・プロペラ;
    static Anime 大型ヘリ・ガドリング;

    static void Load()
    {
        雑魚機.Load("File/unit/fly/zako.png");
        小型機[0].Load("File/unit/fly/000.png", 2, 2, 1);
        小型機[1].Load("File/unit/fly/001.png", 2, 2, 1);
        小型機[2].Load("File/unit/fly/002.png", 2, 2, 1);
        小型機[3].Load("File/unit/fly/003.png", 2, 2, 1);
        小型機[4].Load("File/unit/fly/004.png", 2, 2, 1);
        小型機[5].Load("File/unit/fly/005.png", 2, 2, 1);
        小型機[6].Load("File/unit/fly/006.png", 2, 2, 1);
        小型機[7].Load("File/unit/fly/007.png", 2, 2, 1);
        
        戦車.Load("File/unit/tank/tank_base.png", 4, 1, 4);
        戦車砲A.Load("File/unit/tank/tank_a.png");
        戦車砲B.Load("File/unit/tank/tank_b.png");

        大型ヘリ・本体.Load("File/unit/boss1/boss1a.png");
        大型ヘリ・大破.Load("File/unit/boss1/boss1b.png");
        大型ヘリ・砲台.Load("File/unit/boss1/boss1c.png",4,4,1);
        大型ヘリ・パーツ.Load("File/unit/boss1/boss1d.png",2,2,1);
        大型ヘリ・プロペラ.Load("File/unit/boss1/boss1e.png",4,4,1);
        大型ヘリ・ガドリング.Load("File/unit/boss1/boss1f.png",3,3,1);
    }
}

namespace MYukkuri
{
    static Anime きめぇまる;
    static Anime チルノフ;
    static Anime しょう;
    static Anime ほうとう;
    static Anime けいねA;
    static Anime けいねB;
    static Anime きすめ;
    static Anime りりー;
    static Anime まりさ;
    static Anime なず;
    static Anime にちょり;
    static Anime おりんA;
    static Anime おりんB;
    static Anime しりょう;
    static Anime らん;
    static Anime れいむA;
    static Anime れいむB;
    static Anime れみりゃ;
    static Anime るーみあ;
    static Anime すいか;
    static Anime てんしA;
    static Anime てんしH;
    static Anime おくう;
    static Anime ゆかりん;

    static Anime れいむ後;
    static Anime まりさ後;
    static Anime れみりゃ後;

    static void Load()
    {
        れいむA.Load("File/yukkuri/reimu/reimuA.png", 3, 3, 1);
        れいむB.Load("File/yukkuri/reimu/reimuB.png", 3, 3, 1);
        れいむ後.Load("File/yukkuri/reimu/reimu_back.png", 2, 2, 1);
        まりさ後.Load("File/yukkuri/marisa/marisa_back.png", 2 , 2 , 1);
        れみりゃ後.Load("File/yukkuri/remi/remi_back.png", 2, 2, 1);

        きめぇまる.Add("File/yukkuri/aya/aya.png");
        チルノフ.Add("File/yukkuri/chirnof/chirnof.png");
        しょう.Add("File/yukkuri/hoshi/hoshi.png");
        ほうとう.Add("File/yukkuri/hoshi/houtou.png");
        けいねA.Load("File/yukkuri/keine/keineA.png", 3, 3, 1);
        けいねB.Load("File/yukkuri/keine/keineB.png", 3, 3, 1);
        きすめ.Load("File/yukkuri/kisume/kisume", "png", 7);
        りりー.Load("File/yukkuri/lili/lili", "png", 3);
        まりさ.Load("File/yukkuri/marisa/marisa", "png", 2);
        なず.Load("File/yukkuri/nazu/nazu", "png", 3);
        にちょり.Load("File/yukkuri/nitori/nito", "png", 3);
        おりんA.Load("File/yukkuri/orin/orin", "png", 3);
        おりんB.Add("File/yukkuri/orin/orinB.png");
        しりょう.Load("File/yukkuri/orin/siryo", "png", 3);
        らん.Load("File/yukkuri/ran/ran", "png", 4);
        れみりゃ.Load("File/yukkuri/remi/remi.png", 3, 3, 1);
        るーみあ.Load("File/yukkuri/rumia/rumia.png", 3, 3, 1);
        すいか.Load("File/yukkuri/suica/suica", "png", 3);
        てんしA.Load("File/yukkuri/tenshi/tenshi", "png", 2);
        てんしH.Add("File/yukkuri/tenshi/tenshiH.png");
        おくう.Load("File/yukkuri/utuho/utuho", "png", 4);
        ゆかりん.Load("File/yukkuri/yukari/yukari", "png", 8);
    }
}

namespace MSystem
{
    static ImagePack マップチップ[1];
    static ImagePack ウィンドウ[14];
    static ImagePack 英字[4];
    static ImagePack 数字[2];

    static ImagePack 背景;
    static Anime 矢印;

    static void Load()
    {
        マップチップ[0].Load("File/mapchip/set001.png", 55, 5, 11);
        背景.Load("File/back/back", "jpg", 7);

        ウィンドウ[0].Load( "File/window/window000.png", 9, 3, 3);
        ウィンドウ[1].Load( "File/window/window001.png", 9, 3, 3);
        ウィンドウ[2].Load( "File/window/window002.png", 9, 3, 3);
        ウィンドウ[3].Load( "File/window/window003.png", 9, 3, 3);
        ウィンドウ[4].Load( "File/window/window004.png", 9, 3, 3);
        ウィンドウ[5].Load( "File/window/window005.png", 9, 3, 3);
        ウィンドウ[6].Load( "File/window/window006.png", 9, 3, 3);
        ウィンドウ[7].Load( "File/window/window007.png", 9, 3, 3);
        ウィンドウ[8].Load( "File/window/window008.png", 9, 3, 3);
        ウィンドウ[9].Load( "File/window/window009.png", 9, 3, 3);
        ウィンドウ[10].Load("File/window/window010.png", 9, 3, 3);
        ウィンドウ[11].Load("File/window/window011.png", 9, 3, 3);
        ウィンドウ[12].Load("File/window/window012.png", 9, 3, 3);
        ウィンドウ[13].Load("File/window/window013.png", 9, 3, 3);

        矢印.Load("File/window/arrow000.png", 6, 6, 1);

        英字[0].Load("File/font/alp000.png", 26, 26, 1);
        英字[1].Load("File/font/alp001.png", 26, 26, 1);
        英字[2].Load("File/font/alp002.png", 26, 26, 1);
        英字[3].Load("File/font/alp003.png", 26, 1, 26);
        数字[0].Load("File/font/num000.png", 10, 10, 1);
        数字[1].Load("File/font/num001.png", 10, 10, 1);
    }
}

namespace MEffect
{
    static Anime 爆発[21];
    static Anime プラズマ[8];
    static Anime 煙[4];

    static void Load()
    {

        爆発[0].Load("File/effect/bom/bom000.png",   8,  8, 1);
        爆発[1].Load("File/effect/bom/bom001.png",  20,  8, 3);
        爆発[2].Load("File/effect/bom/bom002.png",   8,  8, 1);
        爆発[3].Load("File/effect/bom/bom003.png",   2,  2, 1);
        爆発[4].Load("File/effect/bom/bom004.png",   2,  2, 1);
        爆発[5].Load("File/effect/bom/bom005.png",    18,  8, 3);
        爆発[6].Load("File/effect/bom/bom006.png",     8,  8, 1);
        爆発[7].Load("File/effect/bom/bom007.png",    13,  8, 2);
        爆発[8].Load("File/effect/bom/bom008.png",  16,  8, 2);
        爆発[9].Load("File/effect/bom/bom009.png",   8,  8, 1);
        爆発[10].Load("File/effect/bom/bom010.png",  8,  8, 1);
        爆発[11].Load("File/effect/bom/bom011.png",  8,  8, 1);
        爆発[12].Load("File/effect/bom/bom012.png",  7,  1, 7 , 10);
        爆発[13].Load("File/effect/bom/bom013.png", 17,  8, 3);
        爆発[14].Load("File/effect/bom/bom014.png",  8,  4, 2);
        爆発[15].Load("File/effect/bom/bom015.png",  4,  4, 1);
        爆発[16].Load("File/effect/bom/bom016.png", 16,  8, 2);
        爆発[17].Load("File/effect/bom/bom017.png", 10, 10, 1);
        爆発[18].Load("File/effect/bom/bom018.png",  8,  8, 1);
        爆発[19].Load("File/effect/bom/bom019.png",  8,  8, 1);
        爆発[20].Load("File/effect/bom/bom020.png",  8,  8, 1);

        プラズマ[0].Load("File/effect/prazma/prazma000.png", 8, 8, 1 , 5);
        プラズマ[1].Load("File/effect/prazma/prazma001.png", 8, 8, 1 , 5);
        プラズマ[2].Load("File/effect/prazma/prazma002.png", 4, 4, 1 , 5);
        プラズマ[3].Load("File/effect/prazma/prazma003.png", 8, 8, 1 , 5);
        プラズマ[4].Load("File/effect/prazma/prazma004.png", 8, 8, 1 , 5);
        プラズマ[5].Load("File/effect/prazma/prazma005.png", 8, 8, 1 , 5);
        プラズマ[6].Load("File/effect/prazma/prazma006.png", 4, 4, 1 , 5);
        プラズマ[7].Load("File/effect/prazma/prazma007.png", 8, 8, 1 , 5);

        煙[0].Load("File/effect/gus/gus000.png", 6, 6, 1);
        煙[1].Load("File/effect/gus/gus001.png", 4, 4, 1);
        煙[2].Load("File/effect/gus/gus002.png", 5, 5, 1);
        煙[3].Load("File/effect/gus/gus003.png", 6, 6, 1);
    }
}

namespace MShot
{
    static Image 火炎;
    static Image 熱線;
    static Image 炎刃;
    static Image 緑丸;
    static Image ビーム超;
    static Image ビーム長;
    static Image ビーム中;
    static Image ビーム短;

    static Image 火;
    static Anime 赤太;
    static Anime 赤細;
    static Anime 緑大;
    static Anime 緑中;
    static Anime 緑小;
    static Anime 緑特大;
    static Anime 緑円盤;

    static void Load()
    {
        火炎.Load("File/effect/shot/shotsingle000.png");
        熱線.Load("File/effect/shot/shotsingle001.png");
        炎刃.Load("File/effect/shot/shotsingle002.png");
        緑丸.Load("File/effect/shot/shotsingle003.png");
        ビーム超.Load("File/effect/shot/shotsingle004.png");
        ビーム長.Load("File/effect/shot/shotsingle005.png");
        ビーム中.Load("File/effect/shot/shotsingle006.png");
        ビーム短.Load("File/effect/shot/shotsingle007.png");

        火.Load("File/effect/shot/shot000.png");
        赤太.Load("File/effect/shot/shot001.png", 8, 8, 1);
        赤細.Load("File/effect/shot/shot002.png", 8, 8, 1);
        緑大.Load("File/effect/shot/shot003.png", 8, 8, 1);
        緑中.Load("File/effect/shot/shot004.png", 8, 8, 1);
        緑小.Load("File/effect/shot/shot005.png", 8, 8, 1);
        緑特大.Load("File/effect/shot/shot006.png", 4, 4, 1);
        緑円盤.Load("File/effect/shot/shot007.png", 6, 6, 1);
    }
}

namespace MMusic
{
    static Music 飛翔;
    static Music ホシノキセキ;
    static Music 砂の雫;
    static Music 時代の再臨;
    static Music タイトル;

    static void Load()
    {
        飛翔.Load("File/music/boss.mp3");
        ホシノキセキ.Load("File/music/ending.mp3");
        砂の雫.Load("File/music/gameover.mp3");
        時代の再臨.Load("File/music/stage.mp3");
        タイトル.Load("File/music/title.mp3");
    }
}

namespace MSound
{
    static Sound 爆発;

    static void Load()
    {
        爆発.Load("File/sound/bom17_c.wav");
    }
}

namespace MFont
{
    static Font ゴシック;
    static Font ゴシック小;
    static Font 明朝;
    static BmpFont 白絵;
    static BmpFont 赤絵;
    static BmpFont 青絵;
    static BmpFont 大絵;

    static void Load()
    {
        ゴシック.Load(SystemFont::Gothic, 24, 1, 2, FontType::Normal);
        ゴシック小.Load(SystemFont::Gothic, 12, 1, 2, FontType::Normal);
        明朝.Load( SystemFont::Mincho , 24, 1, 2, FontType::Normal);

        白絵.SetAlphabetLow(&MSystem::英字[0]);
        白絵.SetAlphabetCapital(&MSystem::英字[0]);
        白絵.SetNumber(&MSystem::数字[0]);

        赤絵.SetAlphabetCapital(&MSystem::英字[1]);
        赤絵.SetNumber(&MSystem::数字[1]);

        青絵.SetAlphabetCapital(&MSystem::英字[2]);

        大絵.SetAlphabetCapital(&MSystem::英字[3]);
    }
}

namespace MFrame
{
    static BmpFrame BMPフレーム[14];

    static void Load()
    {
        for (int i = 0; i < 14; ++i)
        {
            BMPフレーム[i].Make(&MSystem::ウィンドウ[i]);
        }
    }
}

namespace MActer
{
    static Image れいむ体;
    static ImagePack れいむ目;
    static ImagePack れいむ口;
    
    static Image のうかりん体;
    static ImagePack のうかりん目;
    static ImagePack のうかりん口;

    static void Load()
    {
        //れいむ体.Load("File/acter/れいむ/体/00.png");
        //れいむ目.Load("File/acter/れいむ/目/","png",31,"%02d.");
        //れいむ口.Load("File/acter/れいむ/口/","png",31,"%02d.");

        //のうかりん体.Load("File/acter/のうかりん/体/00.png");
        //のうかりん目.Load("File/acter/のうかりん/目/","png",38,"%02d.");
        //のうかりん口.Load("File/acter/のうかりん/口/","png",6,"%02d.");
    }
}

namespace MItem
{
    //素材は36種類+箱
    static ImagePack imageS;

    static void Load()
    {
        imageS.Load( "File/moyasi/item" , "png" , 37 );
    }
}

static void LoadMaterial()
{
    MIcon::Load();
    MEnemy::Load();
    MYukkuri::Load();
    MSystem::Load();
    MEffect::Load();
    MShot::Load();
    MMusic::Load();
    MSound::Load();
    MFont::Load();
    MFrame::Load();
    MActer::Load();
    MItem::Load();
}

}
