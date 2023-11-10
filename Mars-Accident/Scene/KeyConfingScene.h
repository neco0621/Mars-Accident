#pragma once
#include "Scene.h"
#include<unordered_map>
#include"../Input.h"

class Input;
class SceneManager;

class KeyConfigScene :public Scene
{
private:
	int frame_ = 0;

	Input& input_;
	InputTable_t keyCommandTable_;

	//�X�V�����o�֐��|�C���^
	using UpdateFunc_f = void (KeyConfigScene::*)(Input& input);
	UpdateFunc_f updateFunc_;

	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void (KeyConfigScene::*)();
	DrawFunc_t drawFunc_;

	//�X�V�֐�
	void AppearUpdate(Input&);		//�o����
	void NormalUpdate(Input&);		//�ʏ���
	void DisappearUpdate(Input&);	//�ޏ���

	//�`��֐�
	void ExpandDraw();		//�g���k���`��
	void NormalDraw();	//�ʏ�`��

	void DrawCommandList();

public:
	KeyConfigScene(SceneManager& manager, Input& input);
	~KeyConfigScene();
	void Update(Input& input);
	void Draw();
};