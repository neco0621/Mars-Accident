#pragma once
#include "EnemyBase.h"

class EnemyRight : public EnemyBase
{
public:
	EnemyRight();
	virtual ~EnemyRight();

	virtual void Update() override;

	//敵キャラクターをスタートさせる
	void Start();
};