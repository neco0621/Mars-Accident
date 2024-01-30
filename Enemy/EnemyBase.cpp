#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"
#include "../Scene/Stage1Scene.h"

#include <cassert>

namespace
{
	constexpr int kRadius = 30;

	// �A�j���[�V�����Ԋu
	constexpr int kAnimInterval = 3;
	// �����E��
	constexpr int kAnimWidth = 100;
	constexpr int kAnimHeight = 100;
	// �c����
	constexpr int kRow = 10;
	constexpr int kLine = 7;
	// �A�j���[�V������
	constexpr int kAnimNum = 65;
}

EnemyBase::EnemyBase() :
	//������
	m_handle(-1),
	m_radius(kRadius),
	m_isExist(false),
	m_pos(),//�ȗ���.
	m_centerX(m_pos.x),
	m_centerY(m_pos.y),
	m_tq(Game::kScreenHeight * 0.75f),
	m_animFrame(0),
	enemyEXPFlag(false)
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
	//���݂��Ȃ��G�̏����͂��Ȃ�.
	if (!m_isExist)		return;
}

void EnemyBase::S2Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�.
	if (!m_isExist)		return;
}

void EnemyBase::Draw()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�.
	if (!m_isExist)
		return;

	assert(m_handle != -1);
	//�G�̕`�揈��.
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, true, false);
	
#ifdef _DEBUG
	//�����蔻��̕\��.
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	//���S���W���w�肵�ē����蔻���Rect�𐶐�����.
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
}
