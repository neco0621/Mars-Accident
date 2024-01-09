#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

namespace
{
	//“G‚ÌˆÚ“®‚·‚é‘¬“x.
	constexpr float kSpeed = 3.0f;
}

EnemyBase::EnemyBase() :
	//‰Šú‰»
	m_handle(-1),
	m_isExist(false),
	m_pos()	//È—ª‰Â.
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
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	//’†SÀ•W‚ğw’è‚µ‚Ä“–‚½‚è”»’è‚ÌRect‚ğ¶¬‚·‚é.
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}
