#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	//�G�̈ړ����鑬�x.
	constexpr float kSpeed = 3.0f;
}

EnemyBase::EnemyBase() :
	//������
	m_handle(-1),
	m_isExist(false),
	m_pos()	//�ȗ���.
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
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	//���S���W���w�肵�ē����蔻���Rect�𐶐�����.
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}