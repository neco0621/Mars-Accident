#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

EnemyBase::EnemyBase() :
	//‰Šú‰»
	m_handle(-1),
	m_radius(16),
	m_isExist(false),
	m_pos(),//È—ª‰Â.
	m_centerX(m_pos.x),
	m_centerY(m_pos.y)
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
	//‘¶İ‚µ‚È‚¢“G‚Ìˆ—‚Í‚µ‚È‚¢.
	if (!m_isExist)		return;
}

void EnemyBase::Draw()
{
	//‘¶İ‚µ‚È‚¢“G‚Ìˆ—‚Í‚µ‚È‚¢.
	if (!m_isExist)
		return;

	assert(m_handle != -1);
	//“G‚Ì•`‰æˆ—.
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//“–‚½‚è”»’è‚Ì•\¦.
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	//’†SÀ•W‚ğw’è‚µ‚Ä“–‚½‚è”»’è‚ÌRect‚ğ¶¬‚·‚é.
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
}
