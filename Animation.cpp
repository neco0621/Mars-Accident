#include "Animation.h"

Animation AnimExpl;	//�����A�j���[�V����

//�Ǎ��E�n���h������
BOOL Animation_Init(VOID)
{
	//�����A�j���[�V����
	AnimExpl = LoadAnimation(
		LoadGraphic(					//�A�j���[�V�����摜�ǂݍ���
			GraphicPathTitleAnimExpl,	//�A�j���[�V�����摜�p�X
			(m_pUfo->m_pos.x,m_pUfo->m_pos.y),						//�E�ォ��
			GraAlignTopR),
		AnimExplDivX,					//�A�j���[�V������������
		AnimExplDivY					//�A�j���[�V�����c������
	); if (AnimExpl.Handle[0] == -1) { return FALSE; }
}

//��n��
VOID Animation_End(VOID)
{
	DeleteAnimation(AnimExpl);

	return;
}


//�Ǎ��G���[���b�Z�[�W
VOID AnimationLoadErrMessage(const char* path)
{
	//�G���[�p������
	char ErrStr[AnimationPathstrMax];

	//�G���[�p������̓��e����ɂ���
	for (int i = 0; i < AnimationPathstrMax; i++) { ErrStr[i] = '\0'; }

	//�G���[���e��A�����Đ���
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);

	//�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
	MessageBox(
		GetMainWindowHandle(),		//�E�B���h�E�n���h��
		ErrStr,						//�G���[���e
		AnimationLoadErrTitle,		//�G���[�^�C�g��
		MB_OK);						//OK�{�^���̂�

	return;
}

//�A�j���[�V�����ǂݍ���
Animation LoadAnimation(Graphic graphic, int XNum, int YNum)
{
	Animation animation;

	//�ǂݍ��񂾉摜�̏��������p��
	animation.g = graphic;

	//�摜�̕������ݒ�
	animation.a.DivX = XNum;
	animation.a.DivY = YNum;

	//�摜�̕��ƍ������Čv�Z
	animation.g.c.Width = animation.g.c.Width / XNum;
	animation.g.c.Height = animation.g.c.Height / YNum;

	//�A�j���[�V�����̃n���h���z��𓮓I�m��
	animation.Handle
		= (int*)			//int�^�̃|�C���^�Ɍ^�ϊ�
		calloc(				//�������𓮓I�m�ۂ��Ēl���[���ŏ�����
			XNum * YNum		//�m�ۂ���v�f�̌�
			, sizeof(int)	//�m�ۂ���v�f�̃f�[�^�^
	);

	//�A�j���[�V�����𕪊����ă������ɓǍ�
	LoadDivGraph(
		graphic.c.Path,			//�A�j���[�V�����̃p�X
		(XNum * YNum),			//��������
		XNum, YNum,				//|(��)�������A-(�c)������
		animation.g.c.Width,	//��������1���̕�
		animation.g.c.Height,	//��������1���̍���
		animation.Handle		//�A�������n���h���z��̐擪
	);

	//�ǂݍ��݃G���[
	if (animation.Handle == NULL || animation.Handle[0] == -1)
	{
		AnimationLoadErrMessage(graphic.c.Path);
	}

	//�������ɓǂݍ��񂾉摜�̓T�C�Y��m�肽�������Ȃ̂ŗp�ς�
	//��graphic��handle�͏��������
	DeleteGraphic(graphic);

	//�n���h���̗v�f����������
	animation.a.NowHandleIndex = 0;

	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
	animation.g.Handle = animation.Handle[animation.a.NowHandleIndex];

	return animation;
}

//�`��
VOID DrawAnimation(Animation* animation)
{
	//�摜�`��
	DrawGraphic(&animation->g);

	//�A�j���[�V�������Ȃ�R�}��i�߂�
	if (animation->a.IsAnimStractFlg == TRUE)
	{
		if (animation->a.FrameByFrameCnt < animation->a.DivY - 1)
		{
			animation->a.FrameByFrameCnt++;
		}
		else
		{
			//�R�}��i�߂Ă��镔��(-1�����Ȃ��Ɣz��𒴂���)
			if (animation->a.NowHandleIndex < animation->a.DivX * animation->a.DivY)
			{
				animation->a.NowHandleIndex++;
			}
			else
			{
				animation->a.NowHandleIndex = 0;
			}

			//�A�j���[�V�����̗v�f�����Z�b�g
			animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];

			//�R�}���菉����
			animation->a.FrameByFrameCnt = 0;
		}

		//�A�j���[�V�������ԃJ�E���g�A�b�v
		animation->a.FrameByFrameCnt++;

		//�A�j���[�V�����������p���ł͂Ȃ���
		if (animation->a.FrameMax != AnimationInfinity)
		{
			//�A�j���[�V���������݂̂Ȃ�A�j���[�V�����̎��Ԃ𖳎�
			if (animation->a.FrameMax != AnimationOnce)
			{
				//�A�j���[�V�������Ԃ��I���Ȃ�΃A�j���[�V�����I��
				if (animation->a.FrameCnt > animation->a.FrameMax)
				{
					animation->a.IsAnimStractFlg = FALSE;	//�A�j���[�V�����J�n�t���OOFF
					animation->g.c.IsDraw = FALSE;			//�A�j���[�V�����`��t���OOFF
				}
			}

			//�A�j���[�V�����̃R�}�̍Ō�Ȃ�΃A�j���[�V�����I��(-1�����Ȃ��Ɣz��𒴂���)
			if (animation->a.NowHandleIndex >= animation->a.DivX * animation->a.DivY - 1)
			{
				animation->a.IsAnimStractFlg = FALSE;	//�A�j���[�V�����J�n�t���OOFF
				animation->g.c.IsDraw = FALSE;			//�A�j���[�V�����`��t���OOFF
			}
		}
	}

	return;
}

//���
VOID DeleteAnimation(Animation animation)
{
	//����ɓǂݍ��ނ��Ƃ��ł��Ă����
	if (animation.Handle != NULL && animation.Handle[0] != -1)
	{
		//������������
		for (int i = 0; i < animation.a.DivX * animation.a.DivY; i++)
		{
			DeleteGraph(animation.Handle[i]);
		}

		//���I�m�ۂ������������J��
		free(animation.Handle);
	}

	//2��ȏ��free��h���v���O�����̃N���b�V���h�~
	animation.Handle = NULL;

	return;
}

VOID AnimationStart(Animation* animation, int MillTime, int MillInterval)
{
	//�A�j���[�V�����̕b����������
	animation->a.FrameCnt = 0;

	//�A�j���[�V�����̌p�����Ԃ��v�Z
	if (MillTime == AnimationInfinity)
	{
		//�����A�j���[�V�����������p���Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
		animation->a.FrameMax = AnimationInfinity;
	}
	else if (MillTime == AnimationOnce)
	{
		//�����A�j���[�V���������݂̂Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
		animation->a.FrameMax = AnimationOnce;
	}
	else
	{
		animation->a.FrameMax = (MillTime / 1000.0f) * GameFPS;
	}

	//�A�j���[�V�����̊Ԋu��������
	animation->a.FrameByFrameCnt = 0;
	animation->a.FrameByFrameMax = (MillInterval / 1000.0f) * GameFPS;

	//�n���h���̗v�f����������
	animation->a.NowHandleIndex = 0;

	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
	animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];

	//�A�j���[�V�����̊J�n�t���OON
	animation->a.IsAnimStractFlg = TRUE;

	//�A�j���[�V�����`��t���OOn
	animation->g.c.IsDraw = TRUE;

	return;
}
