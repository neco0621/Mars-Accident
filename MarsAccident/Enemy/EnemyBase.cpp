#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

namespace
{
	constexpr int kRadius = 30;
}

EnemyBase::EnemyBase() :
	//初期化
	m_handle(-1),
	m_radius(kRadius),
	m_isExist(false),
	m_pos(),//省略可.
	m_centerX(m_pos.x),
	m_centerY(m_pos.y),
	m_tq(Game::kScreenHeight * 0.75f)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	//存在しない敵の処理はしない.
	if (!m_isExist)		return;
}

void EnemyBase::Draw()
{
	//存在しない敵の処理はしない.
	if (!m_isExist)
		return;

	assert(m_handle != -1);
	//敵の描画処理.
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//当たり判定の表示.
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	//中心座標を指定して当たり判定のRectを生成する.
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
}
