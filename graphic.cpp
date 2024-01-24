//#include "graphic.h"
//#include <cmath>
//
//Graphic::Graphic()
//{
//}
//
//Graphic::~Graphic()
//{
//
//}
//
//BOOL Graphic::Graphic_Init(VOID)
//{
//    return TRUE;
//}
//
//VOID Graphic::Graphic_END(VOID)
//{
//    return VOID();
//}
//
//VOID Graphic::GraphicLoadErrMessage(const char* path)
//{
//    return VOID();
//}
//
//VOID Graphic_End(VOID)
//{
//    return;
//}
//
//VOID GraphicLoadErrMessage(const char* path)
//{
//    //�G���[�p������
//    char ErrStr[ImagePathStrMax];
//
//    //�G���[�p������̓��e����ɂ���
//    for (int i = 0; i < ImagePathStrMax; i++) { ErrStr[i] = '\0'; }
//
//    //�G���[�̓��e��A�����Đ���
//    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, ImageLoadErrCap);
//
//    //�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
//    MessageBox(
//        GetMainWindowHandle(),      //�E�B���h�E�n���h��
//        ErrStr,                     //�G���[���e
//        ImageLoadErrTitle,          //�G���[�^�C�g��
//        MB_OK);                     //OK�{�^���̂�
//
//    return;
//}
//
////�Ǎ�
// Graphic Graphic::LoadGraphic(const char* path, int pos, Graphic_Align align)
//{
//     Graphic graphic;
//    //�t�@�C���̏ꏊ���R�s�[
//    strcpy_s(Path, sizeof(Path), path);
//
//    //�摜���������ɓǂݍ���
//    Handle = LoadGraph(Path);
//
//    //�ǂݍ��݃G���[
//    if (Handle == -1)
//    {
//        GraphicLoadErrMessage(Path);
//    }
//    else
//    {
//        //����ɓǍ����ł�����p�����[�^�[�ݒ�
//
//        //���ƍ������擾
//        GetGraphSize(Handle, &Width, &Height);
//
//        //��_
//        Pos.x = pos;
//
//        //��������
//        Align = align;
//
//        //�摜��`�悷��
//        IsDraw = TRUE;
//
//        //�G�t�F�N�g�̏�����
//        IsFxStartFlg = FALSE;     //�`��G�t�F�N�g�t���O�̏�����
//        Fx = GraFxNone;           //�ʏ�`��
//        FxMillTime = 0;           //�G�t�F�N�g���ԃJ�E���g
//        FxMillTimeMax = 0;        //�G�t�F�N�g���ԃJ�E���gMAX
//        FxInterMillTime = 0;      //�G�t�F�N�g�Ԋu�J�E���g
//        FxInterMillTimeMax = 0;   //�G�t�F�N�g�Ԋu�J�E���gMAX
//        Alpha = 1.0f;             //�����x������
//
//    }
//    return graphic;
// }
//
////�`��
//void Graphic::DrawGraphic(Graphic* graphic)
//{
//    //�G�t�F�N�g�J�n����
//    if (graphic->IsFxStartFlg == TRUE)
//    {
//        //�`��G�t�F�N�g�J�n����
//        switch (graphic->Fx)
//        {
//        case GraFxBlink:
//            //�G�t�F�N�g�Ԋu���ő�̎��ɓ����x��؂�ւ���
//            if (graphic->FxInterMillTime == graphic->FxInterMillTimeMax)
//            {
//                if (graphic->Alpha == 1.0)
//                {
//                    graphic->Alpha = 0.0f;    //�����ɂ���
//                }
//                else if (graphic->Alpha == 0.0)
//                {
//                    graphic->Alpha = 1.0f;    //�s�����ɂ���
//                }
//            }
//            //��������
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->Alpha * 255);
//
//            break;
//
//        case GraFxFadeIn:
//            //�摜�̓����x�̌v�Z
//            graphic->Alpha
//                = sin(
//                    (float)graphic->FxInterMillTime / graphic->FxInterMillTimeMax   //�o�ߎ��Ԃ���S�̂�%���v�Z
//                    * (DX_PI / 2));                                                     //sin(90) = 1�Ƃ��Ċ������v�Z
//            //���ߏ���
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->Alpha * 255);
//            break;
//
//        case GraFxFadeOut:
//
//            //�摜�̓����x���v�Z
//            graphic->Alpha
//                = cos(
//                    (float)graphic->FxInterMillTime / graphic->FxInterMillTimeMax   //�o�ߎ��Ԃ���S�̂�%���v�Z
//                    * (DX_PI / 2));                                                     //cos(90) = 1�Ƃ��Ċ������v�Z
//            //���ߏ���
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphic->Alpha * 255);
//            break;
//
//        case GraFxNone:
//            //�������Ȃ�
//            break;
//        default:
//            break;
//        }
//
//        //�G�t�F�N�g���ԃJ�E���g�A�b�v
//        graphic->FxMillTime++;
//
//        //�G�t�F�N�g�Ԋu�J�E���g�A�b�v
//        graphic->FxInterMillTimeMax++;
//    }
//
//    //�`�揈��
//    if (graphic->IsDraw == TRUE)
//    {
//        //������ɕ`��
//        switch (graphic->Align)
//        {
//        case GraAlignTopL:
//            //�㍶����ɕ`��
//            DrawGraph(
//                graphic->Pos.x,
//                graphic->Pos.y,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignTopC:
//            //�㒆������ɕ`��
//            DrawGraph(
//                graphic->Pos.x - graphic->Width / 2,
//                graphic->Pos.y,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignTopR:
//            DrawGraph(
//                graphic->Pos.x - graphic->Width,
//                graphic->Pos.y,
//                graphic->Handle, TRUE);
//            break;
//
//
//        case GraAlignBottomL:
//            //��������ɕ`��
//            DrawGraph(
//                graphic->Pos.x,
//                graphic->Pos.y - graphic->Height,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignBottomC:
//            //����������ɕ`��
//            DrawGraph(
//                graphic->Pos.x - graphic->Width / 2,
//                graphic->Pos.y - graphic->Height,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignBottomR:
//            //���E����ɕ`��
//            DrawGraph(
//                graphic->Pos.x - graphic->Width,
//                graphic->Pos.y - graphic->Height,
//                graphic->Handle, TRUE);
//            break;
//
//        case GraAlignAllCenter:
//            //�㉺���E�̒����Ɋ�ɕ`��
//            DrawGraph(
//                graphic->Pos.x - graphic->Width / 2,
//                graphic->Pos.y - graphic->Height / 2,
//                graphic->Handle, TRUE);
//            break;
//
//        default:
//            break;
//        }
//    }
//
//    //�G�t�F�N�g�̏I������
//    if (graphic->IsFxStartFlg == TRUE)
//    {
//        switch (Fx)
//        {
//        case GraFxBlink:
//            //�A���t�@�u�����h(���ߏ���)�I��
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxFadeIn:
//            //�A���t�@�u�����h(���ߏ���)�I��
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxFadeOut:
//            //�A���t�@�u�����h(���ߏ���)�I��
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxFadeInOut:
//            //�A���t�@�u�����h(���ߏ���)�I��
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//        case GraFxNone:
//            //�������Ȃ�
//            break;
//        default:
//            break;
//        }
//
//        //�C���^�[�o����MAX�Ȃ猳�ɖ߂�
//        if (graphic->FxInterMillTime > graphic->FxInterMillTimeMax)
//        {
//            graphic->FxInterMillTime = 0;
//        }
//
//        //�G�t�F�N�g�������p���ł͂Ȃ���
//        if (graphic->FxMillTimeMax != GraFxInfinity)
//        {
//            //�G�t�F�N�g���Ԃ��I���Ȃ�΃G�t�F�N�g�I��
//            if (graphic->FxMillTime > graphic->FxMillTimeMax)
//            {
//                graphic->IsFxStartFlg = FALSE;
//            }
//        }
//    }
//    return;
//}
//
////���
//void Graphic::DeleteGraphic(Graphic graphic)
//{
//    //����ɓǍ����ł��Ă����
//    if (graphic.Handle != -1)
//    {
//        //���������
//        DeleteGraph(graphic.Handle);
//    }
//
//    return;
//}
//
//void Graphic::GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval)
//{
//    //�G�t�F�N�g�̕b����������
//    graphic->FxMillTime = 0;
//
//    //�����G�t�F�N�g�������p���Ȃ�A ���ۂ�MAX���Ԃ��v�Z�����Ȃ�
//    if (MillTime == GraFxInfinity)
//    {
//        graphic->FxMillTimeMax = GraFxInfinity;
//    }
//    else
//    {
//        graphic->FxMillTimeMax = (MillTime / 1000.0f) * GameFPS;
//    }
//
//    //�G�t�F�N�g�̊Ԋu��������
//    graphic->FxInterMillTime = 0;
//    graphic->FxInterMillTimeMax = (MillInterval / 10000.0f) * GameFPS;
//
//    //�G�t�F�N�g�̎�ނ�ݒ�
//    graphic->Fx = Fx;
//
//    //�G�t�F�N�g�̊J�n�t���OON
//    graphic->IsFxStartFlg = TRUE;
//
//    return;
//}
//
