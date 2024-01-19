#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"

class Stage1Scene;
class ShotBeam;
class Player
{
public:
	//向いている方向
	enum Dir
	{
		kDirRight,	//右	= 2
		kDirLeft,	//左	= 1
	};

public:
	Player(Stage1Scene* S1Scene);
	~Player();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	//プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	//プレイヤーの当たり判定を取得する
	Rect GetColRect() const {return m_colRect; }

	//プレイヤーがダメージを受けた
	void OnDamage();

	//表示位置
	Vec2 m_pos;

private:
	Stage1Scene* m_pS1Scene;

	std::vector<ShotBeam> m_pBeam;

	int m_handle;	//グラフィックのハンドル

	//当たり判定用の矩形
	Rect m_colRect;

	//向いている方向
	Dir m_dir;

	//歩きアニメーション
	int m_walkAnimFrame;

	//魔法の杖の発射フレームカウント
	int m_beamFrame;
};
