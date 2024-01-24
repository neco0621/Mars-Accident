//#include "graphic.h"
//#include <cmath>
//
//Graphic::Graphic()
//{
//}
//
//Graphic::~Graphic()
//{
//
//}
//
//BOOL Graphic::Graphic_Init(VOID)
//{
//    return TRUE;
//}
//
//VOID Graphic::Graphic_END(VOID)
//{
//    return VOID();
//}
//
//VOID Graphic::GraphicLoadErrMessage(const char* path)
//{
//    return VOID();
//}
//
//VOID Graphic_End(VOID)
//{
//    return;
//}
//
//VOID GraphicLoadErrMessage(const char* path)
//{
//    //エラー用文字列
//    char ErrStr[ImagePathStrMax];
//
//    //エラー用文字列の内容を空にする
//    for (int i = 0; i < ImagePathStrMax; i++) { ErrStr[i] = '\0'; }
//
//    //エラーの内容を連結して生成
//    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, ImageLoadErrCap);
//
//    //パスが間違っているなどでインストールできない場合はエラー
//    MessageBox(
//        GetMainWindowHandle(),      //ウィンドウハンドル
//        ErrStr,                     //エラー内容
//        ImageLoadErrTitle,          //エラータイトル
//        MB_OK);                     //OKボタンのみ
//
//    return;
//}
//
////読込
// Graphic Graphic::LoadGraphic(const char* path, int pos, Graphic_Align align)
//{
//     Graphic graphic;
//    //ファイルの場所をコピー
//    strcpy_s(Path, sizeof(Path), path);
//
//    //画像をメモリに読み込み
//    Handle = LoadGraph(Path);
//
//    //読み込みエラー
//    if (Handle == -1)
//    {
//        GraphicLoadErrMessage(Path);
//    }
//    else
//    {
//        //正常に読込ができたらパラメーター設定
//
//        //幅と高さを取得
//        GetGraphSize(Handle, &Width, &Height);
//
//        //基準点
//        Pos.x = pos;
//
//        //揃え方向
//        Align = align;
//
//        //画像を描画する
//        IsDraw = TRUE;
//
//        //エフェクトの初期化
//        IsFxStartFlg = FALSE;     //描画エフェクトフラグの初期化
//        Fx = GraFxNone;           //通常描画
//        FxMillTime = 0;           //エフェクト時間カウント
//        FxMillTimeMax = 0;        //エフェクト時間カウントMAX
//        FxInterMillTime = 0;      //エフェクト間隔カウント
//        FxInterMillTimeMax = 0;   //エフェクト間隔カウントMAX
//        Alpha = 1.0f;             //透明度初期化
//
//    }
//    return graphic;
// }
//
////描画
//void Graphic::DrawGraphic(Graphic* graphic)
//{
//    //エフェクト開始処理
//    if (graphic->IsFxStartFlg == TRUE)
//    {
//        //描画エフェクト開始処理
//        switch (graphic->Fx)
//        {
//        case GraFxBlink:
//            //エフェクト間隔が最大の時に透明度を切り替える
//            if (graphic->FxInterMillTime == graphic->FxInterMillTimeMax)
//            {
//                if (graphic->Alpha == 1.0)
//                {
//                    graphic->Alpha = 0.0f;    //透明にする
//                }
//                else if (graphic->Alpha == 0.0)
//                {
//                    graphic->Alpha = 1.0f;    //不透明にする
//                }
//            }
//            //透明処理
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->Alpha * 255);
//
//            break;
//
//        case GraFxFadeIn:
//            //画像の透明度の計算
//            graphic->Alpha
//                = sin(
//                    (float)graphic->FxInterMillTime / graphic->FxInterMillTimeMax   //経過時間から全体の%を計算
//                    * (DX_PI / 2));                                                     //sin(90) = 1として割合を計算
//            //透過処理
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->Alpha * 255);
//            break;
//
//        case GraFxFadeOut:
//
//            //画像の透明度を計算
//            graphic->Alpha
//                = cos(
//                    (float)graphic->FxInterMillTime / graphic->FxInterMillTimeMax   //経過時間から全体の%を計算
//                    * (DX_PI / 2));                                                     //cos(90) = 1として割合を計算
//            //透過処理
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->Alpha * 255);
//            break;
//
//        case GraFxNone:
//            //何もしない
//            break;
//        default:
//            break;
//        }
//
//        //エフェクト時間カウントアップ
//        graphic->FxMillTime++;
//
//        //エフェクト間隔カウントアップ
//        graphic->FxInterMillTimeMax++;
//    }
//
//    //描画処理
//    if (graphic->IsDraw == TRUE)
//    {
//        //基準を元に描画
//        switch (graphic->Align)
//        {
//        case GraAlignTopL:
//            //上左を基準に描画
//            DrawGraph(
//                graphic->Pos.x,
//                graphic->Pos.y,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignTopC:
//            //上中央を基準に描画
//            DrawGraph(
//                graphic->Pos.x - graphic->Width / 2,
//                graphic->Pos.y,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignTopR:
//            DrawGraph(
//                graphic->Pos.x - graphic->Width,
//                graphic->Pos.y,
//                graphic->Handle, TRUE);
//            break;
//
//
//        case GraAlignBottomL:
//            //下左を基準に描画
//            DrawGraph(
//                graphic->Pos.x,
//                graphic->Pos.y - graphic->Height,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignBottomC:
//            //下中央を基準に描画
//            DrawGraph(
//                graphic->Pos.x - graphic->Width / 2,
//                graphic->Pos.y - graphic->Height,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignBottomR:
//            //下右を基準に描画
//            DrawGraph(
//                graphic->Pos.x - graphic->Width,
//                graphic->Pos.y - graphic->Height,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignAllCenter:
//            //上下左右の中央に基準に描画
//            DrawGraph(
//                graphic->Pos.x - graphic->Width / 2,
//                graphic->Pos.y - graphic->Height / 2,
//                graphic->Handle, TRUE);
//            break;
//
//        default:
//            break;
//        }
//    }
//
//    //エフェクトの終了処理
//    if (graphic->IsFxStartFlg == TRUE)
//    {
//        switch (Fx)
//        {
//        case GraFxBlink:
//            //アルファブレンド(透過処理)終了
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxFadeIn:
//            //アルファブレンド(透過処理)終了
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxFadeOut:
//            //アルファブレンド(透過処理)終了
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxFadeInOut:
//            //アルファブレンド(透過処理)終了
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxNone:
//            //何もしない
//            break;
//        default:
//            break;
//        }
//
//        //インターバルがMAXなら元に戻す
//        if (graphic->FxInterMillTime > graphic->FxInterMillTimeMax)
//        {
//            graphic->FxInterMillTime = 0;
//        }
//
//        //エフェクトが無限継続ではない時
//        if (graphic->FxMillTimeMax != GraFxInfinity)
//        {
//            //エフェクト時間が終わりならばエフェクト終了
//            if (graphic->FxMillTime > graphic->FxMillTimeMax)
//            {
//                graphic->IsFxStartFlg = FALSE;
//            }
//        }
//    }
//    return;
//}
//
////解放
//void Graphic::DeleteGraphic(Graphic graphic)
//{
//    //正常に読込ができていれば
//    if (graphic.Handle != -1)
//    {
//        //メモリ解放
//        DeleteGraph(graphic.Handle);
//    }
//
//    return;
//}
//
//void Graphic::GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval)
//{
//    //エフェクトの秒数を初期化
//    graphic->FxMillTime = 0;
//
//    //もしエフェクトが無限継続なら、 実際のMAX時間を計算させない
//    if (MillTime == GraFxInfinity)
//    {
//        graphic->FxMillTimeMax = GraFxInfinity;
//    }
//    else
//    {
//        graphic->FxMillTimeMax = (MillTime / 1000.0f) * GameFPS;
//    }
//
//    //エフェクトの間隔を初期化
//    graphic->FxInterMillTime = 0;
//    graphic->FxInterMillTimeMax = (MillInterval / 10000.0f) * GameFPS;
//
//    //エフェクトの種類を設定
//    graphic->Fx = Fx;
//
//    //エフェクトの開始フラグON
//    graphic->IsFxStartFlg = TRUE;
//
//    return;
//}
//
