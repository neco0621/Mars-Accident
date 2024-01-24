//#include "Animation.h"
//
//Animation* AnimExpl;	//�����A�j���[�V����
//
//Animation::Animation()
//{
//}
//
//Animation::~Animation()
//{
//}
//
////�Ǎ��E�n���h������
//BOOL Animation::Animation_Init()
//{
//	//�����A�j���[�V����
//	AnimExpl = LoadAnimation(
//		g.LoadGraphic(					//�A�j���[�V�����摜�ǂݍ���
//			GraphicPathTitleAnimExpl,	//�A�j���[�V�����摜�p�X
//			(m_pUfo->m_pos.x, m_pUfo->m_pos.y),						//�E�ォ��
//			GraAlignTopR),
//		AnimExplDivX,					//�A�j���[�V������������
//		AnimExplDivY					//�A�j���[�V�����c������
//	);
//	if (AnimExpl->Handle[0] == -1) { return FALSE; }
//	return 0;
//}
//
////��n��
//void Animation::Animation_End()
//{
//	DeleteAnimation(*AnimExpl);
//
//	return;
//}
//
////�ǂݍ��݃G���[���b�Z�[�W
//void Animation::AnimationLoadErrMessage(const char* path)
//{
//	//�G���[�p������
//	char ErrStr[AnimationPathstrMax];
//
//	//�G���[�p������̓��e����ɂ���
//	for (int i = 0; i < AnimationPathstrMax; i++) { ErrStr[i] = '\0'; }
//
//	//�G���[���e��A�����Đ���
//	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);
//
//	//�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
//	MessageBox(
//		GetMainWindowHandle(),		//�E�B���h�E�n���h��
//		ErrStr,						//�G���[���e
//		AnimationLoadErrTitle,		//�G���[�^�C�g��
//		MB_OK);						//OK�{�^���̂�
//
//	return;
//}
//
////�A�j���[�V�����ǂݍ���
//Animation* Animation::LoadAnimation(Graphic graphic, int XNum, int YNum)
//{
//	Animation animation;
//
//	//�ǂݍ��񂾉摜�̏��������p��
//	animation.g = graphic;
//
//	//�摜�̕������ݒ�
//	animation.DivX = XNum;
//	animation.DivY = YNum;
//
//	//�摜�̕��ƍ������Čv�Z
//	animation.g.Width = animation.g.Width / XNum;
//	animation.g.Height = animation.g.Height / YNum;
//
//	//�A�j���[�V�����̃n���h���z��𓮓I�m��
//	animation.Handle
//		= (int*)			//int�^�̃|�C���^�Ɍ^�ϊ�
//		calloc(				//�������𓮓I�m�ۂ��Ēl���[���ŏ�����
//			XNum * YNum		//�m�ۂ���v�f�̌�
//			, sizeof(int)	//�m�ۂ���v�f�̃f�[�^�^
//		);
//
//	//�A�j���[�V�����𕪊����ă������ɓǍ�
//	LoadDivGraph(
//		graphic.Path,			//�A�j���[�V�����̃p�X
//		(XNum * YNum),			//��������
//		XNum, YNum,				//|(��)�������A-(�c)������
//		animation.g.Width,	//��������1���̕�
//		animation.g.Height,	//��������1���̍���
//		animation.Handle		//�A�������n���h���z��̐擪
//	);
//
//	//�ǂݍ��݃G���[
//	if (animation.Handle == NULL || animation.Handle[0] == -1)
//	{
//		AnimationLoadErrMessage(graphic.Path);
//	}
//
//	//�������ɓǂݍ��񂾉摜�̓T�C�Y��m�肽�������Ȃ̂ŗp�ς�
//	//��graphic��handle�͏��������
//	g.DeleteGraphic(graphic);
//
//	//�n���h���̗v�f����������
//	animation.NowHandleIndex = 0;
//
//	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
//	animation.g.Handle = animation.Handle[animation.NowHandleIndex];
//	return &animation;
//}
//
////�`��
//void Animation::DrawAnimation(Animation* animation)
//{
//	//�摜�`��
//	g.DrawGraphic(&animation->g);
//
//	//�A�j���[�V�������Ȃ�R�}��i�߂�
//	if (animation->IsAnimStractFlg == TRUE)
//	{
//		if (animation->FrameByFrameCnt < animation->DivY - 1)
//		{
//			animation->FrameByFrameCnt++;
//		}
//		else
//		{
//			//�R�}��i�߂Ă��镔��(-1�����Ȃ��Ɣz��𒴂���)
//			if (animation->NowHandleIndex < animation->DivX * animation->DivY)
//			{
//				animation->NowHandleIndex++;
//			}
//			else
//			{
//				animation->NowHandleIndex = 0;
//			}
//
//			//�A�j���[�V�����̗v�f�����Z�b�g
//			animation->g.Handle = animation->Handle[animation->NowHandleIndex];
//
//			//�R�}���菉����
//			animation->FrameByFrameCnt = 0;
//		}
//
//		//�A�j���[�V�������ԃJ�E���g�A�b�v
//		animation->FrameByFrameCnt++;
//
//		//�A�j���[�V�����������p���ł͂Ȃ���
//		if (animation->FrameMax != AnimationInfinity)
//		{
//			//�A�j���[�V���������݂̂Ȃ�A�j���[�V�����̎��Ԃ𖳎�
//			if (animation->FrameMax != AnimationOnce)
//			{
//				//�A�j���[�V�������Ԃ��I���Ȃ�΃A�j���[�V�����I��
//				if (animation->FrameCnt > animation->FrameMax)
//				{
//					animation->IsAnimStractFlg = FALSE;	//�A�j���[�V�����J�n�t���OOFF
//					animation->g.IsDraw = FALSE;			//�A�j���[�V�����`��t���OOFF
//				}
//			}
//
//			//�A�j���[�V�����̃R�}�̍Ō�Ȃ�΃A�j���[�V�����I��(-1�����Ȃ��Ɣz��𒴂���)
//			if (animation->NowHandleIndex >= animation->DivX * animation->DivY - 1)
//			{
//				animation->IsAnimStractFlg = FALSE;	//�A�j���[�V�����J�n�t���OOFF
//				animation->g.IsDraw = FALSE;			//�A�j���[�V�����`��t���OOFF
//			}
//		}
//	}
//
//	return;
//}
//
////���
//Animation* Animation::DeleteAnimation(Animation animation)
//{
//	//����ɓǂݍ��ނ��Ƃ��ł��Ă����
//	if (animation.Handle != NULL && animation.Handle[0] != -1)
//	{
//		//������������
//		for (int i = 0; i < animation.DivX * animation.DivY; i++)
//		{
//			DeleteGraph(animation.Handle[i]);
//		}
//
//		//���I�m�ۂ������������J��
//		free(animation.Handle);
//	}
//
//	//2��ȏ��free��h���v���O�����̃N���b�V���h�~
//	animation.Handle = NULL;
//	return &animation;
//}
//
//void Animation::AnimationStart(Animation* animation, int MillTime, int MillInterval)
//{
//	//�A�j���[�V�����̕b����������
//	animation->FrameCnt = 0;
//
//	//�A�j���[�V�����̌p�����Ԃ��v�Z
//	if (MillTime == AnimationInfinity)
//	{
//		//�����A�j���[�V�����������p���Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
//		animation->FrameMax = AnimationInfinity;
//	}
//	else if (MillTime == AnimationOnce)
//	{
//		//�����A�j���[�V���������݂̂Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
//		animation->FrameMax = AnimationOnce;
//	}
//	else
//	{
//		animation->FrameMax = (MillTime / 1000.0f) * GameFPS;
//	}
//
//	//�A�j���[�V�����̊Ԋu��������
//	animation->FrameByFrameCnt = 0;
//	animation->FrameByFrameMax = (MillInterval / 1000.0f) * GameFPS;
//
//	//�n���h���̗v�f����������
//	animation->NowHandleIndex = 0;
//
//	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
//	animation->g.Handle = animation->Handle[animation->NowHandleIndex];
//
//	//�A�j���[�V�����̊J�n�t���OON
//	animation->IsAnimStractFlg = TRUE;
//
//	//�A�j���[�V�����`��t���OOn
//	animation->g.IsDraw = TRUE;
//
//	return;
//}