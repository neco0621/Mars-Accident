#pragma once
#include "EnemyBase.h"

class EnemyRight : public EnemyBase
{
public:
	EnemyRight();
	virtual ~EnemyRight();

	virtual void Update() override;
	virtual void S2Update() override;

	//�G�L�����N�^�[���X�^�[�g������
	void Start();
};