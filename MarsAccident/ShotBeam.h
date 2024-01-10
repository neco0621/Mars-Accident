#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class SceneMain;
class UFO;
class Player;
class Input;

namespace
{
	constexpr int ShotMax = 20;
		
}
class ShotBeam
{
public:
	ShotBeam();
	virtual ~ShotBeam();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//弾をスタートさせる
	virtual void Start(Vec2 pos);

	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }


	bool isExist() const { return m_isExist; }

	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }
	
	bool shotFlag[ShotMax];
	bool prevShotFlag;
	float m_radius;
	int m_handle;
	float m_centerX;
	float m_centerY;
	//当たり判定の矩形
	Rect m_colRect;
	//表示位置
	Vec2 m_pos;
	//移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
	float m_pSpeed;
	float m_pMove;
	bool MoveFlag;
	// ショットの生きている時間カウンタ
	int shotLifeCounter;
protected:
	//SceneMainの関数を呼び出すためにポインタを覚えておく
	SceneMain* m_pMain;
	//ショットを撃ったプレイヤーのポインタを覚えておく
	Player* m_pPlayer;
	//
	UFO* m_pUfo;

	bool m_isExist;	//存在するかフラグ(使用中かどうか)

private:
	//残像を表示するために過去の位置を覚えておく
	std::vector<Vec2>  m_posLog;
};

