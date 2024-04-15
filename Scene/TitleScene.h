#pragma once
#include "Scene.h"

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{

public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	void Init();
	void Update(Input& input);
	void Draw();
	void ShakeScreen(int a, int b);

private:
	//更新メンバ関数ポインタ
	void (TitleScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void (TitleScene::*) ();
	DrawFunc_t drawFunc_;
	//更新関数
	void FadeInUpdate(Input& input);	//フェードイン状態
	void NormalUpdate(Input& input);	//通常状態
	void FadeOutUpdate(Input& input);	//フェードアウト状態

	//描画関数
	void FadeDraw();	//フェード中描画
	void NormalDraw();	//非フェード描画

	//グラフィックハンドル
	int m_bgHandle;			//背景のハンドル
	int m_titleHandle;		//タイトルのアイコンのハンドル
	int m_shakeHandle;		//画面揺れのハンドル
	int m_titleButton;		//STARTボタンのハンドル
	int frame_;				//フェイドに関するフレーム
	int m_bgPosX;			//背景の描画位置
	int m_shakeSize;		//画面揺れのサイズ
	int AnimFrame;			//アニメーションの再生時間
	int m_bgFrame;			//背景が消えるまでの時間
	int m_shakeFrame;		//画面揺れの時間
	int m_loopFrame;		//画面揺れのループ時間
	
	//サウンド
	int m_bgm;				//BGM
	int CheckSE;			//STARTボタンを押したときのサウンド
	
	//フラグ
	bool m_isShake;			//画面揺れしているかどうか

	//変数
	int m_AdjustmentWidth;	//X座標の細かい位置調整
	int m_AdjustmentHeight;	//Y座標の細かい位置調整
};

