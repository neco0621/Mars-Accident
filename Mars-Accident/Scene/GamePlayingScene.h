#pragma once
#include "Scene.h"
#include "../Vec2.h"
#include <vector>

class Player;
class EnemyBase;
class ShotBase;

class GamePlayingScene : public Scene
{
private:
	float fps = 0.0f;
	int m_playerHandle = 0;
	int m_enemyHandle = 0;
	int frame_ = 0;

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (GamePlayingScene::*)(Input&);
	using DrawFunc_t = void (GamePlayingScene::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//プレイヤー
	Player* m_pPlayer;

	//UFO
	UFO* m_pUfo;

	//更新関数
	void FadeInUpdate(Input& input);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	//描画関数
	void FadeDraw();
	void NormalDraw();

public:
	GamePlayingScene(SceneManager& mgr);
	~GamePlayingScene();
	void Init();
	void Update(Input& input);
	void Draw();

	//ショットを追加する
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBase* pShot);

private:
	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();

	//敵
	std::vector<EnemyBase*> m_pEnemy;	//配列のサイズは実行時に決める(今回はコンストラクタ)
	//EnemyBase* m_pEnemy[16];   <-今までの書き方

	std::vector<ShotBase*> m_pShot;

	//敵の登場間隔
	int m_enemyInterval;
};

