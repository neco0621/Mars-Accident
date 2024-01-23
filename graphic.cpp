#include "graphic.h"
#include <cmath>

//グローバル変数
Graphic TitleBackImage;     //タイトル背景画像
Graphic TitleLogo;          //タイトルロゴ
Graphic TitleButton;        //タイトルボタン

//読込・ハンドル生成
BOOL Graphic_Init(VOID)
{
    //タイトル背景画像
    TitleBackImage = LoadGraphic(
        GraphicPathTitleBackImage,
        (0,0),              //背景は左上から
        GraAlignTopL);  if (TitleBackImage.Handle == -1) { return FALSE; }

    //タイトルロゴ
    TitleLogo = LoadGraphic(
        GraphicPathTitleLogo,
        (Game::kScreenWidth, Game::kScreenHeight),          //ロゴは画面中央から
        GraAlignBottomC);  if (TitleLogo.Handle == -1) { return FALSE; }

    //タイトルボタン
    TitleButton = LoadGraphic(
        GraphicPathTitleButton,
        (Game::kScreenWidth, Game::kScreenHeight + 50),    //ボタンは下あたりから
        GraAlignTopC);  if (TitleButton.Handle == -1) { return FALSE; }

    return TRUE;
}

VOID Graphic_End(VOID)
{
    DeleteGraphic(TitleBackImage);
    DeleteGraphic(TitleLogo);
    DeleteGraphic(TitleButton);

    return;
}

VOID GraphicLoadErrMessage(const char* path)
{
    //エラー用文字列
    char ErrStr[ImagePathStrMax];

    //エラー用文字列の内容を空にする
    for (int i = 0; i < ImagePathStrMax; i++) { ErrStr[i] = '\0'; }

    //エラーの内容を連結して生成
    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, ImageLoadErrCap);

    //パスが間違っているなどでインストールできない場合はエラー
    MessageBox(
        GetMainWindowHandle(),      //ウィンドウハンドル
        ErrStr,                     //エラー内容
        ImageLoadErrTitle,          //エラータイトル
        MB_OK);                     //OKボタンのみ

    return;
}

//読込
Graphic LoadGraphic(const char* path, int pos, Graphic_Align align)
{
    Graphic graphic;

    //ファイルの場所をコピー
    strcpy_s(graphic.c.Path, sizeof(graphic.c.Path), path);

    //画像をメモリに読み込み
    graphic.Handle = LoadGraph(graphic.c.Path);

    //読み込みエラー
    if (graphic.Handle == -1)
    {
        GraphicLoadErrMessage(graphic.c.Path);
    }
    else
    {
        //正常に読込ができたらパラメーター設定

        //幅と高さを取得
        GetGraphSize(graphic.Handle, &graphic.c.Width, &graphic.c.Height);

        //基準点
        graphic.c.Pos.x = pos;

        //揃え方向
        graphic.c.Align = align;

        //画像を描画する
        graphic.c.IsDraw = TRUE;

        //エフェクトの初期化
        graphic.c.IsFxStartFlg = FALSE;     //描画エフェクトフラグの初期化
        graphic.c.Fx = GraFxNone;           //通常描画
        graphic.c.FxMillTime = 0;           //エフェクト時間カウント
        graphic.c.FxMillTimeMax = 0;        //エフェクト時間カウントMAX
        graphic.c.FxInterMillTime = 0;      //エフェクト間隔カウント
        graphic.c.FxInterMillTimeMax = 0;   //エフェクト間隔カウントMAX
        graphic.c.Alpha = 1.0f;             //透明度初期化

    }

    return graphic;
}

