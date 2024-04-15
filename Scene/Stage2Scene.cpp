#include "Stage2Scene.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "TitleScene.h"
#include "DxLib.h"
#include "../Player.h"
#include "../UFO.h"
#include "../S2UFO.h"
#include "../Pad.h"
#include "../Rect.h"
#include "../Rocket.h"
#include "../Game.h"
#include "../Bg.h"
#include "../Input.h"

//登場する敵
//#include "EnemyBase.h"
#include "../Enemy/EnemyLeft.h"
#include "../Enemy/EnemyRight.h"

//登場するショット
#include "../ShotBeam.h"

#include <cassert>

namespace
{
	//一度に登場できる最大の数.
	constexpr int kEnemyMax = 20;
	//何フレーム沖に敵が登場するか.
	constexpr int kEnemyInterval = 60;

	//画面内に一度に出てくる弾の最大数.
	constexpr int kShotMax = 256;

	//画面がワイプするのにかかるフレーム数.
	constexpr int kWipeFrame = 30;

	constexpr int kShakeSize = 20;

	// アニメーション間隔
	constexpr int kAnimInterval = 3;
	// 高さ・幅
	constexpr int kAnimWidth = 100;
	constexpr int kAnimHeight = 100;
	// 縦横数
	constexpr int kRow = 10;
	constexpr int kLine = 9;
	// アニメーション数
	constexpr int kAnimNum = 82;
}

