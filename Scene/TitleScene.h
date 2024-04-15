#pragma once
#include "Scene.h"

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public Scene
{

public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	void Init();
	void Update(Input& input);
	void Draw();
	void ShakeScreen(int a, int b);

private:
	//�X�V�����o�֐��|�C���^
	void (TitleScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void (TitleScene::*) ();
	DrawFunc_t drawFunc_;
	//�X�V�֐�
	void FadeInUpdate(Input& input);	//�t�F�[�h�C�����
	void NormalUpdate(Input& input);	//�ʏ���
	void FadeOutUpdate(Input& input);	//�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();	//�t�F�[�h���`��
	void NormalDraw();	//��t�F�[�h�`��

	//�O���t�B�b�N�n���h��
	int m_bgHandle;			//�w�i�̃n���h��
	int m_titleHandle;		//�^�C�g���̃A�C�R���̃n���h��
	int m_shakeHandle;		//��ʗh��̃n���h��
	int m_titleButton;		//START�{�^���̃n���h��
	int frame_;				//�t�F�C�h�Ɋւ���t���[��
	int m_bgPosX;			//�w�i�̕`��ʒu
	int m_shakeSize;		//��ʗh��̃T�C�Y
	int AnimFrame;			//�A�j���[�V�����̍Đ�����
	int m_bgFrame;			//�w�i��������܂ł̎���
	int m_shakeFrame;		//��ʗh��̎���
	int m_loopFrame;		//��ʗh��̃��[�v����
	
	//�T�E���h
	int m_bgm;				//BGM
	int CheckSE;			//START�{�^�����������Ƃ��̃T�E���h
	
	//�t���O
	bool m_isShake;			//��ʗh�ꂵ�Ă��邩�ǂ���

	//�ϐ�
	int m_AdjustmentWidth;	//X���W�ׂ̍����ʒu����
	int m_AdjustmentHeight;	//Y���W�ׂ̍����ʒu����
};

