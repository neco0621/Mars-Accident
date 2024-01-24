#pragma once
#include "DxLib.h"
#include "graphic.h"
#include "Game.h"
#include "UFO.h"

//�G���[
#define AnimationLoadErrCap		"���ǂݍ��߂܂���ł���"
#define AnimationLoadErrTitle	"�A�j���[�V�����ǂݍ��݃G���["

//������̒���
#define AnimationPathstrMax 256
#define AnimationErrstrMax 512

//�A�j���[�V�����̃t�@�C���p�X
#define GraphicPathTitleAnimExpl	"data/explosion.png"
#define AnimExplDivX				10					//�����A�j���̉�������
#define AnimExplDivY				8					//�����A�j���̏c������

//�A�j���[�V�����������̎�
#define AnimationInfinity  -99999
//�A�j���[�V����1��̂�(�����Ȃ̂Œʏ�ł͂��肦�Ȃ�����)
#define AnimationOnce		-11111

//�A�j���[�V�����\���̂̃R�A����
class Graphic;
class UFO;
class Animation
{
public:
	Animation();
	~Animation();
	int NowHandleIndex;	//���݂̃n���h���̗v�f��

	int DivX;			//�摜�̉�������
	int DivY;			//�摜�̏c������

	int FrameCnt = 0;		//�A�j���[�V�����̃R�}����
	int FrameMax = 0;		//�A�j���[�V�����̃R�}����MAX

	int FrameByFrameCnt = 0;	//�A�j���̃R�}���莞��
	int FrameByFrameMax = 0;	//�A�j���̃R�}���莞��MAX

	bool IsAnimStractFlg;	//�A�j���[�V�����J�n�t���O

	void SetAnimHandle(int animation) { Handle = animation; }

	Graphic	g;	//�摜
	int* Handle;		//�n���h��(�������𓮓I�m��)


	//�O���O���[�o���ϐ�
	Animation* AnimExpl;	//�����A�j���[�V����

	//�O���v���g�R���錾
	BOOL Animation_Init();						//�Ǎ��E�n���h������
	void Animation_End();						//��n��
	void AnimationLoadErrMessage(const char* path);	//�Ǎ��G���[���b�Z�[�W

	Animation* LoadAnimation(Graphic graphic, int XNum, int YNum);	//�A�j���[�V�����Ǎ�
	void DrawAnimation(Animation* animation);						//�`��

	Animation* DeleteAnimation(Animation animation);

	void AnimationStart(Animation* animation, int MillTime, int MillInterval);	//�A�j���[�V�����̊J�n

	UFO* m_pUfo;

};
