#include "EnemyLeft.h"
#include "../Game.h"
#include "DxLib.h"

#include <cassert>

namespace
{
	//�G�̈ړ����x.
	constexpr float kSpeed		= 1.0f;
	//Stage2�ł̈ړ����x
	constexpr float s2Speed		= 1.3f;

	// �A�j���[�V�����Ԋu
	constexpr int kAnimInterval = 3;
	// �����E��
	constexpr int kAnimWidth	= 100;
	constexpr int kAnimHeight	= 100;
	// �c����
	constexpr int kRow			= 10;
	constexpr int kLine			= 7;
	// �A�j���[�V������
	constexpr int kAnimNum		= 65;
}

EnemyLeft::EnemyLeft() : EnemyBase()
//EnemyLeft()	//�����I�ɌĂ�.
{
	//���N���X(EnemyBase)�̃R���X�g���N�^��
	// �����I�ɌĂ΂Ȃ��Ă������ŌĂ΂��.
}

EnemyLeft::~EnemyLeft()
{
	//�f�X�g���N�^�̌Ă΂��(�͂�).
}

void EnemyLeft::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�.
	if (!m_isExist)		return;

	//���݈ʒu�Ɉړ��ʂ�ǉ�
	m_pos += m_vec;

	//�����蔻��̍X�V
	UpdateCollision();

	//�O���t�̃T�C�Y�̎擾
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//�G����ʊO�ɍs�����琶���t���O��false�ɂ���
	if (m_pos.x > Game::kScreenWidth + width / 2)
	{
		m_isExist = false;
	}
}

//Stage2�ł̍X�V����
void EnemyLeft::S2Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�.
	if (!m_isExist)		return;
	
	//�ړ��ʂ�Stage2�̂��̂ɕύX
	m_vec.x = s2Speed;
	
	//���݈ʒu�Ɉړ��ʂ�ǉ�
	m_pos += m_vec;


	//�����蔻��̍X�V
	UpdateCollision();

	//�O���t�̃T�C�Y���擾
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//�G����ʊO�ɍs�����琶���t���O��false�ɂ���
	if (m_pos.x > Game::kScreenWidth + width / 2)
	{
		m_isExist = false;
	}
}

//�G�̓o�ꏈ��
void EnemyLeft::Start()
{
	//��ʒ����ɓG�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	//�O���t�̃T�C�Y���擾
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//X���W��0�ɐݒ�
	m_pos.x = 0;
	//Y���W�̈ʒu�𒲐�
	m_pos.y = m_tq;

	/*m_pos.x = static_cast<float>(0 - width / 2);
	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);*/

	//1�t���[��������̈ړ��x�N�g�������肷��
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}

