#include "EnemyRight.h"
#include "DxLib.h"
#include "../Game.h"

#include <cassert>

namespace
{
	constexpr float kSpeed = 1.0f;
}

EnemyRight::EnemyRight()
{

}

EnemyRight::~EnemyRight()
{

}

void EnemyRight::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist)
		return;

	m_pos += m_vec;

	//�����蔻��̍X�V
	UpdateCollision();

	//��ʊO�ɏo���瑶�݂�����
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

	//1�t���[��������̈ړ��x�N�g�������肷��
	m_vec.x = -kSpeed;
	m_vec.y = 0.0f;
}