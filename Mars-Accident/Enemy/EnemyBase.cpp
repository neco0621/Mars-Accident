#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

namespace
{
	constexpr float kSpeed = 3.0f;
}

EnemyBase::EnemyBase() :
	m_handle(-1),
	m_isExist(false),
	m_pos()	//省略可
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
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;
}

void EnemyBase::Draw()
{
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;

	assert(m_handle != -1);
	//DrawTurnGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	//m_colRect.Set(m_pos.x, m_pos.y, width, height);
	//m_colRect.SetLT(m_pos.x - width / 2, m_pos.y, width, height);
	//中心座標を指定して当たり判定のRectを生成する
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}