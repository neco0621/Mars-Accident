#include "ShotBeam.h"
#include "Game.h"
#include "DxLib.h"
#include "Scene/SceneMain.h"
#include "UFO.h"
#include "Player.h"

#include <cassert>

namespace
{
	//�萔�̒�`
	constexpr float kSpeed = 6.0f;

	//	�V���b�g�̑傫��
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	constexpr float kRadius = 8.0f;

	//�o���Ă����ߋ��̈ʒu���̐�
	constexpr int kPosLogNum = 12;

	//�e�̏�����ւ̈ړ����x
	constexpr float kMove = 8.0f;
}

ShotBeam::ShotBeam() :
	m_isExist(false),
	m_pPlayer(nullptr),
	m_radius(kRadius),
	m_handle(-1),
	m_centerX(m_pos.x),
	m_centerY(m_pos.y),
	m_pSpeed(kSpeed),
	m_pMove(kMove),
	MoveFlag(false),
	m_z(0,-25)
{
	m_posLog.resize(kPosLogNum);
}

ShotBeam::~ShotBeam()
{
}

void ShotBeam::Init()
{
}

void ShotBeam::Update()
{

	if (!m_isExist) return;
	//�����蔻��̍X�V
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
	m_colRect.SetCenter(m_centerX, m_centerY, kWidth, kHeight);

	//�ʒu�̃��O�����炷
	for (int i = m_posLog.size() - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	//1�t���[�����̈ʒu��������
	m_posLog[0] = m_pos;

	m_pos += m_vec;
	

	//��ʊO�ɏo������
	//�ߋ��̕\���ʒu���܂߂Ă��ׂĉ�ʊO�ɏo����I��
	bool isOut = false;	//�`�F�b�N���̍��W����ʊO���ǂ����t���O

	if (MoveFlag == false)
	{
		m_pos.y -= kMove;
	}

	//�ߋ����O����ʓ��ɂ��邩���`�F�b�N����
	for (int i = 0; i < m_posLog.size(); i++)
	{
		isOut = false;
		if (m_posLog[i].x < 0.0f - kWidth / 2)	isOut = true;
		if (m_posLog[i].x > Game::kScreenWidth + kWidth / 2)	isOut = true;
		if (m_posLog[i].y < 0.0f - kHeight / 2) isOut = true;
		if (m_posLog[i].y > Game::kScreenHeight + kHeight / 2)	isOut = true;

		//�`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
		if (!isOut) return;
	}
	//�����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotBeam::Draw()
{
	if (!m_isExist) return;


	//�c���̕\��
	//DrawCircle(m_pos.x,m_pos.y, kRadius,GetColor(255,0,0),m_handle);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < m_posLog.size(); i++)
	{
		for (int lineNum = 0; lineNum < 16; lineNum++)
		{
			int startX = m_pos.x;
			int startY = m_pos.y;
			int endX = m_posLog[i].x;
			int endY = m_posLog[i].y;

			//��������͂���ĂȂ����e
			//�������悭���邽�߂Ɏg��
			float angle = GetRand(359) / 360.0f * DX_TWO_PI_F;
			float len = GetRand(10) - 2;
			startX += cosf(angle) * len;
			startY += sinf(angle) * len;
			endX += cosf(angle) * len;
			endY += cosf(angle) * len;

			DrawLine(startX, startY, endX, endY, GetColor(16, 2, 1), kWidth);
		}
	}
	//�\�����[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//int alpha = 255;
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//DrawLine(m_pos.x,m_pos.y, m_posLog[0].x, m_posLog[1].y,GetColor(255,255,0),kWidth);

	//for (int i = 1; i < m_posLog.size(); i++)
	//{
	//	alpha -= 20;
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//	DrawLine(m_posLog[i - 1].x, m_posLog[i - 1].y, m_posLog[i].x, m_posLog[i].y, GetColor(255, 255, 0), kWidth);
	//}
	////�\�����[�h�����ɖ߂�
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	//�e�̓����蔻��f�o�b�O�\��
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

void ShotBeam::Start(Vec2 pos)
{
	//SceneMain�̐ݒ�Y��`�F�b�N
	assert(m_pMain);	//m_pMain == nullptr�Ȃ�~�܂�


	m_isExist = true;
	//�����z�u�̌���
	m_pos = pos + m_z;
	//��ԋ߂��G�̕����Ɉړ�����

	//�ߋ��̈ʒu�������������_�ł͏����ʒu�Ɠ����ɂ��Ă��܂�
	//�c�����ςȈʒu�ɕ\������Ȃ��悤�ɂ��邽��
	for (int i = 0; i < m_posLog.size(); i++)
	{
		m_posLog[i] = m_pos;
	}
}


