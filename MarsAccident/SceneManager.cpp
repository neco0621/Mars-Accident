#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
}

void SceneManager::Update(Input& input)
{
	scenes_.back()->Update(input);
}

void SceneManager::Draw()
{
	for (auto& scene : scenes_) {
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes_.empty()) {//���X�g������ۂ����������ւ���̂ł͂Ȃ�
		scenes_.push_back(nextScene);//�����ɒǉ�����
	}
	else {
		scenes_.back() = nextScene;//���ł�1�ȏ゠�����疖���̂��̂����ւ���
	}

}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes_.push_back(scene);
}

void SceneManager::PopScene()
{
	scenes_.pop_back();
}
