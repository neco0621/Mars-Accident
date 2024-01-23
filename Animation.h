#pragma once
#include "DxLib.h"
#include "graphic.h"
#include "Game.h"
#include "UFO.h"

//エラー
#define AnimationLoadErrCap		"が読み込めませんでした"
#define AnimationLoadErrTitle	"アニメーション読み込みエラー"

//文字列の長さ
#define AnimationPathstrMax 256
#define AnimationErrstrMax 512

//アニメーションのファイルパス
#define GraphicPathTitleAnimExpl	"data/explosion.png"
#define AnimExplDivX				10					//爆発アニメの横分割数
#define AnimExplDivY				8					//爆発アニメの縦分割数

//アニメーションが無限の時
#define AnimationInfinity  -99999
//アニメーション1回のみ(負数なので通常ではありえない時間)
#define AnimationOnce		-11111

//アニメーション構造体のコア部分
typedef struct _AnimationCore
{
	int NowHandleIndex = -1;	//現在のハンドルの要素数

	int DivX = 0;			//画像の横分割数
	int DivY = 0;			//画像の縦分割数

	int FrameCnt = 0;		//アニメーションのコマ時間
	int FrameMax = 0;		//アニメーションのコマ時間MAX

	int FrameByFrameCnt = 0;	//アニメのコマ送り時間
	int FrameByFrameMax = 0;	//アニメのコマ送り時間MAX

	BOOL IsAnimStractFlg = FALSE;	//アニメーション開始フラグ

}AnimationCore;

typedef struct _Animation
{
	Graphic			g;	//画像
	AnimationCore	a;	//アニメーションコア
	int* Handle;		//ハンドル(メモリを動的確保)
}Animation;

//外部グローバル変数
extern Animation AnimExpl;	//爆発アニメーション

//外部プロトコル宣言
extern BOOL Animation_Init(VOID);						//読込・ハンドル生成
extern VOID Animation_End(VOID);						//後始末
extern VOID AnimationLoadErrMessage(const char* path);	//読込エラーメッセージ

extern Animation LoadAnimation(Graphic graphic, int XNum, int YNum);	//アニメーション読込
extern VOID DrawAnimation(Animation* animation);						//描画
extern VOID DeleteAnimation(Animation animation);						//解放

extern VOID AnimationStart(Animation* animation, int MillTime, int MillInterval);	//アニメーションの開始