VOID DrawGraphic(Graphic* graphic)
{
    //エフェクト開始処理
    if (graphic->c.IsFxStartFlg == TRUE)
    {
        //描画エフェクト開始処理
        switch (graphic->c.Fx)
        {
        case GraFxBlink:
            //エフェクト間隔が最大の時に透明度を切り替える
            if (graphic->c.FxInterMillTime == graphic->c.FxInterMillTimeMax)
            {
                if (graphic->c.Alpha == 1.0)
                {
                    graphic->c.Alpha = 0.0f;    //透明にする
                }
                else if (graphic->c.Alpha == 0.0)
                {
                    graphic->c.Alpha = 1.0f;    //不透明にする
                }
            }
            //透明処理
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->c.Alpha * 255);

            break;

        case GraFxFadeIn:
            //画像の透明度の計算
            graphic->c.Alpha
                = sin(
                    (float)graphic->c.FxInterMillTime / graphic->c.FxInterMillTimeMax   //経過時間から全体の%を計算
                    * (DX_PI / 2));                                                     //sin(90) = 1として割合を計算
            //透過処理
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->c.Alpha * 255);
            break;

        case GraFxFadeOut:

            //画像の透明度を計算
            graphic->c.Alpha
                = cos(
                    (float)graphic->c.FxInterMillTime / graphic->c.FxInterMillTimeMax   //経過時間から全体の%を計算
                    * (DX_PI / 2));                                                     //cos(90) = 1として割合を計算
            //透過処理
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->c.Alpha * 255);
            break;

        case GraFxNone:
            //何もしない
            break;
        default:
            break;
        }

        //エフェクト時間カウントアップ
        graphic->c.FxMillTime++;

        //エフェクト間隔カウントアップ
        graphic->c.FxInterMillTimeMax++;
    }

    //描画処理
    if (graphic->c.IsDraw == TRUE)
    {
        //基準を元に描画
        switch (graphic->c.Align)
        {
        case GraAlignTopL:
            //上左を基準に描画
            DrawGraph(
                graphic->c.Pos.x,
                graphic->c.Pos.y,
                graphic->Handle, TRUE);
            break;

        case GraAlignTopC:
            //上中央を基準に描画
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width / 2,
                graphic->c.Pos.y,
                graphic->Handle, TRUE);
            break;

        case GraAlignTopR:
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width,
                graphic->c.Pos.y,
                graphic->Handle, TRUE);
            break;


        case GraAlignBottomL:
            //下左を基準に描画
            DrawGraph(
                graphic->c.Pos.x,
                graphic->c.Pos.y - graphic->c.Height,
                graphic->Handle, TRUE);
            break;

        case GraAlignBottomC:
            //下中央を基準に描画
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width / 2,
                graphic->c.Pos.y - graphic->c.Height,
                graphic->Handle, TRUE);
            break;

        case GraAlignBottomR:
            //下右を基準に描画
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width,
                graphic->c.Pos.y - graphic->c.Height,
                graphic->Handle, TRUE);
            break;

        case GraAlignAllCenter:
            //上下左右の中央に基準に描画
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width / 2,
                graphic->c.Pos.y - graphic->c.Height / 2,
                graphic->Handle, TRUE);
            break;

        default:
            break;
        }
    }

    //エフェクトの終了処理
    if (graphic->c.IsFxStartFlg == TRUE)
    {
        switch (graphic->c.Fx)
        {
        case GraFxBlink:
            //アルファブレンド(透過処理)終了
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxFadeIn:
            //アルファブレンド(透過処理)終了
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxFadeOut:
            //アルファブレンド(透過処理)終了
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxFadeInOut:
            //アルファブレンド(透過処理)終了
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxNone:
            //何もしない
            break;
        default:
            break;
        }

        //インターバルがMAXなら元に戻す
        if (graphic->c.FxInterMillTime > graphic->c.FxInterMillTimeMax)
        {
            graphic->c.FxInterMillTime = 0;
        }

        //エフェクトが無限継続ではない時
        if (graphic->c.FxMillTimeMax != GraFxInfinity)
        {
            //エフェクト時間が終わりならばエフェクト終了
            if (graphic->c.FxMillTime > graphic->c.FxMillTimeMax)
            {
                graphic->c.IsFxStartFlg = FALSE;
            }
        }
    }
    return;
}

//解放
VOID DeleteGraphic(Graphic graphic)
{
    //正常に読込ができていれば
    if (graphic.Handle != -1)
    {
        //メモリ解放
        DeleteGraph(graphic.Handle);
    }

    return;
}

//エフェクト開始
VOID GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval)
{
    //エフェクトの秒数を初期化
    graphic->c.FxMillTime = 0;

    //もしエフェクトが無限継続なら、 実際のMAX時間を計算させない
    if (MillTime == GraFxInfinity)
    {
        graphic->c.FxMillTimeMax = GraFxInfinity;
    }
    else
    {
        graphic->c.FxMillTimeMax = (MillTime / 1000.0f) * GameFPS;
    }

    //エフェクトの間隔を初期化
    graphic->c.FxInterMillTime = 0;
    graphic->c.FxInterMillTimeMax = (MillInterval / 10000.0f) * GameFPS;

    //エフェクトの種類を設定
    graphic->c.Fx = Fx;

    //エフェクトの開始フラグON
    graphic->c.IsFxStartFlg = TRUE;

    return;
}
