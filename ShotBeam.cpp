#include "ShotBeam.h"
#include "Game.h"
#include "DxLib.h"
#include "Scene/TutorialScene.h"
#include "Scene/Stage1Scene.h"
#include "UFO.h"
#include "Player.h"

#include <cassert>

namespace
{
	//�萔�̒�`
	constexpr float kSpeed = 16.0f;

	//	�V���b�g�̑傫��
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	constexpr float kRadius = 8.0f;

	//�o���Ă����ߋ��̈ʒu���̐�
	constexpr int kPosLogNum = 12;

	//�e�̏�����ւ̈ړ����x
	constexpr float kMove = 16.0f;
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
	m_z(0,-25),
	m_soundHandle(-1)
{
	m_posLog.resize(kPosLogNum);
	m_soundHandle = LoadSoundMem("data/Sound/ShotBeam.mp3");
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

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}

	m_pos += m_vec;
	

	//��ʊO�ɏo������
	//�ߋ��̕\���ʒu���܂߂Ă��ׂĉ�ʊO�ɏo����I��
	bool isOut = false;	//�`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (MoveFlag == false)
	{
		m_pos.y -= kMove;
	}
	//�����蔻��̍X�V
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
	m_colRect.SetCenter(m_centerX, m_centerY, kWidth, kHeight);
}

void ShotBeam::Draw()
{
	if (!m_isExist) return;	
	//�c���̕\��
	DrawCircle(m_pos.x, m_pos.y, kRadius, GetColor(255, 0, 0), true);
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
	ChangeVolumeSoundMem(100, m_soundHandle);
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
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

void ShotBeam::Sound()
{
	
}


