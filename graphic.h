#pragma once

#include "DxLib.h"
#include "Game.h"
#include "Vec2.h"
#include "UFO.h"

#define GraFxInfinity	-99999	//�G�t�F�N�g�����p��(�����Ȃ̂Œʏ�͂��蓾�Ȃ�����)

//�G���[
#define ImageLoadErrCap		"���ǂݍ��߂܂���ł���"
#define ImageLoadErrTitle	"�摜�ǂݍ��݃G���["

//������̒���
#define ImagePathStrMax	256
#define ImageErrStrMax	512

//�摜�t�@�C���̃p�X
//�����{���G�����Ȃ�2�o�C�g����������邱��(�ň����������œǂݍ��߂Ȃ���������)
//���S�p�󔒁A���p�󔒖�킸�󔒂�����邱��(�t�@�C�����̋�؂肾�Ǝv���邱�Ƃ�����)
#define GraphicPathTitleBackImage	"date/TitleBack.png"
#define GraphicPathTitleLogo		"data/TitleLogo.png"
#define GraphicPathTitleButton		"data/TItleButton.png"


//�ݒ肵����FPS
#define GameFPS	60;

//�񋓌^
enum Graphic_Align
{
	GraAlignTopL,	 //�摜�̊�_�ŏ㍶����
	GraAlignTopC,	 //�摜�̊�_�ŏ㒆������
	GraAlignTopR,	 //�摜�̊�_�ŏ�E����

	GraAlignBottomL,  //�摜�̊�_�ŉ�������
	GraAlignBottomC,  //�摜�̊�_�ŉ���������
	GraAlignBottomR,  //�摜�̊�_�ŉ��E����

	GraAlignAllCenter		//�摜�̊�_�ŏ㉺�����E����������
};

enum Graphic_Fx
{
	GraFxBlink,			//�_��
	GraFxFadeIn,		//�������s����
	GraFxFadeOut,		//�s����������
	GraFxFadeInOut,		//�s������������
	GraFxNone			//�ʏ�`��
};

//�摜�\���̂̃R�A����
typedef struct _GraphicCore
{
	char Path[ImageErrStrMax];		//�p�X

	Vec2 Pos;						//�摜�̊�_
	int Width = 0;					//��
	int Height = 0;					//����

	RECT Coll;						//��`�̓����蔻��
	RECT CollMargin;				//��`�̓����蔻����߂�

	Graphic_Align Align = GraAlignTopL;	//��������

	float Rate = 1.0f;				//�g�嗦
	float Angle = 0.0f;				//�p�x

	BOOL IsDraw = FALSE;			//�`�悷�邩?

	//�������ǉ�
	BOOL IsFxStartFlg = FALSE;		//�`��G�t�F�N�g�t���O
	Graphic_Fx Fx = GraFxNone;		//�`��G�t�F�N�g�̎��
	int FxMillTime = 0;				//�G�t�F�N�g���ԃJ�E���g
	int FxMillTimeMax = 0;			//�G�t�F�N�g���ԃJ�E���gMax
	int FxInterMillTime = 0;		//�G�t�F�N�g�Ԋu�J�E���g
	int FxInterMillTimeMax = 0;		//�G�t�F�N�g�Ԋu�J�E���gMax
	float Alpha = 0.0f;				//�����x(0.0�`1.0�����邱��)

}GraphicCore;

//�摜�\����
typedef struct _Graphic
{
	GraphicCore c;		//�R�A
	int Handle = -1;	//�n���h��
}Graphic;

//�O���O���[�o���ϐ�
extern Graphic TitleBackImage;	//�^�C�g���w�i�摜
extern Graphic TitleLogo;		//�^�C�g�����S
extern Graphic TitleButton;		//�^�C�g���{�^��

//�O���v���g�^�C�v�錾
extern BOOL Graphic_Init(VOID);							//�Ǎ��E�n���h������
extern VOID Graphic_END(VOID);							//��n��
extern VOID GraphicLoadErrMessage(const char* path);	//�Ǎ��G���[���b�Z�[�W

extern Graphic LoadGraphic(const char* path, int pos, Graphic_Align align);	//�Ǎ�
extern VOID DrawGraphic(Graphic* graphic);				//�`��
extern VOID DeleteGraphic(Graphic graphic	);			//���
extern VOID GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval);	//�G�t�F�N�g(Fx)�J�n


class UFO;

UFO* m_pUfo;