Stage2Scene::Stage2Scene(SceneManager& manager) : Scene(manager),
m_enemyInterval(0),
m_S2shakeFrame(0),
m_wipeFrame(0),
m_toNear(Game::kScreenWidth, Game::kScreenHeight),
m_downEnemyCount(0),
m_damageFlag(false),
m_lifeCount(0),
m_isShake(false),
m_shakeSize(kShakeSize),
m_shakeHandle(-1),
m_gameOverFlag(false),
IsGround(false),
StartFlag(false),
AnimFlag(false),
m_animFrame(0),
m_destoryEnemy(-1),
m_bgm(-1),
m_hitHandle(-1),
m_shakeFrame(0)
{
	//ゲーム画面描画先の生成.
	//画面サイズと同じ大きさのグラフィックデータを作成する.
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//プレイヤーのグラフィックのロード.
	m_playerHandle = LoadGraph(L"data/player.png");
	assert(m_playerHandle != -1);
	//敵のグラフィックのロード
	m_leftEnemyHandle = LoadGraph(L"data/Leftenemy.png");
	assert(m_leftEnemyHandle != -1);
	m_rightEnemyHandle = LoadGraph(L"data/Rightenemy.png");
	assert(m_rightEnemyHandle != -1);
	//背景のグラフィックのロード
	m_bgHandle = LoadGraph(L"data/Bg.png");
	assert(m_bgHandle != -1);
	//ショットのグラフィックのロード
	m_shotHandle = LoadGraph(L"data/Shot.png");
	assert(m_shotHandle != -1);
	//UFOのグラフィックのロード
	m_ufoHandle = LoadGraph(L"data/UFO.png");
	assert(m_ufoHandle != -1);
	//Rocketのグラフィックのロード
	m_rocketHandle = LoadGraph(L"data/Rocket.png");
	assert(m_rocketHandle != -1);
	//Rocketの体力のグラフィックのロード
	m_life1Handle = LoadGraph(L"data/Life.png");
	assert(m_life1Handle != -1);
	m_life2Handle = LoadGraph(L"data/Life.png");
	assert(m_life2Handle != -1);
	m_life3Handle = LoadGraph(L"data/Life.png");
	assert(m_life3Handle != -1);
	//爆発のアニメーションのグラフィックのロード
	m_AnimHandle = LoadGraph(L"data/explosion.png");
	assert(m_AnimHandle != -1);
	//ゲームスタート時のボタンのグラフィックのロード
	m_startTitle = LoadGraph(L"data/Start.png");
	assert(StartTitle != -1);
	//敵の爆発アニメーションのグラフィックのロード
	m_enemyEXP = LoadGraph(L"data/enemyEXP.png");
	assert(m_enemyEXP != -1);
	//敵撃破時の音声のグラフィックのロード
	m_destoryEnemy = LoadSoundMem(L"data/Sound/DestoryEnemy.mp3");
	assert(m_destoryEnemy != -1);
	//BGMの音声のグラフィックのロード
	m_bgm = LoadSoundMem(L"data/Sound/Stage1BGM.mp3");
	assert(m_bgm != -1);
	//UFOと弾の衝突時の音声グラフィックのロード
	m_hitHandle = LoadSoundMem(L"data/Sound/UFODamage.mp3");
	assert(m_hitHandle != -1);
	//被弾時の音声のグラフィックのロード
	m_damageHandle = LoadSoundMem(L"data/Sound/Damage.mp3");
	assert(m_damageHandle != -1);
	//ゲームオーバー時の音声のグラフィックのロード
	m_gameover = LoadSoundMem(L"data/Sound/GameOver.mp3");
	assert(m_gameover != -1);
	//決定時の音声のグラフィックのロード
	CheckSE = LoadSoundMem(L"data/Sound/Check.mp3");
	assert(CheckSE != -1);
	//ゲームクリア時の音声のグラフィックのロード
	m_clearSE = LoadSoundMem(L"data/Sound/clear.mp3");
	assert(m_clearSE != -1);

	//BGMの再生
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);

	//プレイヤーのメモリ確保.
	m_pPlayer = new Player{ this };
	//Playerにグラフィックハンドルを渡す
	m_pPlayer->SetHandle(m_playerHandle);

	//背景のメモリ確保
	m_pBg = new Bg{};
	//背景にグラフィックハンドルを渡す
	m_pBg->SetHandle(m_bgHandle);

	//UFOのメモリ確保
	m_pUfo = new UFO{ this };
	//UFOにグラフィックハンドルを渡す
	m_pUfo->SetHandle(m_ufoHandle);
	//UFO落下時のアニメーションのグラフィックハンドルを渡す
	m_pUfo->SetAnimHandle(m_AnimHandle);

	//ステージ2のUFOのメモリ確保
	m_pS2ufo = new S2UFO{ this };
	//ステージ2のUFOにグラフィックハンドルを渡す
	m_pS2ufo->SetHandle(m_ufoHandle);
	//ステージ2のUFO落下時のアニメーションのグラフィックハンドルを渡す
	m_pS2ufo->SetAnimHandle(m_AnimHandle);

	//現在存在する敵の数だけ処理を回す
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//敵にグラフィックハンドルを渡す
		m_pEnemy[i]->SetAnimHandle(m_enemyEXP);
	}

	//Rocketのメモリ確保
	m_pRocket = new Rocket{ this };
	//UFOにグラフィックハンドルを渡す
	m_pRocket->SetHandle(m_rocketHandle);


	//敵の準備.
	//m_pEnemy(vector)何もしなければサイズは0
	//resize関数でkEnemyMaxだけデータを保存できるようにする
	m_pEnemy.resize(kEnemyMax);


	//いつもはコンストラクタでメモリを確保して
	//デストラクタで解放してた
	//ランダムにEnemyLeft,EnemyRight,EnemyToPlayerを確保したい
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
	m_pBeam.resize(kShotMax);
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		m_pBeam[i] = nullptr;	//未使用
	}

	//m_pShot = new ShotBeam;
	////SceneMainの関数を使いたいのでポインタを渡しておく
	////thisで自身のポインタを取得可能
	//m_pShot->SetMain(this);
}

