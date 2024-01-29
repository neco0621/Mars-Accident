#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "TitleScene.h"
#include "DxLib.h"
#include "../Player.h"
#include "../UFO.h"
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
	constexpr int kEnemyMax = 8;
	//何フレーム沖に敵が登場するか.
	constexpr int kEnemyInterval = 90;

	//画面内に一度に出てくる弾の最大数.
	constexpr int kShotMax = 256;

	//画面がワイプするのにかかるフレーム数.
	constexpr int kWipeFrame = 30;

	constexpr int kShakeSize = 10;

	// アニメーション間隔
	constexpr int kAnimInterval = 3;
	// 高さ・幅
	constexpr int kAnimWidth = 100;
	constexpr int kAnimHeight = 100;
	// 縦横数
	constexpr int kRow = 10;
	constexpr int kLine = 7;
	// アニメーション数
	constexpr int kAnimNum = 65;
}

Stage1Scene::Stage1Scene(SceneManager& manager) : Scene(manager),
	m_enemyInterval(0),
	m_shakeFrame(0),
	m_wipeFrame(0),
	m_toNear(Game::kScreenWidth,Game::kScreenHeight),
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
	m_animFrame(0)
{
	//ゲーム画面描画先の生成.
	//画面サイズと同じ大きさのグラフィックデータを作成する.
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);
	m_shakeHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	//グラフィックのロード.
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_leftEnemyHandle = LoadGraph("data/Leftenemy.png");
	assert(m_leftEnemyHandle != -1);
	m_rightEnemyHandle = LoadGraph("data/Rightenemy.png");
	assert(m_rightEnemyHandle != -1);
	m_bgHandle = LoadGraph("data/Bg.png");
	assert(m_bgHandle != -1);
	m_shotHandle = LoadGraph("data/Shot.png");
	assert(m_shotHandle != -1);
	m_ufoHandle = LoadGraph("data/UFO.png");
	assert(m_ufoHandle != -1);
	m_rocketHandle = LoadGraph("data/Rocket.png");
	assert(m_rocketHandle != -1);
	m_life1Handle = LoadGraph("data/Life.png");
	assert(m_life1Handle != -1);
	m_life2Handle = LoadGraph("data/Life.png");
	assert(m_life2Handle != -1);
	m_life3Handle = LoadGraph("data/Life.png");
	assert(m_life3Handle != -1);
	m_AnimHandle = LoadGraph("data/explosion.png");
	assert(m_AnimHandle != -1);
	StartTitle = LoadGraph("data/Start.png");
	assert(StartTitle != -1);
	m_enemyEXP = LoadGraph("data/enemyEXP.png");
	assert(m_enemyEXP != -1);
	

	//プレイヤーのメモリ確保.
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	//Playerにグラフィックハンドルを渡す

	m_pUfo = new UFO{ this };
	m_pUfo->SetHandle(m_ufoHandle);


	m_pUfo->SetAnimHandle(m_AnimHandle);

	m_pBg = new Bg{};
	m_pBg->SetHandle(m_bgHandle);

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->SetAnimHandle(m_enemyEXP);
	}

	m_pRocket = new Rocket{ this };
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

Stage1Scene::~Stage1Scene()
{
	//MakeScreenで生成したグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);
	//メモリからグラフィックを削除
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_leftEnemyHandle);
	DeleteGraph(m_rightEnemyHandle);
	DeleteGraph(m_AnimHandle);
	DeleteGraph(m_shakeHandle);
	DeleteGraph(StartTitle);

	//プレイヤーのメモリ解放.
	delete m_pPlayer;
	m_pPlayer = nullptr;
	//UFOのメモリ開放.
	delete m_pUfo;
	m_pUfo = nullptr;

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

void Stage1Scene::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr の場合止まる

	m_pPlayer->Init();
	m_pUfo->Init();
	m_pRocket->Init();
	/*m_pAnim->AnimationStart(
		&AnimExpel,
		1000,
		500	);*/
}

void Stage1Scene::End()
{

}

