#pragma once
#include "Vec2.h"
#include "Rect.h"

class TutorialScene;
class Stage1Scene;
class Stage2Scene;
class UFO
{
public:
	UFO(TutorialScene* pTuScene);
	UFO(Stage1Scene* pS1Scene);
	UFO(Stage2Scene* pS2Scene);
	~UFO();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	void SetAnimHandle(int AnimHandle) { m_animHnadle = AnimHandle; }
	void Start();
	//UFOの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	//UFOの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	//当たり判定用の矩形
	Rect m_colRect;

	//表示位置
	Vec2 m_pos;
	//半径
	float m_radius;
private:
	TutorialScene* m_pTuScene;
	Stage1Scene* m_pS1Scene;
	Stage2Scene* m_pS2Scene;

	int m_handle;	//グラフィックのハンドル
	int m_animHnadle;
	//接触したかの判定
	bool m_boundFlag;

	//Beamの座標
	Vec2 m_beamPos;
public:
	//移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
	float JumpPower;
	float Gravity = 1.0f;
	float MaxGravity = 10.0f;
	float m_angle;
	float m_tq;
	
	bool KnockBack;
	bool isJump;
	bool m_MoveFlag;
	bool AnimFlag;

	int m_animFrame;
	float AnimPosX;
	int m_ufoS2Max;
	int m_soundHandle;

};

