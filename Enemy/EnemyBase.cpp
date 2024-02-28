#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"
#include "../Scene/Stage1Scene.h"
#include "../Scene/TutorialScene.h"

#include <cassert>

//Enemy�Ŏg�p����萔
namespace
{
	//�����蔻��̔��a
	constexpr int kRadius	    = 30;

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

	//��ʂ�4����3�̈ʒu
	constexpr float kTq			= Game::kScreenHeight * 0.75f;
}

EnemyBase::EnemyBase() :
	//������
	m_handle(-1),
	m_animHandle(-1),
	m_radius(kRadius),
	m_isExist(false),
	m_pos(),
	m_centerX(m_pos.x),
	m_centerY(m_pos.y),
	m_tq(kTq),
	m_pTuScene(nullptr),
	m_pS1Scene(nullptr),
	m_pS2Scene(nullptr)
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

	//�n���h���Ɏw�肵���O���t�B�b�N�������Ă��邩�ǂ���
	assert(m_handle != -1);

	//�G�̕`�揈��.
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y + 10),
		1.0, 0.0,
		m_handle, true, false);	
	

#ifdef _DEBUG
	//�����蔻��̕\��.
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

//�G�����̍X�V����
void EnemyBase::UpdateCollision()
{
	//�c�̃T�C�Y�Ɖ��̃T�C�Y���擾
	int width = 0;
	int height = 0;

	//�O���t�̃T�C�Y���擾
	GetGraphSize(m_handle, &width, &height);

	//���S���W���w�肵�ē����蔻���Rect�𐶐�����.
	m_colRect.SetRadius(m_pos.x, m_pos.y + 10, m_radius);
}
