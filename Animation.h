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
typedef struct _AnimationCore
{
	int NowHandleIndex = -1;	//���݂̃n���h���̗v�f��

	int DivX = 0;			//�摜�̉�������
	int DivY = 0;			//�摜�̏c������

	int FrameCnt = 0;		//�A�j���[�V�����̃R�}����
	int FrameMax = 0;		//�A�j���[�V�����̃R�}����MAX

	int FrameByFrameCnt = 0;	//�A�j���̃R�}���莞��
	int FrameByFrameMax = 0;	//�A�j���̃R�}���莞��MAX

	BOOL IsAnimStractFlg = FALSE;	//�A�j���[�V�����J�n�t���O

}AnimationCore;

typedef struct _Animation
{
	Graphic			g;	//�摜
	AnimationCore	a;	//�A�j���[�V�����R�A
	int* Handle;		//�n���h��(�������𓮓I�m��)
}Animation;

//�O���O���[�o���ϐ�
extern Animation AnimExpl;	//�����A�j���[�V����

//�O���v���g�R���錾
extern BOOL Animation_Init(VOID);						//�Ǎ��E�n���h������
extern VOID Animation_End(VOID);						//��n��
extern VOID AnimationLoadErrMessage(const char* path);	//�Ǎ��G���[���b�Z�[�W

extern Animation LoadAnimation(Graphic graphic, int XNum, int YNum);	//�A�j���[�V�����Ǎ�
extern VOID DrawAnimation(Animation* animation);						//�`��
extern VOID DeleteAnimation(Animation animation);						//���

extern VOID AnimationStart(Animation* animation, int MillTime, int MillInterval);	//�A�j���[�V�����̊J�n

