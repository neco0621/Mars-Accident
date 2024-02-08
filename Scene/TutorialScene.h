#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"

class Player;
class UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class TutorialScene : public Scene
{
public:
	TutorialScene(SceneManager& mgr);
	virtual ~TutorialScene();

	void Init();
	void End();

	void Update(Input& input);

	void Draw();

	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos);
	//ショットを追加する
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBeam* pBeam);

	void ShakeScreen(int a, int b);
	void CreateAnimation();

	Vec2 m_toNear;
	Vec2 pos;
private:
	int handle_ = 0;
	int frame_ = 0;

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (TutorialScene::*)(Input&);
	using DrawFunc_t = void (TutorialScene::*)();
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
	int m_shakeHandle;
	int m_hitHandle;
	int m_damageHandle;
	int CheckSE;
	int LeftHandle;
	int LeftArrowHandle;
	int RightHandle;
	int RightArrowHandle;
	int m_tutorialHandle;
	int m_clearHandle;
	int m_skipHandle;
	int TutorialExplanation;
	int TutorialExplanation2;
	int TutorialExplanation3;
	int TutorialExplanation4;

	int m_enemyEXP;
	int m_downEnemyCount;
	int m_lifeCount;
	int m_tutorialCount;
	int m_destoryEnemy;
	int m_shakeSize;
	int m_shakeFrame;
	int m_animFrame;
	int m_bgm;
	int m_gameover;
	int m_clearSE;

	bool m_damageFlag;
	bool m_gameOverFlag;
	bool IsGround;
	bool m_isShake;
	bool m_startFlag;
	bool m_clearFlag;

	bool MoveLeftFlag;
	bool MoveRightFlag;
	bool ShotFlag;
	bool DamageFlag;
	bool HitFlag;
	bool GameOverFlag;

public:
	bool AnimFlag;


	//プレイヤー
	Player* m_pPlayer;

	UFO* m_pUfo;

	Bg* m_pBg;

	Rocket* m_pRocket;

	//Animation AnimExpel;

	std::vector<ShotBeam*> m_pBeam;

	//敵
	std::vector<EnemyBase*> m_pEnemy;	//配列のサイズは実行時に決める(今回はコンストラクタ)
	//EnemyBase* m_pEnemy[16];   ←今までの書き方

	std::vector<TutorialScene*> m_pAnimation;

	Rect m_pRect;

	//画面ワイプ処理
	int m_wipeFrame;

	//敵の登場間隔
	int m_enemyInterval;
};