#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"



class Player;
class UFO;
class S2UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage2Scene : public Scene
{
public:
	Stage2Scene(SceneManager& mgr);
	virtual ~Stage2Scene();

	void Init();
	void End();

	void Update(Input& input);
	void Draw();
	void ChangeGameOverScene();

	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos);
	//ショットを追加する
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBeam* pBeam);

	Vec2 m_toNear;

private:
	int handle_ = 0;
	int frame_ = 0;

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (Stage2Scene::*)(Input&);
	using DrawFunc_t = void (Stage2Scene::*)();
	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

private:
	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();

private:
	//グラフィックのハンドル
	int m_gameScreenHandle; //ゲーム画面

	//グラフィックのハンドル
	int m_playerHandle;
	int m_leftEnemyHandle;
	int m_rightEnemyHandle;
	int m_life1Handle;
	int m_life2Handle;
	int m_life3Handle;
	int m_bgHandle;
	int m_shotHandle;
	int m_rocketHandle;
	int m_ufoHandle;
	int m_AnimHandle;
	int m_downEnemyCount;
	int m_lifeCount;

	bool m_damageFlag;
	bool m_gameOverFlag;
	bool IsGround;




	//プレイヤー
	Player* m_pPlayer;

	UFO* m_pUfo;
	S2UFO* m_pS2ufo;

	Bg* m_pBg;

	Rocket* m_pRocket;

	std::vector<ShotBeam*> m_pBeam;

	//敵
	std::vector<EnemyBase*> m_pEnemy;	//配列のサイズは実行時に決める(今回はコンストラクタ)
	//EnemyBase* m_pEnemy[16];   ←今までの書き方


	Rect m_pRect;

	//画面ワイプ処理
	int m_wipeFrame;

	//敵の登場間隔
	int m_enemyInterval;

	//ダメージを受けたときの画面揺れ演出
	int m_shakeFrame;
};