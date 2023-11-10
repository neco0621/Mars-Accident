#include "SceneManager.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::~SceneManager()
{

}

void SceneManager::Update(Input& input)
{
	//�����̂ݎ��s
	scenes_.back()->Update(input);
}

void SceneManager::Draw()
{
	//�擪���珇�ɕ`��
	//�Ō�ɐς񂾂��̂��Ō�ɕ`�悳���
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes_.empty())//���X�g������ۂ����������ւ�����
	{
		scenes_.push_back(nextScene);//�����ɒǉ�
	}
	else
	{
		scenes_.back() = nextScene;//���Ɉ�ȏ゠��Ζ�����
	}
}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes_.push_back(scene);
}

void SceneManager::popScene()
{
	scenes_.pop_back();
}