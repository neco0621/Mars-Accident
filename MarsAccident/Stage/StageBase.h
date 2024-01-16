#pragma once
#include "../Vec2.h"
#include "../Rect.h"

class Player;
class StageManager;
class Input;
class StageBase
{
protected:
	StageManager& manager_;	//�V�[���Ǘ��N���X�̎Q��

public:
	StageBase(StageManager& manager);

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//�v���C���[
	Player* m_pPlayer;
};

