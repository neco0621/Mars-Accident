#include "DxLib.h"
#include "Game.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Input.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(false);

	//��ʃT�C�Y�ύX
	//SetGraphMode(x�T�C�Y,y�T�C�Y,�r�b�g��(16 or 32);
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//Scene�J�n
	SceneManager manager;
	manager.ChangeScene(std::make_shared<TitleScene>(manager));
	Input input;
	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		//���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		//�Q�[���̏���
		input.Update();
		manager.Update(input);
		manager.Draw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		//esc�L�[�ŃQ�[�����I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}