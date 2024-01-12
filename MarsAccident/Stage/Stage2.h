#pragma once
#include "StageBase.h"

class Stage2 : public StageBase
{
public:
	Stage2();
	virtual ~Stage2();

	virtual void Update() override;
	virtual void Draw() override;
};

