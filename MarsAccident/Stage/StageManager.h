#pragma once
#include <memory>
#include <list>
class StageBase;
class StageManager
{
private:
	std::list<std::shared_ptr<StageBase>>stage_;
public:
	~StageManager();
	void Update();
	void Draw();
	void ChangeStage(std::shared_ptr<StageBase> nextStage);
	void PushScene(std::shared_ptr<StageBase> stage);
	void PopScene();
};

