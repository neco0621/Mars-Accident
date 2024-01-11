#include "ShotBeam.h"
#include "Game.h"
#include "DxLib.h"
#include "Scene/SceneMain.h"
#include "UFO.h"
#include "Player.h"

#include <cassert>

namespace
{
	//定数の定義
	constexpr float kSpeed = 16.0f;

	//	ショットの大きさ
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	constexpr float kRadius = 8.0f;

	//覚えておく過去の位置情報の数
	constexpr int kPosLogNum = 12;

	//弾の上方向への移動速度
	constexpr float kMove = 16.0f;
}

ShotBeam::ShotBeam() :
	m_isExist(false),
	m_pPlayer(nullptr),
	m_radius(kRadius),
	m_handle(-1),
	m_centerX(m_pos.x),
	m_centerY(m_pos.y),
	m_pSpeed(kSpeed),
	m_pMove(kMove),
	MoveFlag(false),
	m_z(0,-25)
{
	m_posLog.resize(kPosLogNum);
}

ShotBeam::~ShotBeam()
{
}

void ShotBeam::Init()
{
}

void ShotBeam::Update()
{

	if (!m_isExist) return;
	//当たり判定の更新
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
	m_colRect.SetCenter(m_centerX, m_centerY, kWidth, kHeight);

	//位置のログをずらす
	for (int i = m_posLog.size() - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	//1フレーム毎の位置情報を入れる
	m_posLog[0] = m_pos;

	m_pos += m_vec;
	

	//画面外に出た処理
	//過去の表示位置も含めてすべて画面外に出たら終了
	bool isOut = false;	//チェック中の座標が画面外かどうかフラグ

	if (MoveFlag == false)
	{
		m_pos.y -= kMove;
	}

	//過去ログも画面内にあるかをチェックする
	for (int i = 0; i < m_posLog.size(); i++)
	{
		isOut = false;
		if (m_posLog[i].x < 0.0f - kWidth / 2)	isOut = true;
		if (m_posLog[i].x > Game::kScreenWidth + kWidth / 2)	isOut = true;
		if (m_posLog[i].y < 0.0f - kHeight / 2) isOut = true;
		if (m_posLog[i].y > Game::kScreenHeight + kHeight / 2)	isOut = true;

		//チェック中の座標が画面内ならここで終了
		if (!isOut) return;
	}
	//ここに来たということは画面外にいる
	m_isExist = false;
}

void ShotBeam::Draw()
{
	if (!m_isExist) return;


	//残像の表示
	//DrawCircle(m_pos.x,m_pos.y, kRadius,GetColor(255,0,0),m_handle);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < m_posLog.size() / 2; i++)
	{
		for (int lineNum = 0; lineNum < 16; lineNum++)
		{
			int startX = m_pos.x;
			int startY = m_pos.y;
			int endX = m_posLog[i].x;
			int endY = m_posLog[i].y;

			//ここからはやってない内容
			//かっこよくするために使う
			float angle = GetRand(359) / 360.0f * DX_TWO_PI_F;
			float len = GetRand(10) - 2;
			startX += cosf(angle) * len;
			startY += sinf(angle) * len;
			endX += cosf(angle) * len;
			endY += cosf(angle) * len;

			DrawLine(startX, startY, endX, endY, GetColor(26, 16,2), kWidth);
		}
	}
	//表示モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//int alpha = 255;
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//DrawLine(m_pos.x,m_pos.y, m_posLog[0].x, m_posLog[1].y,GetColor(255,255,0),kWidth);

	//for (int i = 1; i < m_posLog.size(); i++)
	//{
	//	alpha -= 20;
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//	DrawLine(m_posLog[i - 1].x, m_posLog[i - 1].y, m_posLog[i].x, m_posLog[i].y, GetColor(255, 255, 0), kWidth);
	//}
	////表示モードを元に戻す
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	//弾の当たり判定デバッグ表示
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif
}

void ShotBeam::Start(Vec2 pos)
{
	//SceneMainの設定忘れチェック
	assert(m_pMain);	//m_pMain == nullptrなら止まる


	m_isExist = true;
	//初期配置の決定
	m_pos = pos + m_z;
	//一番近い敵の方向に移動する

	//過去の位置情報を初期化時点では初期位置と同じにしてしまう
	//残像が変な位置に表示されないようにするため
	for (int i = 0; i < m_posLog.size(); i++)
	{
		m_posLog[i] = m_pos;
	}
}