Stage2Scene::~Stage2Scene()
{
	//MakeScreenで生成したグラフィックを削除する
	DeleteGraph(m_shakeHandle);
	//メモリから背景のグラフィックを削除
	DeleteGraph(m_bgHandle);
	//メモリからPlayerのグラフィックを削除
	DeleteGraph(m_playerHandle);
	//メモリから敵のグラフィックを削除
	DeleteGraph(m_leftEnemyHandle);
	DeleteGraph(m_rightEnemyHandle);
	//メモリからアニメーションのグラフィックを削除
	DeleteGraph(m_AnimHandle);
	//メモリからUFOのグラフィックを削除
	DeleteGraph(m_ufoHandle);
	//メモリから画面揺れのグラフィックを削除
	DeleteGraph(m_shakeHandle);
	//メモリからスタートボタンのグラフィックを削除
	DeleteGraph(m_startTitle);
	//メモリから敵の爆発アニメーションのグラフィックを削除
	DeleteGraph(m_enemyEXP);
	//BGMを止める
	StopSoundMem(m_bgm);

	//プレイヤーのメモリ解放.
	delete m_pPlayer;
	m_pPlayer = nullptr;

	//UFOのメモリ開放.
	delete m_pUfo;
	m_pUfo = nullptr;

	delete m_pS2ufo;
	m_pS2ufo = nullptr;

	delete m_pBg;
	m_pBg = nullptr;

	delete m_pRocket;
	m_pRocket = nullptr;


	//メモリが確保されている敵を探して解放していく
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//nullptr以外のものが入っているということはそこにはポインタが入っている
		if (m_pEnemy[i] != nullptr)
		{
			//敵のメモリ解放.
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (m_pBeam[i])
		{
			//nullptrではない場合
			//ビームのメモリ解放
			delete m_pBeam[i];
			m_pBeam[i] = nullptr;
		}
	}
}

void Stage2Scene::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr の場合止まる

	m_pPlayer->Init();
	m_pUfo->Init();
	m_pS2ufo->Init();
	m_pRocket->Init();
}

void Stage2Scene::End()
{

}

