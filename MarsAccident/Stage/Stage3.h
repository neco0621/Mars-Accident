#pragma once
#include "StageBase.h"

class Stage3 : public StageBase
{
public:
	Stage3();
	virtual ~Stage3();

	virtual void Update() override;
	virtual void Draw() override;
};

