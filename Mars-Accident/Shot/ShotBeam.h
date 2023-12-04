#pragma once
#include "ShotBase.h"
#include "../Vec2.h"

#include <vector>

class ShotBeam : public ShotBase
{
public:
	ShotBeam();
	virtual ~ShotBeam();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	//�e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

	float m_pRadius;

private:
	//�c����\�����邽�߂ɉߋ��̈ʒu���o���Ă���
	std::vector<Vec2>  m_posLog;
};