void Stage2Scene::Update(Input& input)
{	
	m_pRocket->Update();
	Rect ufoRect = m_pUfo->GetColRect();
	Rect S2UfoRect = m_pS2ufo->GetColRect();
	Rect playerRect = m_pPlayer->GetColRect();
	//OKキー(Enterキー)を押したらゲーム開始
	if (input.IsTriggered("OK"))
	{
		StartFlag = true;
		PlaySoundMem(CheckSE,DX_PLAYTYPE_BACK);
	}
	//ゲームの処理
	if (StartFlag)
	{
		m_pPlayer->S2Update();
		m_pUfo->Update();
		m_pS2ufo->Update();
		//UFOとプレイヤーがぶつかったとき
		if (ufoRect.DistanceCollision(playerRect))
		{
			//ゲームオーバーにする
			m_gameOverFlag = true;
		}

		if (S2UfoRect.DistanceCollision(playerRect))
		{
			m_gameOverFlag = true;
		}

		for (int i = 0; i < m_pBeam.size(); i++)
		{
			//nullptrなら処理は行わない
			if (m_pBeam[i])
			{
				m_pBeam[i]->Update();
				//画面外に出たらメモリ解放
				if (!m_pBeam[i]->isExist())
				{
					//ビームのメモリ解放.
					delete m_pBeam[i];
					m_pBeam[i] = nullptr;
				}
				else
				{
					Rect shotRect = m_pBeam[i]->GetColRect();
					if (shotRect.CirCleCollision(ufoRect))
					{
						PlaySoundMem(m_hitHandle, DX_PLAYTYPE_BACK);
						m_pUfo->JumpPower = 10;
						//ターゲット位置.
						//弾の発射位置から一番近くにいる敵の座標を取得する
						//SceneMainに実装した関数を利用する
						const Vec2 target = GetNearEnemyPos(m_pBeam[i]->m_pos);
						//発射位置からターゲットに向かうベクトル
						Vec2 toTarget = target - m_pBeam[i]->m_pos;
						//正規化　totarget自信を正規化(長さを1に)
						toTarget.normalize();
						//弾の速度をkSpeedに
						m_pBeam[i]->m_vec = toTarget * m_pBeam[i]->m_pSpeed;
						m_pBeam[i]->MoveFlag = true;
					}

					if (shotRect.CirCleCollision(S2UfoRect))
					{
						m_pS2ufo->JumpPower = 10;
						//ターゲット位置.
						//弾の発射位置から一番近くにいる敵の座標を取得する
						//SceneMainに実装した関数を利用する
						const Vec2 target = GetNearEnemyPos(m_pBeam[i]->m_pos);
						//発射位置からターゲットに向かうベクトル
						Vec2 toTarget = target - m_pBeam[i]->m_pos;
						//正規化　totarget自信を正規化(長さを1に)
						toTarget.normalize();
						//弾の速度をkSpeedに
						m_pBeam[i]->m_vec = toTarget * m_pBeam[i]->m_pSpeed;
						m_pBeam[i]->MoveFlag = true;
					}

				}
			}
		}
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (m_pEnemy[i])	//nullptrではないチェック
			{
				Rect enemyRect = m_pEnemy[i]->GetColRect();
				for (int a = 0; a < m_pBeam.size(); a++)
				{
					//nullptrなら処理は行わない
					if (!m_pBeam[a])		continue;
					//画面外に出たらメモリ解放
					Rect shotRect = m_pBeam[a]->GetColRect();
					if (shotRect.CirCleCollision(enemyRect))
					{
						PlaySoundMem(m_destoryEnemy, DX_PLAYTYPE_BACK);
						pos = m_pEnemy[i]->m_pos;
						AnimFlag = true;
						delete m_pBeam[a];
						m_pBeam[a] = nullptr;

						//メモリを解放する
						delete m_pEnemy[i];
						m_pEnemy[i] = nullptr;	//使っていないとわかるように
						m_downEnemyCount++;
					}					
					Rect rocketRect = m_pRocket->GetColRect();
					if (enemyRect.DistanceCollision(rocketRect))
					{
						PlaySoundMem(m_damageHandle, DX_PLAYTYPE_BACK);
						////メモリを解放する
						delete m_pEnemy[i];
						m_pEnemy[i] = nullptr;
						m_damageFlag = true;
					}
				}
			}
		}

		if (AnimFlag == true)
		{
			m_animFrame = (m_animFrame + 1) % (kAnimNum * kAnimInterval);
			m_animFrame++;
		}

		if (m_animFrame >= 120)
		{
			AnimFlag = false;
			m_animFrame = 0;
		}
		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (m_pEnemy[i])	//nullptrではないチェック
			{
				m_pEnemy[i]->S2Update();
				Rect enemyRect = m_pEnemy[i]->GetColRect();
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
			switch (GetRand(2))		//0 or 1 or 2
			{
			case 0:		//Left
				CreateEnemyLeft();

				break;
			case 1:		//Right
				CreateEnemyRight();

				break;
			}
		}

		//画面揺れフレームのカウントダウン
		if (m_isShake)
		{
			m_S2shakeFrame--;

			if (m_S2shakeFrame < 0)
			{
				m_isShake = false;
			}
		}

		if (m_pUfo->m_pos.y >= m_pUfo->m_tq - m_pUfo->m_radius / 2)
		{
			IsGround = true;
		}

		if (m_downEnemyCount == 25)
		{
			manager_.ChangeScene(std::make_shared<GameClearScene>(manager_));
			return;
		}

		if (m_damageFlag == true)
		{
			m_lifeCount++;
			m_pRocket->LifeDecrease();
			m_damageFlag = false;
		}

		if (m_lifeCount == 1)
		{
			DeleteGraph(m_life3Handle);
		}
		else if (m_lifeCount == 2)
		{
			DeleteGraph(m_life2Handle);
		}
		else if (m_lifeCount == 3)
		{
			DeleteGraph(m_life1Handle);
		}

		if (m_pRocket->m_life <= 0)
		{
			m_gameOverFlag = true;
		}

		if (m_gameOverFlag == true)
		{
			manager_.ChangeScene(std::make_shared<GameOverScene>(manager_));
			return;
		}
	}

	//ワイプ処理
	m_wipeFrame++;
	if (m_wipeFrame > kWipeFrame)	m_wipeFrame = kWipeFrame;
}

