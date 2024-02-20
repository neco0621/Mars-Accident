#include <DxLib.h>
#include <cassert>
#include "GameOverScene.h"
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage1Scene.h"
#include "../Game.h"

namespace
{
	//フレームの初期値
	constexpr int kFrame = 60;
}

GameOverScene::GameOverScene(SceneManager& mgr) : Scene(mgr),
//初期化
m_gameOver(-1),
m_titleBack(-1),
m_bg(-1),
m_bgm(-1),
m_retry(-1)
{
	//m_updateFuncの中身をFadeInUpdateに設定
	m_updateFunc = &GameOverScene::FadeInUpdate;
	//m_drawFuncの中身をFadeDrawに設定
	m_drawFunc = &GameOverScene::FadeDraw;
	//フレームの初期値をkFrame(60)に設定
	frame_ = kFrame;

	//ゲームオ－バーの文字のロード
	m_gameOver = LoadGraph("data/GameOver.png");
	//タイトルに戻るの文字のロード
	m_titleBack = LoadGraph("data/TitleBack.png");
	//背景のグラフィックのロード
	m_bg = LoadGraph("data/GameOverBg.png");
	//リトライの文字のロード
	m_retry = LoadGraph("data/Retry.png");
	//BGMのロード
	m_bgm = LoadSoundMem("data/Sound/GameOverBgm.mp3");

	//BGMの再生
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

GameOverScene::~GameOverScene()
{
	//BGMを止める
	StopSoundMem(m_bgm);

	//メモリからグラフィックを削除
	DeleteGraph(m_gameOver);
	DeleteGraph(m_titleBack);
	DeleteGraph(m_bg);
	DeleteGraph(m_retry);

	//メモリからサウンドを削除
	DeleteSoundMem(m_bgm);
}

void GameOverScene::Init()
{
}

void GameOverScene::Update(Input& input)
{
	//m_updateFuncの中身を実行
	(this->*m_updateFunc)(input);
}

void GameOverScene::Draw()
{
	//m_drawFuncの中身を実行
	(this->*m_drawFunc)();
}

void GameOverScene::FadeInUpdate(Input&)
{
	//フェイドに関するフレーム数を徐々に下げる
	frame_--;
	//frame_が0以下になったら
	if (frame_ <= 0)
	{
		//m_updateFuncの中身をNormalUpdateに変更
		m_updateFunc = &GameOverScene::NormalUpdate;
		//m_drawFuncの中身をNormalDrawに変更
		m_drawFunc = &GameOverScene::NormalDraw;
	}
}

void GameOverScene::NormalUpdate(Input& input)
{
	//OKキー(Enterキー)が押されたとき
	if (input.IsTriggered("OK"))
	{
		//m_updateFuncの中身をFadeOutUpdateに変える
		m_updateFunc = &GameOverScene::FadeOutUpdate;
		//m_drawFuncの中身をFadeDrawに変える
		m_drawFunc = &GameOverScene::FadeDraw;
	}

	//Rキーが押されたとき
	if (CheckHitKey(KEY_INPUT_R))
	{
		//Stage1Sceneに移行する
		manager_.ChangeScene(std::make_shared<Stage1Scene>(manager_));
	}
}

void GameOverScene::FadeOutUpdate(Input&)
{
	//フェイドに関するフレーム数を徐々に上げる
	frame_++;
	//frame_がkFrame(60)以上になったら
	if (kFrame <= frame_)
	{
		//タイトルシーンに移行する
		manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
	}
}

void GameOverScene::FadeDraw()
{
	//背景の描画
	DrawGraph(0,0,m_bg,true);
	//ゲームオーバーの文字の描画
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25 - 127, m_gameOver, true);
	//タイトルに戻るの文字の描画
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 127, m_titleBack, true);
	//リトライの文字の描画
	DrawGraph(Game::kScreenWidth / 2 - 235, Game::kScreenHeight * 0.75 - 10, m_retry, true);
	//フェイド時の暗幕の描画
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{
	//背景の描画
	DrawGraph(0, 0, m_bg, true);
	//ゲームオーバーの文字の描画
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25 - 127, m_gameOver, true);
	//タイトルに戻るの文字の描画
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 127, m_titleBack, true);
	//リトライの文字の描画
	DrawGraph(Game::kScreenWidth / 2 - 235, Game::kScreenHeight * 0.75 - 10, m_retry, true);
}
