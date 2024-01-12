#include "StageManager.h"
#include "StageBase.h"

StageManager::~StageManager()
{
}

void StageManager::Update()
{
	stage_.back()->Update();
}

void StageManager::Draw()
{
	for (auto& stage : stage_) {
		stage->Draw();
	}
}

void StageManager::ChangeStage(std::shared_ptr<StageBase> nextStage)
{
	if (stage_.empty()) {//ƒŠƒXƒg‚ª‹ó‚Á‚Û‚¾‚Á‚½‚ç“ü‚ê‘Ö‚¦‚é‚Ì‚Å‚Í‚È‚­
		stage_.push_back(nextStage);//––”ö‚É’Ç‰Á‚·‚é
	}
	else {
		stage_.back() = nextStage;//‚·‚Å‚É1‚ÂˆÈã‚ ‚Á‚½‚ç––”ö‚Ì‚à‚Ì‚ğ“ü‚ê‘Ö‚¦‚é
	}
}

void StageManager::PushScene(std::shared_ptr<StageBase> stage)
{
	stage_.push_back(stage);
}

void StageManager::PopScene()
{
	stage_.pop_back();
}
