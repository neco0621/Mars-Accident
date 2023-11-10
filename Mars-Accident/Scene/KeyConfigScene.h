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

	//更新メンバ関数ポインタ
	using UpdateFunc_f = void (KeyConfigScene::*)(Input& input);
	UpdateFunc_f updateFunc_;

	//描画メンバ関数ポインタ
	using DrawFunc_t = void (KeyConfigScene::*)();
	DrawFunc_t drawFunc_;

	//更新関数
	void AppearUpdate(Input&);		//登場状態
	void NormalUpdate(Input&);		//通常状態
	void DisappearUpdate(Input&);	//退場状態

	//描画関数
	void ExpandDraw();		//拡張縮小描画
	void NormalDraw();	//通常描画

	void DrawCommandList();

public:
	KeyConfigScene(SceneManager& manager, Input& input);
	~KeyConfigScene();
	void Update(Input& input);
	void Draw();
};