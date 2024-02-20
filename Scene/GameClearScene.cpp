#include "GameOverScene.h"
#include "GameClearScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Input.h"
#include "../Game.h"

#include <DxLib.h>
#include <cassert>

namespace
{
	//フェードに関するフレーム数の初期値
	constexpr int kFrame			= 60;
	//X軸の調整
	constexpr int kWidthAdjustment	= 225;
	//Y軸の調整
	constexpr int kHeightAdjustment = 127;
}

GameClearScene::GameClearScene(SceneManager& mgr) : Scene(mgr),
//初期化
m_clearSE(0),
m_bgm(0),
m_bg(-1),
m_gameClear(-1),
m_titleBack(-1),
m_widthAdjustment(kWidthAdjustment),
m_heightAdjustment(kHeightAdjustment)
{
	//m_updateFuncの中身をFadeInUpdate
	m_updateFunc = &GameClearScene::FadeInUpdate;
	m_drawFunc = &GameClearScene::FadeDraw;
	//フェードに関するフレーム数の初期値をkFrame(60)に設定
	frame_ = kFrame;
	
	//ゲームクリアの文字表示のグラフィックをロード
	m_gameClear = LoadGraph("data/GameClear.png");
	//背景のグラフィックをロード
	m_bg = LoadGraph("data/GameClearBg.png");
	//タイトルへ戻るのボタンのハンドルのロード
	m_titleBack = LoadGraph("data/TitleBack.png");
	//ゲームクリア時のサウンドをロード
	m_clearSE = LoadSoundMem("data/Sound/ClearSE.mp3");
	//BGMのサウンドをロード
	m_bgm = LoadSoundMem("data/Sound/ClearSceneBgm.mp3");

	//BGMの再生
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

GameClearScene::~GameClearScene()
{
	//BGMを止める
	StopSoundMem(m_bgm);

	//メモリからグラフィックを削除
	DeleteGraph(m_gameClear);
	DeleteGraph(m_bg);
	DeleteGraph(m_titleBack);

	//メモリからサウンドを削除
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_clearSE);
}

void GameClearScene::Init()
{
}

void GameClearScene::Update(Input& input)
{
	//FadeInUpdateを呼び出す
	(this->*m_updateFunc)(input);
}

void GameClearScene::Draw()
{
	//FadeDrawを呼び出す
	(this->*m_drawFunc)();
}

void GameClearScene::FadeInUpdate(Input&)
{
	//フェイドに関するフレーム数を徐々に下げる
	frame_--;
	//frame_が0以下になったら
	if (frame_ <= 0)
	{
		//m_updateFuncの中身をNormalUpdateに変える
		m_updateFunc = &GameClearScene::NormalUpdate;
		//m_drawFuncの中身をNormalDrawに変える
		m_drawFunc = &GameClearScene::NormalDraw;
	}
}

void GameClearScene::NormalUpdate(Input& input)
{
	//OKキー(Enterキー)が押されたとき
	if (input.IsTriggered("OK"))
	{
		//m_updateFuncの中身をFadeOutUpdateに変える
		m_updateFunc = &GameClearScene::FadeOutUpdate;
		//m_drawFuncの中身をFadeDrawに変える
		m_drawFunc = &GameClearScene::FadeDraw;
	}
}

void GameClearScene::FadeOutUpdate(Input&)
{
	//フェイドに関するフレーム数を徐々に上げる
	frame_++;
	//frame_がkFrame(60)以上になったら
	if (kFrame <= frame_)
	{
		//タイトルシーンに変える
		manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
	}
}

void GameClearScene::FadeDraw()
{
	//背景の描画
	DrawGraph(0,0,m_bg,true);
	//ゲームクリアボタンの描画
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment,
		Game::kScreenHeight * 0.25 - m_heightAdjustment, m_gameClear, true);
	//タイトルへ戻るのボタン描画
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment,
		Game::kScreenHeight * 0.75 - m_heightAdjustment, m_titleBack, true);
	//Fade時の暗幕の描画
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameClearScene::NormalDraw()
{
	//背景の描画
	DrawGraph(0, 0, m_bg, true);
	//ゲームクリアボタンの描画
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment, 
		Game::kScreenHeight * 0.25 - m_heightAdjustment, m_gameClear, true);
	//タイトルへ戻るのボタン描画
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment, 
		Game::kScreenHeight * 0.75 - m_heightAdjustment, m_titleBack, true);
}
// <a href = "https://jp.freepik.com/free-vector/pixel-art-mystical-background_29019077.htm#query=pixel%20art&position=0&from_view=keyword&track=ais&uuid=acea7397-7e5c-4d2b-8020-153b3f30c072">著作者：pikisuperstar< / a>／出典：Freepik