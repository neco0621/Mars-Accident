#pragma once
#include "DxLib.h"
class SceneMain;
class Bg
{
public:
	Bg();
	~Bg();
	void Init();
	void Update();
	void Draw();
	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	SceneMain* m_pMain;
	int m_handle;
};

