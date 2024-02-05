#pragma once
#include "Scene.h"

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{
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

	void BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight);

	int m_bgHandle;
	int m_animHandle;
	int m_titleHandle;
	int m_shakeHandle;
	int m_titleButton;
	int m_moon;
	int frame_;
	int areaX;
	int speed;
	int m_bgPosX;
	int m_shakeSize;
	int AnimFrame;
	int m_bgFrame;
	int m_shakeFrame;
	int m_loopFrame;
	int m_bgm;
	int CheckSE;
	
	bool m_isShake;

public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	void Init();
	void Update(Input& input);
	void Draw();
	void ShakeScreen(int a, int b);
};

