#include "EnemyRight.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

namespace
{
	//敵の移動速度
	constexpr float kSpeed		= 1.0f;
	//Stage2での移動速度
	constexpr float s2Speed		= 1.3f;

	// アニメーション間隔
	constexpr int kAnimInterval = 3;
	// 高さ・幅
	constexpr int kAnimWidth	= 100;
	constexpr int kAnimHeight	= 100;
	// 縦横数
	constexpr int kRow			= 10;
	constexpr int kLine			= 7;
	// アニメーション数
	constexpr int kAnimNum		= 65;
}

EnemyRight::EnemyRight() 
{

}

EnemyRight::~EnemyRight()
{

}

void EnemyRight::Update()
{
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;

	//現在位置に移動量を追加
	m_pos += m_vec;

	//当たり判定の更新
	UpdateCollision();

	//グラフのサイズの取得
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//画面外に出たら存在を消す
	if (m_pos.x < 0.0f - width / 2)
	{
		m_isExist = false;
	}
}

//Stage2での更新処理
void EnemyRight::S2Update()
{
	//存在しない敵の処理はしない.
	if (!m_isExist)		return;

	//移動量をStage2のものに変更
	m_vec.x = -s2Speed;

	//現在位置に移動量を追加
	m_pos += m_vec;


	//当たり判定の更新
	UpdateCollision();

	//グラフのサイズを取得
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//敵が画面外に行ったら生存フラグをfalseにする
	if (m_pos.x < 0.0f - width / 2)
	{
		m_isExist = false;
	}
}

//敵の登場処理
void EnemyRight::Start()
{
	//画面中央に敵キャラクターを登場させる
	m_isExist = true;

	//グラフのサイズを取得
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//X座標を右画面端に設定
	m_pos.x = Game::kScreenWidth;
	//Y座標の位置を調整
	m_pos.y = m_tq;

	//1フレーム当たりの移動ベクトルを決定する
	m_vec.x = -kSpeed;
	m_vec.y = 0.0f;
}