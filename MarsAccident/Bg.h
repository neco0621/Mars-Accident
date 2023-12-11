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
	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	SceneMain* m_pMain;
	int m_handle;
};

