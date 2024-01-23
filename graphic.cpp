#include "graphic.h"
#include <cmath>

//�O���[�o���ϐ�
Graphic TitleBackImage;     //�^�C�g���w�i�摜
Graphic TitleLogo;          //�^�C�g�����S
Graphic TitleButton;        //�^�C�g���{�^��

//�Ǎ��E�n���h������
BOOL Graphic_Init(VOID)
{
    //�^�C�g���w�i�摜
    TitleBackImage = LoadGraphic(
        GraphicPathTitleBackImage,
        (0,0),              //�w�i�͍��ォ��
        GraAlignTopL);  if (TitleBackImage.Handle == -1) { return FALSE; }

    //�^�C�g�����S
    TitleLogo = LoadGraphic(
        GraphicPathTitleLogo,
        (Game::kScreenWidth, Game::kScreenHeight),          //���S�͉�ʒ�������
        GraAlignBottomC);  if (TitleLogo.Handle == -1) { return FALSE; }

    //�^�C�g���{�^��
    TitleButton = LoadGraphic(
        GraphicPathTitleButton,
        (Game::kScreenWidth, Game::kScreenHeight + 50),    //�{�^���͉������肩��
        GraAlignTopC);  if (TitleButton.Handle == -1) { return FALSE; }

    return TRUE;
}

VOID Graphic_End(VOID)
{
    DeleteGraphic(TitleBackImage);
    DeleteGraphic(TitleLogo);
    DeleteGraphic(TitleButton);

    return;
}

VOID GraphicLoadErrMessage(const char* path)
{
    //�G���[�p������
    char ErrStr[ImagePathStrMax];

    //�G���[�p������̓��e����ɂ���
    for (int i = 0; i < ImagePathStrMax; i++) { ErrStr[i] = '\0'; }

    //�G���[�̓��e��A�����Đ���
    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, ImageLoadErrCap);

    //�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
    MessageBox(
        GetMainWindowHandle(),      //�E�B���h�E�n���h��
        ErrStr,                     //�G���[���e
        ImageLoadErrTitle,          //�G���[�^�C�g��
        MB_OK);                     //OK�{�^���̂�

    return;
}

//�Ǎ�
Graphic LoadGraphic(const char* path, int pos, Graphic_Align align)
{
    Graphic graphic;

    //�t�@�C���̏ꏊ���R�s�[
    strcpy_s(graphic.c.Path, sizeof(graphic.c.Path), path);

    //�摜���������ɓǂݍ���
    graphic.Handle = LoadGraph(graphic.c.Path);

    //�ǂݍ��݃G���[
    if (graphic.Handle == -1)
    {
        GraphicLoadErrMessage(graphic.c.Path);
    }
    else
    {
        //����ɓǍ����ł�����p�����[�^�[�ݒ�

        //���ƍ������擾
        GetGraphSize(graphic.Handle, &graphic.c.Width, &graphic.c.Height);

        //��_
        graphic.c.Pos.x = pos;

        //��������
        graphic.c.Align = align;

        //�摜��`�悷��
        graphic.c.IsDraw = TRUE;

        //�G�t�F�N�g�̏�����
        graphic.c.IsFxStartFlg = FALSE;     //�`��G�t�F�N�g�t���O�̏�����
        graphic.c.Fx = GraFxNone;           //�ʏ�`��
        graphic.c.FxMillTime = 0;           //�G�t�F�N�g���ԃJ�E���g
        graphic.c.FxMillTimeMax = 0;        //�G�t�F�N�g���ԃJ�E���gMAX
        graphic.c.FxInterMillTime = 0;      //�G�t�F�N�g�Ԋu�J�E���g
        graphic.c.FxInterMillTimeMax = 0;   //�G�t�F�N�g�Ԋu�J�E���gMAX
        graphic.c.Alpha = 1.0f;             //�����x������

    }

    return graphic;
}