void Stage2Scene::Draw()
{
	ClearDrawScreen();
	//バックバッファに直接書き込むのではなく、
	//自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_shakeHandle);

	//描画先スクリーンをクリアする
	ClearDrawScreen();

	//主な描画処理
	m_pBg->Draw();
	DrawGraph(Game::kScreenWidth / 2 - 96, Game::kScreenHeight / 2, m_life1Handle, true);
	DrawGraph(Game::kScreenWidth / 2 - 32, Game::kScreenHeight / 2, m_life2Handle, true);
	DrawGraph(Game::kScreenWidth / 2 + 32, Game::kScreenHeight / 2, m_life3Handle, true);
	SetFontSize(64);
	DrawFormatString(Game::kScreenWidth / 2 - 64, 40, GetColor(232, 1, 164), L"%d / 25", m_downEnemyCount);
	m_pRocket->Draw();
	m_pPlayer->Draw();
	m_pUfo->Draw();
	m_pS2ufo->Draw();

	//スタートボタンの描画
	if (StartFlag == false)
	{
		DrawGraph(Game::kScreenWidth / 2 - 450 / 2, Game::kScreenHeight / 2 - 371 / 2, m_startTitle, true);
	}

	//画面揺れの描画処理
	if (m_isShake)
	{
		SetDrawScreen(m_shakeHandle);
		ClearDrawScreen();
	}

	//弾の描画処理
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (!m_pBeam[i])		continue;
		m_pBeam[i]->Draw();
	}

	//アニメーション生成
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			if (AnimFlag == true)
			{
				int index = m_animFrame / kAnimInterval;
				int srcX = (index % kRow) * kAnimWidth;
				int srcY = (index / kLine) * kAnimHeight;

				DrawRectRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y),
					srcX, srcY, kAnimWidth, kAnimHeight,
					1.0, 0.0,
					m_enemyEXP, true, false);
			}
		}
	}

	if (IsGround == true)
	{
		ShakeScreen(m_S2shakeFrame, kShakeSize);
		IsGround = false;
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Draw();
		}
	}

	//弾の数を表示する
	int shotNum = 0;
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (m_pBeam[i]) shotNum++;
	}

	int enemyNum = 0;
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]) enemyNum++;
	}

#ifdef _DEBUG
	//プレイヤーの位置をデバッグ表示する
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum%d", shotNum);
	DrawFormatString(8, 72, GetColor(255, 255, 255), "EnemyNum%d", enemyNum);
	DrawFormatString(8, 88, GetColor(255, 255, 255), "残りライフ%d", m_pRocket->m_life);
