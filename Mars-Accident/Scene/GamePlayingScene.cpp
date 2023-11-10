#include "GamePlayingScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Player.h"
#include "../UFO.h"

//登場する敵
//#include "EnemyBase.h"
#include "../Enemy/EnemyLeft.h"
#include "../Enemy/EnemyRight.h"

//登場するショット
#include "../Shot/ShotBeam.h"

#include <cassert>
#include <DxLib.h>

namespace
{
	//一度に登場できる最大の数
	constexpr int kEnemyMax = 10;

	//何フレーム沖に敵が登場するか
	constexpr int kEnemyInterval = 60;

	//画面内に一度に出てくる弾の最大数
	constexpr int kShotMax = 256;
}


void GamePlayingScene::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0)
	{
		updateFunc_ = &GamePlayingScene::NormalUpdate;
		drawFunc_ = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
		drawFunc_ = &GamePlayingScene::FadeDraw;
	}
	else if (input.IsTriggered("pause"))
	{
		manager_.PushScene(std::make_shared<PauseScene>(manager_));
	}
}

void GamePlayingScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		manager_.ChangeScene(std::make_shared<GameOverScene>(manager_));
	}
}

void GamePlayingScene::FadeDraw()
{
	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	m_pPlayer->Draw();
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (!m_pShot[i])		continue;
		m_pShot[i]->Draw();
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Draw();
		}
	}
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawCircle(320, 120, 10, GetColor(255, 255, 0), true);
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		L"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
	DrawFormatString(10, 10, 0xffffff, L"fps=%2.2f", fps);
}

GamePlayingScene::GamePlayingScene(SceneManager& mgr) : Scene(mgr)
{
	m_playerHandle = LoadGraph(L"./img/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph(L"./img/enemy.png");
	assert(m_enemyHandle != -1);
	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
	frame_ = 60;
	m_enemyInterval = 0;

	//プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	//Playerにグラフィックハンドルを渡す

	//敵の準備
	//m_pEnemy(vector)何もしなければサイズは0
	//resize関数でkEnemyMaxだけデータを保存できるようにする
	m_pEnemy.resize(kEnemyMax);

	//いつもはコンストラクタでメモリを確保して
	//デストラクタで解放してた
	//ランダムにEnemyLeft,EnemyRightを確保したい
	//どれかわからないのであらかじめ確保することができない
	//→動的にメモリを確保する　Update()中に必要に応じて

	//初期状態ではメモリを確保していないことがわかるようにしておく
	//未使用状態にする　nullptrを入れておく
	//size()で現在使用可能な要素数を取得可能
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;

		//m_pEnemyのなかにはLeft,Right,ToPlayerのどれかが入る
		//現時点ではどれが入るのか決定できない
	}

	//ショットの準備
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr;	//未使用
	}
}

GamePlayingScene::~GamePlayingScene()
{
	//メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);

	//プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;
	//メモリが確保されている敵を探して解放していく
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//nullptr以外のものが入っているということはそこにはポインタが入っている
		if (m_pEnemy[i] != nullptr)
		{
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			//nullptrではない場合
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void GamePlayingScene::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr の場合止まる

	m_pPlayer->Init();
}

void GamePlayingScene::Update(Input& input)
{
	m_pPlayer->Update();

	for (int i = 0; i < m_pShot.size(); i++)
	{
		//nullptrなら処理は行わない
		if (!m_pShot[i])		continue;

		m_pShot[i]->Update();
		//画面外に出たらメモリ解放
		if (!m_pShot[i]->isExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	Rect playerRect = m_pPlayer->GetColRect();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!m_pEnemy[i]->isExist())
			{
				//メモリを解放する
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	//使っていないとわかるように
			}
		}

	}
	//敵キャラクターを登場させる
	//kEnemyIntervalフレーム経過するごとにランダムに敵を登場させる
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		//ランダムに敵を選択
		switch (GetRand(1))		//0 or 1 
		{
		case 0:		//Left
			CreateEnemyLeft();

			break;
		case 1:		//Right
			CreateEnemyRight();

			break;
		default:	assert(false);		//breakなし
		}
	}

	fps = GetFPS();
	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	(this->*drawFunc_)();
}

bool GamePlayingScene::AddShot(ShotBase* pShot)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		//使用中なら次のチェックへ
		if (m_pShot[i])	continue;

		//ここに来たということはm_pShot[i] == nullptr
		m_pShot[i] = pShot;
		//登録したら終了
		return true;
	}

	//ここに来た、ということはm_pShotにポインタを登録できなかった
	delete pShot;
	return false;
}

void GamePlayingScene::CreateEnemyLeft()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//メモリを確保したら以降はチェックしない
		}
	}
}

void GamePlayingScene::CreateEnemyRight()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//メモリを確保したら以降はチェックしない
		}
	}
}