VOID DrawGraphic(Graphic* graphic)
{
    //�G�t�F�N�g�J�n����
    if (graphic->c.IsFxStartFlg == TRUE)
    {
        //�`��G�t�F�N�g�J�n����
        switch (graphic->c.Fx)
        {
        case GraFxBlink:
            //�G�t�F�N�g�Ԋu���ő�̎��ɓ����x��؂�ւ���
            if (graphic->c.FxInterMillTime == graphic->c.FxInterMillTimeMax)
            {
                if (graphic->c.Alpha == 1.0)
                {
                    graphic->c.Alpha = 0.0f;    //�����ɂ���
                }
                else if (graphic->c.Alpha == 0.0)
                {
                    graphic->c.Alpha = 1.0f;    //�s�����ɂ���
                }
            }
            //��������
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->c.Alpha * 255);

            break;

        case GraFxFadeIn:
            //�摜�̓����x�̌v�Z
            graphic->c.Alpha
                = sin(
                    (float)graphic->c.FxInterMillTime / graphic->c.FxInterMillTimeMax   //�o�ߎ��Ԃ���S�̂�%���v�Z
                    * (DX_PI / 2));                                                     //sin(90) = 1�Ƃ��Ċ������v�Z
            //���ߏ���
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->c.Alpha * 255);
            break;

        case GraFxFadeOut:

            //�摜�̓����x���v�Z
            graphic->c.Alpha
                = cos(
                    (float)graphic->c.FxInterMillTime / graphic->c.FxInterMillTimeMax   //�o�ߎ��Ԃ���S�̂�%���v�Z
                    * (DX_PI / 2));                                                     //cos(90) = 1�Ƃ��Ċ������v�Z
            //���ߏ���
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->c.Alpha * 255);
            break;

        case GraFxNone:
            //�������Ȃ�
            break;
        default:
            break;
        }

        //�G�t�F�N�g���ԃJ�E���g�A�b�v
        graphic->c.FxMillTime++;

        //�G�t�F�N�g�Ԋu�J�E���g�A�b�v
        graphic->c.FxInterMillTimeMax++;
    }

    //�`�揈��
    if (graphic->c.IsDraw == TRUE)
    {
        //������ɕ`��
        switch (graphic->c.Align)
        {
        case GraAlignTopL:
            //�㍶����ɕ`��
            DrawGraph(
                graphic->c.Pos.x,
                graphic->c.Pos.y,
                graphic->Handle, TRUE);
            break;

        case GraAlignTopC:
            //�㒆������ɕ`��
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width / 2,
                graphic->c.Pos.y,
                graphic->Handle, TRUE);
            break;

        case GraAlignTopR:
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width,
                graphic->c.Pos.y,
                graphic->Handle, TRUE);
            break;


        case GraAlignBottomL:
            //��������ɕ`��
            DrawGraph(
                graphic->c.Pos.x,
                graphic->c.Pos.y - graphic->c.Height,
                graphic->Handle, TRUE);
            break;

        case GraAlignBottomC:
            //����������ɕ`��
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width / 2,
                graphic->c.Pos.y - graphic->c.Height,
                graphic->Handle, TRUE);
            break;

        case GraAlignBottomR:
            //���E����ɕ`��
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width,
                graphic->c.Pos.y - graphic->c.Height,
                graphic->Handle, TRUE);
            break;

        case GraAlignAllCenter:
            //�㉺���E�̒����Ɋ�ɕ`��
            DrawGraph(
                graphic->c.Pos.x - graphic->c.Width / 2,
                graphic->c.Pos.y - graphic->c.Height / 2,
                graphic->Handle, TRUE);
            break;

        default:
            break;
        }
    }

    //�G�t�F�N�g�̏I������
    if (graphic->c.IsFxStartFlg == TRUE)
    {
        switch (graphic->c.Fx)
        {
        case GraFxBlink:
            //�A���t�@�u�����h(���ߏ���)�I��
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxFadeIn:
            //�A���t�@�u�����h(���ߏ���)�I��
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxFadeOut:
            //�A���t�@�u�����h(���ߏ���)�I��
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxFadeInOut:
            //�A���t�@�u�����h(���ߏ���)�I��
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;
        case GraFxNone:
            //�������Ȃ�
            break;
        default:
            break;
        }

        //�C���^�[�o����MAX�Ȃ猳�ɖ߂�
        if (graphic->c.FxInterMillTime > graphic->c.FxInterMillTimeMax)
        {
            graphic->c.FxInterMillTime = 0;
        }

        //�G�t�F�N�g�������p���ł͂Ȃ���
        if (graphic->c.FxMillTimeMax != GraFxInfinity)
        {
            //�G�t�F�N�g���Ԃ��I���Ȃ�΃G�t�F�N�g�I��
            if (graphic->c.FxMillTime > graphic->c.FxMillTimeMax)
            {
                graphic->c.IsFxStartFlg = FALSE;
            }
        }
    }
    return;
}

//���
VOID DeleteGraphic(Graphic graphic)
{
    //����ɓǍ����ł��Ă����
    if (graphic.Handle != -1)
    {
        //���������
        DeleteGraph(graphic.Handle);
    }

    return;
}

//�G�t�F�N�g�J�n
VOID GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval)
{
    //�G�t�F�N�g�̕b����������
    graphic->c.FxMillTime = 0;

    //�����G�t�F�N�g�������p���Ȃ�A ���ۂ�MAX���Ԃ��v�Z�����Ȃ�
    if (MillTime == GraFxInfinity)
    {
        graphic->c.FxMillTimeMax = GraFxInfinity;
    }
    else
    {
        graphic->c.FxMillTimeMax = (MillTime / 1000.0f) * GameFPS;
    }

    //�G�t�F�N�g�̊Ԋu��������
    graphic->c.FxInterMillTime = 0;
    graphic->c.FxInterMillTimeMax = (MillInterval / 10000.0f) * GameFPS;

    //�G�t�F�N�g�̎�ނ�ݒ�
    graphic->c.Fx = Fx;

    //�G�t�F�N�g�̊J�n�t���OON
    graphic->c.IsFxStartFlg = TRUE;

    return;
}
