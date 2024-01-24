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
class Graphic;
class UFO;
class Animation
{
public:
	Animation();
	~Animation();
	int NowHandleIndex;	//現在のハンドルの要素数

	int DivX;			//画像の横分割数
	int DivY;			//画像の縦分割数

	int FrameCnt = 0;		//アニメーションのコマ時間
	int FrameMax = 0;		//アニメーションのコマ時間MAX

	int FrameByFrameCnt = 0;	//アニメのコマ送り時間
	int FrameByFrameMax = 0;	//アニメのコマ送り時間MAX

	bool IsAnimStractFlg;	//アニメーション開始フラグ

	void SetAnimHandle(int animation) { Handle = animation; }

	Graphic	g;	//画像
	int* Handle;		//ハンドル(メモリを動的確保)


	//外部グローバル変数
	Animation* AnimExpl;	//爆発アニメーション

	//外部プロトコル宣言
	BOOL Animation_Init();						//読込・ハンドル生成
	void Animation_End();						//後始末
	void AnimationLoadErrMessage(const char* path);	//読込エラーメッセージ

	Animation* LoadAnimation(Graphic graphic, int XNum, int YNum);	//アニメーション読込
	void DrawAnimation(Animation* animation);						//描画

	Animation* DeleteAnimation(Animation animation);

	void AnimationStart(Animation* animation, int MillTime, int MillInterval);	//アニメーションの開始

	UFO* m_pUfo;

};
