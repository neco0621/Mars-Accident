#pragma once

#include "DxLib.h"
#include "Game.h"
#include "Vec2.h"
#include "UFO.h"

#define GraFxInfinity	-99999	//エフェクト無限継続(負数なので通常はあり得ない時間)

//エラー
#define ImageLoadErrCap		"が読み込めませんでした"
#define ImageLoadErrTitle	"画像読み込みエラー"

//文字列の長さ
#define ImagePathStrMax	256
#define ImageErrStrMax	512

//画像ファイルのパス
//※日本語や絵文字など2バイト文字を避けること(最悪文字化けで読み込めない時がある)
//※全角空白、半角空白問わず空白を避けること(ファイル名の区切りだと思われることもある)
#define GraphicPathTitleBackImage	"date/TitleBack.png"
#define GraphicPathTitleLogo		"data/TitleLogo.png"
#define GraphicPathTitleButton		"data/TItleButton.png"


//設定したいFPS
#define GameFPS	60;

//列挙型
enum Graphic_Align
{
	GraAlignTopL,	 //画像の基準点で上左揃え
	GraAlignTopC,	 //画像の基準点で上中央揃え
	GraAlignTopR,	 //画像の基準点で上右揃え

	GraAlignBottomL,  //画像の基準点で下左揃え
	GraAlignBottomC,  //画像の基準点で下中央揃え
	GraAlignBottomR,  //画像の基準点で下右揃え

	GraAlignAllCenter		//画像の基準点で上下も左右も中央揃え
};

enum Graphic_Fx
{
	GraFxBlink,			//点滅
	GraFxFadeIn,		//透明→不透明
	GraFxFadeOut,		//不透明→透明
	GraFxFadeInOut,		//不透明←→透明
	GraFxNone			//通常描画
};

//画像構造体のコア部分
typedef struct _GraphicCore
{
	char Path[ImageErrStrMax];		//パス

	Vec2 Pos;						//画像の基準点
	int Width = 0;					//幅
	int Height = 0;					//高さ

	RECT Coll;						//矩形の当たり判定
	RECT CollMargin;				//矩形の当たり判定を定める

	Graphic_Align Align = GraAlignTopL;	//揃え方向

	float Rate = 1.0f;				//拡大率
	float Angle = 0.0f;				//角度

	BOOL IsDraw = FALSE;			//描画するか?

	//★★★追加
	BOOL IsFxStartFlg = FALSE;		//描画エフェクトフラグ
	Graphic_Fx Fx = GraFxNone;		//描画エフェクトの種類
	int FxMillTime = 0;				//エフェクト時間カウント
	int FxMillTimeMax = 0;			//エフェクト時間カウントMax
	int FxInterMillTime = 0;		//エフェクト間隔カウント
	int FxInterMillTimeMax = 0;		//エフェクト間隔カウントMax
	float Alpha = 0.0f;				//透明度(0.0～1.0を入れること)

}GraphicCore;

//画像構造体
typedef struct _Graphic
{
	GraphicCore c;		//コア
	int Handle = -1;	//ハンドル
}Graphic;

//外部グローバル変数
extern Graphic TitleBackImage;	//タイトル背景画像
extern Graphic TitleLogo;		//タイトルロゴ
extern Graphic TitleButton;		//タイトルボタン

//外部プロトタイプ宣言
extern BOOL Graphic_Init(VOID);							//読込・ハンドル生成
extern VOID Graphic_END(VOID);							//後始末
extern VOID GraphicLoadErrMessage(const char* path);	//読込エラーメッセージ

extern Graphic LoadGraphic(const char* path, int pos, Graphic_Align align);	//読込
extern VOID DrawGraphic(Graphic* graphic);				//描画
extern VOID DeleteGraphic(Graphic graphic	);			//解放
extern VOID GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval);	//エフェクト(Fx)開始


class UFO;

UFO* m_pUfo;


