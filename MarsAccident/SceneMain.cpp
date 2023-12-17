#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "UFO.h"
#include "Pad.h"
#include "Rect.h"
#include "Rocket.h"
#include "Game.h"
#include "Bg.h"

//登場する敵
//#include "EnemyBase.h"
#include "EnemyLeft.h"
#include "EnemyRight.h"

//登場するショット
#include "ShotBeam.h"

#include <cassert>

namespace
{
	//一度に登場できる最大の数.
	constexpr int kEnemyMax = 64;
	//何フレーム沖に敵が登場するか.
	constexpr int kEnemyInterval = 60;

	//画面内に一度に出てくる弾の最大数.
	constexpr int kShotMax = 256;

	//画面がワイプするのにかかるフレーム数.
	constexpr int kWipeFrame = 30;
}

SceneMain::SceneMain() :
	m_enemyInterval(0),
	m_shakeFrame(0),
	m_wipeFrame(0),
	m_toNear(Game::kScreenWidth,Game::kScreenHeight)
{
	//ゲーム画面描画先の生成.
	//画面サイズと同じ大きさのグラフィックデータを作成する.
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//グラフィックのロード.
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/Bg.png");
	assert(m_bgHandle != -1);
	m_rocketHandle = LoadGraph("data/Rocket.png");
	assert(m_bgHandle != -1);

	//プレイヤーのメモリ確保.
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	//Playerにグラフィックハンドルを渡す

	m_pUfo = new UFO{ this };


	m_pBg = new Bg{};
	m_pBg->SetHandle(m_bgHandle);

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

SceneMain::~SceneMain()
{
	//MakeScreenで生成したグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);
	//メモリからグラフィックを削除
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_rocketHandle);

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

void SceneMain::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr の場合止まる

	m_pPlayer->Init();
	m_pUfo->Init();
}

void SceneMain::End()
{

}

void SceneMain::Update()
{
	Rect ufoRect = m_pUfo->GetColRect();
	Rect playerRect = m_pPlayer->GetColRect();
	
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		//nullptrなら処理は行わない
		if (!m_pBeam[i])		continue;

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
				m_pUfo->m_pos.y -=  (m_pUfo->v * m_pUfo->dt) ;//速度から座標
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
	m_pPlayer->Update();
	m_pUfo->Update();
	
	

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

	//ワイプ処理
	m_wipeFrame++;
	if (m_wipeFrame > kWipeFrame)	m_wipeFrame = kWipeFrame;



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
	m_shakeFrame--;
	
}

void SceneMain::Draw()
{
	//バックバッファに直接書き込むのではなく、
	//自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_gameScreenHandle);

	//描画先スクリーンをクリアする
	ClearDrawScreen();

	m_pBg->Draw();
	m_pPlayer->Draw();
	m_pUfo->Draw();
	m_pRocket->Draw();

	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (!m_pBeam[i])		continue;
		m_pBeam[i]->Draw();
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Draw();
		}
	}

	

	//プレイヤーの位置をデバッグ表示する
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);

	//弾の数を表示する
	int shotNum = 0;
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (m_pBeam[i]) shotNum++;
	}
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum%d", shotNum);

	//バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;
	if (m_shakeFrame > 0)
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
}

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) 
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
		//チェックする敵との距離
		Vec2 toEnemy = m_pEnemy[i]->GetPos();	//posからチェック中の敵に向かうベクトル
		//今までチェックした中で一番近い敵との距離
		if (toEnemy.sqLength() < m_toNear.sqLength())
		{
			m_toNear = toEnemy;	//posから暫定一位の座標に向かうベクトル
		}
	}
	//すべての敵のチェックを行ったのでこいつが一位で確定
	return m_toNear;
}

bool SceneMain::AddShot(ShotBeam* pBeam)
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

void SceneMain::CreateEnemyLeft()
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

void SceneMain::CreateEnemyRight()
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