#pragma once
#include "Vec2.h"
#include "Rect.h"

class Stage1Scene;
class Stage2Scene;
class Animation;
class Graphic;
class S2UFO
{
public:
	S2UFO(Stage2Scene* pS2Scene);
	~S2UFO();

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
	Stage2Scene* m_pS2Scene;
	//Animation* m_pAnimation;
	Graphic* graphic;

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
	bool isJump;
	float Gravity = 1.0f;
	float MaxGravity = 10.0f;
	bool KnockBack;
	float m_angle;

	float m_tq;

	bool m_MoveFlag;

	int m_animFrame;
	bool AnimFlag;
	int AnimPosX;

	int m_ufoS2Max;
	int m_soundHandle;
};

