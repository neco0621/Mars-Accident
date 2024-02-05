#pragma once
#include "Scene.h"

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public Scene
{
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

	void BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight);

	int m_bgHandle;
	int m_animHandle;
	int m_titleHandle;
	int m_shakeHandle;
	int m_titleButton;
	int m_moon;
	int frame_;
	int areaX;
	int speed;
	int m_bgPosX;
	int m_shakeSize;
	int AnimFrame;
	int m_bgFrame;
	int m_shakeFrame;
	int m_loopFrame;
	int m_bgm;
	int CheckSE;
	
	bool m_isShake;

public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	void Init();
	void Update(Input& input);
	void Draw();
	void ShakeScreen(int a, int b);
};

