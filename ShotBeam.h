#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class TutorialScene;
class Stage1Scene;
class Stage2Scene;
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

	void SetTutorial(TutorialScene* pTuScene) { m_pTuScene = pTuScene; }
	void SetS1(Stage1Scene* pS1Scene) { m_pS1Scene = pS1Scene; }
	void SetS2(Stage2Scene* pS2Scene) { m_pS2Scene = pS2Scene; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void SetHandle(int handle) { m_handle = handle; }
	void Sound();

	bool isExist() const { return m_isExist; }

	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }
	

	int m_radius;
	int m_handle;
	int m_soundHandle;
	int m_shotHandle;
	float m_centerX;
	float m_centerY;
	//当たり判定の矩形
	Rect m_colRect;
	//表示位置
	Vec2 m_pos;
	Vec2 m_z;
	//移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
	float m_pSpeed;
	float m_pMove;
	bool MoveFlag;
protected:
	//SceneMainの関数を呼び出すためにポインタを覚えておく
	TutorialScene* m_pTuScene;
	Stage1Scene* m_pS1Scene;
	Stage2Scene* m_pS2Scene;
	//ショットを撃ったプレイヤーのポインタを覚えておく
	Player* m_pPlayer;
	//
	UFO* m_pUfo;

	bool m_isExist;	//存在するかフラグ(使用中かどうか)

private:
	//残像を表示するために過去の位置を覚えておく
	std::vector<Vec2>  m_posLog;
};

