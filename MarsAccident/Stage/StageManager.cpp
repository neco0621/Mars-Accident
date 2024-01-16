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
	if (stage_.empty()) {//���X�g������ۂ����������ւ���̂ł͂Ȃ�
		stage_.push_back(nextStage);//�����ɒǉ�����
	}
	else {
		stage_.back() = nextStage;//���ł�1�ȏ゠�����疖���̂��̂����ւ���
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
