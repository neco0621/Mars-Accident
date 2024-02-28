#include "EnemyBase.h"
#include "DxLib.h"
#include "../Game.h"
#include "../Scene/Stage1Scene.h"
#include "../Scene/TutorialScene.h"

#include <cassert>

//Enemyで使用する定数
namespace
{
	//当たり判定の半径
	constexpr int kRadius	    = 30;

	// アニメーション間隔
	constexpr int kAnimInterval = 3;
	// 高さ・幅
	constexpr int kAnimWidth	= 100;
	constexpr int kAnimHeight	= 100;
	// 縦横数
	constexpr int kRow			= 10;
	constexpr int kLine			= 7;
	// アニメーション数
	constexpr int kAnimNum		= 65;

	//画面の4分の3の位置
	constexpr float kTq			= Game::kScreenHeight * 0.75f;
}

EnemyBase::EnemyBase() :
	//初期化
	m_handle(-1),
	m_animHandle(-1),
	m_radius(kRadius),
	m_isExist(false),
	m_pos(),
	m_centerX(m_pos.x),
	m_centerY(m_pos.y),
	m_tq(kTq),
	m_pTuScene(nullptr),
	m_pS1Scene(nullptr),
	m_pS2Scene(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	//存在しない敵の処理はしない.
	if (!m_isExist)		return;
}

void EnemyBase::S2Update()
{
	//存在しない敵の処理はしない.
	if (!m_isExist)		return;
}

void EnemyBase::Draw()
{
	//存在しない敵の処理はしない.
	if (!m_isExist)
		return;

	//ハンドルに指定したグラフィックが入っているかどうか
	assert(m_handle != -1);

	//敵の描画処理.
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y + 10),
		1.0, 0.0,
		m_handle, true, false);	
	

#ifdef _DEBUG
	//当たり判定の表示.
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

//敵かやらの更新処理
void EnemyBase::UpdateCollision()
{
	//縦のサイズと横のサイズを取得
	int width = 0;
	int height = 0;

	//グラフのサイズを取得
	GetGraphSize(m_handle, &width, &height);

	//中心座標を指定して当たり判定のRectを生成する.
	m_colRect.SetRadius(m_pos.x, m_pos.y + 10, m_radius);
}