#endif
	//バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;
	if (m_S2shakeFrame > 0)
	{
		//画面揺れ
		screenX = GetRand(8) - 4;
		screenY = GetRand(8) - 4;
	}

	//m_wipeFrameから描画する範囲を計算する
	//m_wipeFrameゲーム開始時に0,
	//毎フレーム加算されてkWipeFrame(30)まで変化する
	//wipeRateはm_wipeFrameの変化に合わせて0.0->1.0に変化する
	float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(kWipeFrame);
	float wipeHeight = Game::kScreenHeight * wipeRate;

	/*DrawRectGraph(screenX,screenY,
		0,0,Game::kScreenWidth, wipeHeight,
		m_gameScreenHandle, true, false);*/

		//offsetの値をwipeの進行に合わせて320->0に変化させたい

		//0->320に変化させるのはわかりやすい  320*wipeRate

	float offset = 320 * (1.0f - wipeRate);

	//画面の上から1ラインずつ描画を行っている
	for (int y = 0; y < Game::kScreenHeight; y++)
	{
		float x = sinf(y * 0.05f) * offset;
		DrawRectGraph(x, y,
			0, y, Game::kScreenWidth, 1,
			m_gameScreenHandle, true, false);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	if (m_isShake)
	{

		int x = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		int y = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		DrawGraph(x, y, m_shakeHandle, true);
#ifdef _DEBUG
		//プレイヤーの位置をデバッグ表示する
		Vec2 playerPos = m_pPlayer->GetPos();
		DrawFormatString(8, 24, GetColor(255, 255, 255),
			"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
		DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum%d", shotNum);
		DrawFormatString(8, 72, GetColor(255, 255, 255), "EnemyNum%d", enemyNum);
		DrawFormatString(8, 88, GetColor(255, 255, 255), "残りライフ%d", m_pRocket->m_life);
		DrawFormatString(8, 104, GetColor(255, 255, 255), "倒した敵の数%d", m_downEnemyCount);
		DrawFormatString(8, 56, GetColor(255, 255, 255), "%f", m_pUfo->m_angle);
#endif
	}
}

Vec2 Stage2Scene::GetNearEnemyPos(Vec2 pos)
{
	//敵がいない場合は適当な座標を返す
	Vec2 result{ 0,0 };
	//最初の敵チェック済みフラグ
	bool isFirst = false;


	//一番近い敵キャラクターの座標をresultに入れる
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//使われていない敵はチェックしない
		if (!m_pEnemy[i])	continue;

		//ここにきている時点でm_pEnemy[i]はnullptrでないことは確定

		//すでに消えることが確定している敵はチェックしない
		if (!m_pEnemy[i]->isExist()) continue;

		//pos とm_pEnemy[i]の距離をチェックする

		if (isFirst)
		{
			//1体目の敵
			//距離がいくら離れていようとも現時点では一番近い敵
			result = m_pEnemy[i]->GetPos();
			isFirst = false;
		}
		else
		{
			//2体目以降の敵
			//resultの中には一番近い敵の座標が入ってくる

			//今までチェックした中で一番近い敵との距離
			Vec2 toNear = result - pos;	//posから暫定一位の座標に向かうベクトル

			//チェックする敵との距離
			Vec2 toEnemy = m_pEnemy[i]->GetPos() - pos;	//posからチェック中の敵に向かうベクトル

			//処理を軽くするため居y理の比較を行う場合は距離の2乗で比較を行う
			if (toNear.sqLength() > toEnemy.sqLength())
			{
				//今チェックしている敵への距離が暫定一位よりも短い場合
				//今チェックしている敵を暫定一位に
				result = m_pEnemy[i]->GetPos();
			}
			//暫定一位の方が今チェックしている敵より近い場合は何もしない
		}
	}
	//すべての敵のチェックを行ったのでこいつが一位で確定
	return result;
}

bool Stage2Scene::AddShot(ShotBeam* pBeam)
{
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		//使用中なら次のチェックへ
		if (m_pBeam[i])	continue;

		//ここに来たということはm_pShot[i] == nullptr
		m_pBeam[i] = pBeam;
		//登録したら終了
		return true;
	}

	//ここに来た、ということはm_pShotにポインタを登録できなかった
	delete pBeam;
	return false;
}

void Stage2Scene::ShakeScreen(int frame, int size = kShakeSize)
{
	m_S2shakeFrame = frame;
	m_shakeSize = size;
	m_isShake = true;
}

void Stage2Scene::CreateEnemyLeft()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_leftEnemyHandle);
			m_pEnemy[i]->Start();
			return;	//メモリを確保したら以降はチェックしない
		}
	}
}

void Stage2Scene::CreateEnemyRight()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_rightEnemyHandle);
			m_pEnemy[i]->Start();
			return;	//メモリを確保したら以降はチェックしない
		}
	}
}