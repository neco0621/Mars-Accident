#include "EnemyRight.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

namespace
{
	constexpr float kSpeed = 1.0f;

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

	m_pos += m_vec;

	//当たり判定の更新
	UpdateCollision();

	//画面外に出たら存在を消す
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_pos.x < 0.0f - width / 2)
	{
		m_isExist = false;
	}
}

void EnemyRight::Start()
{
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	m_pos.x = Game::kScreenWidth;
	m_pos.y = m_tq;

	//1フレーム当たりの移動ベクトルを決定する
	m_vec.x = -kSpeed;
	m_vec.y = 0.0f;
}