void Stage1Scene::Update(Input& input)
{
	Rect ufoRect = m_pUfo->GetColRect();
	Rect playerRect = m_pPlayer->GetColRect();
	if(input.IsTriggered("space"))
	{
		StartFlag = true;
	}
	if (StartFlag)
	{
		m_pPlayer->Update();
		m_pUfo->Update();
		m_pRocket->Update();

		if (ufoRect.DistanceCollision(playerRect))
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
						AnimFlag = true;
						delete m_pBeam[a];
						m_pBeam[a] = nullptr;

						//メモリを解放する
						delete m_pEnemy[i];
						m_pEnemy[i] = nullptr;	//使っていないとわかるように
						m_downEnemyCount++;						
					}
					Rect ufoRect = m_pUfo->GetColRect();
					if (ufoRect.CirCleCollision(enemyRect))
					{
						//メモリを解放する
						delete m_pEnemy[i];
						m_pEnemy[i] = nullptr;	//使っていないとわかるように
					}
					Rect rocketRect = m_pRocket->GetColRect();
					if (enemyRect.DistanceCollision(rocketRect))
					{
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
				m_pEnemy[i]->Update();
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

		if (m_isShake)
		{
			m_shakeFrame--;

			if (m_shakeFrame < 0)
			{
				m_isShake = false;
			}
		}

		if (m_pUfo->m_pos.y >= m_pUfo->m_tq - m_pUfo->m_radius / 2)
		{
			IsGround = true;
		}

		if (m_downEnemyCount == 5)
		{
			manager_.ChangeScene(std::make_shared<Stage2Scene>(manager_));
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

void Stage1Scene::Draw()
{	
	//バックバッファに直接書き込むのではなく、
	//自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_gameScreenHandle);

	//描画先スクリーンをクリアする
	ClearDrawScreen();

	m_pBg->Draw();
	DrawGraph(Game::kScreenWidth / 2 - 96, Game::kScreenHeight / 2,m_life1Handle, true);
	DrawGraph(Game::kScreenWidth / 2 - 32, Game::kScreenHeight / 2, m_life2Handle, true);
	DrawGraph(Game::kScreenWidth / 2 +32, Game::kScreenHeight / 2, m_life3Handle, true);
	DrawBox(0,Game::kScreenHeight * 0.75 + 32,Game::kScreenWidth,Game::kScreenHeight, 0x84331F,true);
	m_pRocket->Draw();
	m_pPlayer->Draw();
	m_pUfo->Draw();
	if (StartFlag == false)
	{
		DrawGraph(Game::kScreenWidth / 2 - 450 / 2, Game::kScreenHeight / 2 - 371 / 2, StartTitle, true);
	}
	if (m_isShake)
	{
		SetDrawScreen(m_shakeHandle);
		ClearDrawScreen();
	}

	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (!m_pBeam[i])		continue;
		m_pBeam[i]->Draw();
	}
	/*if (IsGround)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		
		int x = GetRand(kWipeFrame) - static_cast<int>(kWipeFrame * 2);
		int y = GetRand(kWipeFrame) - static_cast<int>(kWipeFrame * 2);
		DrawGraph(x,y,m_gameScreenHandle,true);
		int Count = 0;
		Count++;
		if (Count < 120)
		{
			IsGround = false;
		}
	}*/
	
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			if (AnimFlag == true)
			{
				int index = m_animFrame / kAnimInterval;
				int srcX = (index % kRow) * kAnimWidth;
				int srcY = (index / kLine) * kAnimHeight;

				DrawRectRotaGraph(static_cast<int>(m_pEnemy[i]->m_pos.x), static_cast<int>(m_pEnemy[i]->m_pos.y),
					srcX, srcY, kAnimWidth, kAnimHeight,
					1.0, 0.0,
					m_AnimHandle, true, false);
			}
		}
	}
	

	if (IsGround == true)
	{
		ShakeScreen(m_shakeFrame, kShakeSize);
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


	//バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;

	//m_wipeFrameから描画する範囲を計算する
	//m_wipeFrameゲーム開始時に0,
	//毎フレーム加算されてkWipeFrame(30)まで変化する
	//wipeRateはm_wipeFrameの変化に合わせて0.0->1.0に変化する
	float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(kWipeFrame);
	int wipeHeight = Game::kScreenHeight * wipeRate;

	/*DrawRectGraph(screenX,screenY,
		0,0,Game::kScreenWidth, wipeHeight,
		m_gameScreenHandle, true, false);*/

		//offsetの値をwipeの進行に合わせて320->0に変化させたい

		//0->320に変化させるのはわかりやすい  320*wipeRate

	int offset = 320 * (1.0f - wipeRate);

	//画面の上から1ラインずつ描画を行っている
	for (int y = 0; y < Game::kScreenHeight; y++)
	{
		int x = sinf(y * 0.05f) * offset;
		DrawRectGraph(x, y,
			0, y, Game::kScreenWidth, 1,
			m_gameScreenHandle, true, false);
	}

	if (m_isShake)
	{
		SetDrawScreen(DX_SCREEN_BACK);

		int x = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		int y = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		DrawGraph(x, y, m_shakeHandle, true);
	}
#ifdef _DEBUG
	//プレイヤーの位置をデバッグ表示する
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum%d", shotNum);
	DrawFormatString(8, 72, GetColor(255, 255, 255), "EnemyNum%d", enemyNum);
	DrawFormatString(8, 88, GetColor(255, 255, 255), "残りライフ%d", m_pRocket->m_life);
	DrawFormatString(8, 104, GetColor(255, 255, 255), "倒した敵の数%d", m_downEnemyCount);
	DrawFormatString(8, 56, GetColor(255, 255, 255),"%f", m_pUfo->m_angle);
#endif
}

Vec2 Stage1Scene::GetNearEnemyPos(Vec2 pos)
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

bool Stage1Scene::AddShot(ShotBeam* pBeam)
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

void Stage1Scene::ShakeScreen(int frame, int size = kShakeSize)
{
	m_shakeFrame = frame;
	m_shakeSize = size;
	m_isShake = true;
}

void Stage1Scene::CreateEnemyLeft()
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

void Stage1Scene::CreateEnemyRight()
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
